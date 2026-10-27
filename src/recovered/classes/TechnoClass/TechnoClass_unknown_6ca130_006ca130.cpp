// EBolt *TechnoClass::unknown_6ca130(AbstractClass *target) (0x006CA130)
// Fires the weapon chosen for the target as an electric bolt from its fire
// coordinate (0x006CA020); a unit with +0x7D set and no bolt yet keeps it
// at +0x5C4 and attaches itself (0x004B2580). Never called: inlined at
// every use.
#include "shared/techno.hpp"
#include "shared/weapon_type.hpp"
#include "shared/ebolt.hpp"
// @ref ?Attach_004B2580@EBolt@@QAEXPAVTechnoClass@@H@Z=004b2580

EBolt *TechnoClass::unknown_6ca130(AbstractClass *target)
{
    int weapon = unknown_slot174(target);
    WeaponTypeClass *type = unknown_slot231(weapon)->WeaponType;
    CoordStruct source = unknown_slot43(weapon);
    EBolt *bolt = unknown_6ca020(target, type, source);
    if (bolt != 0 && Kind_Of() == 1 && unknown_7d && ((UnitClass *)this)->unknown_5c4 == 0) {
        ((UnitClass *)this)->unknown_5c4 = bolt;
        bolt->Attach_004B2580(this, weapon);
    }
    return bolt;
}
