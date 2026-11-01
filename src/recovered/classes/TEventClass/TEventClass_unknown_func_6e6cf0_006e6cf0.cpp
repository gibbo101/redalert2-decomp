// bool TEventClass::unknown_func_6e6cf0() const (0x006E6CF0)
// TS's TEventClass::Is_Time_Based: the events that fire only when the caller
// reports them (TriggerClass::Spring 0x006ED740 marks them).
#include "shared/object.hpp"

bool TEventClass::unknown_func_6e6cf0() const
{
    switch (Type) {
    case 0x01:
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x06:
    case 0x07:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x1D:
    case 0x1F:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x2B:
    case 0x2C:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x35:
    case 0x36:
        return true;
    }
    return false;
}
