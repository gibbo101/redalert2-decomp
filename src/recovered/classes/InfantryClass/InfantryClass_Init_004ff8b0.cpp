// void InfantryClass::Init() (0x004FF8B0, slot 9)
// TechnoClass::Init and the house's notice; then from the type: flag
// +0x118 when the house type lists it (+0x14C) or for Trainable types of
// houses with +0x206, strength, ammunition and Cloakable (+0x32A).
#include "shared/infantry.hpp"
#include "shared/house_type.hpp"
// @ref ?Init@TechnoClass@@UAEXXZ=006c1c50
// @ref ?unknown_4ea970@HouseClass@@QAEXPAVTechnoClass@@@Z=004ea970
// @ref ?unknown_713520@UnknownTechnoPair@@QAEX_N@Z=00713520

void InfantryClass::Init()
{
    TechnoClass::Init();
    if (House != 0) {
        House->unknown_4ea970(this);
    }
    if (Type != 0) {
        if (House != 0) {
            TypeList<InfantryTypeClass *> &types = House->Type->VeteranInfantry;
            for (int index = 0; index < types.Count(); index++) {
                if (types[index] == Type) {
                    unknown_118.unknown_713520(true);
                    break;
                }
            }
        }
        if (House != 0 && House->unknown_206 && Type->Trainable) {
            unknown_118.unknown_713520(true);
        }
        Strength = Type->MaxStrength;
        unknown_70 = Type->MaxStrength;
        if (Type->InitialAmmo != -1) {
            unknown_254 = Type->InitialAmmo;
        } else {
            unknown_254 = Type->Ammo;
        }
        unknown_32a = Type->Cloakable;
    }
}
