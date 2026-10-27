// void BuildingClass::unknown_44f800() (0x0044F800)
// For each animation slot of the type: a Powered entry stops its animation
// (0x00422C10); a PoweredLight entry removes its animation (unknown_44cfd0)
// and, for the delayed-fire slot 10, restarts animation 3 when that is
// Powered, in the state the health gives.
#include "shared/building.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?unknown_422c10@UnknownBuildingAnim@@QAEXXZ=00422c10
// @ref ?unknown_44cfd0@BuildingClass@@QAEXH@Z=0044cfd0

void BuildingClass::unknown_44f800()
{
    for (int index = 0; index < 18; index++) {
        if (Type->Anims[index].Powered) {
            if (unknown_454[index]) {
                ((UnknownBuildingAnim *)unknown_454[index])->unknown_422c10();
            }
        } else if (Type->Anims[index].PoweredLight) {
            if (unknown_454[index]) {
                unknown_44cfd0(index);
                if (index == 10 && Type->IsAnimDelayedFire && Type->Anims[3].Powered) {
                    unknown_44c920(3, Health_Ratio() <= Rules->unknown_1368, false, 0);
                }
            }
        }
    }
}
