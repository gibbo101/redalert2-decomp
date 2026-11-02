// Spiral_Index_To_Point(int) (0x00522040): the grid offset a spiral index
// stands for (index 0 is the centre; ring n holds 8n points).
Point2D __fastcall Spiral_Index_To_Point(int index)
{
    index--;
    int layer = 1;
    if (index >= 8) {
        for (int i = 8; index >= i; i += 8) {
            index -= i;
            layer++;
        }
    }
    if (index < 2 * layer + 1) {
        return Point2D(layer, index - layer);
    } else if (index < 4 * layer + 1) {
        return Point2D(3 * layer - index, layer);
    } else if (index < 6 * layer + 1) {
        return Point2D(-layer, 5 * layer - index);
    } else {
        return Point2D(index - 7 * layer, -layer);
    }
}
