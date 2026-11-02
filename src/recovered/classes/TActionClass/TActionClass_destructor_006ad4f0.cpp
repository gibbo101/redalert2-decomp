// TActionClass::~TActionClass() (0x006AD4F0)
#include "shared/object.hpp"

// The abstract list 0x00AC0C98 (element type AbstractClass * by RTTI).
extern DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0c98;

TActionClass::~TActionClass()
{
    Unknown_006ECB90(this, true);
    unknown_objects_ac0cb0.Delete((ObjectClass *)this);
    unknown_AbstractClass_list_00ac0c98.Delete(this);
    unknown_TActionClass_list_00abfd88.Delete(this);
    Text[0] = 0;
}


