// bool TagTypeClass::unknown_func_6b4c60() const (0x006B4C60)
// Whether any trigger type answers TriggerTypeClass::unknown_func_6ee1b0.
#include "shared/object.hpp"

bool TagTypeClass::unknown_func_6b4c60() const
{
    for (TriggerTypeClass *trigger = Triggers; trigger != 0; trigger = trigger->Next) {
        if (trigger->unknown_func_6ee1b0()) {
            return true;
        }
    }
    return false;
}
