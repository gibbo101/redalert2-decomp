// HRESULT SwizzleManagerClass::Fetch_Swizzle_ID(void *pointer, long *id) (0x0069FD70, slot 5)
// An object's saved id is its address.
#include "shared/swizzle.hpp"

HRESULT __stdcall SwizzleManagerClass::Fetch_Swizzle_ID(void *pointer, long *id)
{
    if (pointer != 0 && id != 0) {
        *id = (long)pointer;
        return S_OK;
    }
    return E_POINTER;
}
