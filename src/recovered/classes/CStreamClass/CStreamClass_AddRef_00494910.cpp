// unsigned long __stdcall CStreamClass::AddRef() -- 0x00494910
// Counts a live COM object and a reference (IUnknown slot 1).
#include "shared/cstream.hpp"
// @ref ?unknown_com_objects_a6eb14@@3JA=00a6eb14
// @ref __imp__InterlockedIncrement@4=0079a1bc

unsigned long __stdcall CStreamClass::AddRef()
{
    unknown_com_objects_a6eb14++;
    return InterlockedIncrement(&RefCount);
}
