// bool TriggerTypeClass::unknown_func_6ee180() const (0x006EE180)
// Whether the type has an Event of type 0x1A.
#include "shared/object.hpp"

bool TriggerTypeClass::unknown_func_6ee180() const
{
    bool result = false;
    for (TEventClass *item = Events; item != 0; item = item->Next) {
        if (item->Type == 0x1A) {
            result = true;
            break;
        }
    }
    return result;
}
