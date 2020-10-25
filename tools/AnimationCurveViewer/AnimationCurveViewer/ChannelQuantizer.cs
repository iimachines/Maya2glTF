using System;
using System.Windows.Documents;
using glTFLoader.Schema;

namespace iim.AnimationCurveViewer
{
    public class ChannelQuantizer
    {
        public void Process(Gltf gltf,
            Animation animation, AnimationChannel channel,
            Span<float> times, Span<float> values, bool isRoot)
        {
            var pathKind = channel.Target.Path;

            // Assuming an export in cm, we want 1/10th mm precision
            const int cmScale = 10;
            const int mScale = cmScale * 100;

            // Number of bits, excluding sign bit.
            var qBits = pathKind switch
            {
                // -50m to 50m for roots, -3m to +3m for children
                AnimationChannelTarget.PathEnum.translation => (int)Math.Ceiling(Math.Log2((isRoot ? 100 : 6) * mScale)),
                AnimationChannelTarget.PathEnum.rotation => 11,
                AnimationChannelTarget.PathEnum.scale => 10,
                AnimationChannelTarget.PathEnum.weights => 10,
                _ => throw new ArgumentOutOfRangeException()
            };

            var qScale = pathKind switch
            {
                AnimationChannelTarget.PathEnum.translation => cmScale,
                AnimationChannelTarget.PathEnum.rotation => (1 << qBits) - 1, // NOTE: We assume quaternions are normalized.
                AnimationChannelTarget.PathEnum.scale => (1 << (qBits - 2)) - 1, // HACK: Maximum scale 4 
                AnimationChannelTarget.PathEnum.weights => (1 << (qBits - 1)) - 1, // HACK: Maximum weight 2
                _ => throw new ArgumentOutOfRangeException()
            };

            var qRange = 1 << qBits;
            var qMin = -qRange;
            var qMax = qRange - 1;

            for (int i = 0; i < values.Length; ++i)
            {
                var v = values[i];

                var q = Math.Round(v * qScale);

                if (q < qMin || q > qMax)
                    throw new IndexOutOfRangeException($"{gltf.GetChannelName(animation, channel)} frame:{i} value:{v} doesn't fit in quantized range");

                values[i] = (float)(q / qScale);
            }

        }

    }
}