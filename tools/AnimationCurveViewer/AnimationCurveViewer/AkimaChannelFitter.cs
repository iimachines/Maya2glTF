using System;
using System.Linq;
using System.Net.NetworkInformation;
using System.Windows;
using glTFLoader.Schema;

namespace iim.AnimationCurveViewer
{
    public class AkimaChannelFitter
    {
        public int InputByteCount;
        public int OutputByteCount;

        public void Process(Gltf gltf,
            Animation animation, AnimationChannel channel,
            Span<float> times, Span<float> values, bool isRoot)
        {
            var pathKind = channel.Target.Path;

            var accessor = gltf.GetChannelOutputAccessor(animation, channel);
            var dimension = accessor.GetComponentDimension();

            var pointCount = times.Length;

            var points = new Point[pointCount];

            // var maxError = pathKind switch
            // {
            //     AnimationChannelTarget.PathEnum.translation => 0.05,
            //     AnimationChannelTarget.PathEnum.rotation => 0.005,
            //     AnimationChannelTarget.PathEnum.scale => 0.005,
            //     AnimationChannelTarget.PathEnum.weights => 0.01,
            //     _ => throw new ArgumentOutOfRangeException()
            // };

            var maxError = pathKind switch
            {
                AnimationChannelTarget.PathEnum.translation => 0.1,
                AnimationChannelTarget.PathEnum.rotation => 0.1,
                AnimationChannelTarget.PathEnum.scale => 0.01,
                AnimationChannelTarget.PathEnum.weights => 0.01,
                _ => throw new ArgumentOutOfRangeException()
            };

            InputByteCount += 4 * values.Length;

            for (int axis = 0; axis < dimension; ++axis)
            {
                for (int i = 0; i < pointCount; ++i)
                {
                    var j = i * dimension + axis;
                    var t = times[i];
                    var v = values[j];
                    points[i] = new Point(t, v);
                }

                var knots = Solvers.FitAkimaSpline(points, maxError);

                OutputByteCount += knots.Count * 5;

                alglib.spline1dbuildakima(
                    knots.Select(i => points[i].X).ToArray(),
                    knots.Select(i => points[i].Y).ToArray(),
                    out var spline);

                for (int i = 0; i < pointCount; ++i)
                {
                    var j = i * dimension + axis;
                    var t = times[i];
                    var y = alglib.spline1dcalc(spline, t);
                    values[j] = (float)y;
                }
            }
        }
    }
}