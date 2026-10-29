// bool Init_Network_005bc460() (0x005BC460)
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/string_table.hpp"
// @ref ?Set_Bridge@IPXManagerClass@@QAEXQAE@Z=00527730

bool Init_Network_005bc460()
{
    NetNumType net;
    NetNodeType node;

    if (!unknown_ipx_manager_a40978.Init()) {
        return false;
    }
    if (unknown_game_mode_a3d298 != 4 && unknown_dest_net_set_a3f604) {
        unknown_dest_net_a3f608.Get_Address(net, node);
        unknown_ipx_manager_a40978.Set_Bridge(net);
    }
    Init_Lobby_Entries_005c86e0();
    Clear_Slot_Lists_005c8a70();
    Unknown_Reset_Slots_005c8a90();
    return true;
}
