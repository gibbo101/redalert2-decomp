// void UnknownOwnedList_0063F070::unknown_clear() -- 0x0063F070
// Purpose: frees and removes the first element until the list (a
// DynamicVectorClass at +0x00) is empty, then clears +0x18 and +0x1C.
// Assumptions: the owner and element classes are unidentified; elements
// need no destructor. Name hypothesis.
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

struct UnknownItem_0063f070 {
    int unknown_00;
};

struct UnknownOwnedList_0063f070 {
    DynamicVectorClass<UnknownItem_0063f070 *> Items;   // +0x00
    bool unknown_18;                                    // +0x18
    int unknown_1c;                                     // +0x1C
    void unknown_clear();
};

void UnknownOwnedList_0063f070::unknown_clear()
{
    while (Items.Count() != 0) {
        delete Items[0];
        Items.Delete(0);
    }
    unknown_18 = false;
    unknown_1c = 0;
}
