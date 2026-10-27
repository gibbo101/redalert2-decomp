// InfantryTypeClass *TechnoClass::unknown_slot184() (0x006D30B0, slot 184)
// The crew type a Crewed techno leaves: AlliedCrew or SovietCrew by the
// owner's +0x130 (else Technician); Technician for houses without a side,
// and with a 15% chance for armed technos.
#include "shared/techno.hpp"
#include "shared/house_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0

InfantryTypeClass *TechnoClass::unknown_slot184()
{
    if (!unknown_slot32()->Crewed) {
        return 0;
    }
    InfantryTypeClass *crew;
    int side = House->unknown_130;
    if (side == 0) {
        crew = Rules->AlliedCrew;
    } else if (side == 1) {
        crew = Rules->SovietCrew;
    } else {
        crew = Rules->Technician;
    }
    if (House->Type->Side != -1) {
        if (unknown_slot163() && unknown_id_source_a3d290->Random()(0, 99) < 15) {
            crew = Rules->Technician;
        }
    } else {
        crew = Rules->Technician;
    }
    return crew;
}
