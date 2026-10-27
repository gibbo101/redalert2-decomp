// long __stdcall HouseClass::Public_Category_Quantity(int category) (0x004E2C20)
// The number of this house's technos of a category.
#include "shared/techno.hpp"

long __stdcall HouseClass::Public_Category_Quantity(int category)
{
    int count = 0;
    for (int index = 0; index < Technos.Count(); index++) {
        TechnoClass *techno = Technos[index];
        if (techno->House == this && techno->unknown_slot32()->Category == category) {
            count++;
        }
    }
    return count;
}
