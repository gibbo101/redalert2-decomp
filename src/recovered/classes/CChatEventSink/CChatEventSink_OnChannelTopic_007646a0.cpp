// HRESULT __stdcall CChatEventSink::OnChannelTopic(HRESULT result, WOL::Channel *channel, char const *topic) (0x007646A0, slot 12)
// Ignored.
#include "shared/wol_sink.hpp"

HRESULT __stdcall CChatEventSink::OnChannelTopic(HRESULT result, WOL::Channel *channel, char const *topic)
{
    return S_OK;
}
