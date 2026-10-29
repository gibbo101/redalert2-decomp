// void HouseClass::unknown_func_4f0ff0(ObjectClass const *object, int strength, int *grid, Rect const &area) (0x004F0FF0)
// Adds an object's influence to a grid covering an area of cells: each cell
// within six of the object's (by Fast_Sqrt) gains strength over
// (distance - 1) * 0.1 + 1, distances under one counting as one.
#include "shared/techno.hpp"
#include "shared/rect.hpp"
#include "shared/fast_math.hpp"

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

void HouseClass::unknown_func_4f0ff0(ObjectClass const *object, int strength, int *grid, Rect const &area)
{
    if (strength <= 0) {
        strength = 1;
    }
    CoordStruct coord = object->Coord;
    Cell cell = Coord_Cell(coord);
    int left = MAX(cell.X - 6, area.X);
    int right = MIN(area.X + area.Width, cell.X + 6);
    int top = MAX(cell.Y - 6, area.Y);
    int bottom = MIN(area.Y + area.Height, cell.Y + 6);
    for (int y = top; y < bottom; y++) {
        for (int x = left; x < right; x++) {
            int dx = x - cell.X;
            int dy = y - cell.Y;
            double distance = Fast_Sqrt(dx * dx + dy * dy);
            if (distance < 6.0) {
                int column = x - area.X;
                int row = y - area.Y;
                double scale = distance;
                if (scale < 1.0) {
                    scale = 1.0;
                }
                int width = area.Width;
                grid[width * row + column] += strength / ((scale - 1.0) * 0.1 + 1.0);
            }
        }
    }
}
