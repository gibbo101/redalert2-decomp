// Rect TerrainClass::unknown_slot73() (0x006E4910, slot 73)
// The area the object draws over, in tactical-area pixels (hypothesis):
// the union of its image's first frame and its shadow frame (the second
// half), centred on the image and placed at its screen point (+0xC0)
// relative to the view origin; the empty rectangle without an image.
#include "shared/terrain.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
// @ref ?unknown_slot26@ObjectClass@@UAEPAXXZ=005d27b0
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c

Rect TerrainClass::unknown_slot73()
{
    Point2D origin(unknown_tactical_83996c->TacPixelX, unknown_tactical_83996c->TacPixelY);
    Point2D offset(unknown_b8.Width - origin.X, unknown_b8.Height - origin.Y);
    ShapeFileStruct const *shape = (ShapeFileStruct const *)ObjectClass::unknown_slot26();
    if (shape == 0) {
        return SHAPE_FILE_EMPTY_RECT;
    }
    Rect image = shape->Get_Frame_Rect(0);
    Rect shadow = shape->Get_Frame_Rect(shape->FrameCount / 2);
    int width = shape->Width;
    int height = shape->Height;
    Rect rect = Union(image, shadow);
    return Rect(rect.X - width / 2 + offset.X, rect.Y - height / 2 + offset.Y, rect.Width, rect.Height);
}
