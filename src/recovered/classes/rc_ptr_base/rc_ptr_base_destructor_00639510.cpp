// rc_ptr_base::~rc_ptr_base() (0x00639510): releases the pointer (tail call).
#include "shared/reference_counted.hpp"

rc_ptr_base::~rc_ptr_base()
{
    if (Pointer != 0) {
        ReferenceCounted *old = Pointer;
        Pointer = 0;
        old->Release();
    }
}
