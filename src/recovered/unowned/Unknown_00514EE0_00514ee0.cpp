// bool Unknown_00514EE0() -- 0x00514EE0
// Purpose: resets the network layer before a LAN or internet game: replaces the
// packet transport with a UDP interface, restarts listening, clears the session's
// connection tables and steps PortBase, then saves PortBase/PortPool to RA2.INI.
// Returns the result of 0x005BB540 (hypothesis: the network code initialised).
// @ref ??_C@_07IBND@RA2?4INI?$AA@=007db8b8
// @ref ??_C@_08CLJJ@PortPool?$AA@=007dbcd8
// @ref ??_C@_08DDKG@PortBase?$AA@=007dbcf0
// @ref ??_C@_0CG@DJMM@About?5to?5initialise?5the?5network?5@=007dbcfc
// @ref ??_C@_0M@MLEF@MultiPlayer?$AA@=007dbce4
// @ref ?Unknown_0063F070@OwnerTalkClass@@QAEXXZ=0063f070
// @ref ?Unknown_005BB540@@YI_NXZ=005bb540
// @ref ?unknown_a71b28@@3HA=00a71b28
#include "shared/session_state.hpp"
#include "shared/house_type.hpp"
#include "shared/ccini_class.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/udp_interface.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/owner_talk.hpp"
#include "shared/lobby.hpp"
#include "shared/crt_memory.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_globals.hpp"

extern int unknown_a71b28;                  // 0x00A71B28 RA2.INI [MultiPlayer] PortPool
bool __fastcall Unknown_005BB540();

bool __fastcall Unknown_00514EE0()
{
    if (PacketTransport != 0) {
        delete PacketTransport;
        PacketTransport = 0;
    }
    for (int house = 0; house < HouseTypes.Count(); house++) {
        HouseTypes[house]->Read_INI(*unknown_ini_8396d0);
    }
    if (PacketTransport == 0) {
        PacketTransport = new UDPInterfaceClass;
    }
    unknown_session_a3d2ac = 2;
    PacketTransport->unknown_slot15(0);
    unknown_ipx_manager_a40978.Set_Timing(30, -1, 600, true);
    Debug_Printf("About to initialise the network code\n");
    bool result = Unknown_005BB540();
    PacketTransport->Start_Listening();
    memset(&unknown_session_a3d298.unknown_3022, 0, sizeof(unknown_session_a3d298.unknown_3022));
    unknown_session_a3d298.unknown_3020 = false;
    unknown_session_a3d298.unknown_3014 = false;
    unknown_session_a3d298.unknown_292c = 0;
    unknown_session_a3d298.unknown_3016 = 0;
    unknown_session_a3d298.unknown_3034 = 0;
    unknown_session_a3d298.unknown_303c = -1;
    unknown_session_a3d298.unknown_3044 = 20;
    unknown_session_a3d298.unknown_3048 = 0;
    unknown_session_a3d298.unknown_304c = 0;
    unknown_session_a3d298.unknown_3050 = -1;
    memset(unknown_session_a3d298.unknown_29bc, 0, sizeof(unknown_session_a3d298.unknown_29bc));
    memset(unknown_session_a3d298.unknown_2bbc, -1, sizeof(unknown_session_a3d298.unknown_2bbc));
    memset(unknown_session_a3d298.unknown_2dc0, 0, sizeof(unknown_session_a3d298.unknown_2dc0));
    memset(&unknown_session_a3d298.unknown_2fa0, 0, sizeof(unknown_session_a3d298.unknown_2fa0));
    unknown_session_a3d298.unknown_2dbc = 0;
    if (unknown_session_a3d298.unknown_2f9c != 0) {
        unknown_session_a3d298.PortBase = unknown_session_a3d298.unknown_2f9c;
    } else if (unknown_session_a3d298.unknown_2fc0) {
        unknown_session_a3d298.PortBase += 5;
        if (unknown_session_a3d298.PortBase >= 1750) {
            unknown_session_a3d298.PortBase = 1250;
        }
        unknown_session_a3d298.unknown_2fc0 = false;
    }
    RawFileClass file("RA2.INI");
    unknown_ini_839740.Put_Int("MultiPlayer", "PortBase", unknown_session_a3d298.PortBase);
    unknown_ini_839740.Put_Int("MultiPlayer", "PortPool", unknown_a71b28);
    unknown_ini_839740.Save(file, false);
    unknown_OwnerTalkClass_00ab6d18.Unknown_0063F070();
    unknown_session_a3f616 = true;
    return result;
}
