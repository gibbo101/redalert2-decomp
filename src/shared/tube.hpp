// TubeClass: a tunnel (Tube.cpp; RTTI vtable, TClassFactory<TubeClass>).
// Only the member FootClass reads is known (FootClass slot 19 0x004CA6F0:
// the cell at +0x28 of the tube FootClass +0x574 indexes).
#ifndef RA2_SHARED_TUBE_HPP
#define RA2_SHARED_TUBE_HPP

#include "shared/abstract_class.hpp"
#include "shared/vector_class_decl.hpp"

class TubeClass : public AbstractClass {
public:
    char unknown_24[0x28 - 0x24];
    Cell unknown_28;              // +0x28
};

// Every tube (0x008661C8; defined in the globals unit).
extern DynamicVectorClass<TubeClass *> unknown_TubeClass_list_008661c8;

#endif
