// bool LogicClass::Submit(ObjectClass *object, bool sort) (0x0053E330; vtable 0x0079A8EC slot 7)
// Westwood LOGIC.CPP: an object already in the logic layer (ObjectClass +0x84) is accepted
// at once; otherwise the layer adds it and the object is marked as submitted.
#include "shared/logic.hpp"
#include "shared/object.hpp"
// @ref ?Submit@LayerClass@@UAE_NPAVObjectClass@@_N@Z=005348a0

bool LogicClass::Submit(ObjectClass *object, bool sort)
{
    if (object->unknown_84) {
        return true;
    }
    if (LayerClass::Submit(object, sort)) {
        object->unknown_84 = true;
        return true;
    }
    return false;
}
