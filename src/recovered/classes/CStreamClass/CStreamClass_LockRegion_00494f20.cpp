// HRESULT __stdcall CStreamClass::LockRegion(ULARGE_INTEGER offset, ULARGE_INTEGER size, unsigned long type) -- 0x00494F20
// IStream slot 10: forwards to the held inner stream (E_POINTER through
// _com_issue_error when none is held).
#include "shared/cstream.hpp"

HRESULT __stdcall CStreamClass::LockRegion(ULARGE_INTEGER offset, ULARGE_INTEGER size, unsigned long type)
{
    return Stream->LockRegion(offset, size, type);
}
