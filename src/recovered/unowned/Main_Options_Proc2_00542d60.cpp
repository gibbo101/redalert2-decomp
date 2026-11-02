#define WOL_IDENTIFIER_DECLARE_CLEAR
// Network card, socket, destination-network and firewall options dialog.
#include "shared/main_opt.hpp"
#include "shared/ipx_interface.hpp"
#include "shared/session_state.hpp"
#include "shared/ccini_class.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/wol_chat.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
#include "shared/main_opt_ipx.hpp"
// @ref ?unknown_card_selected_7dfdb8@@3HA=007dfdb8
// @ref ?Clear_005b9e70@WolUnknownIdentifier@@QAEXXZ=005b9e70

int __stdcall Main_Options_Proc2(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int handled = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (handled) return handled;
    int *result = (int *)GetWindowLongA(window, 8);
    char text[16];
    char address[64];
    switch (message) {
    case 0x497:
        {
            HWND cards = GetDlgItem(window, 0x5d4);
            bool temporary = false;
            if (PacketTransport == 0) {
                PacketTransport = new IPXInterfaceClass;
                PacketTransport->Init();
                temporary = true;
            }
            if (PacketTransport != 0) {
                Debug_Printf("Creating IPX Interface\n");
                IPXInterfaceClass *transport = (IPXInterfaceClass *)PacketTransport;
                for (int card = 0; card < 20; ++card) {
                    if (transport->unknown_76a230(card, address, 64)) {
                        Debug_Printf("Got address for network card %d\n", card);
                        Debug_Printf("Address is %s\n", address);
                        if (SendMessageA(cards, 0x4b8, 0, (LPARAM)address) == -1) {
                            SendMessageA(cards, 0x4bc, 0, (LPARAM)address);
                        }
                    }
                }
            }
            if (temporary) {
                delete PacketTransport;
                PacketTransport = 0;
            }
            if (SendMessageA(cards, 0x146, 0, 0) == 0) {
                SendMessageA(cards, 0x4c2, 0, (LPARAM)StringTable::Load_String("TXT_NO_BOUND_NET_CARD", 0, "D:\\Ra2\\MainOpt.cpp", 886));
            }
            int selected = Options.NetCard;
            if (selected < 0 || selected >= SendMessageA(cards, 0x146, 0, 0)) selected = 0;
            SendMessageA(cards, 0x14e, selected, 0);
            SendMessageA(window, 0x464, 0, 0);
            unknown_card_selected_7dfdb8 = -1;
            HWND socket = GetDlgItem(window, 0x5d1);
            if (Options.Socket != 0xffff) {
                sprintf(text, "%d", Options.Socket);
                SendMessageA(socket, 0x4b4, 0, (LPARAM)text);
            }
            SendMessageA(socket, 0xc5, 5, 0);
            HWND destination = GetDlgItem(window, 0x5d3);
            if (strlen(Options.DestNet)) SendMessageA(destination, 0x4b4, 0, (LPARAM)Options.DestNet);
            SendMessageA(destination, 0xc5, 11, 0);
            if (unknown_session_a3d298.SendDelay)
                SendDlgItemMessageA(window, 0x762, 0xf1, 1, 0);
            else
                SendDlgItemMessageA(window, 0x762, 0xf1, 0, 0);
            HWND port = GetDlgItem(window, 0x5d7);
            if (port != (HWND)-1 && unknown_session_a3d298.PortNumberOverride != 0) {
                sprintf(text, "%d", unknown_session_a3d298.PortNumberOverride);
                SendMessageA(port, 0x4b4, 0, (LPARAM)text);
            }
        }
        break;
    case 0x111:
        switch (wparam & 0xffff) {
        case 1:
            {
                HWND socket_control = GetDlgItem(window, 0x5d1);
                SendMessageA(socket_control, 0x4b5, 16, (LPARAM)text);
                unsigned short socket;
                if (strlen(text)) {
                    socket = (unsigned short)atoi(text);
                    if (strlen(text) > 5 || socket > 0x3fff) {
                        WWMessageBox((unsigned short const *)L" ").Process(StringTable::Load_String("TXT_INVALID_SOCKET",0,"D:\\Ra2\\MainOpt.cpp",975),
                                    StringTable::Load_String("TXT_OK",0,"D:\\Ra2\\MainOpt.cpp",975),0,0,false);
                        return 0;
                    }
                } else socket = 0xffff;
                char destination[32];
                char saved_destination[32];
                HWND destination_control = GetDlgItem(window, 0x5d3);
                SendMessageA(destination_control, 0x4b5, 32, (LPARAM)destination);
                strncpy(saved_destination, destination, 32);
                if (strlen(destination)) {
                    char *token = strtok(destination, ".");
                    int network[4] = {-1,-1,-1,-1};
                    if (token) {
                        int *part = network;
                        do {
                            sscanf(token, "%x", part);
                            ++part;
                            token = strtok(0, ".");
                        } while (token);
                    }
                    if ((network[0] & 255) != network[0] || (network[1] & 255) != network[1] ||
                        (network[2] & 255) != network[2] || (network[3] & 255) != network[3]) {
                        WWMessageBox((unsigned short const *)L" ").Process(StringTable::Load_String("TXT_DESTNET_ADDR_ERROR",0,"D:\\Ra2\\MainOpt.cpp",1009),
                                    StringTable::Load_String("TXT_OK",0,"D:\\Ra2\\MainOpt.cpp",1009),0,0,false);
                        return 0;
                    }
                }
                HWND card_control = GetDlgItem(window, 0x5d4);
                Options.NetCard = SendMessageA(card_control, 0x147, 0, 0);
                Options.Socket = socket;
                strcpy(Options.DestNet, saved_destination);
                HWND port_control = GetDlgItem(window, 0x5d7);
                char port_text[32];
                memset(port_text, 0, sizeof(port_text));
                SendMessageA(port_control, 0x4b5, 8, (LPARAM)port_text);
                strncpy(address, port_text, 32);
                int port = atoi(address);
                if (port > 65535) {
                    WWMessageBox((unsigned short const *)L" ").Process(StringTable::Load_String("TXT_PORT_NUMBER_ERROR",0,"D:\\Ra2\\MainOpt.cpp",1050),
                                StringTable::Load_String("TXT_OK",0,"D:\\Ra2\\MainOpt.cpp",1050),0,0,false);
                    return 0;
                }
                if (SendDlgItemMessageA(window, 0x762, 0xf0, 0, 0) == 1) {
                    if (!unknown_session_a3d298.SendDelay) {
                        WWMessageBox((unsigned short const *)L" ").Process(StringTable::Load_String("TXT_FIREWALL_SETTINGS_WARNING1",0,"D:\\Ra2\\MainOpt.cpp",1059),
                                    StringTable::Load_String("TXT_OK",0,"D:\\Ra2\\MainOpt.cpp",1059),0,0,false);
                    }
                    unknown_session_a3d298.SendDelay = true;
                } else unknown_session_a3d298.SendDelay = false;
                if (port > 0 && unknown_session_a3d298.PortNumberOverride == 0) {
                    WWMessageBox((unsigned short const *)L" ").Process(StringTable::Load_String("TXT_FIREWALL_SETTINGS_WARNING2",0,"D:\\Ra2\\MainOpt.cpp",1070),
                                StringTable::Load_String("TXT_OK",0,"D:\\Ra2\\MainOpt.cpp",1070),0,0,false);
                }
                unknown_session_a3d298.PortNumberOverride = port;
                unknown_identifier_a71b18.Clear_005b9e70();
                RawFileClass settings("RA2.INI");
                unknown_ini_839740.Put_Bool("MultiPlayer", "SendDelay", unknown_session_a3d298.SendDelay);
                unknown_ini_839740.Put_Int("MultiPlayer", "PortNumberOverride", unknown_session_a3d298.PortNumberOverride, 0);
                unknown_ini_839740.Save(settings, false);
            }
            // The OK path closes through the same result as Cancel.
        case 2:
            *result = 2;
            break;
        case 0x5d4:
            {
                HWND card_control = GetDlgItem(window, 0x5d4);
                unknown_card_selected_7dfdb8 = SendMessageA(card_control, 0x147, 0, 0);
            }
            break;
        }
        break;
    case 0x4db:
        Unknown_005def80(lparam, wparam != 0);
        return 0;
    }
    return 0;
}

// @ref ??_C@_0BP@PELD@TXT_FIREWALL_SETTINGS_WARNING2?$AA@=007dfe24
// @ref ??_C@_0BP@LAK@TXT_FIREWALL_SETTINGS_WARNING1?$AA@=007dfe44
// @ref ??_C@_0BG@JOJD@TXT_PORT_NUMBER_ERROR?$AA@=007dfe64
// @ref ??_C@_0BH@HNGG@TXT_DESTNET_ADDR_ERROR?$AA@=007dfe7c
// @ref ??_C@_0BD@PKGD@TXT_INVALID_SOCKET?$AA@=007dfe94
// @ref ??_C@_0BG@JFP@TXT_NO_BOUND_NET_CARD?$AA@=007dfea8
// @ref ??_C@_0P@CJFA@Address?5is?5?$CFs?6?$AA@=007dfec0
// @ref ??_C@_0CB@MILL@Got?5address?5for?5network?5card?5?$CFd?6@=007dfed0
// @ref ??_C@_0BI@CKHD@Creating?5IPX?5Interface?6?$AA@=007dfef4

// @ref ??_C@_01PJCK@?4?$AA@=007dbe44
// @ref ??_C@_02JDLK@?$CFx?$AA@=007db4b4
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_07IBND@RA2?4INI?$AA@=007db8b8
// @ref ??_C@_09OJJN@SendDelay?$AA@=007dfe18
// @ref ??_C@_0BD@JACO@PortNumberOverride?$AA@=007dfe04
// @ref ??_C@_0BD@OMLL@D?3?2Ra2?2MainOpt?4cpp?$AA@=007dfde0
// @ref ??_C@_0M@MLEF@MultiPlayer?$AA@=007dbce4
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
