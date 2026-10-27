// ObjectClass *DisplayClass::Next_Object(ObjectClass *object) (0x0049A5D0)
// The next object (by slot 24) after the given one in layers 2, 3 and 4;
// the first one when the given object is null or last.
#include "shared/display.hpp"
#include "shared/object.hpp"
// @ref ?Layer@DisplayClass@@2PAVLayerClass@@A=00852578
// @ref ?unknown_layers_7d5cdc@@3PAHA=007d5cdc

ObjectClass *DisplayClass::Next_Object(ObjectClass *object)
{
    ObjectClass *first = 0;
    bool found = false;
    if (!object) {
        found = true;
    }
    for (int order = 0; order < 3; order++) {
        for (int index = 0; index < Layer[unknown_layers_7d5cdc[order]].Count(); index++) {
            ObjectClass *candidate = Layer[unknown_layers_7d5cdc[order]][index];
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
