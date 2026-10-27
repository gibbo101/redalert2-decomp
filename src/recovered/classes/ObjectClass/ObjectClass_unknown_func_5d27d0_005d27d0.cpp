// bool ObjectClass::unknown_func_5d27d0(char const *name) const (0x005D27D0)
#include "shared/object_type.hpp"

bool ObjectClass::unknown_func_5d27d0(char const *name) const
{
    return *Class_Of() == name;
}
