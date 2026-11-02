// Calculate_Index_To_Surface_LUT(int) (0x00522150): each spiral index's
// offset in a surface of the given stride (expanded in Draw_All).
void __fastcall Calculate_Index_To_Surface_LUT(int stride)
{
    SpiralIndexToSurfaceLUT[0] = 0;
    BlastSurfaceStride = stride;
    for (int index = 1; index < 289; index++) {
        Point2D point = Spiral_Index_To_Point(index);
        SpiralIndexToSurfaceLUT[index] = point.X + point.Y * stride;
    }
}
