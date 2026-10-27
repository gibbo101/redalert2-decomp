// int BulletClass::unknown_slot29() const (0x00461BF0)
// The display layer: 1 for types with +0x2C7 set, else 3.
#include "shared/bullet.hpp"

int BulletClass::unknown_slot29() const
{
    return Type_View(Type)->unknown_2c7 ? 1 : 3;
}
