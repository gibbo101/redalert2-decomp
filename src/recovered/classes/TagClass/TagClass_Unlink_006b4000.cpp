// bool TagClass::Unlink(TriggerClass *trigger) (0x006B4000): takes the trigger out of the chain;
// false when it was not attached (TibSun Unlink).
#include "shared/object.hpp"

bool TagClass::Unlink(TriggerClass *trigger)
{
    if (trigger != 0) {
        if (AttachedTrigger == trigger) {
            AttachedTrigger = trigger->Next;
            return true;
        }
        TriggerClass *trigptr = AttachedTrigger;
        while (trigptr != 0) {
            if (trigptr->Next == trigger) {
                trigptr->Next = trigger->Next;
                return true;
            }
            trigptr = trigptr->Next;
        }
    }
    return false;
}
