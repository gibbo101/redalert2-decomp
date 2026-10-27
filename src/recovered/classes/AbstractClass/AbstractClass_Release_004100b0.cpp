// unsigned long __stdcall AbstractClass::Release() (0x004100B0)
// IUnknown: no reference counting (always 1).
#include "shared/abstract.hpp"

unsigned long __stdcall AbstractClass::Release()
{
    return 1;
}
