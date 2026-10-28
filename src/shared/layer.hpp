// LayerClass (Layer.cpp, unit 0x005346B0; RTTI vtable 0x0079E868, 10
// slots): a display layer, a list of objects drawn in order (Westwood's
// LAYER.CPP). Moved out of shared/display.hpp so the Layer unit does not
// include the map chain.
#ifndef RA2_SHARED_LAYER_HPP
#define RA2_SHARED_LAYER_HPP

#include "shared/vector_class.hpp"
#include "shared/com_persist.hpp"

class ObjectClass;

// A display layer: a list of objects (RTTI vtable 0x0079E868, 10 slots).
class LayerClass : public DynamicVectorClass<ObjectClass *> {
public:
    // Adds an object (sorted when asked) (0x005348A0, slot 7).
    virtual bool Submit(ObjectClass *object, bool sort = false);
    // One bubble pass by ObjectClass slot 45 (0x00534920).
    void Sort();
    // Inserts the object before the first larger one (0x00534980).
    int Sorted_Add(ObjectClass *object);
    HRESULT Load(IStream *stream);                  // 0x00534A80
    HRESULT Save(IStream *stream);                  // 0x00534A10
    virtual void unknown_slot8();
    virtual void unknown_slot9();
};

#endif
