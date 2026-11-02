// rc_ptr_base::rc_ptr_base(ReferenceCounted *pointer) (0x006394F0): takes a reference.
#include "shared/reference_counted.hpp"

rc_ptr_base::rc_ptr_base(ReferenceCounted *pointer) : Pointer(pointer)
{
    if (pointer != 0) {
        pointer->RefCount++;
    }
}
