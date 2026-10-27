// BSTR __stdcall HouseClass::Name() (0x004E2AF0)
#include "shared/techno.hpp"

BSTR __stdcall HouseClass::Name()
{
    wchar_t buffer[32];
    MultiByteToWideChar(0, 1, Type->Name, -1, buffer, 32);
    return SysAllocString(buffer);
}
