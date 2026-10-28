// HRESULT SwizzleManagerClass::Get_Save_Size(int *size) (0x0069FCF0, slot 9)
#include "shared/swizzle.hpp"

HRESULT __stdcall SwizzleManagerClass::Get_Save_Size(int *size)
{
    if (size == 0) {
        return E_POINTER;
    }
    *size = 4;
    return S_OK;
}
