// int UnitClass::unknown_707130() (0x00707130): the value of the stored load
// (StorageClass::Get_Total_Value) scaled by the owner's float at +0x148 of its
// type. No call sites: the original inlines it everywhere.
#include "shared/unit.hpp"
#include "shared/house.hpp"
// @ref ?Get_Total_Value@StorageClass@@QBEHXZ=0069adc0
// @ref ?Unknown_004F5B30@HouseClass@@QAEMXZ=004f5b30
// @ref __ftol=0077f110

int UnitClass::unknown_707130()
{
    float value = (float)unknown_294.Get_Total_Value();
    return (int)(House->Unknown_004F5B30() * value);
}
