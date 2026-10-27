// int ObjectClass::unknown_func_5d46b0() const (0x005D46B0)
#include "shared/object_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

int ObjectClass::unknown_func_5d46b0() const
{
    if (Health_Ratio() <= Rules->unknown_1370 && Strength > 0) {
        return 0;
    }
    if (Health_Ratio() > Rules->unknown_1370 && Health_Ratio() <= Rules->unknown_1368) {
        return 1;
    }
    return 2;
}
