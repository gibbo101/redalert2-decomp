// unsigned long __stdcall ApplicationClass::Release() -- 0x00426CF0
// IUnknown slot 2: the application object is static; never deleted.
#include "shared/application.hpp"

unsigned long __stdcall ApplicationClass::Release()
{
    return 1;
}
