// HRESULT __stdcall CStreamClass::SetSize(ULARGE_INTEGER) -- 0x00494E30
// IStream slot 6: refused (E_FAIL) while either state flag is set,
// otherwise forwarded to the inner stream.
#include "shared/cstream.hpp"

HRESULT __stdcall CStreamClass::SetSize(ULARGE_INTEGER size)
{
    if (unknown_10 || unknown_11) {
        return E_FAIL;
    }
    return Stream->SetSize(size);
}
