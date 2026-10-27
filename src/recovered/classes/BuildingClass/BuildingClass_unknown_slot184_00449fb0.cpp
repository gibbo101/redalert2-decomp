// InfantryTypeClass *BuildingClass::unknown_slot184() (0x00449FB0, slot 184)
// For factory type 7 without the flag at +0x5B3, a 25% chance of the rules
// Engineer; otherwise the techno crew.
#include "shared/building.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_slot184@TechnoClass@@UAEPAVInfantryTypeClass@@XZ=006d30b0

InfantryTypeClass *BuildingClass::unknown_slot184()
{
    if (!unknown_5b3 && unknown_id_source_a3d290->Random()(0, 99) < 25 && Type->Factory == 7) {
        return Rules->Engineer;
    }
    return TechnoClass::unknown_slot184();
}
