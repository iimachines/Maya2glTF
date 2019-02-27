using System;
using System.CodeDom.Compiler;

namespace WonderMedia.glTF.ModelClipMerger
{
    public struct IndentScope : IDisposable
    {
        private readonly IndentedTextWriter _writer;
        private readonly int _indent;

        public IndentScope(IndentedTextWriter writer)
        {
            _indent = writer.Indent;
            _writer = writer;
            _writer.Indent += 1;
        }

        public void Dispose()
        {
            _writer.Indent = _indent;
        }
    }

    public static class IndentedTextWriterExt
    {
        public static IndentScope Indented(this IndentedTextWriter writer) => new IndentScope(writer);
    }
}
