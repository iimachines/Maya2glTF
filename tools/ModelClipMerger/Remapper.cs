using System.Collections.Generic;
using System.Linq;

namespace WonderMedia.glTF.ModelClipMerger
{
    public sealed class Remapper<T>
    {
        public readonly T[] InputItems;
        public readonly T[] OutputItems;

        public readonly Dictionary<T, int> OutputIndexOf;

        public Remapper(T[] inputItems, IEnumerable<T> outputItems)
        {
            InputItems = inputItems;
            OutputItems = outputItems.ToArray();

            OutputIndexOf = OutputItems
                .Select((item, index) => (item, index))
                .ToDictionary(pair => pair.Item1, pair => pair.Item2);
        }

        public int Remap(int inputIndex)
        {
            var item = InputItems[inputIndex];
            var outputIndex = OutputIndexOf[item];
            return outputIndex;
        }

        //public static void Remap<U>(IEnumerable<U> entries, Func<U, int> getIndex, Action<U, int> set )
        //{

        //}
    }

    public static class RemapperExt
    {
        public static Remapper<T> RemapFrom<T>(this IEnumerable<T> outputItems, T[] inputItems) => new Remapper<T>(inputItems, outputItems);
    }
}
