// void TagClass::Link(TriggerClass *trigger) (0x006B3FF0): puts the trigger at the head of the chain
// (TibSun Link).
#include "shared/object.hpp"

void TagClass::Link(TriggerClass *trigger)
{
    trigger->Next = AttachedTrigger;
    AttachedTrigger = trigger;
}
