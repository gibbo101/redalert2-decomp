// HRESULT __stdcall CChatEventSink::OnChannelLeave(HRESULT result, WOL::Channel *channel, WOL::User *user) (0x00760BD0, slot 11)
// Logs failures; otherwise passes the leaving user to 0x00741750.
#include "shared/wol_sink.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Unknown_00741750@@YIXPAUUser@WOL@@@Z=00741750

HRESULT __stdcall CChatEventSink::OnChannelLeave(HRESULT result, WOL::Channel *channel, WOL::User *user)
{
    if (result < 0) {
        Debug_Printf("OnChannelLeave with error!\n");
        return S_OK;
    }
    Unknown_00741750(user);
    return S_OK;
}
// @ref ??_C@_0BM@CBD@OnChannelLeave?5with?5error?$CB?6?$AA@=007fde84
