// int TechnoTypeClass::Repair_Cost() const (0x006DAEC0)
// Cost of one repair step (slot 44; RA1 formula): at least 1.
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref __ftol=0077f110

int TechnoTypeClass::Repair_Cost() const
{
    int result = (int)((Raw_Cost() / (MaxStrength / Rules->unknown_1334)) * Rules->unknown_1338);
    if (result <= 1) {
        result = 1;
    }
    return result;
}
