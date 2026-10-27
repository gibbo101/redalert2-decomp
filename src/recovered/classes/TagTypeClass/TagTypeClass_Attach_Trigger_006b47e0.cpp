// bool TagTypeClass::Attach_Trigger(TriggerTypeClass *trigger) (0x006B47E0)
#include "shared/object.hpp"

bool TagTypeClass::Attach_Trigger(TriggerTypeClass *trigger)
{
    if (trigger != 0) {
        trigger->Next = Triggers;
        Triggers = trigger;
        return true;
    }
    return false;
}
