// HRESULT __stdcall CDownloadEventSink::OnError(int error) (0x007668F0, slot 4)
// Tells the current dialog the download failed (message 0x5F5, the error).
#include "shared/wol_sink.hpp"
// @ref ?Unknown_00735B10@@YAPAUHWND__@@XZ=00735b10

HRESULT __stdcall CDownloadEventSink::OnError(int error)
{
    SendMessageA(Unknown_00735B10(), 0x5F5, 0, error);
    return S_OK;
}
