// long __stdcall HouseClass::Available_Storage() (0x004E2B70)
#include "shared/techno.hpp"

long __stdcall HouseClass::Available_Storage()
{
    return Capacity - (int)Tiberium.Get_Total_Amount();
}
