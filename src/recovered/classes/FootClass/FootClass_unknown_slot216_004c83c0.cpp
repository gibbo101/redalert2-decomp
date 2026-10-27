// void FootClass::unknown_slot216(int arg1) (0x004C83C0)
// For a player-controlled house and a type that is not Spawned: raises
// event 7 at the cell of slot 104 and, when that succeeds, announces
// EVA_UnitLost (hypothesis: the unit was lost).
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Unknown_00715B40@@YIXPBDHH@Z=00715b40
// @ref ?Unknown_0063B5B0@@YI_NHVCell@@@Z=0063b5b0
// @ref ??_C@_0N@PGLC@EVA_UnitLost?$AA@=007d82c0

void FootClass::unknown_slot216(int arg1)
{
    if (House->Unknown_004F52B0() && !unknown_slot32()->Spawned) {
        if (Unknown_0063B5B0(7, unknown_slot104())) {
            Unknown_00715B40("EVA_UnitLost", -1, -1);
        }
    }
}
