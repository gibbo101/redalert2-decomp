// HRESULT __stdcall CStreamClass::UnlockRegion(ULARGE_INTEGER offset, ULARGE_INTEGER size, unsigned long type) -- 0x00494F60
// IStream slot 11: forwards to the held inner stream (E_POINTER through
// _com_issue_error when none is held).
#include "shared/cstream.hpp"

HRESULT __stdcall CStreamClass::UnlockRegion(ULARGE_INTEGER offset, ULARGE_INTEGER size, unsigned long type)
{
    return Stream->UnlockRegion(offset, size, type);
}
