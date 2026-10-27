// void FootClass::unknown_slot98(int arg1) (0x004C8A40)
// When arg1 is set: announces the sale to a player-controlled house
// (EVA_UnitSold and the rules sound at +0x5C4), refunds slot 167's amount
// to the house, then slots 210, 52 and 60 (hypothesis: selling the unit).
#include "shared/foot.hpp"
#include "shared/house.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Unknown_00715B40@@YIXPBDHH@Z=00715b40
// @ref ?Unknown_00713DB0@@YIHHMHH@Z=00713db0
// @ref ?Refund_Money@HouseClass@@QAEXH@Z=004e5440
// @ref ??_C@_0N@GEGF@EVA_UnitSold?$AA@=007cf9c4

void FootClass::unknown_slot98(int arg1)
{
    if (arg1) {
        if (House->Unknown_004F52B0()) {
            Unknown_00715B40("EVA_UnitSold", -1, -1);
            Unknown_00713DB0(Rules->unknown_5c4, 1.0f, 0x2000, 0);
        }
        House->Refund_Money(unknown_slot167());
        unknown_slot210();
        unknown_slot52();
        unknown_slot60();
    }
}
