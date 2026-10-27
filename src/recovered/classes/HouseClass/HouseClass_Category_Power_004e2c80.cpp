// long __stdcall HouseClass::Category_Power(int category) (0x004E2C80)
// The summed power values of this house's technos of a category.
#include "shared/techno.hpp"

long __stdcall HouseClass::Category_Power(int category)
{
    int power = 0;
    for (int index = 0; index < Technos.Count(); index++) {
        TechnoClass *techno = Technos[index];
        TechnoTypeClass *type = techno->unknown_slot32();
        if (techno->House == this && type->Category == category) {
            power += type->unknown_59c + type->ThreatPosed;
        }
    }
    return power;
}
