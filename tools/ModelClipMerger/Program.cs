using System;

namespace WonderMedia.glTF.ModelClipMerger
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var merger = new ModelClipMerger(@"D:\Nova\export", @"D:\Nova\glTF"))
            {
                merger.CleanOutputFolder();
                merger.Process();

                Console.WriteLine("Done");
                Console.ReadLine();
            }
        }
    }
}
