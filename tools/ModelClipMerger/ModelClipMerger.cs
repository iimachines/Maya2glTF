using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using glTFLoader;
using glTFLoader.Schema;
using JetBrains.Annotations;
using Buffer = glTFLoader.Schema.Buffer;

namespace WonderMedia.glTF.ModelClipMerger
{
    public sealed class ModelClipMerger : IDisposable
    {
        public static readonly float[] DefaultTranslation = { 0, 0, 0 };
        public static readonly float[] DefaultScale = { 1, 1, 1 };
        public static readonly float[] DefaultRotation = { 0, 0, 0, 1 };

        private const string OutputBufferFilename = "buffer.bin";
        private const string OutputModelFilename = "model.glTF";

        private readonly Dictionary<Buffer, byte[]> _bufferFileData = new Dictionary<Buffer, byte[]>();
        private HashSet<string> _allModelNodeNames;

        public string InputFolder { get; }
        public string OutputFolder { get; }

        public IndentedTextWriter Log { get; }

        public ModelClipMerger(string inputFolder, string outputFolder, TextWriter log = null)
        {
            InputFolder = inputFolder;
            OutputFolder = outputFolder;
            Log = new IndentedTextWriter(log ?? Console.Out, "  ");
        }

        public void CleanOutputFolder()
        {
            // Delete all files in output folder
            if (Directory.Exists(OutputFolder))
            {
                Log.WriteLine($"Cleaning {OutputFolder}...");
                Directory.Delete(OutputFolder, true);
            }
        }

        public void Process()
        {
            Log.WriteLine("Loading glTF files...");

            GltfFile[] modelFiles;
            GltfFile[] animFiles;

            using (Log.Indented())
            {
                string[] allFilePaths = Directory.GetFiles(InputFolder, "*.glTF", SearchOption.AllDirectories);
                var allFiles = allFilePaths.Select(LoadFile).ToArray();
                modelFiles = allFiles.Where(m => IsNullOrEmpty(m.Data.Animations)).ToArray();
                animFiles = allFiles.Except(modelFiles).OrderBy(file => file.Path).ToArray();
            }

            // Gather all names of all nodes in all models.
            // If any animation refers to a node not in this set,
            // we print a warning because the animation will most likely be broken then,
            // and re-export is needed.
            _allModelNodeNames = modelFiles
                .SelectMany(pair => pair.Data.Nodes.Select(n => n.Name))
                .ToHashSet();

            Log.WriteLine($"Merging glTF models {string.Join(", ", modelFiles.Select(f => Path.GetFileNameWithoutExtension(f.Path)))}...");

            using (Log.Indented())
            {
                foreach (var modelFile in modelFiles)
                {
                    Log.WriteLine($"Merging {modelFile.Path}...");
                    using (Log.Indented())
                    {
                        ProcessModel(modelFile, animFiles);
                    }
                }
            }
        }

        private void ProcessModel(GltfFile modelFile, GltfFile[] animFiles)
        {
            var modelPath = modelFile.Path;
            var modelData = modelFile.Data;

            var modelName = Path.GetFileNameWithoutExtension(modelPath);

            var outputModelFolder = Path.Combine(OutputFolder, modelName);
            Directory.CreateDirectory(outputModelFolder);

            Log.WriteLine($"Copying images...");

            using (Log.Indented())
            {
                CopyImages(modelData, modelPath, outputModelFolder);
            }

            Log.WriteLine($"Fetching model buffers...");

            using (Log.Indented())
            {
                FetchBuffers(modelData, modelPath);
            }

            var modelNodeIndexByName = modelData.Nodes.Select((n, i) => (n, i))
                .ToDictionary(pair => pair.Item1.Name, pair => pair.Item2);

            foreach (GltfFile animFile in animFiles)
            {
                Log.WriteLine($"Processing animations in {animFile.Path}...");
                using (Log.Indented())
                {
                    ProcessAnimations(modelFile, animFile, modelNodeIndexByName, outputModelFolder);
                }

                // The anim-file-data was modified, reload next time.
                animFile.Invalidate();
            }

            var outputBufferPath = Path.Combine(outputModelFolder, OutputBufferFilename);
            using (var newBufferStream = File.Create(outputBufferPath))
            {
                Log.WriteLine($"Packing all accessors in a single buffer...");
                PackAccessors(modelFile, newBufferStream, OutputBufferFilename);

                Log.WriteLine($"Writing model glTF file...");
                var outputModelPath = Path.Combine(outputModelFolder, OutputModelFilename);
                modelData.SaveModel(outputModelPath);
            }
        }

        /// <summary>
        /// Creates a single buffer and a minimum number of buffer-views to pack all the accessors.
        /// </summary>
        private void PackAccessors(GltfFile modelFile, Stream newBufferStream, string outputBufferUri)
        {
            var fileData = modelFile.Data;

            var buffers = fileData.Buffers;
            var bufferViews = fileData.BufferViews;

            // TODO: Check sparse accessors
            // Group accessor by optional target, component-stride and component byte-length
            // For each group, we need to create a single buffer-view.
            var accessorGroups = fileData
                .Accessors
                .Where(a => a.BufferView.HasValue)
                .GroupBy(a => (target: bufferViews[a.BufferView.Value].Target, stride: a.GetByteStride(bufferViews)/*, componentByteLength: a.GetComponentByteLength()*/))
                .ToDictionary(g => g.Key, g => g.ToArray());

            // NOTE: The following select sequence has a side-effect
            var newBufferViews = accessorGroups
                .Select((pair, newBufferViewIndex) =>
                {
                    //var ((target, stride, componentByteLength), accessors) = pair;
                    var ((target, stride), accessors) = pair;

                    var newBufferViewOffset = (int)newBufferStream.Position;

                    //Debug.Assert(newBufferStream.GetComponentPadding(componentByteLength) == 0);

                    foreach (var accessor in accessors)
                    {
                        var componentByteLength = accessor.GetComponentByteLength();

                        var accessorPadding = newBufferStream.GetComponentPadding(componentByteLength);
                        newBufferStream.WriteByte(0, accessorPadding);

                        var newAccessorByteOffset = (int)(newBufferStream.Position - newBufferViewOffset);

                        Debug.Assert(accessor.BufferView.HasValue);
                        var bufferView = bufferViews[accessor.BufferView.Value];
                        var buffer = buffers[bufferView.Buffer];
                        var data = _bufferFileData[buffer];

                        var bufferOffset = bufferView.ByteOffset + accessor.ByteOffset;

                        var rowLength = accessor.GetComponentDimension() * componentByteLength;

                        for (int i = 0; i < accessor.Count; ++i)
                        {
                            Debug.Assert(newBufferStream.GetComponentPadding(componentByteLength) == 0);
                            newBufferStream.Write(data, bufferOffset + i * stride, rowLength);
                            Debug.Assert(newBufferStream.GetComponentPadding(componentByteLength) == 0);
                        }

                        // Patch the accessor.
                        accessor.ByteOffset = newAccessorByteOffset;
                        accessor.BufferView = newBufferViewIndex;
                    }

                    var newBufferView = new BufferView
                    {
                        Target = target,
                        ByteOffset = newBufferViewOffset,
                        ByteStride = target == BufferView.TargetEnum.ARRAY_BUFFER ? stride : (int?)null,
                        ByteLength = (int)(newBufferStream.Position - newBufferViewOffset)
                    };

                    return newBufferView;
                })
                .ToArray();

            var newBuffer = new Buffer
            {
                ByteLength = (int)newBufferStream.Length,
                Uri = outputBufferUri
            };

            fileData.BufferViews = newBufferViews;
            fileData.Buffers = new[] { newBuffer };
        }

        private void ProcessAnimations(GltfFile modelFile, GltfFile animFile, Dictionary<string, int> modelNodeIndexByName, string outputModelFolder)
        {
            foreach (Animation animation in animFile.Data.Animations)
            {
                using (Log.Indented())
                {
                    Log.WriteLine($"Processing animation clip {animation.Name} in {animFile.Path}...");

                    using (Log.Indented())
                    {
                        ProcessAnimation(modelFile, animFile, animation, modelNodeIndexByName, outputModelFolder);
                    }
                }
            }
        }

        private void ProcessAnimation(GltfFile modelFile, GltfFile animFile, Animation animation, Dictionary<string, int> modelNodeIndexByName, string outputModelFolder)
        {
            var animData = animFile.Data;
            var modelData = modelFile.Data;

            // Load all animation buffers into memory
            // TODO: This could be done lazily!
            FetchBuffers(animData, animFile.Path);

            foreach (var channel in animation.Channels)
            {
                var nodeIndex = channel.Target?.Node;
                if (nodeIndex.HasValue)
                {
                    var nodeName = animData.Nodes[nodeIndex.Value].Name;
                    if (!_allModelNodeNames.Contains(nodeName))
                    {
                        Log.WriteLine($"WARNING: Clip node '{nodeName}' not found in any model. Similar node names are:");
                        using (Log.Indented())
                        {
                            Fastenshtein.Levenshtein lev = new Fastenshtein.Levenshtein(nodeName);
                            Log.WriteLine(string.Join(", ", _allModelNodeNames.OrderBy(lev.DistanceFrom).Take(3)));
                        }
                    }
                }
            }

            int tc = 0;
            int rc = 0;
            int sc = 0;
            int wc = 0;

            // Keep only those animation channels that animate the current model,
            // and are different from the initial scene
            AnimationChannel[] clipChannels = animation
                .Channels
                .Where(channel =>
                {
                    var nodeIndex = channel?.Target?.Node;
                    if (!nodeIndex.HasValue)
                        return false;
                    var node = animData.Nodes[nodeIndex.Value];
                    if (!modelNodeIndexByName.ContainsKey(node.Name))
                        return false;

                    var sampler = animation.Samplers[channel.Sampler];
                    var outputAccessor = animData.Accessors[sampler.Output];

                    // We assume the exporter already reduced constant curves to a single key.
                    if (outputAccessor.Count != 1)
                        return true;

                    // We don't handle sparse data yet, keep it
                    if (!outputAccessor.BufferView.HasValue)
                        return true;

                    var mesh = node.Mesh.HasValue ? animData.Meshes[node.Mesh.Value] : null;

                    var outputValues = GetComponentAtIndex(animData, outputAccessor, 0);

                    switch (channel.Target.Path)
                    {
                        case AnimationChannelTarget.PathEnum.translation:
                            return AreDifferent(ref tc, outputValues, node.Translation ?? DefaultTranslation, 1e-3f);
                        case AnimationChannelTarget.PathEnum.rotation:
                            return AreDifferent(ref rc, outputValues, node.Rotation ?? DefaultRotation, 1e-4f);
                        case AnimationChannelTarget.PathEnum.scale:
                            return AreDifferent(ref sc, outputValues, node.Scale ?? DefaultScale, 1e-4f);
                        case AnimationChannelTarget.PathEnum.weights:
                            return AreDifferent(ref wc, outputValues, node.Weights ?? mesh?.Weights, 1e-3f);
                        default:
                            return true;
                    }
                })
                .ToArray();

            if (clipChannels.Length == 0)
            {
                Log.WriteLine($"NOTE: Animation '{animation.Name}' is not used by model '{modelFile.Path}'");
                return;
            }

            if (tc+rc+sc+wc > 0)
            {
                Log.WriteLine($"Skipped {tc} translation, {rc} rotation, {sc} scaling and {wc} weight redundant animation channels");
            }

            // Keep only those samplers used by any channel
            AnimationSampler[] clipSamplers = clipChannels
                .Select(channel => animation.Samplers[channel.Sampler])
                .Distinct()
                .ToArray();

            AnimationChannelTarget[] clipTargets = clipChannels
                .Select(channel => channel.Target)
                .ToArray();

            Accessor[] clipSamplerInputs = clipSamplers.Select(sampler => animData.Accessors[sampler.Input]).ToArray();
            Accessor[] clipSamplerOutputs = clipSamplers.Select(sampler => animData.Accessors[sampler.Output]).ToArray();

            Accessor[] clipAccessors = clipSamplerInputs.Concat(clipSamplerOutputs).Distinct().ToArray();

            Remapper<Accessor> newAccessors = modelData.Accessors.Concat(clipAccessors).RemapFrom(animData.Accessors);

            Remapper<AnimationSampler> newSamplers = clipSamplers.RemapFrom(animation.Samplers);
            Remapper<AnimationChannel> newChannels = clipChannels.RemapFrom(animation.Channels);


            // Remap sampler indices
            foreach (var sampler in clipSamplers)
            {
                sampler.Input = newAccessors.Remap(sampler.Input);
                sampler.Output = newAccessors.Remap(sampler.Output);
            }

            // Remap channel indices
            foreach (var channel in clipChannels)
            {
                channel.Sampler = newSamplers.Remap(channel.Sampler);
            }

            // Remap animation channel targets
            foreach (var target in clipTargets)
            {
                // ReSharper disable once PossibleInvalidOperationException
                var clipNode = animData.Nodes[(int)target.Node];
                var nodeIndex = modelNodeIndexByName[clipNode.Name];
                target.Node = nodeIndex;
            }

            animation.Channels = newChannels.OutputItems;
            animation.Samplers = newSamplers.OutputItems;

            var clipBufferViews = clipAccessors
                .Select(a => a.BufferView)
                .Where(bv => bv.HasValue)
                .Select(bv => bv.Value)
                .Distinct()
                .Select(i => animData.BufferViews[i])
                .ToArray();

            var newBufferViews = modelData.BufferViews.Concat(clipBufferViews)
                .RemapFrom(animData.BufferViews);

            // Remap clip accessor indices
            foreach (var accessor in clipAccessors)
            {
                if (accessor.BufferView.HasValue)
                {
                    accessor.BufferView = newBufferViews.Remap(accessor.BufferView.Value);
                }
            }

            var clipBuffers = clipBufferViews
                .Select(bv => bv.Buffer)
                .Distinct()
                .Select(i => animData.Buffers[i])
                .ToArray();

            var newBuffers = modelData.Buffers.Concat(clipBuffers).RemapFrom(animData.Buffers);

            // Remap buffer view indices
            foreach (var bufferView in clipBufferViews)
            {
                bufferView.Buffer = newBuffers.Remap(bufferView.Buffer);
            }

            // TODO: Animation indices don't need to be remapped?
            modelData.Animations = (modelData.Animations ?? Array.Empty<Animation>()).Append(animation).ToArray();
            modelData.Accessors = newAccessors.OutputItems;
            modelData.BufferViews = newBufferViews.OutputItems;
            modelData.Buffers = newBuffers.OutputItems;
        }

        static bool IsNullOrEmpty<T>(ICollection<T> items)
        {
            return items == null || items.Count == 0;
        }

        private GltfFile LoadFile(string filePath)
        {
            Log.WriteLine($"Loading {filePath}...");
            return new GltfFile(filePath);
        }

        private void CopyImages(Gltf gltfFile, string gltfPath, string outputFolder)
        {
            for (var i = 0; i < gltfFile.Images.Length; i++)
            {
                var image = gltfFile.Images[i];

                var outputPath = Path.Combine(outputFolder, image.Uri);

                Log.WriteLine($"Copying image {outputPath}...");

                // TODO: Supported embedded image buffers
                using (var inputStream = gltfFile.OpenImageFile(i, gltfPath))
                using (var outputStream = File.OpenWrite(outputPath))
                {
                    inputStream.CopyTo(outputStream);
                }
            }
        }

        private void FetchBuffers(Gltf gltfFile, string gltfPath, IEnumerable<int> bufferIndices)
        {
            foreach (var bufferIndex in bufferIndices)
            {
                var buffer = gltfFile.Buffers[bufferIndex];

                if (_bufferFileData.ContainsKey(buffer))
                    continue;

                var bufferName = string.IsNullOrEmpty(buffer.Uri)
                    ? $"buffer#{bufferIndex}"
                    : buffer.Uri.Substring(0, Math.Min(100, buffer.Uri.Length));

                Log.WriteLine($"Fetching buffer {bufferName}...");

                var data = gltfFile.LoadBinaryBuffer(bufferIndex, gltfPath);
                _bufferFileData.Add(buffer, data);
            }
        }

        private void FetchBuffers(Gltf gltfFile, string gltfPath)
        {
            FetchBuffers(gltfFile, gltfPath, Enumerable.Range(0, gltfFile.Buffers.Length));
        }

        public void Dispose()
        {
            Log?.Dispose();
        }

        private float[] GetComponentAtIndex(Gltf gltf, Accessor accessor, int index)
        {
            var bufferView = gltf.BufferViews[accessor.BufferView ?? throw new Exception($"Accessor '{accessor.Name ?? "?"}' has no buffer-view!")];
            int byteOffset = accessor.ByteOffset + bufferView.ByteOffset;
            int dimension = accessor.GetComponentDimension();
            byteOffset += accessor.GetByteStride(gltf.BufferViews) * index;
            var buffer = gltf.Buffers[bufferView.Buffer];
            var data = new Span<byte>(_bufferFileData[buffer]);

            var component = new float[dimension];

            for (int i = 0; i < dimension; i++)
            {
                switch (accessor.ComponentType)
                {
                    case Accessor.ComponentTypeEnum.BYTE:
                        component[i] = ReadNext<sbyte>(data, ref byteOffset);
                        break;
                    case Accessor.ComponentTypeEnum.UNSIGNED_BYTE:
                        component[i] = ReadNext<byte>(data, ref byteOffset);
                        break;
                    case Accessor.ComponentTypeEnum.SHORT:
                        component[i] = ReadNext<short>(data, ref byteOffset);
                        break;
                    case Accessor.ComponentTypeEnum.UNSIGNED_SHORT:
                        component[i] = ReadNext<ushort>(data, ref byteOffset);
                        break;
                    case Accessor.ComponentTypeEnum.FLOAT:
                        component[i] = ReadNext<float>(data, ref byteOffset);
                        break;
                    case Accessor.ComponentTypeEnum.UNSIGNED_INT:
                        component[i] = ReadNext<uint>(data, ref byteOffset);
                        break;
                }
            }

            return component;
        }

        private static unsafe T ReadNext<T>(Span<byte> buffer, ref int byteOffset) where T : unmanaged
        {
            var value = MemoryMarshal.Read<T>(buffer.Slice(byteOffset, sizeof(T)));
            byteOffset += sizeof(T);
            return value;
        }

        /// <summary>
        /// Checks if two floating point arrays different
        /// If the second array is null, all floats are assumed to be 0.0f
        /// </summary>
        public static bool AreDifferent(ref int equalityCounter, float[] a, [CanBeNull] float[] b, float epsilon)
        {
            var length = a.Length;

            if (b == null)
            {
                for (int i = 0; i < length; i++)
                {
                    if (Math.Abs(a[i]) > epsilon)
                        return true;
                }
            }
            else
            {
                if (length != b.Length)
                    return true;

                for (int i = 0; i < length; i++)
                {
                    if (Math.Abs(a[i] - b[i]) > epsilon)
                        return true;
                }

            }

            ++equalityCounter;
            return false;
        }

    }
}
