// void __fastcall Reject_Join_005bc3e0(NodeNameType *node) (0x005BC3E0)
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/string_table.hpp"
// @ref ?unknown_gpacket_a3f640@@3UUnknownGlobalPacket@@A=00a3f640

void __fastcall Reject_Join_005bc3e0(NodeNameType *node)
{
    memset(&unknown_gpacket_a3f640, 0, sizeof(unknown_gpacket_a3f640));
    unknown_gpacket_a3f640.Command = 8;
    unknown_gpacket_a3f640.Reject.Why = 4;
    unknown_ipx_manager_a40978.Send_Global_Message(&unknown_gpacket_a3f640, sizeof(unknown_gpacket_a3f640), 1, &node->Address, 0, 0);
}
