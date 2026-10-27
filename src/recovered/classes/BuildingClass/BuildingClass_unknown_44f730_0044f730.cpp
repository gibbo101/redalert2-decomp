// void BuildingClass::unknown_44f730() (0x0044F730)
// For each animation slot of the type: a Powered entry restarts its
// animation (0x00422C20); a PoweredLight entry with no animation yet, while
// unknown_5b4 is set (and not the delayed-fire slot 10), creates it in the
// state the health gives.
#include "shared/building.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?unknown_422c20@UnknownBuildingAnim@@QAEXXZ=00422c20

void BuildingClass::unknown_44f730()
{
    for (int index = 0; index < 18; index++) {
        if (Type->Anims[index].Powered) {
            if (unknown_454[index]) {
                ((UnknownBuildingAnim *)unknown_454[index])->unknown_422c20();
            }
        } else if (Type->Anims[index].PoweredLight && !unknown_454[index] && unknown_5b4) {
            if (!(Type->IsAnimDelayedFire && index == 10)) {
                unknown_44c920(index, Health_Ratio() <= Rules->unknown_1368, false, 0);
            }
        }
    }
}
