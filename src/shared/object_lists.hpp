// The global object lists (names unknown), moved out of shared/object.hpp so
// units below the object layer (AlphaShapeClass) can use them.
#ifndef RA2_SHARED_OBJECT_LISTS_HPP
#define RA2_SHARED_OBJECT_LISTS_HPP

#include "shared/vector_class_decl.hpp"

class AbstractClass;
class ObjectClass;
class TechnoClass;

extern DynamicVectorClass<ObjectClass *> unknown_objects_a40368;   // 0x00A40368
// Defined in 0x006EC3A0's unit; AbstractClass * by their vtables (0x007A177C).
extern DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0d60; // 0x00AC0D60
extern DynamicVectorClass<AbstractClass *> unknown_objects_ac0c30; // 0x00AC0C30
extern DynamicVectorClass<AbstractClass *> unknown_objects_ac0cb0; // 0x00AC0CB0 (objects and types; defined as AbstractClass * at 0x006EC3A0's unit)
// Trigger, tag, event and action objects (0x00AC0C98; element type AbstractClass * by RTTI).
extern DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0c98;
// Foot objects and neurons (0x00AC0C18). RTTI types its vtable 0x007A177C as
// DynamicVectorClass<AbstractClass *>; TechnoClass * is a placeholder kept for
// FootClass's out-of-line Delete(int) copy 0x00454B20.
extern DynamicVectorClass<TechnoClass *> unknown_list_ac0c18;

#endif
