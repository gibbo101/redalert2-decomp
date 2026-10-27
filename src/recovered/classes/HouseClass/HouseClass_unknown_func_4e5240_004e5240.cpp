// double HouseClass::unknown_func_4e5240() const (0x004E5240)
#include "shared/techno.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

double HouseClass::unknown_func_4e5240() const
{
    if (unknown_254.Get_Total_Amount() == 0.0f) {
        return 0.0;
    }
    return unknown_254.Get_Total_Amount() / Rules->unknown_1410;
}
