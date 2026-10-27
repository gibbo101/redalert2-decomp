// static int __fastcall HouseClass::unknown_func_4eb550(int kind, int index) (0x004EB550)
// A building type's +0xBA0 value (0 for other kinds and for no index).
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

int __fastcall HouseClass::unknown_func_4eb550(int kind, int index)
{
    if (index < 0) {
        return 0;
    }
    TechnoTypeClass *type = Unknown_00482C00(kind, index);
    if (kind == 6 || kind == 7) {
        return ((UnknownBuildingTypeBA0View *)type)->unknown_ba0;
    }
    return 0;
}
