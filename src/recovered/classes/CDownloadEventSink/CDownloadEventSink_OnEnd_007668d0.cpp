// HRESULT __stdcall CDownloadEventSink::OnEnd() (0x007668D0, slot 3)
// Tells the current dialog the download finished (message 0x5F4).
#include "shared/wol_sink.hpp"
// @ref ?Unknown_00735B10@@YIPAUHWND__@@XZ=00735b10

HRESULT __stdcall CDownloadEventSink::OnEnd()
{
    SendMessageA(Unknown_00735B10(), 0x5F4, 0, 0);
    return S_OK;
}
