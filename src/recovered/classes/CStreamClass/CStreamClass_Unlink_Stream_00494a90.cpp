#include "shared/cstream.hpp"
// @ref ?unknown_flush_495000@CStreamClass@@QAEJPAXH@Z=00495000
HRESULT __stdcall CStreamClass::Unlink_Stream(IUnknown **stream)
{
    unknown_flush_pending();
    if (!Stream) return E_FAIL;
    if (stream) {
        Stream->AddRef();
        *stream = Stream;
    }
    HRESULT result = Stream->Commit(0);
    if (SUCCEEDED(result)) {
        Stream.Release();
        result = S_OK;
    }
    return result;
}
