// int ObjectClass::unknown_func_5d4600() const (0x005D4600)
#include "shared/object_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

int ObjectClass::unknown_func_5d4600() const
{
    if (Health_Ratio() > Rules->unknown_1370 && Health_Ratio() <= Rules->unknown_1368) {
        return 1;
    }
    return 0;
}
