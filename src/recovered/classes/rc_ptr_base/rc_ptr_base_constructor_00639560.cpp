// rc_ptr_base::rc_ptr_base(rc_ptr_base const &other) (0x00639560): shares other's pointer (its scalar deleting destructor 0x00639580 follows).
#include "shared/reference_counted.hpp"

rc_ptr_base::rc_ptr_base(rc_ptr_base const &other) : Pointer(other.Pointer)
{
    if (Pointer != 0) {
        Pointer->RefCount++;
    }
}
