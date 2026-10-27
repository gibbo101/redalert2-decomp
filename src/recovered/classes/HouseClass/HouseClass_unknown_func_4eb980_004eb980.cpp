// int HouseClass::unknown_func_4eb980(int kind, bool naval) (0x004EB980)
// The counter of 0x004EAB10 for an object kind (0 for other kinds).
#include "shared/techno.hpp"

int HouseClass::unknown_func_4eb980(int kind, bool naval)
{
    int *value = unknown_func_4eab10(kind, naval);
    if (value != 0) {
        return *value;
    }
    return 0;
}
