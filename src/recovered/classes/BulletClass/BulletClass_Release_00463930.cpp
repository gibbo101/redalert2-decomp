// unsigned long __stdcall BulletClass::Release() (0x00463930)
#include "shared/bullet.hpp"

unsigned long __stdcall BulletClass::Release()
{
    unknown_com_objects_a6eb14--;
    long count = InterlockedDecrement(&RefCount);
    if (count == 0) {
        delete this;
    }
    return count;
}
