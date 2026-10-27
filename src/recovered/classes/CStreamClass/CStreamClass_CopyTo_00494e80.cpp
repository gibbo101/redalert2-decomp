// HRESULT __stdcall CStreamClass::CopyTo(IStream *stream, ULARGE_INTEGER size, ULARGE_INTEGER *read, ULARGE_INTEGER *written) -- 0x00494E80
// IStream slot 7: forwards to the held inner stream (E_POINTER through
// _com_issue_error when none is held).
#include "shared/cstream.hpp"

HRESULT __stdcall CStreamClass::CopyTo(IStream *stream, ULARGE_INTEGER size, ULARGE_INTEGER *read, ULARGE_INTEGER *written)
{
    return Stream->CopyTo(stream, size, read, written);
}
