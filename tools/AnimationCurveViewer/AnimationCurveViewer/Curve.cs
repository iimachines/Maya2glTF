using System.Linq;
using System.Windows;
using System.Windows.Media;

namespace iim.AnimationCurveViewer
{
	public static class Curve
	{
		public static StreamGeometry ToPointsGeometry(Point[] points, int radius)
		{
			var geometry = new StreamGeometry();

			var ps = new Point[3];

			using (var sgc = geometry.Open())
			{
				foreach (var point in points)
				{
					var x = point.X;
					var y = point.Y;

					var p0 = new Point(x - radius, y - radius);
					var p1 = new Point(x + radius, y - radius);
					var p2 = new Point(x + radius, y + radius);
					var p3 = new Point(x - radius, y + radius);

					ps[0] = p1;
					ps[1] = p2;
					ps[2] = p3;
					sgc.BeginFigure(p0, true, true);
					sgc.PolyLineTo(ps, false, false);
				}
			}

			geometry.Freeze();
			return geometry;
		}

		public static StreamGeometry ToLineGeometry(Point[] points)
		{
			var geometry = new StreamGeometry();
			using (var sgc = geometry.Open())
			{
				sgc.BeginFigure(points[0], false, false);
				sgc.PolyLineTo(points.Skip(1).ToArray(), true, true);
			}
			geometry.Freeze();
			return geometry;
		}
	}
}