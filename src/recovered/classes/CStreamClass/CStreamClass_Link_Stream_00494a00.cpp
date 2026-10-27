#include "shared/cstream.hpp"
// @ref _unknown_uuid_IStream_7d5988=007d5988
HRESULT __stdcall CStreamClass::Link_Stream(IUnknown *stream)
{
    if (!stream) return E_POINTER;
    if (Stream) return E_FAIL;
    Stream = stream;
    return S_OK;
}
