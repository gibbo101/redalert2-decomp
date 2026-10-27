// unsigned long __stdcall ApplicationClass::AddRef() -- 0x00426CE0
// IUnknown slot 1: the application object is static; no reference count.
#include "shared/application.hpp"

unsigned long __stdcall ApplicationClass::AddRef()
{
    return 1;
}
