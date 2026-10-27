// bool TriggerClass::unknown_func_6ed4d0() const (0x006ED4D0)
// TriggerTypeClass::unknown_func_6ee1b0 of this trigger's type or of any later one.
#include "shared/object.hpp"

bool TriggerClass::unknown_func_6ed4d0() const
{
    if (Next != 0) {
        return Class->unknown_func_6ee1b0() || Next->unknown_func_6ed4d0();
    }
    return Class->unknown_func_6ee1b0();
}
