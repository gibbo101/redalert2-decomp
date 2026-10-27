// bool TEventClass::unknown_func_6e6d50() const (0x006E6D50)
#include "shared/object.hpp"

bool TEventClass::unknown_func_6e6d50() const
{
    switch (Type) {
    case 1:
    case 6:
    case 0x2C:
        return false;
    }
    return true;
}
