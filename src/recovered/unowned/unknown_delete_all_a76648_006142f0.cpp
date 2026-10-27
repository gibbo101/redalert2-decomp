// void unknown_delete_all_a76648() -- 0x006142F0
// Purpose: empties the list at 0x00A76648 from the end: each element runs
// 0x0062E6E0, leaves the list and is freed.
// Assumptions: the element class is unidentified and needs no destructor
// here; 0x0062E6E0 is taken to be its cleanup.
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
// @ref ?unknown_list_a76648@@3V?$DynamicVectorClass@PAUUnknownItem_006142f0@@@@A=00a76648
// @ref ?unknown_cleanup_62e6e0@UnknownItem_006142f0@@QAEXXZ=0062e6e0
// @ref ??3@YAXPAX@Z=00781d3b

struct UnknownItem_006142f0 {
    void unknown_cleanup_62e6e0();          // 0x0062E6E0
};
extern DynamicVectorClass<UnknownItem_006142f0 *> unknown_list_a76648;

void unknown_delete_all_a76648()
{
    int index = unknown_list_a76648.Count();
    while (--index >= 0) {
        UnknownItem_006142f0 *item = unknown_list_a76648[index];
        item->unknown_cleanup_62e6e0();
        unknown_list_a76648.Delete(index);
        delete item;
    }
}
