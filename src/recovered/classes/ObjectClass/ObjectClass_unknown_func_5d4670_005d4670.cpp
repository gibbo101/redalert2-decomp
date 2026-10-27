// int ObjectClass::unknown_func_5d4670() const (0x005D4670)
#include "shared/object_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

int ObjectClass::unknown_func_5d4670() const
{
    if (Health_Ratio() > Rules->unknown_1368) {
        return 1;
    }
    return 0;
}
