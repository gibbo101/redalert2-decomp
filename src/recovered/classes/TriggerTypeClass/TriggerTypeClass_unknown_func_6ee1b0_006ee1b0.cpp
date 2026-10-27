// bool TriggerTypeClass::unknown_func_6ee1b0() const (0x006EE1B0)
// Whether the type has an Event of type 0x19.
#include "shared/object.hpp"

bool TriggerTypeClass::unknown_func_6ee1b0() const
{
    bool result = false;
    for (TEventClass *item = Events; item != 0; item = item->Next) {
        if (item->Type == 0x19) {
            result = true;
            break;
        }
    }
    return result;
}
