// void SwizzleManagerClass::Process_Tables() (0x0069FC30)
// Sorts both tables by old address, writes each field's new address and empties them. A field
// whose object was never reported deliberately faults (1 / 0 through a volatile zero: the stored
// divisor and quotient are in the original).
#include "shared/swizzle.hpp"

// @ref ?ptr_compare_func@@YAHPBX0@Z=0069fc00

void SwizzleManagerClass::Process_Tables()
{
    if (UnswizzledPointers.Count() != 0) {
        if (SwizzledPointers.Count() > 0) {
            qsort(&SwizzledPointers[0], SwizzledPointers.Count(), sizeof(SwizzlePointerClass), ptr_compare_func);
        }
        if (UnswizzledPointers.Count() > 0) {
            qsort(&UnswizzledPointers[0], UnswizzledPointers.Count(), sizeof(SwizzlePointerClass), ptr_compare_func);
        }
        SwizzlePointerClass *sptr = &SwizzledPointers[0];
        int scount = SwizzledPointers.Count();
        int ucount = UnswizzledPointers.Count();
        SwizzlePointerClass *uptr = &UnswizzledPointers[0];
        while (ucount > 0) {
            if (uptr->ID == sptr->ID) {
                *(void **)uptr->Pointer = sptr->Pointer;
                uptr++;
                ucount--;
            } else {
                if (uptr->ID > sptr->ID) {
                    do {
                        sptr++;
                        scount--;
                    } while (uptr->ID > sptr->ID);
                }
                if (uptr->ID != sptr->ID) {
                    volatile int zero = 0;
                    zero = 1 / zero;
                }
            }
        }
        UnswizzledPointers.Clear();
        SwizzledPointers.Clear();
    }
}
