// void DisplayClass::Submit(ObjectClass *object) (0x00499A40)
// Puts an object into the display layer it belongs to (its slot 29), after
// taking it out of the layer it was in (+0x80, -1 when none); ground layer 2
// is kept sorted.
#include "shared/display.hpp"
#include "shared/object.hpp"
// @ref ?Remove@DisplayClass@@QAEXPAVObjectClass@@@Z=00499a90
// @ref ?Layer@DisplayClass@@2PAVLayerClass@@A=00852578
// @ref ?Submit@LayerClass@@UAE_NPAVObjectClass@@_N@Z=005348a0

void DisplayClass::Submit(ObjectClass *object)
{
    if (object) {
        if (object->unknown_80 != -1) {
            Remove(object);
        }
        int layer = object->unknown_slot29();
        if (layer != -1) {
            if (Layer[layer].Submit(object, layer == 2)) {
                object->unknown_80 = layer;
            }
        }
    }
}
