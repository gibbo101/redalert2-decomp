// void BuildingClass::Init() (0x0043F840, slot 9)
// TechnoClass::Init, then registration with the owner and the type's
// strength, ammunition and turn rate; loads the buildup image (type slot 48)
// or clears unknown_5ac.
#include "shared/building.hpp"
// @ref ?Init@TechnoClass@@UAEXXZ=006c1c50
// @ref ?unknown_4ea970@HouseClass@@QAEXPAVTechnoClass@@@Z=004ea970
// @ref ?Set_ROT@FacingClass@@QAEXH@Z=004b8e90
// @ref ?Free_Buildup@BuildingTypeClass@@QAEXXZ=0045e920

void BuildingClass::Init()
{
    TechnoClass::Init();
    if (House) {
        unknown_434 = House->Type->House;
        House->unknown_4ea970(this);
    }
    if (Type) {
        unknown_70 = Strength = Type->MaxStrength;
        if (Type->InitialAmmo == -1) {
            unknown_254 = Type->Ammo;
        } else {
            unknown_254 = Type->InitialAmmo;
        }
        unknown_2e0.Set_ROT(Type->ROT);
        if (!Type->unknown_slot48()) {
            unknown_5ac = false;
            return;
        }
        Type->Free_Buildup();
        unknown_5b9 = true;
    }
}
