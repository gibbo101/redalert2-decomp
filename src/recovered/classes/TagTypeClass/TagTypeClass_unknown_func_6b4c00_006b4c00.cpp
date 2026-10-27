// int TagTypeClass::unknown_func_6b4c00() const (0x006B4C00)
// The combined flags of the type's trigger types.
#include "shared/object.hpp"

int TagTypeClass::unknown_func_6b4c00() const
{
    int flags = 0;
    for (TriggerTypeClass *trigger = Triggers; trigger != 0; trigger = trigger->Next) {
        flags |= trigger->unknown_func_6ee410();
    }
    return flags;
}
