// @ref ?Rasterize_Line_Span_0061c0a0@@YIXHHHHHHAAPAUPoint2D@@@Z=0061c0a0
// Convert a closed polygon into left/right scanline spans,0061BE40.
#define RA2_TRACK_POINT_STRUCT
#include "shared/wave_geometry.hpp"
void __fastcall Rasterize_Line_Span_0061c0a0(int x, int y, int end_x, int end_y, int side, int skip, Point2D *&cursor);
// @ref ??2@YAPAXI@Z=00782017

// Westwood swap operation: both endpoints are passed by reference.
template<class T> inline void Swap_Polygon_Endpoints(T &first, T &second)
{
    T saved;
    saved = first;
    first = second;
    second = saved;
}

void __fastcall Rasterize_Polygon_0061be40(WavePolygonInput const &shape, WaveScanlineBuffer &raster)
{
    Point2D *out;
    Point2D const *vertices = shape.Points;
    int const &count = shape.Count;
    if (count) {
        int low_index = 0;
        int high_index = 0;
        int low_y = vertices[0].Y;
        int high_y = low_y;
        for (int i = 1; i < count; ++i) {
            if (vertices[i].Y < low_y) {
                low_index = i;
                low_y = vertices[i].Y;
            } else if (vertices[i].Y > high_y) {
                high_index = i;
                high_y = vertices[i].Y;
            }
        }
        if (low_y != high_y) {
            int after_low = low_index;
            while (vertices[after_low].Y == low_y) after_low = (after_low + 1) % count;
            int right = (count - 1 + after_low) % count;
            while (vertices[low_index].Y == low_y) low_index = (count - 1 + low_index) % count;
            int left = (low_index + 1) % count;
            int direction = -1;
            int right_x = vertices[right].X;
            int left_x = vertices[left].X;
            int flat = left_x != right_x;
            if (flat == 1) {
                if (left_x > right_x) {
                    direction = 1;
                    Swap_Polygon_Endpoints(left, right);
                }
            } else {
                int next_right = (right + 1) % count;
                int previous_left = (count - 1 + left) % count;
                int y = vertices[left].Y;
                if ((vertices[previous_left].Y - y) * (vertices[next_right].X - left_x) -
                    (vertices[next_right].Y - y) * (vertices[previous_left].X - left_x) < 0) {
                    direction = 1;
                    Swap_Polygon_Endpoints(left, right);
                }
            }
            int rows = flat - low_y - 1 + high_y;
            raster.Count = rows;
            if (rows > 0) {
                raster.FirstY = low_y - flat + 1;
                if (!raster.Spans) raster.Spans = (Point2D *)new Point2DStruct[rows + 200];
                if (!raster.Spans) {
                    raster.Count = 0;
                    return;
                }
                out = raster.Spans;
                int skip = flat == 0;
                int previous = left;
                int first_skip = skip;
                do {
                    if (direction > 0) left = (left + 1) % count;
                    else left = (left - 1 + count) % count;
                    Rasterize_Line_Span_0061c0a0(vertices[previous].X, vertices[previous].Y,
                        vertices[left].X, vertices[left].Y, 1, skip, out);
                    skip = 0;
                    previous = left;
                } while (left != high_index);
                out = raster.Spans;
                skip = first_skip;
                int current_right = right;
                int next_right_index = right;
                do {
                    if (-direction > 0) next_right_index = (next_right_index + 1) % count;
                    else {
                        next_right_index = (next_right_index - 1 + count) % count;
                    }
                    Rasterize_Line_Span_0061c0a0(vertices[current_right].X - 1, vertices[current_right].Y,
                        vertices[next_right_index].X - 1, vertices[next_right_index].Y, 0, skip, out);
                    skip = 0;
                    current_right = next_right_index;
                } while (current_right != high_index);
            }
        }
    }
}
