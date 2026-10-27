// bool __stdcall HouseClass::Is_Powered() (0x004E2AB0)
#include "shared/techno.hpp"

bool __stdcall HouseClass::Is_Powered()
{
    return Power >= Drain;
}
