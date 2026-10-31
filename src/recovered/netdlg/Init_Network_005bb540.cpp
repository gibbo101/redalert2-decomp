// @ref ?Set_Bridge@IPXManagerClass@@QAEXQAE@Z=00527730
#include "shared/lobby.hpp"
#include "shared/netdlg.hpp"
#include "shared/ipx_manager.hpp"

// Red Alert's Init_Network as NetDlg.CPP has it (0x005BB540; netdlg2.cpp's copy 0x005BC460 also
// resets the lobby lists).
bool Init_Network_005bb540()
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
    return true;
}
