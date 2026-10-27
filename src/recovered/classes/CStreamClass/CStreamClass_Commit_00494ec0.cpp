// HRESULT __stdcall CStreamClass::Commit(unsigned long flags) -- 0x00494EC0
// IStream slot 8: forwards to the held inner stream (E_POINTER through
// _com_issue_error when none is held).
#include "shared/cstream.hpp"

HRESULT __stdcall CStreamClass::Commit(unsigned long flags)
{
    return Stream->Commit(flags);
}
