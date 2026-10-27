// double HouseClass::Power_Fraction() const (0x004E8330)
#include "shared/techno.hpp"

double HouseClass::Power_Fraction() const
{
    int power = Power;
    int drain = Drain;
    if (power < drain && drain != 0) {
        if (power != 0) {
            return (double)power / drain;
        }
        return 0.0;
    }
    return 1.0;
}
