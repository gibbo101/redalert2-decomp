// void OverlayTypeClass::unknown_slot40(Point2D const *point, Rect const *window, int frame) (0x005DC8E0)
// Draws a frame of the type's image at a point of the tactical area (tactical
// by half a cell) with the drawer at 0x008323B8.
#include "shared/overlay_type.hpp"
#include "shared/palette.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_drawer_8323b8@@3PAVConvertClass@@A=008323b8

void OverlayTypeClass::unknown_slot40(Point2D const *point, Rect const *window, int frame)
{
    Point2D tactical(unknown_int_839630, unknown_int_839634);
    Point2D position(point->X + tactical.X, point->Y + tactical.Y);
    position.X += 30;
    position.Y += 15;
    CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323b8, (ShapeFileStruct const *)unknown_slot39(), frame, position, *window,
                  0x600, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
}
