// int ObjectClass::unknown_func_5d45b0() const (0x005D45B0)
#include "shared/object_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

int ObjectClass::unknown_func_5d45b0() const
{
    if (Health_Ratio() <= Rules->unknown_1370 && Strength > 0) {
        return 1;
    }
    return 0;
}
