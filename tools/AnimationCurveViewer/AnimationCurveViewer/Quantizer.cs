using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Compression;
using System.Linq;
using System.Numerics;
using System.Runtime.InteropServices;
using glTFLoader.Schema;

namespace iim.AnimationCurveViewer
{
    public static class Quantizer
    {
        public static void Process(Gltf gltf, BufferProvider bufferProvider)
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
            float[] timelineFloats = gltf.GetComponentSpan<float>(timelineAccessor, bufferProvider).ToArray();
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

            foreach (var node in sortedAnimatingNodes)
            {
                var animEntries = nodeAnimEntries[node];

                var tEntry = animEntries[AnimationChannelTarget.PathEnum.translation];
                var rEntry = animEntries[AnimationChannelTarget.PathEnum.rotation];
                var sEntry = animEntries[AnimationChannelTarget.PathEnum.scale];

                var translations = gltf.GetFloatChannel<Vector3>(bufferProvider, tEntry.animation, tEntry.channel).ToArray();
                var rotations = gltf.GetFloatChannel<Quaternion>(bufferProvider, rEntry.animation, rEntry.channel).ToArray();
                var scales = gltf.GetFloatChannel<Vector3>(bufferProvider, sEntry.animation, sEntry.channel).ToArray();

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

            // Quantize the channels of each node, starting at the roots.
            // Correct the errors by correcting the child nodes channels.
            foreach (var node in sortedAnimatingNodes)
            {
                var animEntries = nodeAnimEntries[node];
                var parentNode = GetParentNode(node);
                var parentTransforms = GetNodeWorldTransforms(parentNode);

                foreach (var (channel, animation, targetNode) in animEntries.Values)
                {
                    var channelName = gltf.GetChannelName(animation, channel);
                    Console.WriteLine($"Quantizing channels of {channelName}...");

                    bool isRoot = GetParentNode(targetNode) == null;

                    var pathKind = channel.Target.Path;

                    // Number of bits, excluding sign bit.
                    var qBits = pathKind switch
                    {
                        // -50m to 50m for roots, -3m to +3m for children
                        AnimationChannelTarget.PathEnum.translation => (int)Math.Ceiling(Math.Log2(isRoot ? 100_000 : 3_000)),
                        AnimationChannelTarget.PathEnum.rotation => 11,
                        AnimationChannelTarget.PathEnum.scale => 8,
                        AnimationChannelTarget.PathEnum.weights => 10,
                        _ => throw new ArgumentOutOfRangeException()
                    };

                    var qScale = pathKind switch
                    {
                        AnimationChannelTarget.PathEnum.translation => 10, // cm to mm
                        AnimationChannelTarget.PathEnum.rotation => (1 << qBits) - 1, // NOTE: We assume quaternions are normalized.
                        AnimationChannelTarget.PathEnum.scale => (1 << (qBits - 2)) - 1, // HACK: Maximum scale 4 
                        AnimationChannelTarget.PathEnum.weights => (1 << (qBits - 1)) - 1, // HACK: Maximum weight 2
                        _ => throw new ArgumentOutOfRangeException()
                    };

                    var qRange = 1 << qBits;
                    var qMin = -qRange;
                    var qMax = qRange - 1;

                    var values = gltf.GetFloatChannel<float>(bufferProvider, animation, channel);

                    for (int i = 0; i < values.Length; ++i)
                    {
                        var v = values[i];

                        var q = Math.Round(v * qScale);

                        if (q < qMin || q > qMax)
                            throw new IndexOutOfRangeException($"{channelName } frame:{i} value:{v} doesn't fit in quantized range");

                        values[i] = (float)(q / qScale);
                    }
                }

                // All channels of the current node are quantized.
                // Adjusts the channels of the children to compensate the error.
                var tEntry = animEntries[AnimationChannelTarget.PathEnum.translation];
                var rEntry = animEntries[AnimationChannelTarget.PathEnum.rotation];
                var sEntry = animEntries[AnimationChannelTarget.PathEnum.scale];

                var translations = gltf.GetFloatChannel<Vector3>(bufferProvider, tEntry.animation, tEntry.channel).ToArray();
                var rotations = gltf.GetFloatChannel<Quaternion>(bufferProvider, rEntry.animation, rEntry.channel).ToArray();
                var scales = gltf.GetFloatChannel<Vector3>(bufferProvider, sEntry.animation, sEntry.channel).ToArray();

                Matrix4x4[] qWorldTransforms = timelineFloats.Select((time, frame) =>
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

                // var qWorldTransforms = nodeWorldTransforms[node];

                if (node.Children != null)
                {
                    foreach (var childIndex in node.Children)
                    {
                        var childNode = gltf.Nodes[childIndex];
                        var childWorldTransforms = nodeWorldTransforms[childNode];
                        var childAnimEntries = nodeAnimEntries[childNode];

                        var childLocalTransforms = childWorldTransforms
                            .Select((localToWorldTransform, i) =>
                            {
                                var parentToWorldTransform = qWorldTransforms[i];
                                Matrix4x4.Invert(parentToWorldTransform, out var worldToParentTransform);
                                var localToParentTransform = localToWorldTransform * worldToParentTransform;
                                var decomposed = Matrix4x4.Decompose(localToParentTransform, out var scale, out var rotation, out var translation);
                                Debug.Assert(decomposed);
                                return (scale, rotation, translation);
                            })
                            .ToArray();

                        var tChildEntry = childAnimEntries[AnimationChannelTarget.PathEnum.translation];
                        var rChildEntry = childAnimEntries[AnimationChannelTarget.PathEnum.rotation];
                        var sChildEntry = childAnimEntries[AnimationChannelTarget.PathEnum.scale];

                        childLocalTransforms.Select(trs => trs.translation).ToArray().CopyTo(
                            gltf.GetFloatChannel<Vector3>(bufferProvider, tChildEntry.animation, tChildEntry.channel));

                        childLocalTransforms.Select(trs => trs.rotation).ToArray().CopyTo(
                            gltf.GetFloatChannel<Quaternion>(bufferProvider, rChildEntry.animation, rChildEntry.channel));

                        childLocalTransforms.Select(trs => trs.scale).ToArray().CopyTo(
                            gltf.GetFloatChannel<Vector3>(bufferProvider, sChildEntry.animation, sChildEntry.channel));
                    }
                }

#if false
                    switch (pathKind)
                    {
                        case AnimationChannelTarget.PathEnum.translation:
                            localTransforms.Select(trs => trs.translation).ToArray().CopyTo(
                                gltf.GetFloatChannel<Vector3>(bufferProvider, animation, channel));
                            break;
                        case AnimationChannelTarget.PathEnum.rotation:
                            localTransforms.Select(trs => trs.rotation).ToArray().CopyTo(
                                gltf.GetFloatChannel<Quaternion>(bufferProvider, animation, channel));
                            break;
                        case AnimationChannelTarget.PathEnum.scale:
                            localTransforms.Select(trs => trs.scale).ToArray().CopyTo(
                                gltf.GetFloatChannel<Vector3>(bufferProvider, animation, channel));
                            break;
                        case AnimationChannelTarget.PathEnum.weights:
                            break;
                        default:
                            throw new ArgumentOutOfRangeException();
                    }
#endif
            }

#if false
            // Convert all node animations to world transform animations.
            foreach (var node in sortedAnimatingNodes)
            {
                var animEntries = nodeAnimEntries[node];

                foreach (var (channel, animation, targetNode) in animEntries)
                {
                    Debug.Assert(node == targetNode);

                    var curveKind = channel.Target.Path;

                    var targetNodeName = targetNode.Name;

                    var pathTitle = $"{targetNodeName}/{animation.Name}/{curveKind}";
                    Console.WriteLine($"Quantizing {pathTitle}...");

                    var sampler = animation.Samplers[channel.Sampler];

                    var timesAccessor = gltf.Accessors[sampler.Input];
                    var valuesAccessor = gltf.Accessors[sampler.Output];

                    if (!timesAccessor.BufferView.HasValue || !valuesAccessor.BufferView.HasValue)
                        continue;

                    var timesSpan = gltf.GetComponentSpan(timesAccessor, bufferProvider);
                    var valuesSpan = gltf.GetComponentSpan(valuesAccessor, bufferProvider);

                    if (timesAccessor.ComponentType != Accessor.ComponentTypeEnum.FLOAT)
                        throw new NotSupportedException($"{pathTitle} has non-float time accessor");

                    if (valuesAccessor.ComponentType != Accessor.ComponentTypeEnum.FLOAT)
                        throw new NotSupportedException($"{pathTitle} has non-float values accessor");

                    var timesFloats = MemoryMarshal.Cast<byte, float>(valuesSpan);
                    var valueFloats = MemoryMarshal.Cast<byte, float>(valuesSpan);

                    var pointCount = timesAccessor.Count;

                    var dimension = valuesAccessor.GetComponentDimension();

                    bool isRoot = parentTable[targetNode] == null;

                    // Number of bits, excluding sign bit.
                    var qBits = curveKind switch
                    {
                        // -50m to 50m for roots, -3m to +3m for children
                        AnimationChannelTarget.PathEnum.translation => (int)Math.Ceiling(Math.Log2(isRoot ? 100_000 : 3_000)),
                        AnimationChannelTarget.PathEnum.rotation => 8,
                        AnimationChannelTarget.PathEnum.scale => 8,
                        AnimationChannelTarget.PathEnum.weights => 10,
                        _ => throw new ArgumentOutOfRangeException()
                    };

                    var qScale = curveKind switch
                    {
                        AnimationChannelTarget.PathEnum.translation => 10, // cm to mm
                        AnimationChannelTarget.PathEnum.rotation => (1 << qBits) - 1, // NOTE: We assume quaternions are normalized.
                        AnimationChannelTarget.PathEnum.scale => (1 << (qBits - 2)) - 1, // HACK: Maximum scale 4 
                        AnimationChannelTarget.PathEnum.weights => (1 << (qBits - 1)) - 1, // HACK: Maximum weight 2
                    };

                    var qRange = 1 << qBits;
                    var qMin = -qRange;
                    var qMax = qRange - 1;

                    for (int i = 0; i < pointCount * dimension; ++i)
                    {
                        var v = valueFloats[i];

                        var q = Math.Round(v * qScale);

                        if (q < qMin || q > qMax)
                            throw new IndexOutOfRangeException($"{pathTitle} frame:{i} value:{v} doesn't fit in quantized range");

                        valueFloats[i] = (float)(q / qScale);
                    }

                    // Compute the error we made in the world.



                }
            }
#endif
        }
    }
}