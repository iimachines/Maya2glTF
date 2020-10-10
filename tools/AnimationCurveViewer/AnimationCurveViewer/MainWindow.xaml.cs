using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
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

            const float minRange = 1e-9f;
            const int curveHeight = 256;
            const int curveMargin = 10;
            const float timeScale = 60 * 5;
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
            var curveKinds = Enum.GetNames(curveKindType).Zip(
                Enum.GetValues(curveKindType).Cast<AnimationChannelTarget.PathEnum>(),
                (name, value) => (name, value));

            var tabBackground = new SolidColorBrush(Color.FromRgb(32, 32, 32));

            // Create a tab per animation curve kind (rotation, translation,...)
            foreach (var curveKind in curveKinds)
            {
                var tab = new TabItem
                {
                    Header = curveKind.name
                };

                var curveStack = new StackPanel
                {
                    Orientation = Orientation.Vertical,
                    Background = tabBackground
                };

                Console.WriteLine($"Processing {gltf.Animations.Length} animations...");

                // var gltf = glTFLoader.Interface.LoadModel(@"C:\Users\bugfa\Downloads\001_KneeBounce\Legs_ClosedKnee_Sides\Legs_ClosedKnee_Sides.gltf");
                // var buffer = new Span<byte>(File.ReadAllBytes(@"C:\Users\bugfa\Downloads\001_KneeBounce\Legs_ClosedKnee_Sides\Legs_ClosedKnee_Sides0.bin"));
                foreach (var animation in gltf.Animations)
                {
                    for (var iChannel = 0; iChannel < animation.Channels.Length; iChannel++)
                    {
                        var channel = animation.Channels[iChannel];
                        if (channel.Target.Path != curveKind.value)
                            continue;

                        var targetNodeName = channel.Target.Node.HasValue
                            ? gltf.Nodes[channel.Target.Node.Value].Name
                            : null;

                        Console.WriteLine($"Processing animation '{animation.Name}' for target node '{targetNodeName ?? "(null)"}'...");

                        var sampler = animation.Samplers[channel.Sampler];

                        var timesAccessor = gltf.Accessors[sampler.Input];
                        var valuesAccessor = gltf.Accessors[sampler.Output];

                        if (!timesAccessor.BufferView.HasValue || !valuesAccessor.BufferView.HasValue)
                            continue;

                        var timesSpan = gltf.GetComponentSpan(timesAccessor, bufferProvider);
                        var valuesSpan = gltf.GetComponentSpan(valuesAccessor, bufferProvider);

                        var dimension = valuesAccessor.GetComponentDimension();

                        // Add a curve for each dimension to the canvas
                        var pointCount = timesAccessor.Count;
                        var curveTimes = new float[pointCount];
                        var curvesPoints = new Point[dimension][];

                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            curvesPoints[axis] = new Point[pointCount];
                        }

                        var xByteCursor = 0;
                        var yByteCursor = 0;

                        var isQuaternion = channel.Target.Path == AnimationChannelTarget.PathEnum.rotation;

                        Quaternion q0 = Quaternion.Identity;

                        // Built raw points. Measure min/max. Can't use min/max from glTF because if change the curves.
                        var xValue = new float[1];
                        var yValue = new float[dimension];
                        var yMin = Enumerable.Repeat(float.PositiveInfinity, dimension).ToArray();
                        var yMax = Enumerable.Repeat(float.NegativeInfinity, dimension).ToArray();

                        for (int i = 0; i < pointCount; i++)
                        {
                            timesAccessor.GetNextFloatComponents(timesSpan, xValue, ref xByteCursor);
                            valuesAccessor.GetNextFloatComponents(valuesSpan, yValue, ref yByteCursor);

                            float t = xValue[0];
                            curveTimes[i] = t;

                            if (isQuaternion)
                            {
                                // Check if the negative quaternion is a closer.
                                var qp = new Quaternion(yValue[0], yValue[1], yValue[2], yValue[3]);
                                var qn = -qp;

                                var dp = (q0 - qp);
                                var dn = (q0 - qn);

                                if (dn.LengthSquared() < dp.LengthSquared())
                                {
                                    q0 = qn;

                                    yValue[0] = qn.X;
                                    yValue[1] = qn.Y;
                                    yValue[2] = qn.Z;
                                    yValue[3] = qn.W;
                                }

                                else
                                {
                                    q0 = qp;
                                }
                            }

                            for (int axis = 0; axis < dimension; ++axis)
                            {
                                var y = yValue[axis];
                                curvesPoints[axis][i] = new Point(t, y);

                                yMin[axis] = Math.Min(yMin[axis], y);
                                yMax[axis] = Math.Max(yMax[axis], y);
                            }
                        }

                        // Compute y starts (visual min) and scales.
                        var yStarts = new double[dimension];
                        var yScales = new double[dimension];

                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            if (isQuaternion)
                            {
                                yStarts[axis] = -1.0;
                                yScales[axis] = 0.5;
                            }
                            else
                            {
                                var center = (yMax[axis] + yMin[axis]) / 2;
                                var range = yMax[axis] - yMin[axis];

                                if (Math.Abs(range) < minRange)
                                {
                                    yStarts[axis] = center - minRange;
                                    yScales[axis] = 0.5 / minRange;
                                }
                                else
                                {
                                    yStarts[axis] = yMin[axis];
                                    yScales[axis] = 1 / (yMax[axis] - yMin[axis]);
                                }
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
                                var t = p.X;
                                var y = p.Y;
                                p.X = xOffset + t * timeScale;
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

                        StringBuilder fittedPointCounts = new StringBuilder();

                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            var cubicSegments = CubicRegression.FitCubics(visualPoints[axis], 16);
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
                                IsHitTestVisible = false
                            });
                        }

                        const int textBlockMargin = 20;

                        var animationHeader = new DockPanel
                        {
                            LastChildFill = true,
                            HorizontalAlignment = HorizontalAlignment.Stretch,
                        };

                        // Create range text blocks
                        for (int axis = 0; axis < dimension; ++axis)
                        {
                            var text = $"min:{yMin[axis]:F6} max:{yMax[axis]:F6} range:{(yMax[axis] - yMin[axis]):F6}";
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

                        animationHeader.Children.Add(new TextBlock
                        {
                            Text = $"{targetNodeName}/{animation.Name}#{iChannel} ({timesAccessor.Count} -> {fittedPointCounts})",
                            Foreground = Brushes.Yellow,
                            HorizontalAlignment = HorizontalAlignment.Left,
                            Margin = new Thickness(textBlockMargin, 0, textBlockMargin, 0),
                        });

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

                        curvesCanvas.MouseLeave += (sender, e) =>
                        {
                            frameMarker.Visibility = Visibility.Hidden;
                        };

                        curvesCanvas.MouseMove += (sender, e) =>
                        {
                            if (e.LeftButton != MouseButtonState.Pressed)
                                return;

                            frameMarker.Visibility = Visibility.Visible;

                            var mp = e.GetPosition(curvesCanvas);

                            var time = (float)((mp.X - xOffset) / timeScale);

                            var index = Array.BinarySearch(curveTimes, time, Comparer<float>.Default);

                            if (index < 0)
                            {
                                index = ~index;
                            }

                            if (index >= 0 && index < curveTimes.Length)
                            {
                                var text = new StringBuilder();

                                time = curveTimes[index];

                                text.Append($"frame: {index}  time: {time}  value: (");

                                frameMarker.X1 = frameMarker.X2 = time * timeScale + xOffset;

                                for (int axis = 0; axis < dimension; ++axis)
                                {
                                    if (axis != 0)
                                        text.Append("; ");

                                    text.Append(curvesPoints[axis][index].Y);
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
        }
    }
}
