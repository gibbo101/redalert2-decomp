// bool TriggerTypeClass::unknown_func_6ee280(int value) const (0x006EE280)
// Whether the type has an event of type 0x24 or 0x25 with this data.
#include "shared/object.hpp"

bool TriggerTypeClass::unknown_func_6ee280(int value) const
{
    bool result = false;
    for (TEventClass *event = Events; event != 0; event = event->Next) {
        if ((event->Type == 0x24 || event->Type == 0x25) && event->Data == value) {
            result = true;
            break;
        }
    }
    return result;
}
