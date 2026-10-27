// long __stdcall HouseClass::Available_Money() (0x004E2B30)
#include "shared/techno.hpp"

long __stdcall HouseClass::Available_Money()
{
    float scale = Type->unknown_0x148;
    return (long)(Tiberium.Get_Total_Value() * scale + Balance);
}
