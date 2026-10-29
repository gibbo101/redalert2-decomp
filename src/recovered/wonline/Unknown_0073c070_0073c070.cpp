// bool __fastcall Unknown_0073c070(WOL::User const *user) (0x0073C070)
// Whether a message from user shows: from the channel owner (flag bit 0), with dialog 0xC2 or 0xC9
// open, or else when unknown_b2a7e8 is set; never without a user. The narrow counterpart of
// unknown_can_send_chat 0x0073C0B0 (OnPrivateMessage inlines this test).
#include "shared/wol_sink.hpp"
// @ref ?unknown_b2a7e8@@3HA=00b2a7e8
// @ref ?Unknown_00735940@@YIPAXH@Z=00735940

bool __fastcall Unknown_0073c070(WOL::User const *user)
{
    if (!user) return false;
    if (user->flags & 1) return true;
    if (Unknown_00735940(0xC2)) return true;
    if (Unknown_00735940(0xC9)) return true;
    return unknown_b2a7e8 != 0;
}
