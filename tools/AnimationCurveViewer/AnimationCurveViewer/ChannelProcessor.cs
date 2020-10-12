using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Numerics;
using System.Runtime.InteropServices;
using glTFLoader.Schema;
using JM.LinqFaster;
using JM.LinqFaster.Utils;

namespace iim.AnimationCurveViewer
{
    public delegate void ChannelProcessorHandler(Gltf gltf, Animation animation, AnimationChannel channel, Span<float> times, Span<float> values, bool isRoot);

    public static class ChannelProcessor
    {
        public static void Process(Gltf gltf, BufferProvider bufferProvider, ChannelProcessorHandler handler)
        {
            // 1) Quantize parent channels first.
            // 2) Correct child channels with the error made by the parents.
            // 3) Recurse

            var parentTable = gltf.Nodes
                .Where(n => n.Children != null)
                .SelectMany(parent => parent
                    .Children.Select(c => (child: gltf.Nodes[c], parent)))
                .ToDictionary(pair => pair.child, pair => pair.parent);

            Node? GetParentNode(Node node)
            {
                parentTable.TryGetValue(node, out var parent);
                return parent;
            }

            int GetDistanceFromRoot(Node node)
            {
                for (int distance = 0; ; ++distance)
                {
                    var parent = GetParentNode(node);
                    if (parent == null)
                        return distance;
                    node = parent;
                }
            }

            var nodeAnimEntries = gltf.Animations
                .SelectMany(animation => animation
                    .Channels
                    .Where(channel => channel.Target.Node != null)
                    .Select(channel => (channel, animation, node: gltf.Nodes[channel.Target.Node.Value])))
                .GroupBy(entry => entry.node)
                .ToDictionary(group => group.Key, group => group.ToDictionary(g => g.channel.Target.Path));

            (Animation animation, AnimationChannel channel)? GetAnimationChannel(Node node, AnimationChannelTarget.PathEnum path)
            {
                if (!nodeAnimEntries!.TryGetValue(node, out var entries))
                    return null;

                if (!entries.TryGetValue(path, out var pair))
                    return null;

                return (pair.animation, pair.channel);
            }

            var sortedAnimatingNodes = gltf.Nodes
                .Where(nodeAnimEntries.ContainsKey)
                .OrderBy(GetDistanceFromRoot)
                .ToArray();

            foreach (var node in sortedAnimatingNodes)
            {
                var d = GetDistanceFromRoot(node);
                var i = new string(' ', d * 2);
                Console.WriteLine($"{i}{node.Name}");
            }

            var timelineEntry = nodeAnimEntries[sortedAnimatingNodes[0]][0];
            var timelineChannel = timelineEntry.channel;
            var timelineSampler = timelineEntry.animation.Samplers[timelineChannel.Sampler];
            var timelineAccessor = gltf.Accessors[timelineSampler.Input];
            var timelineSpan = gltf.GetComponentSpan<float>(timelineAccessor, bufferProvider);
            float[] timelineFloats = timelineSpan.ToArray();
            if (timelineAccessor.ComponentType != Accessor.ComponentTypeEnum.FLOAT)
                throw new NotSupportedException($"Only float times are supported");

            var sampleCount = timelineFloats.Length;

            var nodeWorldTransforms = new Dictionary<Node, Matrix4x4[]>();

            Matrix4x4[]? GetNodeWorldTransforms(Node? node)
            {
                Matrix4x4[]? transforms = null;
                if (node != null)
                    nodeWorldTransforms?.TryGetValue(node, out transforms);
                return transforms;
            }

            Span<Vector3> PeekTranslations(Node node)
            {
                var tAnimEntry = GetAnimationChannel(node, AnimationChannelTarget.PathEnum.translation);
                return tAnimEntry == null
                    ? Span<Vector3>.Empty
                    : gltf.GetFloatOutputChannel<Vector3>(bufferProvider, tAnimEntry.Value.animation, tAnimEntry.Value.channel);
            }

            Span<Quaternion> PeekRotations(Node node)
            {
                var rAnimEntry = GetAnimationChannel(node, AnimationChannelTarget.PathEnum.rotation);
                return rAnimEntry == null
                    ? Span<Quaternion>.Empty
                    : gltf.GetFloatOutputChannel<Quaternion>(bufferProvider, rAnimEntry.Value.animation, rAnimEntry.Value.channel).ToArray();
            }

            Span<Vector3> PeekScales(Node node)
            {
                var sAnimEntry = GetAnimationChannel(node, AnimationChannelTarget.PathEnum.scale);
                return sAnimEntry == null
                    ? Span<Vector3>.Empty
                    : gltf.GetFloatOutputChannel<Vector3>(bufferProvider, sAnimEntry.Value.animation, sAnimEntry.Value.channel).ToArray();
            }

            Span<Vector3> GetTranslations(Node node)
            {
                var defaultTranslation = MemoryMarshal.Cast<float, Vector3>(node.Translation.ToSpan())[0];
                var span = PeekTranslations(node);
                return span.IsEmpty
                    ? Enumerable.Repeat(defaultTranslation, sampleCount).ToArray()
                    : span;
            }

            Span<Quaternion> GetRotations(Node node)
            {
                var defaultRotation = MemoryMarshal.Cast<float, Quaternion>(node.Rotation.ToSpan())[0];
                var span = PeekRotations(node);
                return span.IsEmpty
                    ? Enumerable.Repeat(defaultRotation, sampleCount).ToArray()
                    : span;
            }

            Span<Vector3> GetScales(Node node)
            {
                var defaultScale = MemoryMarshal.Cast<float, Vector3>(node.Scale.ToSpan())[0];
                var span = PeekScales(node);
                return span.IsEmpty
                    ? Enumerable.Repeat(defaultScale, sampleCount).ToArray()
                    : span;
            }

            foreach (var node in sortedAnimatingNodes)
            {
                var translations = GetTranslations(node).ToArray();
                var rotations = GetRotations(node).ToArray();
                var scales = GetScales(node).ToArray();

                if (translations.Length != sampleCount)
                    throw new NotSupportedException($"Invalid {node.Name} translation sample count");

                if (rotations.Length != sampleCount)
                    throw new NotSupportedException($"Invalid {node.Name} rotation sample count");

                if (scales.Length != sampleCount)
                    throw new NotSupportedException($"Invalid {node.Name} scale sample count");

                var parentNode = GetParentNode(node);
                var parentTransforms = GetNodeWorldTransforms(parentNode);

                var worldTransforms = timelineFloats.Select((time, frame) =>
                {
                    var s = scales[frame];
                    var t = translations[frame];
                    var r = rotations[frame];
                    var sm = Matrix4x4.CreateScale(s);
                    var rm = Matrix4x4.CreateFromQuaternion(r);
                    var tm = Matrix4x4.CreateTranslation(t);
                    var lm = sm * rm * tm;
                    var wm = parentTransforms?[frame] ?? Matrix4x4.Identity;
                    return lm * wm;
                }).ToArray();

                nodeWorldTransforms[node] = worldTransforms;
            }

            // Process the channels.
            // Fix the errors by correcting the child nodes channels.
            foreach (var node in sortedAnimatingNodes)
            {
                var animEntries = nodeAnimEntries[node];
                var parentNode = GetParentNode(node);
                var parentTransforms = GetNodeWorldTransforms(parentNode);

                foreach (var (channel, animation, targetNode) in animEntries.Values)
                {
                    var channelName = gltf.GetChannelName(animation, channel);
                    Console.WriteLine($"Processing channels of {channelName}...");

                    var values = gltf.GetFloatOutputChannel<float>(bufferProvider, animation, channel);

                    bool isRoot = GetParentNode(targetNode) == null;
                    handler(gltf, animation, channel, timelineSpan, values, isRoot);

                    var accessor = gltf.GetChannelOutputAccessor(animation, channel);

                    // Fix min/max
                    var dimension = accessor.GetComponentDimension();

                    for (int axis = 0; axis < dimension; ++axis)
                    {
                        var min = float.PositiveInfinity;
                        var max = float.NegativeInfinity;

                        for (int i = axis; i < values.Length; i += dimension)
                        {
                            min = Math.Min(min, values[i]);
                            max = Math.Max(max, values[i]);
                        }

                        accessor.Min[axis] = min;
                        accessor.Max[axis] = max;
                    };
                }

                // All channels of the current node are quantized.
                // Adjusts the channels of the children to compensate the error.
                var translations = GetTranslations(node).ToArray();
                var rotations = GetRotations(node).ToArray();
                var scales = GetScales(node).ToArray();

                Matrix4x4[] newWorldTransforms = timelineFloats.Select((time, frame) =>
                {
                    var s = scales[frame];
                    var t = translations[frame];
                    var r = rotations[frame];
                    var sm = Matrix4x4.CreateScale(s);
                    var rm = Matrix4x4.CreateFromQuaternion(r);
                    var tm = Matrix4x4.CreateTranslation(t);
                    var lm = sm * rm * tm;
                    var wm = parentTransforms?[frame] ?? Matrix4x4.Identity;
                    return lm * wm;
                }).ToArray();

                if (node.Children != null)
                {
                    foreach (var childIndex in node.Children)
                    {
                        var childNode = gltf.Nodes[childIndex];

                        if (!nodeWorldTransforms.TryGetValue(childNode, out var childWorldTransforms))
                            continue;

                        var childLocalTransforms = childWorldTransforms
                            .Select((localToWorldTransform, i) =>
                            {
                                var parentToWorldTransform = newWorldTransforms[i];
                                Matrix4x4.Invert(parentToWorldTransform, out var worldToParentTransform);
                                var localToParentTransform = localToWorldTransform * worldToParentTransform;
                                var decomposed = Matrix4x4.Decompose(localToParentTransform, out var scale, out var rotation, out var translation);
                                Debug.Assert(decomposed);
                                return (scale, rotation, translation);
                            })
                            .ToArray();

                        var childTranslations = PeekTranslations(childNode);
                        var childRotations = PeekRotations(childNode);
                        var childScales = PeekScales(childNode);

                        if (!childTranslations.IsEmpty)
                            childLocalTransforms.Select(trs => trs.translation).ToArray().CopyTo(childTranslations);

                        if (!childRotations.IsEmpty)
                            childLocalTransforms.Select(trs => trs.rotation).ToArray().CopyTo(childRotations);

                        if (!childScales.IsEmpty)
                            childLocalTransforms.Select(trs => trs.scale).ToArray().CopyTo(childScales);
                    }
                }
            }
        }
    }
}