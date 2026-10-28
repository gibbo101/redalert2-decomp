// bool LayerClass::Submit(ObjectClass *object, bool sort) (0x005348A0, slot 7)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"
#include "shared/layer.hpp"
#include "shared/object.hpp"
// @ref ?Sorted_Add@LayerClass@@QAEHPAVObjectClass@@@Z=00534980

bool LayerClass::Submit(ObjectClass *object, bool sort)
{
    if (sort) {
        return Sorted_Add(object);
    }
    return Add(object) != false;
}
