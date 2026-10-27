// double HouseClass::Tiberium_Fraction() const (0x004E2DF0)
#include "shared/techno.hpp"

double HouseClass::Tiberium_Fraction() const
{
    if ((int)Tiberium.Get_Total_Amount() == 0) {
        return 0.0;
    }
    return Tiberium.Get_Total_Amount() / Capacity;
}
