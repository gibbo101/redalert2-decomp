// void ObjectClass::unknown_slot54(bool arg1) (0x005D3C10, slot 54)
// Releases the +0x94 object; calls slot 81 when arg1 is set, the object has
// no owner, or the owner fails 0x004F52B0 and the object is not a techno
// passing TechnoClass slot 191; clears the map's 0x0049EC40 selection when it
// is this object; then flags the object in its owner's lists (0x006ECB90).
#include "shared/object_type.hpp"
#include "shared/techno.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_005394F0@UnknownObject5394F0@@QAEXXZ=005394f0
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90

void ObjectClass::unknown_slot54(bool arg1)
{
    if (unknown_94 != 0) {
        unknown_94->Unknown_005394F0();
        unknown_94 = 0;
    }
    HouseClass *house = Owning_House();
    bool keep = false;
    if (!arg1) {
        bool techno;
        if (this != 0) {
            techno = unknown_14_bit0;
        }
        if (this != 0 && techno && ((TechnoClass *)this)->unknown_slot191()) {
            keep = true;
        }
    }
    if (arg1 || house == 0 || (!house->Unknown_004F52B0() && !keep)) {
        unknown_slot81();
    }
    if (Map.Unknown_0049EC40() == this) {
        Map.Unknown_0049EC60(0);
    }
    Unknown_006ECB90(this, arg1);
}
