// bool BombClass::Unknown_00436070() const (0x00436070): whether a timed bomb
// (type 0) has reached its frame without being disarmed.
#include "shared/object.hpp"
// @ref ?Frame@@3HA=00a40d2c

bool BombClass::Unknown_00436070() const
{
    if (Type == 0 && Frame > unknown_38 && !unknown_58) {
        return true;
    }
    return false;
}
