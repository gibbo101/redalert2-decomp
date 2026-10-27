// ObjectClass *DisplayClass::Prev_Object(ObjectClass *object) (0x0049A670)
// The object (by slot 24) before the given one, walking layers 4, 3 and 2
// backwards; the last one when the given object is null or first.
#include "shared/display.hpp"
#include "shared/object.hpp"
// @ref ?Layer@DisplayClass@@2PAVLayerClass@@A=00852578
// @ref ?unknown_layers_7d5ce8@@3PAHA=007d5ce8

ObjectClass *DisplayClass::Prev_Object(ObjectClass *object)
{
    ObjectClass *first = 0;
    bool found = false;
    if (!object) {
        found = true;
    }
    for (int order = 0; order < 3; order++) {
        for (int index = Layer[unknown_layers_7d5ce8[order]].Count() - 1; index >= 0; index--) {
            ObjectClass *candidate = Layer[unknown_layers_7d5ce8[order]][index];
            if (candidate && candidate->unknown_slot24()) {
                if (!first) {
                    first = candidate;
                }
                if (found) {
                    return candidate;
                }
                if (object == candidate) {
                    found = true;
                }
            }
        }
    }
    return first;
}
