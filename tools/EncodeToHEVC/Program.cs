using System;
using System.ComponentModel.DataAnnotations;
using System.Diagnostics;
using System.IO;

namespace EncodeToHEVC
{
    class Program
    {
        static string Q(string s) => $"\"{s}\"";

        static void Main(string[] args)
        {
            var folders = Directory.GetDirectories(@"C:\dev\glTF\Maya2glTF\maya\playblast\maya", "video", SearchOption.AllDirectories);
            var ffmpegPath = @"C:\dev\AnimationNow\Assets\Deploy\Any\ffmpeg.exe";

            foreach (var folder in folders)
            {
                var parentFolder = Path.GetDirectoryName(folder);
                var clipName = Path.GetFileNameWithoutExtension(parentFolder);
                var outputFolder = Path.GetFullPath(Path.Combine(parentFolder, "..", "..", "H265"));
                Directory.CreateDirectory(outputFolder);
                var colorPath = Path.Combine(outputFolder, $"{clipName}_color.mp4");
                var alphaPath = Path.Combine(outputFolder, $"{clipName}_alpha.mp4");

                var arguments = $"-y -i {Q(Path.Combine(folder, "frame.%04d.png"))} -threads 0 -r 25 -ac 2 " +
                          $"-filter_complex \"[0:v]format = yuv444p[COLOR];[0:v] alphaextract[ALPHA]\" " +
                          $"-map [COLOR] -c:v hevc_nvenc -preset hq -g 300 -rc constqp -global_quality:v 18 -pix_fmt yuv420p {Q(colorPath)} " +
                          $"-map [ALPHA] -c:v hevc_nvenc -preset lossless -g 30 -rc constqp -global_quality:v 1 -pix_fmt yuv420p {Q(alphaPath)} ";

                Console.WriteLine($"Encoding {clipName}...");
                var encoder = Process.Start(ffmpegPath, arguments);
                encoder.WaitForExit();
            }

            Console.WriteLine("All done, press ENTER to exit");
            Console.ReadLine();
        }
    }
}
