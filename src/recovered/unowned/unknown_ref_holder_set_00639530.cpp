// void rc_ptr_base::Set(ReferenceCounted *pointer) (0x00639530; was UnknownRefHolder_00639530::Set): takes a reference to pointer, releases the old one.
#include "shared/reference_counted.hpp"

void rc_ptr_base::Set(ReferenceCounted *pointer)
{
    if (pointer != Pointer) {
        if (pointer != 0) {
            pointer->RefCount++;
        }
        if (Pointer != 0) {
            ReferenceCounted *old = Pointer;
            Pointer = 0;
            old->Release();
        }
        Pointer = pointer;
    }
}
