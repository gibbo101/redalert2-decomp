// void ObjectClass::Set_Health_Ratio(double ratio) (0x005D4560)
#include "shared/object_type.hpp"
// @ref __real@8@00000000000000000000=0079b610
// @ref __ftol=0077f110

void ObjectClass::Set_Health_Ratio(double ratio)
{
    if (ratio > 0.0) {
        Strength = (int)(Class_Of()->MaxStrength * ratio);
        if (Strength == 0) {
            Strength = 1;
        }
    } else {
        Strength = 0;
    }
}
