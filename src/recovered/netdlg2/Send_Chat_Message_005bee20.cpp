// void __fastcall Send_Chat_Message_005bee20(HWND dialog, int color, int unknown) (0x005BEE20)
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/taunt_packet.hpp"
// @ref ?unknown_chat_a3fa4c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa4c
// @ref ?unknown_join_state_a71e94@@3HA=00a71e94
// @ref ??_C@_1BA@FNA@?$AA?$FL?$AA?$CF?$AAs?$AA?$FN?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007e1e78
// @ref ??_C@_11A@?$AA?$AA@=00839d4c

void __fastcall Send_Chat_Message_005bee20(HWND dialog, int color, int unknown)
{
    wchar_t text[112];

    HWND edit = GetDlgItem(dialog, 0x540);
    SendMessageA(edit, 0x4B3, 0x6F, (LPARAM)text);
    text[0x6F] = 0;
    int length = wcslen(text);
    edit = GetDlgItem(dialog, 0x540);
    SendMessageA(edit, 0x4B2, 0, (LPARAM)L"");
    InvalidateRect(dialog, 0, 1);
    if (length > 2) {
        Unknown_005C2C80(color, L"[%s] %s", Unknown_006FA180(unknown_name_a3d3a0), text);
        UnknownGlobalPacket packet;
        memset(&packet, 0, sizeof(packet));
        packet.Command = 12;
        strcpy(packet.Name, unknown_name_a3d3a0);
        wcscpy(packet.Message.Buf, text);
        packet.Message.unknown_110 = unknown;
        packet.Message.unknown_114 = Unknown_005bba50(unknown_host_name_a3f618);
        if (unknown_join_state_a71e94 == 2) {
            int count = unknown_players_a3fa7c.Count();
            for (int i = 1; i < count; i++) {
                unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_players_a3fa7c[i]->Address, 0, 0);
                Service_Game_IO_00481fb0();
            }
        } else {
            int count = unknown_chat_a3fa4c.Count();
            for (int i = 1; i < count; i++) {
                unknown_ipx_manager_a40978.Send_Global_Message(&packet, sizeof(packet), 1, &unknown_chat_a3fa4c[i]->Address, 0, 0);
                Service_Game_IO_00481fb0();
            }
        }
    }
}
