// TActionClass::TActionClass() (0x006AD370)
// A new action, numbered by its place in TActions.
#include "shared/object.hpp"

// The abstract list 0x00AC0C98 (element type AbstractClass * by RTTI).
extern DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0c98;

TActionClass::TActionClass() :
    unknown_24(-1),
    Next(0),
    Type(0),
    unknown_30(0),
    unknown_34(0),
    unknown_38(0),
    unknown_3c(0),
    unknown_40(0),
    unknown_44(0),
    unknown_48(0),
    unknown_4c(0),
    unknown_50(0)
{
    unknown_TActionClass_list_00abfd88.Add(this);
    unknown_24 = unknown_TActionClass_list_00abfd88.ID(this);
    unknown_objects_ac0cb0.Add((ObjectClass *)this);
    unknown_AbstractClass_list_00ac0c98.Add(this);
    Text[0] = 0;
    Data = 0;
}
