// RGBClass OverlayTypeClass::unknown_func_5dd000(unsigned frame) const (0x005DD000)
// The radar colour of a frame of the type's image, or of its cell animation's
// (TibSun overtype.cpp OverlayTypeClass::Get_Radar_Color): tiberium overlays
// (0x7F-0x8A, 0x93-0x9E) swap green and blue; black without an image.
#include "shared/overlay_type.hpp"
#include "shared/anim_type.hpp"
#include "shared/shape_file.hpp"

RGBClass OverlayTypeClass::unknown_func_5dd000(unsigned frame) const
{
    ShapeFileStruct const *image = (ShapeFileStruct const *)unknown_slot39();

    if (image == 0 && CellAnim != 0) {
        image = (ShapeFileStruct const *)CellAnim->unknown_slot39();
    }

    if (image != 0) {
        if ((ArrayIndex >= 0x7F && ArrayIndex <= 0x8A) || (ArrayIndex >= 0x93 && ArrayIndex <= 0x9E)) {
            RGBClass color = image->Get_Color(frame);
            return RGBClass(color.Get_Red(), color.Get_Blue(), color.Get_Green());
        }
        return image->Get_Color(frame);
    }

    return RGBClass(0, 0, 0);
}
