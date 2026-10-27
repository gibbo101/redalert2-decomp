// bool TriggerClass::unknown_func_6ed550() const (0x006ED550)
// TriggerTypeClass::unknown_func_6ee1e0 of this trigger's type or the next one's.
#include "shared/object.hpp"

bool TriggerClass::unknown_func_6ed550() const
{
    if (Next != 0) {
        return Class->unknown_func_6ee1e0() || Next->Class->unknown_func_6ee1e0();
    }
    return Class->unknown_func_6ee1e0();
}
