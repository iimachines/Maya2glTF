using System;
using System.IO;
using glTFLoader;
using glTFLoader.Schema;

namespace WonderMedia.glTF.ModelClipMerger
{
    /// <summary>
    /// Portions of this code are based on the GLTF library from https://github.com/KhronosGroup/COLLADA2GLTF.
    /// </summary>
    public static class GltfExt
    {
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
            return GetComponentPadding(componentByteLength, (int) outputStream.Position);
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
    }
}
