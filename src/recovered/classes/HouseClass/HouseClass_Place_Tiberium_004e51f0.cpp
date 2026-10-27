// void HouseClass::Place_Tiberium(int count, int type) (0x004E51F0)
#include "shared/techno.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

void HouseClass::Place_Tiberium(int count, int type)
{
    while (count > 0) {
        float limit = (float)Rules->unknown_1410;
        if (!(unknown_254.Get_Total_Amount() < limit)) {
            break;
        }
        unknown_254.Add_Amount(1.0f, type);
        count--;
    }
}
