// HRESULT SwizzleManagerClass::Swizzle(void **pointer) (0x0069FB20, slot 4)
// Records a loaded pointer field (its saved value is the old address) and clears it.
#include "shared/swizzle.hpp"

HRESULT __stdcall SwizzleManagerClass::Swizzle(void **pointer)
{
    if (pointer == 0) {
        return E_POINTER;
    }
    if (*pointer == 0) {
        return S_OK;
    }
    UnswizzledPointers.Add(SwizzlePointerClass((long)*pointer, pointer));
    *pointer = 0;
    return S_OK;
}
