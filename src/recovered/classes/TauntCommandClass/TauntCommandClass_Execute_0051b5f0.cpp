// void TauntCommandClass::Execute(int key) const -- 0x0051B5F0
// Sends this taunt to the other players of a network game (modes 3 and 4) at most every five
// seconds: plays it locally, sends the packet to every connection named like a house that is a
// multiplayer house, and, when the router flags are set, to the router's flagged connections.
#define VECTOR_IMPLEMENT_ALL
#include "shared/command.hpp"
#include "shared/house_screen.hpp"
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/owner_talk.hpp"
#include "shared/connection.hpp"
#include "shared/taunt_packet.hpp"
// @ref __imp__timeGetTime@0=0079a524
// @ref ?unknown_taunt_time_7db560@@3KA=007db560
// @ref ?unknown_flag_a3f120@@3_NA=00a3f120
// @ref ?unknown_flag_a3f121@@3_NA=00a3f121
// @ref ?unknown_flags_a3f118@@3PA_NA=00a3f118
// @ref ?unknown_a3d3b4@@3HA=00a3d3b4
// @ref ?unknown_int_a3d548@@3HA=00a3d548
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_flag_a3fba8@@3_NA=00a3fba8
// @ref ?unknown_host_name_a3f618@@3PAGA=00a3f618
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?unknown_ipx_manager_a40978@@3VIPXManagerClass@@A=00a40978
// @ref ?unknown_OwnerTalkClass_00ab6d18@@3VOwnerTalkClass@@A=00ab6d18
// @ref ?Unknown_005bba50@@YIHPAG@Z=005bba50
// @ref ?Unknown_Play_Taunt_00715fb0@@YIXD@Z=00715fb0
// @ref ?Unknown_0063F4C0@OwnerTalkClass@@QAEEH@Z=0063f4c0
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
// @ref _wcscmp=007837d3
// @ref ?Service@IPXManagerClass@@UAEHXZ=00525f60

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern "C" char *__cdecl strcpy(char *destination, char const *source);
#pragma intrinsic(strcpy)
extern "C" int __cdecl wcscmp(unsigned short const *left, unsigned short const *right);

void TauntCommandClass::Execute(int key) const
{
    if (unknown_game_mode_a3d298 != 3 && unknown_game_mode_a3d298 != 4) {
        return;
    }
    if (unknown_int_a3d548 != 0) {
        return;
    }
    unsigned long now = timeGetTime();
    if (unknown_taunt_time_7db560 != 0xFFFFFFFF && (int)(now - unknown_taunt_time_7db560) <= 5000) {
        return;
    }
    if (!((unknown_flag_a3f120 && unknown_game_mode_a3d298 == 3) ||
          (unknown_flag_a3f121 && unknown_game_mode_a3d298 == 4))) {
        return;
    }
    unknown_taunt_time_7db560 = now;
    UnknownTauntPacket packet;
    packet.Type = 0x1D;
    strcpy(packet.Name, Unknown_006FA120(unknown_players_a3fa7c[0]->Name));
    packet.Session = unknown_a3d3b4;
    packet.Checksum = Unknown_005bba50(unknown_host_name_a3f618);
    unsigned char high = unknown_players_a3fa7c[0]->unknown_4b << 4;
    packet.Packed = ((TauntNumber & 0xf) ^ high) & 0xf ^ high;
    Unknown_Play_Taunt_00715fb0(packet.Packed);
    packet.Muted = 0;
    int houses = Houses.Count();
    for (int h = 0; h < houses; h++) {
        HouseClass *house = Houses[h];
        if (house != 0 && house->Type->Multiplay && unknown_flags_a3f118[h]) {
            int connections = unknown_ipx_manager_a40978.Num_Connections();
            for (int c = 0; c < connections; c++) {
                int id = unknown_ipx_manager_a40978.Connection_ID(c);
                if (wcscmp(house->UIName, unknown_ipx_manager_a40978.Connection_Name(id)) == 0) {
                    IPXAddressClass *address = unknown_ipx_manager_a40978.Connection_Address(id);
                    if (unknown_flag_a3fba8) {
                        packet.Muted |= unknown_OwnerTalkClass_00ab6d18.Unknown_0063F4C0(id);
                    } else {
                        unknown_ipx_manager_a40978.Send_Global_Message(&packet, 0x1C7, 1, address, 0, 0);
                        unknown_ipx_manager_a40978.Service();
                    }
                }
            }
        }
    }
    if (unknown_flag_a3fba8 && packet.Muted) {
        unknown_ipx_manager_a40978.Send_Global_Message(&packet, 0x1C7, 1, &unknown_players_a3fa7c[0]->Address, 0, 0);
        unknown_ipx_manager_a40978.Service();
    }
}
