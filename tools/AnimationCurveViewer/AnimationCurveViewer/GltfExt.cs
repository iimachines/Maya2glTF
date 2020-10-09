using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using glTFLoader;
using glTFLoader.Schema;
using Buffer = glTFLoader.Schema.Buffer;

namespace iim.AnimationCurveViewer
{
    public delegate byte[] BufferProvider(Buffer buffer, int index);

    /// <summary>
    /// Portions of this code are based on the GLTF library from https://github.com/KhronosGroup/COLLADA2GLTF.
    /// </summary>
    public static class GltfExt
    {
        public static BufferProvider CreateDefaultBufferProvider(this Gltf gltf, string gltfFilePath)
        {
            var bufferDataCache = new Dictionary<int, byte[]>();

            return (buffer, index) =>
            {
                if (!bufferDataCache.TryGetValue(index, out var data))
                {
                    data = bufferDataCache[index] = gltf.LoadBinaryBuffer(index, gltfFilePath);
                }

                return data;
            };
        }

        public static int GetComponentByteLength(this Accessor.ComponentTypeEnum componentType)
        {
            switch (componentType)
            {
                case Accessor.ComponentTypeEnum.BYTE:
                case Accessor.ComponentTypeEnum.UNSIGNED_BYTE:
                    return 1;
                case Accessor.ComponentTypeEnum.SHORT:
                case Accessor.ComponentTypeEnum.UNSIGNED_SHORT:
                    return 2;
                case Accessor.ComponentTypeEnum.FLOAT:
                case Accessor.ComponentTypeEnum.UNSIGNED_INT:
                    return 4;
            }

            return 0;
        }

        public static int GetComponentByteLength(this Accessor accessor)
        {
            return GetComponentByteLength(accessor.ComponentType);
        }

        public static int GetComponentDimension(this Accessor.TypeEnum type)
        {
            switch (type)
            {
                case Accessor.TypeEnum.SCALAR:
                    return 1;
                case Accessor.TypeEnum.VEC2:
                    return 2;
                case Accessor.TypeEnum.VEC3:
                    return 3;
                case Accessor.TypeEnum.VEC4:
                case Accessor.TypeEnum.MAT2:
                    return 4;
                case Accessor.TypeEnum.MAT3:
                    return 9;
                case Accessor.TypeEnum.MAT4:
                    return 16;
                default:
                    return 0;
            }
        }

        public static int GetComponentDimension(this Accessor accessor)
        {
            return GetComponentDimension(accessor.Type);
        }

        /// <summary>
        /// Computes how much to advance a byte-offset to store components of the given byte-length.
        /// </summary>
        public static int GetComponentPadding(int componentByteLength, int byteOffset)
        {
            return (componentByteLength - byteOffset % componentByteLength) % componentByteLength;
        }

        public static int GetComponentPadding(this Stream outputStream, int componentByteLength)
        {
            return GetComponentPadding(componentByteLength, (int)outputStream.Position);
        }

        /// <summary>
        /// Computes how much to advance a byte-offset to store components of the given type.
        /// </summary>
        public static int GetComponentPadding(this Accessor.ComponentTypeEnum componentType, int byteOffset)
        {
            var componentByteLength = GetComponentByteLength(componentType);
            return GetComponentPadding(componentByteLength, byteOffset);
        }

        public static int GetComponentPadding(this Accessor accessor, int byteOffset)
        {
            return GetComponentPadding(accessor.ComponentType, byteOffset);
        }

        public static int GetByteStride(this Accessor accessor, BufferView[] bufferViews)
        {
            if (accessor.BufferView.HasValue && bufferViews[accessor.BufferView.Value].ByteStride.HasValue)
            {
                return bufferViews[accessor.BufferView.Value].ByteStride.Value;
            }

            return GetComponentDimension(accessor) * GetComponentByteLength(accessor);
        }

        public static Span<byte> GetComponentSpan(this Gltf gltf, Accessor accessor, BufferProvider bufferProvider, int index = 0)
        {
            var bufferView = gltf.BufferViews[accessor.BufferView ?? throw new Exception($"Accessor '{accessor.Name ?? "?"}' has no buffer-view!")];
            int byteOffset = accessor.ByteOffset + bufferView.ByteOffset;
            byteOffset += accessor.GetByteStride(gltf.BufferViews) * index;
            var buffer = gltf.Buffers[bufferView.Buffer];
            var data = new Span<byte>(bufferProvider(buffer, bufferView.Buffer)).Slice(byteOffset);
            return data;
        }

        public static float[] GetNextFloatComponents(this Accessor accessor, Span<byte> data, float[] components, ref int byteOffset)
        {
            for (int i = 0; i < components.Length; i++)
            {
                switch (accessor.ComponentType)
                {
                    case Accessor.ComponentTypeEnum.BYTE:
                        components[i] = ReadNext<sbyte>(data, ref byteOffset);
                        break;
                    case Accessor.ComponentTypeEnum.UNSIGNED_BYTE:
                        components[i] = ReadNext<byte>(data, ref byteOffset);
                        break;
                    case Accessor.ComponentTypeEnum.SHORT:
                        components[i] = ReadNext<short>(data, ref byteOffset);
                        break;
                    case Accessor.ComponentTypeEnum.UNSIGNED_SHORT:
                        components[i] = ReadNext<ushort>(data, ref byteOffset);
                        break;
                    case Accessor.ComponentTypeEnum.FLOAT:
                        components[i] = ReadNext<float>(data, ref byteOffset);
                        break;
                    case Accessor.ComponentTypeEnum.UNSIGNED_INT:
                        components[i] = ReadNext<uint>(data, ref byteOffset);
                        break;
                }
            }

            return components;
        }

        private static unsafe T ReadNext<T>(Span<byte> buffer, ref int byteOffset) where T : unmanaged
        {
            var value = MemoryMarshal.Read<T>(buffer.Slice(byteOffset, sizeof(T)));
            byteOffset += sizeof(T);
            return value;
        }
    }
}