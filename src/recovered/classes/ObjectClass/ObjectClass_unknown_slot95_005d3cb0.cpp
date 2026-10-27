// int ObjectClass::unknown_slot95(RadioClass *from, int message, long &param) (0x005D3CB0)
#include "shared/object_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

int ObjectClass::unknown_slot95(RadioClass *from, int message, long &param)
{
    switch (message) {
    case 0x22:
        if (Health_Ratio() < Rules->unknown_1360) {
            return 1;
        }
        return 10;
    case 0x0D:
        unknown_slot71(2);
        return 1;
    }
    return 0;
}
