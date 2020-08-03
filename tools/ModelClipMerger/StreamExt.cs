using System.IO;

namespace WonderMedia.glTF.ModelClipMerger
{
    public static class StreamExt
    {
        public static void WriteByte(this Stream stream, byte value, int count)
        {
            while (--count >= 0)
            {
                stream.WriteByte(value);
            }
        }
    }
}
