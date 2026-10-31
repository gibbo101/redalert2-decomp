#include "shared/wol_sink.hpp"
#include "shared/session_state.hpp"
void __fastcall Queue_Peer_Timeout_0074e590(int peer)
{
    unknown_session_a3d298.unknown_2f14[unknown_session_a3d298.unknown_2f94]=peer;
    unknown_session_a3d298.unknown_2f34[unknown_session_a3d298.unknown_2f94]=CDTimerClass<SystemTimerClass>(1200);
    ++unknown_session_a3d298.unknown_2f94;
}
