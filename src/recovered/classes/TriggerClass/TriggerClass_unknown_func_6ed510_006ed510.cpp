// bool TriggerClass::unknown_func_6ed510() const (0x006ED510)
// TriggerTypeClass::unknown_func_6ee180 of this trigger's type or of any later one.
#include "shared/object.hpp"

bool TriggerClass::unknown_func_6ed510() const
{
    if (Next != 0) {
        return Class->unknown_func_6ee180() || Next->unknown_func_6ed510();
    }
    return Class->unknown_func_6ee180();
}
