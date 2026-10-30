// double HouseClass::Power_Fraction() const (0x004E8330)
#include "shared/techno.hpp"

double HouseClass::Power_Fraction() const
{
    if (Power < Drain && Drain != 0) {
        if (Power != 0) {
            return (double)Power / Drain;
        }
        return 0.0;
    }
    return 1.0;
}
