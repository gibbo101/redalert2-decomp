// HRESULT __stdcall CStreamClass::Stat(STATSTG *stat, unsigned long flags) -- 0x00494FA0
// IStream slot 12: forwards to the held inner stream (E_POINTER through
// _com_issue_error when none is held).
#include "shared/cstream.hpp"

HRESULT __stdcall CStreamClass::Stat(STATSTG *stat, unsigned long flags)
{
    return Stream->Stat(stat, flags);
}
