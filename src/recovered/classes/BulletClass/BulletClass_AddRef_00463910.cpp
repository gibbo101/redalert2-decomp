// unsigned long __stdcall BulletClass::AddRef() (0x00463910)
// Bullets are reference counted COM objects.
#include "shared/bullet.hpp"

unsigned long __stdcall BulletClass::AddRef()
{
    unknown_com_objects_a6eb14++;
    return InterlockedIncrement(&RefCount);
}
