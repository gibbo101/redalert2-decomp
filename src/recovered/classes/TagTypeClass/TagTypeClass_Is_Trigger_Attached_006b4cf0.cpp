// bool TagTypeClass::Is_Trigger_Attached(TriggerTypeClass *trigger) const (0x006B4CF0)
#include "shared/object.hpp"

bool TagTypeClass::Is_Trigger_Attached(TriggerTypeClass *trigger) const
{
    for (TriggerTypeClass *attached = Triggers; attached != 0; attached = attached->Next) {
        if (attached == trigger) {
            return true;
        }
    }
    return false;
}
