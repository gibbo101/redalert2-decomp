// Point_To_Spiral_Index(Point2D) (0x005220C0): the inverse of
// Spiral_Index_To_Point.
int __fastcall Point_To_Spiral_Index(Point2D point)
{
    if (point == Point2D(0, 0)) {
        return 0;
    }
    int layer = Max(abs(point.X), abs(point.Y));
    int index = 1;
    for (int i = 1; i < layer; i++) {
        index += 8 * i;
    }
    if (point.X == layer) {
        index += 1 * layer + point.Y;
    } else if (point.Y == layer) {
        index += 3 * layer - point.X;
    } else if (point.X == -layer) {
        index += 5 * layer - point.Y;
    } else {
        index += 7 * layer + point.X;
    }
    return index;
}
