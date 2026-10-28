// static int ptr_compare_func(void const *, void const *) (0x0069FC00)
// qsort order of table entries by old address.
#include "shared/swizzle.hpp"

static int __cdecl ptr_compare_func(void const *ptr1, void const *ptr2)
{
    long id1 = ((SwizzlePointerClass const *)ptr1)->ID;
    long id2 = ((SwizzlePointerClass const *)ptr2)->ID;
    if (id1 == id2) {
        return 0;
    }
    return id1 < id2 ? -1 : 1;
}
