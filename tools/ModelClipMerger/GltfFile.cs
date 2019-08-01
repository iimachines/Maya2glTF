using System.IO;
using glTFLoader;
using glTFLoader.Schema;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace WonderMedia.glTF.ModelClipMerger
{
    public sealed class GltfFile
    {
        private Gltf _data;

        public Gltf Data
        {
            get { return _data ?? Load(); }
        }

        private Gltf Load()
        {
            return _data = Interface.LoadModel(Path);
        }

        public readonly string Path;

        public GltfFile(string path)
        {
            Path = path;
            Load();
        }

        public void Invalidate()
        {
            _data = null;
        }
    }
}
