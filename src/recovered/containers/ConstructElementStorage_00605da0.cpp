// Original 0x00605da0: 136 body bytes plus 8 independently frozen NOP bytes.
// First actual C++ constructor/element-array construction recipe.
#include "shared/array_element_storage_views.hpp"

extern "C" unsigned char array_storage_dispatch_00605da0[];

ElementStorage_00605da0::ElementStorage_00605da0(int initial_count, Element_00605da0* supplied_storage)
    : storage(0), count(initial_count), unknown_0x0c(1), owns_storage(0)
{
    // Raw table identity is explicit; no unknown virtual hierarchy is synthesized.
    dispatch_table = array_storage_dispatch_00605da0;
    if (initial_count != 0) {
        if (supplied_storage != 0) {
            storage = new (supplied_storage) Element_00605da0[initial_count];
        } else {
            storage = new Element_00605da0[initial_count];
            owns_storage = 1;
        }
    }
    // Element padding and owner 0x0e/0x0f remain uninitialized.
    // Constructor ABI supplies the observed EAX receiver return.
}
