using System;
using System.Buffers;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using glTFLoader;
using glTFLoader.Schema;
using Microsoft.Win32;
using Path = System.IO.Path;
using PathShape = System.Windows.Shapes.Path;

namespace iim.AnimationCurveViewer
{
    public partial class MainWindow
    {
        public MainWindow()
        {
            // TODO: This was a quick and dirty one-day job, cleanup!

            InitializeComponent();

            var args = Environment.GetCommandLineArgs();

            string gltfFilePath = null;

            if (args.Length < 2)
            {
                var dlg = new OpenFileDialog
                {
                    Title = "Select glTF file",
                    Filter = "gltF files|*.gltf|glb files|*.glb|All files|*.*",
                    CheckFileExists = true
                };

                if (dlg.ShowDialog() != true)
                    return;

                gltfFilePath = Path.GetFullPath(dlg.FileName);
            }
            else
            {
                gltfFilePath = args[1];
            }

            Console.WriteLine($"Loading {gltfFilePath}...");

            var gltf = glTFLoader.Interface.LoadModel(gltfFilePath);

            var bufferProvider = gltf.CreateDefaultBufferProvider(gltfFilePath);

            // ChannelProcessor.Process(gltf, bufferProvider, ChannelQuantizer.Process);
            var fitter = new ChannelFitter();
            ChannelProcessor.Process(gltf, bufferProvider, fitter.Process, true);
            Title = $"{fitter.InputByteCount} -> {fitter.OutputByteCount}";

            foreach (var path in Directory.GetFiles(Path.GetDirectoryName(gltfFilePath)))
            {
                File.Copy(path, Path.Combine(@"c:\temp\gltf", Path.GetFileName(path)), true);
            }

            for (var index = 0; index < gltf.Buffers.Length; index++)
            {
                var buffer = gltf.Buffers[index];
                File.WriteAllBytes(Path.Combine(@"c:\temp\gltf", buffer.Uri), bufferProvider(buffer, index));
            }

            //Application.Current.Shutdown();

            // var gltf = glTFLoader.Interface.LoadModel(@"C:\Users\bugfa\Downloads\001_KneeBounce\Arms_Baseball_Standard\Arms_Baseball_Standard.gltf");
            // var buffer = File.ReadAllBytes(@"C:\Users\bugfa\Downloads\001_KneeBounce\Arms_Baseball_Standard\Arms_Baseball_Standard0.bin");

            // TODO: Use viewmodels!
            var fontFamily = new FontFamily("Consolas");

            var curveColors = new[]
            {
                Brushes.OrangeRed,
                Brushes.LimeGreen,
                Brushes.DodgerBlue,
                Brushes.MediumTurquoise
            };

            const float minRange = 1e-6f;
            const int curveHeight = 256;
            const int curveMargin = 10;
            const int pixelsPerFrame = 10;
            const int curveThickness = 2;
            const bool showCurveSamples = false;

            var tabs = new TabControl();

            var keyInfo = new TextBlock
            {
                Height = 20,
                HorizontalAlignment = HorizontalAlignment.Stretch,
                Foreground = Brushes.Yellow
            };

            keyInfo.SetValue(DockPanel.DockProperty, Dock.Top);

            var curveKindType = typeof(AnimationChannelTarget.PathEnum);
            var curveKinds = Enum.GetValues(curveKindType).Cast<AnimationChannelTarget.PathEnum>();

            var tabBackground = new SolidColorBrush(Color.FromRgb(32, 32, 32));


#if true
            var inputByteCount = 0;
            var outputByteCount = 0;

            var countedAccessors = new HashSet<int>();

            var quantStream = new MemoryStream();
            var zipStream = new GZipStream(quantStream, CompressionLevel.Optimal, true);

            // Create a tab per animation curve kind (rotation, translation,...)
            foreach (var curveKind in curveKinds)
            {
                var tab = new TabItem
                {
                    Header = curveKind
                };

                var curveStack = new StackPanel
                {
                    Orientation = Orientation.Vertical,
                    Background = tabBackground
                };

                Console.WriteLine($"Processing {gltf.Animations.Length} animations...");

                var parentTable = gltf.Nodes
                    .Where(n => n.Children != null)
                    .SelectMany(parent => parent
                        .Children.Select(c => (child: gltf.Nodes[c], parent)))
                    .ToDictionary(pair => pair.child, pair => pair.parent);

                // var gltf = glTFLoader.Interface.LoadModel(@"C:\Users\bugfa\Downloads\001_KneeBounce\Legs_ClosedKnee_Sides\Legs_ClosedKnee_Sides.gltf");
                // var buffer = new Span<byte>(File.ReadAllBytes(@"C:\Users\bugfa\Downloads\001_KneeBounce\Legs_ClosedKnee_Sides\Legs_ClosedKnee_Sides0.bin"));
                foreach (var animation in gltf.Animations)
                {
                    for (var iChannel = 0; iChannel < animation.Channels.Length; iChannel++)
                    {
                        var channel = animation.Channels[iChannel];
                        if (channel.Target.Path != curveKind)
                            continue;

                        var targetNode = channel.Target.Node.HasValue
                            ? gltf.Nodes[channel.Target.Node.Value]
                            : null;

                        var targetNodeName = targetNode?.Name;

                        var channelTitle = $"{targetNodeName ?? "(null)"}/{animation.Name}/{curveKind}";

                        Console.WriteLine($"Processing {channelTitle}...");

                        var sampler = animation.Samplers[channel.Sampler];

                        var timesAccessor = gltf.Accessors[sampler.Input];
                        var valuesAccessor = gltf.Accessors[sampler.Output];

                        if (!timesAccessor.BufferView.HasValue || !valuesAccessor.BufferView.HasValue)
                            continue;

                        var timesSpan = gltf.GetComponentSpan(timesAccessor, bufferProvider);
                        var valuesSpan = gltf.GetComponentSpan(valuesAccessor, bufferProvider);

                        var dimension = valuesAccessor.GetComponentDimension();

                        if (countedAccessors.Add(sampler.Input))
                            inputByteCount += timesAccessor.Count * timesAccessor.GetComponentByteLength();

                        if (countedAccessors.Add(sampler.Output))
                            inputByteCount += valuesAccessor.Count * valuesAccessor.GetComponentByteLength() * dimension;

                        // Add a curve for each dimension to the canvas
                        var pointCount = timesAccessor.Count;
                        var curveTimes = new float[pointCount];
                        var curvesPoints = new Point[dimension][];

                        if (timesAccessor.ComponentType != Accessor.ComponentTypeEnum.FLOAT)
                            throw new NotSupportedException($"{channelTitle} has non-float time accessor");

                        if (valuesAccessor.ComponentType != Accessor.ComponentTypeEnum.FLOAT)
                            throw new NotSupportedException($"{channelTitle} has non-float values accessor");

                        var timesFloats = MemoryMarshal.Cast<byte, float>(valuesSpan);
                        var valueFloats = MemoryMarshal.Cast<byte, float>(valuesSpan);

                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            var curvePoints = curvesPoints[axis] = new Point[pointCount];

                            for (int i = 0; i < pointCount; ++i)
                            {
                                var j = i * dimension + axis;
                                var t = timesFloats[i];
                                var v = valueFloats[j];
                                curvePoints[i] = new Point(t, v);
                            }
                        }

                        // Compute y starts (visual min) and scales.
                        var yStarts = new double[dimension];
                        var yScales = new double[dimension];

                        var yMin = valuesAccessor.Min;
                        var yMax = valuesAccessor.Max;

                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            var center = (yMax[axis] + yMin[axis]) / 2;
                            var range = yMax[axis] - yMin[axis];

                            var isConst = Math.Abs(range) < minRange;

                            if (isConst)
                            {
                                yStarts[axis] = 0;
                                yScales[axis] = 0;
                            }
                            else
                                switch (curveKind)
                                {
                                    case AnimationChannelTarget.PathEnum.translation:
                                        yStarts[axis] = yMin[axis];
                                        yScales[axis] = 1 / range;
                                        break;
                                    case AnimationChannelTarget.PathEnum.rotation:
                                        yStarts[axis] = -1.0;
                                        yScales[axis] = 0.5;
                                        break;
                                    case AnimationChannelTarget.PathEnum.scale:
                                        yStarts[axis] = yMin[axis];
                                        yScales[axis] = 0.25;
                                        break;
                                    case AnimationChannelTarget.PathEnum.weights:
                                        yStarts[axis] = yMin[axis];
                                        yScales[axis] = 0.5;
                                        break;
                                    default:
                                        throw new ArgumentOutOfRangeException();
                                }
                        }

                        // Normalize points
                        var normalizedPoints = new Point[dimension][];

                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            normalizedPoints[axis] = new Point[pointCount];
                        }

                        for (int i = 0; i < pointCount; i++)
                        {
                            for (int axis = 0; axis < dimension; ++axis)
                            {
                                Point p = curvesPoints[axis][i];
                                var t = p.X;
                                var y = p.Y;
                                p.X = t;
                                p.Y = (y - yStarts[axis]) * yScales[axis];
                                normalizedPoints[axis][i] = p;
                            }
                        }

                        // Compute visual points
                        var xOffset = curveThickness;
                        var yOffset = curveThickness;
                        var yHeight = curveHeight - 2 * curveThickness;
                        var visualPoints = new Point[dimension][];

                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            visualPoints[axis] = new Point[pointCount];
                        }

                        for (int i = 0; i < pointCount; i++)
                        {
                            for (int axis = 0; axis < dimension; ++axis)
                            {
                                Point p = normalizedPoints[axis][i];
                                var y = p.Y;
                                p.X = xOffset + i * pixelsPerFrame;
                                p.Y = yOffset + y * yHeight;
                                visualPoints[axis][i] = p;
                            }
                        }

                        var curvesCanvas = new Canvas
                        {
                            Width = Math.Ceiling(visualPoints[0].Last().X + 2 * curveThickness),
                            Height = (curveHeight + 2 * curveMargin),
                            Margin = new Thickness(0, curveMargin, 0, curveMargin),
                            Background = Brushes.Transparent,
                            HorizontalAlignment = HorizontalAlignment.Left,
                            IsHitTestVisible = true
                        };

                        const int textBlockMargin = 20;

                        var animationHeader = new DockPanel
                        {
                            LastChildFill = true,
                            HorizontalAlignment = HorizontalAlignment.Stretch,
                        };

                        // Create range text blocks
                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            var text = $"{(yScales[axis] == 0 ? '_' : '~')} min:{yMin[axis]:F6} max:{yMax[axis]:F6} range:{(yMax[axis] - yMin[axis]):F6}";

                            var textBlock = new TextBlock
                            {
                                FontFamily = fontFamily,
                                Foreground = curveColors[axis],
                                Text = text,
                                Margin = new Thickness(textBlockMargin, 0, textBlockMargin, 0),
                                HorizontalAlignment = HorizontalAlignment.Left
                            };
                            textBlock.SetValue(DockPanel.DockProperty, Dock.Right);
                            animationHeader.Children.Insert(0, textBlock);
                        }

                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            var line = Curve.ToLineGeometry(visualPoints[axis]);

                            curvesCanvas.Children.Add(new PathShape
                            {
                                Data = line,
                                Height = curveHeight,
                                Stroke = curveColors[axis],
                                StrokeThickness = curveThickness,
                                ClipToBounds = false,
                                IsHitTestVisible = false
                            });

                            if (showCurveSamples)
                            {
                                var dots = Curve.ToPointsGeometry(visualPoints[axis], curveThickness);

                                curvesCanvas.Children.Add(new PathShape
                                {
                                    Data = dots,
                                    Height = curveHeight,
                                    Fill = Brushes.LightGoldenrodYellow,
                                    ClipToBounds = false,
                                    IsHitTestVisible = false
                                });
                            }
                        }

                        StringBuilder fittedKnotCounts = new StringBuilder();

                        // bool isRoot = parentTable[targetNode] == null;
                        //
                        // // We want 0.1mm precision for translation.
                        // // We give roots a range of ~ 100x100 meter,
                        // // and children a range of ~ 3x3 meter.
                        // // TODO: Compute bits for quaternion.
                        // var quantBits = curveKind switch
                        // {
                        //     AnimationChannelTarget.PathEnum.translation => isRoot ? 20 : 15,
                        //     AnimationChannelTarget.PathEnum.rotation => 10,
                        //     AnimationChannelTarget.PathEnum.scale => 10,
                        //     AnimationChannelTarget.PathEnum.weights => 10,
                        //     _ => throw new ArgumentOutOfRangeException()
                        // };
                        //
                        // var quantErrorBits = curveKind switch
                        // {
                        //     AnimationChannelTarget.PathEnum.translation => isRoot ? 8 : 4,
                        //     _ => 4
                        // };
                        //
                        // var qScale = curveKind switch
                        // {
                        //     AnimationChannelTarget.PathEnum.translation => 10, // cm to mm
                        //     _ => 1 << quantBits
                        // };
                        //
                        // var qMin = -(1 << (quantErrorBits - 1));
                        // var qMax = (1 << (quantErrorBits - 1)) - 1;

#if false

                        var segmentsCount = 0;

                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            var curvePoints = curvesPoints[axis];

                            var segments = CubicRegression.FitCubics(curvePoints, qScale, qMin, qMax);

                            segmentsCount += segments.Count;

                            var fittedPoints = new Point[pointCount];

                            int index = 0;

                            sbyte[] quantErrors = ArrayPool<sbyte>.Shared.Rent(pointCount);

                            var valueFloats = MemoryMarshal.Cast<byte, float>(valuesSpan);

                            foreach (var (segment, stop) in segments)
                            {
                                while (index < stop)
                                {
                                    var cp = curvePoints[index];
                                    var py = segment.AbsEvaluate(cp.X);
                                    var qError = Math.Round((py - cp.Y) * qScale);
                                    Debug.Assert(qError >= qMin && qError <= qMax);

                                    valueFloats[index * dimension + axis] = (float) (py + qError / qScale);

                                    quantErrors[index] = (sbyte)qError;

                                    var vx = xOffset + index * pixelsPerFrame;
                                    var vy = yOffset + (py - yStarts[axis]) * yScales[axis] * yHeight;
                                    fittedPoints[index++] = new Point(vx, vy);
                                }
                            }

                            var quantData = MemoryMarshal.AsBytes(new Span<sbyte>(quantErrors));
                            zipStream.Write(quantData);

                            /*
                            var polys = Solvers.FitBestPolynomial(curvePoints, precision);


                            int index = 0;

                            foreach (var (stop, poly) in polys)
                            {
                                while (index < stop)
                                {
                                    var x = curvePoints[index].X;
                                    var y = alglib.barycentriccalc(poly, x);

                                    var vx = xOffset + index * pixelsPerFrame;
                                    var vy = yOffset + (y - yStarts[axis]) * yScales[axis] * yHeight;
                                    fittedPoints[index++] = new Point(vx, vy);
                                }
                            }
                            */

                            var dots = Curve.ToPointsGeometry(fittedPoints, curveThickness * 2);

                            curvesCanvas.Children.Add(new PathShape
                            {
                                Data = dots,
                                Height = curveHeight,
                                Fill = curveColors[axis],
                                ClipToBounds = false,
                                IsHitTestVisible = false
                            });
                        }

                        // one byte per segment-index (todo: fit per 256 samples)
                        fittedKnotCounts.Append(segmentsCount * 4);
                        outputByteCount += segmentsCount + segmentsCount * 16;
#endif

#if false
                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            var inputPoints = visualPoints[axis];

                            alglib.spline1dfit(
                                inputPoints.Select(p => p.X).ToArray(),
                                inputPoints.Select(p => p.Y).ToArray(),
                                8, 1e-4,
                                out var spline, out var report);

                            alglib.spline1dunpack(spline, out var count, out var curvePoints);

                            var controlPointCount = curvePoints.GetLength(0);

                            fittedPointCounts.Append(controlPointCount);
                            fittedPointCounts.Append(' ');

                            var fittedPoints = new Point[pointCount];
                            var firstX = inputPoints[0].X;
                            var lastX = inputPoints[pointCount - 1].X;

                            for (int i = 0; i < pointCount; ++i)
                            {
                                var x = inputPoints[i].X;
                                var y = alglib.spline1dcalc(spline, x);
                                fittedPoints[i] = new Point(x, y);
                            }

                            var line = Curve.ToLineGeometry(fittedPoints);

                            curvesCanvas.Children.Add(new PathShape
                            {
                                Data = line,
                                Height = curveHeight,
                                Stroke = curveColors[axis],
                                StrokeThickness = curveThickness * 2,
                                Opacity = 0.5,
                                ClipToBounds = false,
                                IsHitTestVisible = false
                            });

                            var points = new Point[controlPointCount + 1];

                            for (int i = 0; i < controlPointCount; i++)
                            {
                                var x = curvePoints[i, 0];
                                var y = alglib.spline1dcalc(spline, x);
                                points[i] = new Point(x, y);

                                if (i == controlPointCount - 1)
                                {
                                    x = curvePoints[i, 1];
                                    y = alglib.spline1dcalc(spline, x);
                                    points[i + 1] = new Point(x, y);
                                }
                            }

                            var dots = Curve.ToPointsGeometry(points, curveThickness * 3);

                            curvesCanvas.Children.Add(new PathShape
                            {
                                Data = dots,
                                Height = curveHeight,
                                Fill = curveColors[axis],
                                ClipToBounds = false,
                                IsHitTestVisible = false
                            });
                    }
#endif

#if false
                        //var maxErrors = yScales.Select(_ => 0.01D).ToArray();
                        //var (knotIndices, largestError) = Solvers.FitAkimaSplines(channelTitle, normalizedPoints, pointCount, dimension, maxErrors);

                        // Translation: quantize to 32-bit integer, in mm.
                        // allow 4-bits difference from curve => ±7.5mm

                        var maxError = curveKind switch
                        {
                            AnimationChannelTarget.PathEnum.translation => 0.1, // mm
                            AnimationChannelTarget.PathEnum.rotation => 0.01, // 1%
                            AnimationChannelTarget.PathEnum.scale => 0.001,
                            AnimationChannelTarget.PathEnum.weights => 0.001,
                            _ => throw new ArgumentOutOfRangeException()
                        };

                        var maxErrors = Enumerable.Range(0, dimension).Select(_ => maxError).ToArray();

                        var (knotIndices, largestError) = Solvers.FitAkimaSplines(curvesPoints, pointCount, dimension, maxErrors);

                        fittedKnotCounts.Append($"#{knotIndices.Count} {largestError}");

                        // TODO: This only works with a GLTF extension that supports Akima splines...
                        outputFloatCount += knotIndices.Count * (1 + dimension);

                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            var inputPoints = visualPoints[axis];
                            var knotPoints = knotIndices.Select(i => inputPoints[i]).ToArray();

                            alglib.spline1dbuildakima(
                                knotPoints.Select(p => p.X).ToArray(),
                                knotPoints.Select(p => p.Y).ToArray(),
                                out var spline);

                            var fittedPoints = new Point[pointCount];

                            for (int i = 0; i < pointCount; ++i)
                            {
                                var x = inputPoints[i].X;
                                var y = alglib.spline1dcalc(spline, x);
                                fittedPoints[i] = new Point(x, y);
                            }

                            var line = Curve.ToLineGeometry(fittedPoints);

                            curvesCanvas.Children.Add(new PathShape
                            {
                                Data = line,
                                Height = curveHeight,
                                Stroke = curveColors[axis],
                                StrokeThickness = curveThickness * 2,
                                Opacity = 0.5,
                                ClipToBounds = false,
                                IsHitTestVisible = false
                            });

                            var dots = Curve.ToPointsGeometry(knotPoints, curveThickness * 3);

                            curvesCanvas.Children.Add(new PathShape
                            {
                                Data = dots,
                                Height = curveHeight,
                                Fill = curveColors[axis],
                                ClipToBounds = false,
                                IsHitTestVisible = false,
                                Opacity = 0.5
                            });
                        }
#endif

#if false
                        var quantRange = 1 << quantBits;

                        // Quantize values accessors

                        if (curveKind == AnimationChannelTarget.PathEnum.rotation)
                        {
                            for (var i = 0; i < valueFloats.Length; i++)
                            {
                                var f = Math.Round(valueFloats[i] * qScale) / qScale;
                                valueFloats[i] = (float)f;
                            }
                        }
#endif

#if false
                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            // Quantize the curve points
                            var baseline = yMin[axis];
                            var encodedPoints = curvesPoints[axis]
                                .Select(p => new Point(p.X, (p.Y - baseline) * quantScale))
                                .ToArray();

                            if (encodedPoints.Any(p => p.Y < 0 || p.Y >= quantRange))
                                throw new ArgumentOutOfRangeException(channelTitle);

                            var (knotIndices, quantErrors) = Solvers.FitAkimaSpline(encodedPoints, quantError);

                            fittedKnotCounts.Append($"#{knotIndices.Count}");

                            var quantData = MemoryMarshal.AsBytes(new Span<sbyte>(quantErrors));
                            zipStream.Write(quantData);

                            // 8-bits per time (todo: fit per 256 samples)
                            // outputByteCount += knotIndices.Count * 5 + quantErrors.Length * quantError / 8;
                            outputByteCount += knotIndices.Count * 5;

                            var knotPoints = knotIndices.Select(i => encodedPoints[i]).ToArray();

                            alglib.spline1dbuildakima(
                                knotPoints.Select(p => p.X).ToArray(),
                                knotPoints.Select(p => p.Y).ToArray(),
                                out var spline);

                            var fittedPoints = new Point[pointCount];

                            for (int i = 0; i < pointCount; ++i)
                            {
                                var x = encodedPoints[i].X;
                                var y = Math.Round(alglib.spline1dcalc(spline, x));
                                y += quantErrors[i];
                                y /= quantScale;
                                y += baseline;
                                fittedPoints[i] = new Point(x, y);
                            }

                            for (var i = 0; i < pointCount; ++i)
                            {
                                valueFloats[i * dimension + axis] = (float)fittedPoints[i].Y;
                            }

                            var visualKnotPoints = knotIndices.Select(i => visualPoints[axis][i]).ToArray();

                            var yStart = yStarts[axis];
                            var yScale = yScales[axis];

                            var decodedPoints = fittedPoints
                                .Select((p, i) =>
                                {
                                    var x = xOffset + i * pixelsPerFrame;
                                    var y = yOffset + (p.Y - yStart) * yScale * yHeight;
                                    return new Point(x, y);
                                })
                                .ToArray();

                            var dots = Curve.ToPointsGeometry(decodedPoints, curveThickness * 1.5);

                            curvesCanvas.Children.Add(new PathShape
                            {
                                Data = dots,
                                Height = curveHeight,
                                Fill = curveColors[axis],
                                ClipToBounds = false,
                                IsHitTestVisible = false,
                                Opacity = 0.5
                            });

                            var line = Curve.ToLineGeometry(visualKnotPoints);

                            curvesCanvas.Children.Add(new PathShape
                            {
                                Data = line,
                                Height = curveHeight,
                                Stroke = curveColors[axis],
                                StrokeThickness = curveThickness * 2,
                                Opacity = 0.5,
                                ClipToBounds = false,
                                IsHitTestVisible = false
                            });

                            // var dots = Curve.ToPointsGeometry(knotPoints, curveThickness * 3);
                            //
                            // curvesCanvas.Children.Add(new PathShape
                            // {
                            //     Data = dots,
                            //     Height = curveHeight,
                            //     Fill = curveColors[axis],
                            //     ClipToBounds = false,
                            //     IsHitTestVisible = false,
                            //     Opacity = 0.5
                            // });
                        }
#endif

#if false
                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            var cubicSegments = CubicRegression.FitCubics(visualPoints[axis], 8);
                            var cubicGeometry = CubicSegment.GetGeometry(cubicSegments);

                            fittedPointCounts.Append(cubicSegments.Count * 3 + 1);
                            fittedPointCounts.Append(' ');

                            curvesCanvas.Children.Add(new PathShape
                            {
                                Data = cubicGeometry,
                                Height = curveHeight,
                                Stroke = curveColors[axis],
                                StrokeThickness = curveThickness * 2,
                                Opacity = 0.5,
                                ClipToBounds = false,
                                IsHitTestVisible = false
                            });

                            var points = CubicSegment.GetPoints(cubicSegments).ToArray();

                            var dots = Curve.ToPointsGeometry(points, curveThickness * 3);

                            curvesCanvas.Children.Add(new PathShape
                            {
                                Data = dots,
                                Height = curveHeight,
                                Fill = curveColors[axis],
                                ClipToBounds = false,
                                IsHitTestVisible = false,
                                Opacity = 0.5,
                            });
                        }
#endif
                        animationHeader.Children.Add(new TextBlock
                        {
                            Text = $"{targetNodeName}/{animation.Name}#{iChannel} ({timesAccessor.Count} -> {fittedKnotCounts})",
                            Foreground = Brushes.Yellow,
                            HorizontalAlignment = HorizontalAlignment.Left,
                            Margin = new Thickness(textBlockMargin, 0, textBlockMargin, 0),
                        });

                        var curvesScroller = new ScrollViewer
                        {
                            VerticalScrollBarVisibility = ScrollBarVisibility.Disabled,
                            HorizontalScrollBarVisibility = ScrollBarVisibility.Visible,
                            Content = curvesCanvas
                        };

                        var animationGroup = new StackPanel
                        {
                            Orientation = Orientation.Vertical,
                            Children =
                            {
                                animationHeader,
                                curvesScroller
                            }
                        };

                        var frameMarker = new Line
                        {
                            Stroke = Brushes.Yellow,
                            StrokeThickness = 1,
                            Visibility = Visibility.Hidden,
                            Y1 = 0,
                            Y2 = curvesCanvas.Height
                        };

                        curvesCanvas.Children.Add(frameMarker);

                        curvesCanvas.MouseLeave += (sender, e) => { frameMarker.Visibility = Visibility.Hidden; };

                        curvesCanvas.MouseMove += (sender, e) =>
                        {
                            if (e.LeftButton != MouseButtonState.Pressed)
                                return;

                            frameMarker.Visibility = Visibility.Visible;

                            var mp = e.GetPosition(curvesCanvas);

                            var frame = (int)Math.Round((mp.X - xOffset) / pixelsPerFrame);

                            if (frame >= 0 && frame < curveTimes.Length)
                            {
                                var text = new StringBuilder();

                                var time = curveTimes[frame];

                                text.Append($"frame: {frame}  time: {time}  value: (");

                                frameMarker.X1 = frameMarker.X2 = frame * pixelsPerFrame + xOffset;

                                for (int axis = 0; axis < dimension; ++axis)
                                {
                                    if (axis != 0)
                                        text.Append("; ");

                                    text.Append(curvesPoints[axis][frame].Y);
                                }

                                text.Append(')');

                                keyInfo.Text = text.ToString();
                            }
                        };

                        curveStack.Children.Add(animationGroup);

                        // STOP AT FIRST
                        // break;
                    }

                    // STOP AT FIRST
                    // break;
                }

                tab.Content = new ScrollViewer
                {
                    Content = curveStack
                };

                tabs.Items.Add(tab);

                // STOP AT FIRST
                // break;
            }

            Content = new DockPanel
            {
                LastChildFill = true,
                Children =
                {
                    keyInfo,
                    tabs,
                }
            };

            zipStream.Close();

            outputByteCount += (int)quantStream.Length;

            //Title = $"{inputByteCount} -> {outputByteCount} 1/{inputByteCount * 1D / outputByteCount:F2} {outputByteCount * 100D / inputByteCount:F2}%)";
#endif

        }
    }
}
