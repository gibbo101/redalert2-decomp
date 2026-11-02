#include "shared/infantry.hpp"
#include "shared/spawn_manager.hpp"
#include "shared/techno_map.hpp"

// void TechnoClass::unknown_slot220(AbstractClass *target) (0x006C9AF0, slot 220)
// Sets the target (+0x228), clearing +0x404 first: this object means the
// cell under it; an object (flag bit 1) that is not +0x7D or has no
// strength is dropped, and one with flag bit 2 too when it is +0x325 or
// busy infantry. A dropped target tells +0x238, clears +0x310 and drops
// +0x25C when slot 213 refuses it.
// @ref ?Is_Busy_00509760@InfantryClass@@QBE_NXZ=00509760

// Red Alert's Target_Legal: any target but none.
inline bool Target_Legal(AbstractClass const *target)
{
    return target != 0;
}

void TechnoClass::unknown_slot220(AbstractClass *target)
{
    unknown_404 = false;
    if (target == unknown_228) {
        return;
    }
    if (!Target_Legal(target)) {
        target = 0;
    } else {
        if (target == this) {
            target = (AbstractClass *)Map_Cell(CoordStruct(Coord));
        } else if (target->AbstractFlags.IsObject) {
            if (!((ObjectClass *)target)->unknown_7d || ((ObjectClass *)target)->Strength == 0) {
                target = 0;
            } else {
                bool active = target->AbstractFlags.IsFoot;
                TechnoClass *techno;
                if (active && (techno = (TechnoClass *)target)->unknown_325) {
                    target = 0;
                }
                if (active && techno->Kind_Of() == 15 && ((InfantryClass *)techno)->Is_Busy_00509760()) {
                    target = 0;
                }
            }
        }
    }
    unknown_228 = target;
    if (SpawnManager != 0 && target == 0) {
        SpawnManager->Set_Target(target);
    }
    if (unknown_228 == 0) {
        unknown_310 = 0;
    }
    if (unknown_25c[0] != 0 && !unknown_slot213(target)) {
        unknown_25c[0]->unknown_slot60();
        unknown_25c[0] = 0;
    }
}
