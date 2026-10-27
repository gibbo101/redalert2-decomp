// unsigned long __stdcall CStreamClass::Release() -- 0x00494930
// Drops a reference; the last one deletes the stream (IUnknown slot 2).
#include "shared/cstream.hpp"
// @ref ?unknown_com_objects_a6eb14@@3JA=00a6eb14
// @ref __imp__InterlockedDecrement@4=0079a1c0

unsigned long __stdcall CStreamClass::Release()
{
    unknown_com_objects_a6eb14--;
    long count = InterlockedDecrement(&RefCount);
    if (count == 0) {
        delete this;
    }
    return count;
}
