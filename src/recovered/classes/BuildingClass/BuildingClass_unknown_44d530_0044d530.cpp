// void BuildingClass::unknown_44d530() (0x0044D530)
// Powers the building off: when it is on (unknown_530) and its type has a
// power drain (+0xC6C above 0) or is Powered, clears unknown_530, sets
// unknown_75, flags the house (+0x5668, +0x5669, +0x144), runs
// unknown_44d6c0, announces EVA_BuildingOffLine to the player's house, tells
// the house its factory type is gone (0x004F3170) and, for the rules' type
// at +0x7BC, 0x004EEB90.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/foot.hpp"
#include "shared/rules.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_44d6c0@BuildingClass@@QAEXXZ=0044d6c0
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?unknown_func_4f3170@HouseClass@@QAEXH_NH@Z=004f3170
// @ref ?unknown_func_4eeb90@HouseClass@@QAEXXZ=004eeb90
// @ref ?Unknown_00715B40@@YIHPBDHH@Z=00715b40
// @ref ??_C@_0BE@MBKF@EVA_BuildingOffLine?$AA@=007cfa98

void BuildingClass::unknown_44d530()
{
    if (unknown_530 && (Type->PowerDrain_c6c > 0 || Type->Powered)) {
        unknown_530 = false;
        unknown_75 = true;
        House->unknown_5668 = true;
        House->unknown_5669 = true;
        House->unknown_144 = true;
        unknown_44d6c0();
        if (House->Unknown_004F52B0()) {
            Unknown_00715B40("EVA_BuildingOffLine", -1, -1);
        }
        if (Type->Factory) {
            House->unknown_func_4f3170(Type->Factory, Type->Naval, 0);
        }
        if (Type == Rules->unknown_7bc) {
            House->unknown_func_4eeb90();
        }
    }
}
