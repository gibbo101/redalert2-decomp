// TEventClass::TEventClass() (0x006E5DE0)
// A new event, numbered by its place in TEvents.
#include "shared/object.hpp"

// The abstract list 0x00AC0C98 (element type AbstractClass * by RTTI).
extern DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0c98;

TEventClass::TEventClass() :
    unknown_24(-1),
    Next(0),
    Type(0),
    unknown_30(0)
{
    unknown_TEventClass_list_00ac0808.Add(this);
    unknown_24 = unknown_TEventClass_list_00ac0808.ID(this);
    unknown_AbstractClass_list_00ac0c98.Add(this);
    unknown_objects_ac0cb0.Add((ObjectClass *)this);
    Data = 0;
}
