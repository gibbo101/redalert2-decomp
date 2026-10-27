// double ObjectClass::Health_Ratio() const (0x005D4540)
#include "shared/object_type.hpp"

double ObjectClass::Health_Ratio() const
{
    return (double)Strength / Class_Of()->MaxStrength;
}
