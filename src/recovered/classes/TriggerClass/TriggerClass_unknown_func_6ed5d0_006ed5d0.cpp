// bool TriggerClass::unknown_func_6ed5d0(int value) const (0x006ED5D0)
#include "shared/object.hpp"

bool TriggerClass::unknown_func_6ed5d0(int value) const
{
    if (Next != 0) {
        return Class->unknown_func_6ee240(value) || Next->Class->unknown_func_6ee240(value);
    }
    return Class->unknown_func_6ee240(value);
}
