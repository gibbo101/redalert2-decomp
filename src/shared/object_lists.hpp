// The global object lists (names unknown), moved out of shared/object.hpp so
// units below the object layer (AlphaShapeClass) can use them.
#ifndef RA2_SHARED_OBJECT_LISTS_HPP
#define RA2_SHARED_OBJECT_LISTS_HPP

#include "shared/vector_class_decl.hpp"

class AbstractClass;
class ObjectClass;
class TechnoClass;

// The globals unit (0x004D2BA0) defines this list and sets RA2_GLOBAL_LISTS_DEFINED: a later
// extern declaration there makes VC6 emit a second dynamic initializer and atexit pair.
#ifndef RA2_GLOBAL_LISTS_DEFINED
extern DynamicVectorClass<ObjectClass *> unknown_objects_a40368;   // 0x00A40368
#endif
// Defined in 0x006EC3A0's unit; AbstractClass * by their vtables (0x007A177C). Skipped there
// (RA2_TRACKER_LISTS_DEFINED): VC6 emits a second dynamic initializer for an extern
// redeclaration that follows the definition.
#ifndef RA2_TRACKER_LISTS_DEFINED
extern DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0d60; // 0x00AC0D60
extern DynamicVectorClass<AbstractClass *> unknown_objects_ac0c30; // 0x00AC0C30
extern DynamicVectorClass<AbstractClass *> unknown_objects_ac0cb0; // 0x00AC0CB0 (objects and types; defined as AbstractClass * at 0x006EC3A0's unit)
// Trigger, tag, event and action objects (0x00AC0C98; element type AbstractClass * by RTTI).
extern DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0c98;
// Foot objects and neurons (0x00AC0C18; vtable 0x007A177C, RTTI DynamicVectorClass<AbstractClass *>).
extern DynamicVectorClass<AbstractClass *> unknown_list_ac0c18;
// Buildings and houses (0x00AC0C80; vtable 0x007A177C).
extern DynamicVectorClass<AbstractClass *> unknown_abstracts_ac0c80;
#endif

#endif
