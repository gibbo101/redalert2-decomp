// HRESULT __stdcall CStreamClass::Seek(LARGE_INTEGER, unsigned long, ULARGE_INTEGER *) -- 0x00494DE0
// IStream slot 5: refused (E_FAIL) while either state flag is set,
// otherwise forwarded to the inner stream.
#include "shared/cstream.hpp"

HRESULT __stdcall CStreamClass::Seek(LARGE_INTEGER move, unsigned long origin, ULARGE_INTEGER *position)
{
    if (unknown_10 || unknown_11) {
        return E_FAIL;
    }
    return Stream->Seek(move, origin, position);
}
