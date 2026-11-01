// The current artwork rectangle in view-relative pixels, or the unit's empty rectangle.
#include "shared/object.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
extern Rect unknown_rect_839630;
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref _unknown_static_rect=00a72ed0
Rect ObjectClass::unknown_slot72()
{
    Point2D pixel;
    unknown_tactical_83996c->Coord_To_Pixel(unknown_slot42(),pixel);
    ShapeFileStruct const *shape=static_cast<ShapeFileStruct const *>(unknown_slot26());
    if (!shape) return unknown_static_rect;
    Rect frame=shape->Get_Frame_Rect(0);
    Rect visual(pixel.X+frame.X-shape->Get_Width()/2,
                pixel.Y+frame.Y-shape->Get_Height()/2,
                frame.Width,frame.Height);
    if (unknown_rect_839630.Is_Overlapping(visual+unknown_rect_839630.Top_Left())) return visual;
    return unknown_static_rect;
}
