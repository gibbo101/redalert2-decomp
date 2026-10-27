// bool TagTypeClass::unknown_func_6b4cc0() const (0x006B4CC0)
// Whether any trigger type answers TriggerTypeClass::unknown_func_6ee1e0.
#include "shared/object.hpp"

bool TagTypeClass::unknown_func_6b4cc0() const
{
    for (TriggerTypeClass *trigger = Triggers; trigger != 0; trigger = trigger->Next) {
        if (trigger->unknown_func_6ee1e0()) {
            return true;
        }
    }
    return false;
}
