// TagClass::TagClass(TagTypeClass *type) (0x006B3870)
// A live tag with one trigger per trigger type of its type.
#include "shared/object.hpp"

// The abstract list 0x00AC0D48 (element type AbstractClass * by RTTI).
extern DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0d48;

TagClass::TagClass(TagTypeClass *type) :
    Class(type),
    AttachedTrigger(0),
    unknown_2c(0),
    unknown_30(unknown_geometry_k),
    unknown_34(false),
    unknown_35(false)
{
    unknown_TagClass_list_00abfe48.Add(this);
    unknown_objects_ac0cb0.Add((ObjectClass *)this);
    unknown_AbstractClass_list_00ac0d48.Add(this);
    if (type != 0) {
        for (TriggerTypeClass *trigger = type->Triggers; trigger != 0; trigger = trigger->Next) {
            TriggerClass *made = new TriggerClass(trigger);
            made->Next = AttachedTrigger;
            AttachedTrigger = made;
        }
    }
}
