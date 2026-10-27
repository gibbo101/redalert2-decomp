// int TechnoTypeClass::unknown_slot33(int house) const (0x006DAD30)
// Cost for a house (hypothesis: RA1 Cost_Of): Raw_Cost scaled by the
// house's multiplier. The base declares the argument as int.
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?Cost_Multiplier@HouseClass@@QAEMPBVTechnoTypeClass@@@Z=004f5960
// @ref __ftol=0077f110

int TechnoTypeClass::unknown_slot33(int house) const
{
    if (house) {
        float factor = ((HouseClass *)house)->Cost_Multiplier(this);
        return (int)(Raw_Cost() * factor);
    }
    return Raw_Cost();
}
