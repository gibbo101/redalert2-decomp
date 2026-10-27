// void BuildingClass::unknown_44b910() (0x0044B910)
// Drops the infantry in unknown_53c whose +0x228 target is not this
// building; unknown_531 is then set when three are left, or when at least
// one is, unknown_530 holds and the house has full power.
#define VECTOR_IMPLEMENT_ALL
#include "shared/building.hpp"
#include "shared/house.hpp"
// @ref ?Power_Fraction@HouseClass@@QBENXZ=004e8330

void BuildingClass::unknown_44b910()
{
    for (int index = unknown_53c.Count() - 1; index >= 0; index--) {
        if (((TechnoClass *)unknown_53c[index])->unknown_228 != this) {
            unknown_53c.Delete(index);
        }
    }
    int count = unknown_53c.Count();
    if (count >= 3 || (House->Power_Fraction() == 1.0 && unknown_530 && count >= 1)) {
        unknown_531 = true;
    } else {
        unknown_531 = false;
    }
}
