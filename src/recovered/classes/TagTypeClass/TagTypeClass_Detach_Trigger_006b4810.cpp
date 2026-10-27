// bool TagTypeClass::Detach_Trigger(TriggerTypeClass *trigger) (0x006B4810)
#include "shared/object.hpp"

bool TagTypeClass::Detach_Trigger(TriggerTypeClass *trigger)
{
    TriggerTypeClass *current = Triggers;
    if (current == trigger) {
        Triggers = trigger->Next;
        return true;
    }
    while (current != 0) {
        if (current->Next == trigger) {
            current->Next = trigger->Next;
            return true;
        }
        current = current->Next;
    }
    return false;
}
