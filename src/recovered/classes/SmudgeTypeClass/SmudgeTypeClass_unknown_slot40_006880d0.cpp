// void SmudgeTypeClass::unknown_slot40(Point2D const *point, Rect const *window, int piece, int height, Cell const *cell) (0x006880D0)
// Draws the image at a point: a piece of a multi-cell smudge (row-major in
// Width) is moved to its own cell of the isometric block; the cell supplies
// the drawer and the light level, the height the depth.
#include "shared/smudge_type.hpp"
#include "shared/map_view.hpp"
#include "shared/palette.hpp"
#include "shared/anim.hpp"
#include "shared/unknown_globals.hpp"

void SmudgeTypeClass::unknown_slot40(Point2D const *point, Rect const *window, int piece, int height, Cell const *cell)
{
    void *shape = unknown_slot39();
    if (shape != 0) {
        Point2D position = *point;
        if (piece != 0) {
            int x = piece % Width;
            int y = piece / Width;
            position.Y -= (y + x) * 15;
            position.X += (y - x) * 60 / 2;
        }
        CellClass &here = Map[*cell];
        int level = here.unknown_10c;
        CC_Draw_Shape(unknown_surface_83995c, (ConvertClass *)here.unknown_34, (ShapeFileStruct const *)shape, 0, position, *window,
                      0xE00, 0, -1 - Unknown_006A2970(height), 0, level, 0, 0, Point2D(0, 0));
    }
}
