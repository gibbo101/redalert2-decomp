// void BulletClass::unknown_func_463bc0() (0x00463BC0)
// Tracks the bullet in BulletClass::Array and updates the type's value by
// how many are tracked.
#include "shared/bullet.hpp"

void BulletClass::unknown_func_463bc0()
{
    Array.Add(this);
    int count = Array.Count() - 5;
    if (count < 0) {
        count = 0;
    }
    Type_View(Type)->Unknown_00465150(Type_View(Type)->unknown_2b4 + count / 3);
}
