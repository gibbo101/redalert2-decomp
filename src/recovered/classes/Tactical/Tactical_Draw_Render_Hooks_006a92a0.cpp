// void Tactical::Draw_Render_Hooks(ObjectClass *object, Rect const &cliprect) (0x006A92A0): an object's two
// decoration passes around its pixel, when it lies near the view (TibSun Tactical::Draw_Render_Hooks).
#include "shared/tactical.hpp"
#include "shared/object.hpp"

void __fastcall Tactical::Draw_Render_Hooks(ObjectClass *object, Rect const &cliprect)
{
    Point2D pixel;
    if (unknown_tactical_83996c->Coord_To_Pixel(object->Center_Coord(), pixel)) {
        object->unknown_slot65((int)&pixel, (int)&cliprect);
        object->unknown_slot66(pixel, cliprect);
    }
}
