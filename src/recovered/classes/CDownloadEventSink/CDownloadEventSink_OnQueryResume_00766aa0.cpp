// HRESULT __stdcall CDownloadEventSink::OnQueryResume() (0x00766AA0, slot 6)
// Always S_OK.
#include "shared/wol_sink.hpp"

HRESULT __stdcall CDownloadEventSink::OnQueryResume()
{
    return S_OK;
}
