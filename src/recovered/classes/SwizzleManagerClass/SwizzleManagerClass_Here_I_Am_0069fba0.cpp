// HRESULT SwizzleManagerClass::Here_I_Am(long id, void *pointer) (0x0069FBA0, slot 6)
// Records a loaded object: its address when saved and its new address.
#include "shared/swizzle.hpp"

HRESULT __stdcall SwizzleManagerClass::Here_I_Am(long id, void *pointer)
{
    SwizzlePointerClass entry;
    entry.Pointer = pointer;
    entry.ID = id;
    SwizzledPointers.Add(entry);
    return S_OK;
}
