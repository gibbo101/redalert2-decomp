// void AnimClass::Attach_To(ObjectClass *object) (0x00422540; name hypothesis)
// Moves the animation from the object it follows (unknown_b4) to object:
// leaving clears the old object's flag (+0x78, through its slot 89) when no
// other animation still follows it and keeps the animation at its current
// center; joining stores the offset from the new object's center (slot
// 103). The map entry is removed and re-added around each change.
#include "shared/anim.hpp"

#include "shared/map_view.hpp"

void AnimClass::Attach_To(ObjectClass *object)
{
    if (unknown_b4 != 0) {
        ObjectClass *old = unknown_b4;
        bool on_map = unknown_74;
        if (on_map) {
            Map.Remove(this);
        }
        int index;
        for (index = 0; index < Anims.Count(); index++) {
            AnimClass *anim = Anims[index];
            if (anim != this && anim->unknown_b4 == unknown_b4) {
                break;
            }
        }
        if (index == Anims.Count()) {
            old->unknown_slot89();
            old->unknown_78 = false;
        }
        CoordStruct coord = Center_Coord();
        unknown_b4 = 0;
        unknown_slot103(coord);
        if (on_map) {
            Map.Submit(this);
        }
    }
    if (object != 0) {
        CoordStruct coord = Center_Coord();
        Map.Remove(this);
        object->unknown_78 = true;
        unknown_b4 = object;
        CoordStruct offset = coord - object->Center_Coord();
        unknown_slot103(offset);
        Map.Submit(this);
    }
}
