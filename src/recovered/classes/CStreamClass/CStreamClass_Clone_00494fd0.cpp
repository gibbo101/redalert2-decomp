// HRESULT __stdcall CStreamClass::Clone(IStream **stream) -- 0x00494FD0
// IStream slot 13: forwards to the held inner stream (E_POINTER through
// _com_issue_error when none is held).
#include "shared/cstream.hpp"

HRESULT __stdcall CStreamClass::Clone(IStream **stream)
{
    return Stream->Clone(stream);
}
