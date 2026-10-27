// Deploy / undeploy action and weapon-target choice (0x00506530).
#include "shared/infantry.hpp"
#include "shared/techno_map.hpp"
// @ref ?unknown_slot137@FootClass@@UAEHXZ=004c8d70
// @ref ?Unknown_006D8640@TechnoClass@@QAE_NPAUWeaponStruct@@@Z=006d8640
// @ref ?unknown_func_5d27d0@ObjectClass@@QBE_NPBD@Z=005d27d0
// @ref ??_C@_04BEF@DESO?$AA@=007daf2c
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
int InfantryClass::unknown_slot137()
{
    if (Type->Deployer) {
        int delay = -1;
        if (unknown_5090d0()) {
            if (Type->UndeployDelay <= -1) {
                unknown_slot311(31, true, false);
            }
        } else {
            unknown_slot311(27, true, false);
            WeaponStruct *weapon = unknown_slot229();
            if (Unknown_006D8640(weapon) && weapon->WeaponType->unknown_126) {
                if (unknown_func_5d27d0("DESO")) {
                    delay = Type->DoControls[27].Count + 1;
                } else {
                    unknown_slot220((AbstractClass *)&Map[unknown_slot104()]);
                }
            }
            if (Type->UndeployDelay > -1) {
                delay = Type->UndeployDelay;
            }
        }
        unknown_slot118(5);
        unknown_slot260(0, 1);
        if (delay > -1) {
            return delay;
        }
    }
    return FootClass::unknown_slot137();
}

