// void AircraftClass::Init() (0x00413CA0, slot 9)
// TechnoClass::Init, then from the type: flag +0x118 when the house type
// lists it, both facings' rate, the second facing set to the first, the
// flight level, ammunition and strength; finally tells the house.
#include "shared/aircraft.hpp"
// @ref ?Init@TechnoClass@@UAEXXZ=006c1c50
// @ref ?unknown_713520@UnknownTechnoPair@@QAEX_N@Z=00713520
// @ref ?Set_ROT@FacingClass@@QAEXH@Z=004b8e90
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?Set_Current@FacingClass@@QAEXABUUnknownFacingDir@@@Z=004b8b10
// @ref ?unknown_4ea970@HouseClass@@QAEXPAVTechnoClass@@@Z=004ea970

void AircraftClass::Init()
{
    TechnoClass::Init();
    if (Type != 0) {
        if (House != 0) {
            DynamicVectorClass<TechnoTypeClass *> &types = (DynamicVectorClass<TechnoTypeClass *> &)House->Type->VeteranAircraft;
            for (int index = 0; index < types.Count(); index++) {
                if (types[index] == Type) {
                    unknown_118.unknown_713520(true);
                    break;
                }
            }
        }
        unknown_2e0.Set_ROT(Type->ROT);
        unknown_2f8.Set_ROT(Type->ROT);
        unknown_2f8.Set_Current(unknown_2e0.Current());
        unknown_slot109(Type->Flight_Level());
        unknown_254 = Type->InitialAmmo != -1 ? Type->InitialAmmo : Type->Ammo;
        unknown_70 = Strength = Type->MaxStrength;
    }
    if (House != 0) {
        House->unknown_4ea970(this);
    }
}
