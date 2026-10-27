// HRESULT __stdcall CStreamClass::Revert() -- 0x00494EF0
// IStream slot 9: forwards to the held inner stream (E_POINTER through
// _com_issue_error when none is held).
#include "shared/cstream.hpp"

HRESULT __stdcall CStreamClass::Revert()
{
    return Stream->Revert();
}
