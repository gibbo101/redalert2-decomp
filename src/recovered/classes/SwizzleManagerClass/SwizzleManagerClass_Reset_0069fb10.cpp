// HRESULT SwizzleManagerClass::Reset() (0x0069FB10, ISwizzle slot 3)
// Resolves every recorded field and empties the tables.
#include "shared/swizzle.hpp"

// @ref ?Process_Tables@SwizzleManagerClass@@AAEXXZ=0069fc30

HRESULT __stdcall SwizzleManagerClass::Reset()
{
    Process_Tables();
    return S_OK;
}
