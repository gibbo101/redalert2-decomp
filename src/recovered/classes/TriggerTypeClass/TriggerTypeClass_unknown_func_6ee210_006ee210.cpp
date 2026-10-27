// bool TriggerTypeClass::unknown_func_6ee210() const (0x006EE210)
// Whether the type has an Action of type 0xF.
#include "shared/object.hpp"

bool TriggerTypeClass::unknown_func_6ee210() const
{
    bool result = false;
    for (TActionClass *item = Actions; item != 0; item = item->Next) {
        if (item->Type == 0xF) {
            result = true;
            break;
        }
    }
    return result;
}
