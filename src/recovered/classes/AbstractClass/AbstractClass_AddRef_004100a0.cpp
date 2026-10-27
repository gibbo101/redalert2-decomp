// unsigned long __stdcall AbstractClass::AddRef() (0x004100A0)
// IUnknown: no reference counting (always 1).
#include "shared/abstract.hpp"

unsigned long __stdcall AbstractClass::AddRef()
{
    return 1;
}
