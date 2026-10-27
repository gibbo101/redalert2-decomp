// void DisplayClass::Remove(ObjectClass *object) (0x00499A90)
// Takes an object out of its display layer (+0x80); when it was not found
// there, out of every layer, as often as it appears. (Each search is given
// a fresh copy of the pointer, as the original passes a temporary.)
#include "shared/display.hpp"
#include "shared/object.hpp"
// @ref ?Layer@DisplayClass@@2PAVLayerClass@@A=00852578

// Not expanded into Submit in the original (kept out of line).
#pragma auto_inline(off)
void DisplayClass::Remove(ObjectClass *object)
{
    ObjectClass *entry;
    if (object && object->unknown_80 != -1) {
        if (Layer[object->unknown_80].Delete(entry = object)) {
            object->unknown_80 = -1;
        }
        if (object->unknown_80 != -1) {
            for (int layer = 0; layer < 5; layer++) {
                while (Layer[layer].Delete(entry = object)) {
                }
            }
            object->unknown_80 = -1;
        }
    }
}
#pragma auto_inline(on)
