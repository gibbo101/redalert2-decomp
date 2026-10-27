// TriggerClass scalar deleting destructor (0x006EDBA0): compiler generated,
// with the destructor expanded inline. The destructor itself (0x006ED3C0) is
// defined here: its frozen inventory bound is split at 0x006ED49A, so it is
// bound by reference until the bound is refined.
#include "shared/object.hpp"

// The abstract list 0x00AC0D48 (element type AbstractClass * by RTTI).
extern DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0d48;

TriggerClass::~TriggerClass()
{
    Unknown_006ECB90(this, true);
    unknown_TriggerClass_list_00a40aa0.Delete(this);
    unknown_objects_ac0cb0.Delete((ObjectClass *)this);
    unknown_AbstractClass_list_00ac0d48.Delete(this);
}
