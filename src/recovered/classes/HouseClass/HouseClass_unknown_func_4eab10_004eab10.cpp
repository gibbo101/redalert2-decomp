// int *HouseClass::unknown_func_4eab10(int kind, bool naval) (0x004EAB10)
// The counter per object kind at +0x52B8..+0x52C8 (0 for other kinds).
#include "shared/techno.hpp"

int *HouseClass::unknown_func_4eab10(int kind, bool naval)
{
    switch (kind) {
    case 1:
    case 40:
        if (naval) {
            return &unknown_52c8;
        }
        return &unknown_52c0;
    case 2:
    case 3:
        return &unknown_52b8;
    case 15:
    case 16:
        return &unknown_52bc;
    case 6:
    case 7:
        return &unknown_52c4;
    }
    return 0;
}
