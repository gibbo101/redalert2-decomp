// TEventClass::~TEventClass() (0x006E5F40)
#include "shared/object.hpp"

// The abstract list 0x00AC0C98 (element type AbstractClass * by RTTI).
extern DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0c98;

TEventClass::~TEventClass()
{
    Unknown_006ECB90(this, true);
    unknown_AbstractClass_list_00ac0c98.Delete(this);
    unknown_objects_ac0cb0.Delete((ObjectClass *)this);
    unknown_TEventClass_list_00ac0808.Delete(this);
}
