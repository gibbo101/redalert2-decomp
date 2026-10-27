// bool TagTypeClass::unknown_func_6b4c30() const (0x006B4C30)
// Whether any trigger type answers TriggerTypeClass::unknown_func_6ee210.
#include "shared/object.hpp"

bool TagTypeClass::unknown_func_6b4c30() const
{
    for (TriggerTypeClass *trigger = Triggers; trigger != 0; trigger = trigger->Next) {
        if (trigger->unknown_func_6ee210()) {
            return true;
        }
    }
    return false;
}
