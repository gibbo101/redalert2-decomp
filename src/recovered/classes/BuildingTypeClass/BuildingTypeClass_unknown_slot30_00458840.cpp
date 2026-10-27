// CoordStruct BuildingTypeClass::unknown_slot30() const (0x00458840, slot 30)
// The size of the type's image (slot 39) from its first frame: (width,
// width, height); zero without an image.
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/building_type.hpp"
#include "shared/shape_file.hpp"

CoordStruct BuildingTypeClass::unknown_slot30() const
{
    ShapeFileStruct const *shape = (ShapeFileStruct const *)unknown_slot39();
    int width;
    int height;
    if (shape) {
        Rect rect = shape->Get_Frame_Rect(0);
        width = rect.Width;
        height = rect.Height;
    } else {
        width = 0;
        height = 0;
    }
    return CoordStruct(width, width, height);
}
