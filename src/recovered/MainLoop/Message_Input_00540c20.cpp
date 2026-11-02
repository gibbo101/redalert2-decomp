// void __fastcall Message_Input(int &input) (0x00540C20; Westwood's Message_Input): feeds the
// IME result string to the message edit line; in a multiplayer game Return, Backspace or '\' opens
// the chat edit line (or the beacon text edit line while a beacon is being placed); passes the
// key to the edit line, mirrors it to the edited beacon, and on a send (3, or 4 with overflow)
// sends the text to the modem peer, as a WOL page or reply, or to the chosen players.
#include "shared/main_loop.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/session_state.hpp"
#include "shared/string_table.hpp"
#include "shared/keyboard.hpp"
#include "shared/win_stub.hpp"
#include "shared/gscreen.hpp"
#include "shared/map_view.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/gadget.hpp"
#include "shared/text_label.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/owner_talk.hpp"
#include "shared/null_modem.hpp"
#include "shared/connection.hpp"
#include "shared/name_crc.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/debug_printf.hpp"

// @ref ??_C@_0BJ@PHJC@Sending?5chat?0?5mask?5?$DN?5?$CFd?6?$AA@=007dfbb0
// @ref ??_C@_0BH@EPE@TXT_OBSERVER_CANT_SEND?$AA@=007dfbcc
// @ref ??_C@_0BH@IEJM@TXT_NAME_NOT_SPECIFIED?$AA@=007dfbe4
// @ref ??_C@_0BI@GNCH@TXT_REPLY_COMMAND_SHORT?$AA@=007dfbfc
// @ref ??_C@_0BC@MKF@TXT_REPLY_COMMAND?$AA@=007dfc14
// @ref ??_C@_1BA@EBBI@?$AA?$CF?$AAs?$AA?$CF?$AAs?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007dfc28
// @ref ??_C@_1BA@EKIK@?$AA?$CF?$AAs?$AA?5?$AA?$DO?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007dfc38
// @ref ??_C@_0BJ@IBBF@TXT_CANT_SEND_BLANK_PAGE?$AA@=007dfc48
// @ref ??_C@_0BG@BNFA@TXT_NO_NAME_SPECIFIED?$AA@=007dfc64
// @ref ??_C@_0BB@OKDD@TXT_PAGE_COMMAND?$AA@=007dfc7c
// @ref ??_C@_08JLKA@TXT_FROM?$AA@=007dfc90
// @ref ??_C@_0BD@PBOC@TXT_BEACON_MESSAGE?$AA@=007dfc9c
// @ref ??_C@_0BE@ECPO@D?3?2Ra2?2MainLoop?4CPP?$AA@=007dfcb0
// @ref ??_C@_01NON@_?$AA@=007cf730
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ??_C@_1M@EOJM@?$AA?$CF?$AAs?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007dc0d0
// @ref ?Get_Edit_Buf@MessageListClass@@QAEPAGXZ=005b55e0
// @ref ?Unknown_0042E940@Unknown84E8D0@@QAEPAVUnknownBeacon@@H@Z=0042e940
// @ref ?Unknown_0042EC20@Unknown84E8D0@@QAEXPBGHH_N@Z=0042ec20
// @ref ?unknown_chat_target_a6ebe0@@3HA=00a6ebe0

extern "C" wchar_t *__cdecl wcsncat(wchar_t *destination, wchar_t const *source, unsigned int count);
extern "C" int __cdecl wcsncmp(wchar_t const *a, wchar_t const *b, unsigned int count);
extern "C" int __cdecl wcscmp(wchar_t const *a, wchar_t const *b);
extern "C" char *__cdecl strcpy(char *destination, char const *source);
#pragma intrinsic(strcpy)
extern NullModemClass serial_manager_00a40a28;     // 0x00A40A28 (also shared/serial_progress.hpp)

void __fastcall Message_Input(int &input)
{
    int rc;
    int i;
    int count;
    wchar_t name[16];
    wchar_t command[64];
    wchar_t command2[64];
    wchar_t edit[162];
    wchar_t message[224];
    wchar_t prefix[112];
    wchar_t rest[224];
    wchar_t txt[224];

    int len = wcslen(IMEResultString);
    if (len) {
        int key = 0;
        for (int k = 0; k < len; k++) {
            unknown_session_a3d298.Messages.Input(key, IMEResultString[k]);
        }
        IMEResultString[0] = 0;
    }

    if (input == 0) {
        return;
    }

    if (unknown_session_a3d298.Type != 0 && unknown_session_a3d298.Type != 5 && !unknown_session_a3d298.Messages.IsEdit) {
        if (input & 0x8000) {
            return;
        }
        int ascii = (unsigned char)Main_Loop_To_ASCII(WWKeyboard, input);
        if (ascii == '\r' || ascii == '\\' || ascii == '\b') {
            txt[0] = 0;
            bool beacon = unknown_object_84e8d0.Unknown_0042E940(unknown_player_a35db4->ArrayIndex) != 0;
            if (beacon) {
                swprintf(txt, StringTable::Load_String("TXT_BEACON_MESSAGE", 0, "D:\\Ra2\\MainLoop.CPP", 1796));
            } else {
                swprintf(txt, StringTable::Load_String("TXT_FROM", 0, "D:\\Ra2\\MainLoop.CPP", 1798), unknown_player_a35db4->UIName);
                if (ascii == '\r') {
                    unknown_chat_target_a6ebe0 = 1;
                } else if (ascii == '\\') {
                    unknown_chat_target_a6ebe0 = 3;
                } else if (ascii == '\b') {
                    unknown_chat_target_a6ebe0 = 2;
                }
            }
            input = 0;
            int color = unknown_session_a3d298.Unknown_006715D0(unknown_a3d3b4);
            TextLabelClass *label = unknown_session_a3d298.Messages.Add_Edit(color, 0x4046, txt, 0, beacon ? 10000 : -1);
            if (beacon) {
                if (label) {
                    label->IsHidden = true;
                }
                unknown_session_a3d298.Messages.unknown_18 = false;
                wcscpy(name, Unknown_006FA180("_"));
                unknown_object_84e8d0.Unknown_0042EC20(name, -1, -1, false);
            } else {
                unknown_session_a3d298.Messages.unknown_18 = true;
            }
            Map.Flag_To_Redraw(false);
            IMEResultString[0] = 0;
        }
    }

    int copy_input = input;
    rc = unknown_session_a3d298.Messages.Input(input, 0);

    if (rc == 1 && unknown_session_a3d298.Type != 0) {
        Map.Flag_To_Redraw(false);
    } else if (rc == 2 && unknown_session_a3d298.Type != 0) {
        if (copy_input == 0x1B) {
            Map.Flag_To_Redraw(2);
            unknown_chat_target_a6ebe0 = 0;
        } else {
            Map.Flag_To_Redraw(false);
        }
    }

    if ((unknown_object_84e8d0.Unknown_0042E940(unknown_player_a35db4->ArrayIndex) && copy_input && rc == 1) || rc == 2 || rc == 4 || IMEComposing) {
        if (copy_input == 0x1B) {
            unknown_object_84e8d0.Unknown_0042EC20(0, -1, -1, true);
        } else {
            wcsncpy(edit, unknown_session_a3d298.Messages.Get_Edit_Buf(), 162);
            edit[161] = 0;
            wcsncat(edit, IMECompositionString, 162);
            edit[161] = 0;
            wcsncat(edit, Unknown_006FA180("_"), 162);
            edit[161] = 0;
            unknown_object_84e8d0.Unknown_0042EC20(edit, -1, -1, false);
        }
    }

    if ((rc == 3 || rc == 4) && unknown_session_a3d298.Type != 0 && unknown_session_a3d298.Type != 5) {
        if (unknown_session_a3d298.Type == 2 || unknown_session_a3d298.Type == 1) {
            char *packet = serial_manager_00a40a28.BuildBuf;
            if (rc == 3 || rc == 4) {
                *(int *)packet = 0x68;
            }
            Unknown_006FA0F0(packet + 4, unknown_players_a3fa7c[0]->Name, -1);
            packet[0x18] = (char)unknown_a3d3b4;
            if (rc == 3) {
                wcscpy((wchar_t *)(packet + 0x19), unknown_session_a3d298.Messages.Get_Edit_Buf());
            } else if (rc == 4) {
                wcscpy((wchar_t *)(packet + 0x19), unknown_session_a3d298.Messages.OverflowBuf);
                unknown_session_a3d298.Messages.OverflowBuf[0] = 0;
            }
            serial_manager_00a40a28.Send_Message(serial_manager_00a40a28.BuildBuf, 0xFA, 1);
            if (rc == 3 || rc == 4) {
                wcscpy(unknown_last_message_a3f122, (wchar_t *)(packet + 0x19));
            }
        } else if (unknown_session_a3d298.Type == 3 || unknown_session_a3d298.Type == 4) {
            if (unknown_object_84e8d0.Unknown_0042E940(unknown_player_a35db4->ArrayIndex)) {
                unknown_object_84e8d0.Unknown_0042EC20(unknown_session_a3d298.Messages.Get_Edit_Buf(), -1, -1, true);
            } else {
                if (unknown_session_a3d298.Type == 4) {
                    if (rc == 3) {
                        wcscpy(message, unknown_session_a3d298.Messages.Get_Edit_Buf());
                    } else if (rc == 4) {
                        wcscpy(message, unknown_session_a3d298.Messages.OverflowBuf);
                    }
                    int page = Parse_Page_Command_00746480(message);
                    if (page) {
                        if (page == 1) {
                        int n = 0;
                        wcscpy(command, StringTable::Load_String("TXT_PAGE_COMMAND", 0, "D:\\Ra2\\MainLoop.CPP", 1984));
                        wchar_t *p = &message[wcslen(command)];
                        while (*p != 0 && wcsncmp(p, L" ", 1) == 0) {
                            p++;
                        }
                        while (*p != 0 && wcsncmp(p, L" ", 1) != 0 && n <= 10) {
                            name[n++] = *p++;
                        }
                        name[n] = 0;
                        while (*p != 0 && wcsncmp(p, L" ", 1) == 0) {
                            p++;
                        }
                        if (wcslen(name) == 0) {
                            unknown_session_a3d298.Messages.Add_Message(0, -1,
                                StringTable::Load_String("TXT_NO_NAME_SPECIFIED", 0, "D:\\Ra2\\MainLoop.CPP", 2000),
                                unknown_session_a3d298.Unknown_006715D0(unknown_a3d3b4), 0x4046, (int)(Rules->MessageDelay * 900.0), false);
                        } else if (wcslen(p) == 0) {
                            unknown_session_a3d298.Messages.Add_Message(0, -1,
                                StringTable::Load_String("TXT_CANT_SEND_BLANK_PAGE", 0, "D:\\Ra2\\MainLoop.CPP", 2005),
                                unknown_session_a3d298.Unknown_006715D0(unknown_a3d3b4), 0x4046, (int)(Rules->MessageDelay * 900.0), false);
                        } else {
                            swprintf(command2, L"%s > %s", unknown_players_a3fa7c[0]->Name, name);
                            unknown_session_a3d298.Messages.Add_Message(command2, unknown_a3d3b4, p,
                                unknown_session_a3d298.Unknown_006715D0(unknown_a3d3b4), 0x4046, (int)(Rules->MessageDelay * 900.0), false);
                        }
                        if (rc == 4) {
                            wchar_t *buf = unknown_session_a3d298.Messages.Get_Edit_Buf();
                            if (buf) {
                                swprintf(prefix, StringTable::Load_String("TXT_FROM", 0, "D:\\Ra2\\MainLoop.CPP", 2024), unknown_player_a35db4->UIName);
                                swprintf(rest, L"%s%s %s", command, name, buf);
                                unknown_session_a3d298.Messages.Remove_Edit();
                                unknown_session_a3d298.Messages.Add_Edit(unknown_a3d3b4, 0x4046, prefix, 0, -1);
                                buf = unknown_session_a3d298.Messages.Get_Edit_Buf();
                                if (buf) {
                                    wcscat(buf, rest);
                                }
                            }
                        }
                        }
                        unknown_session_a3d298.Messages.OverflowBuf[0] = 0;
                        return;
                    }
                    if (Parse_Online_Command_00746240(message)) {
                        unknown_session_a3d298.Messages.OverflowBuf[0] = 0;
                        return;
                    }
                    int reply = Reply_To_Last_Pager_007466c0(message);
                    if (reply) {
                        if (reply == 1) {
                        bool shortform = false;
                        wcscpy(command, StringTable::Load_String("TXT_REPLY_COMMAND", 0, "D:\\Ra2\\MainLoop.CPP", 2054));
                        wcscpy(command2, StringTable::Load_String("TXT_REPLY_COMMAND_SHORT", 0, "D:\\Ra2\\MainLoop.CPP", 2055));
                        wchar_t *p;
                        if (wcsncmp(message, command, wcslen(command)) == 0) {
                            p = &message[wcslen(command)];
                        } else {
                            p = &message[wcslen(command2)];
                            shortform = true;
                        }
                        while (*p != 0 && wcsncmp(p, L" ", 1) == 0) {
                            p++;
                        }
                        swprintf(prefix, L"%s > %s", unknown_players_a3fa7c[0]->Name, Unknown_006FA180(unknown_last_pager_b2ac48));
                        if (wcslen(Unknown_006FA180(unknown_last_pager_b2ac48)) == 0) {
                            unknown_session_a3d298.Messages.Add_Message(0, unknown_a3d3b4,
                                StringTable::Load_String("TXT_NAME_NOT_SPECIFIED", 0, "D:\\Ra2\\MainLoop.CPP", 2069),
                                unknown_session_a3d298.Unknown_006715D0(unknown_a3d3b4), 0x4046, (int)(Rules->MessageDelay * 900.0), false);
                        } else if (wcslen(p) > 0) {
                            unknown_session_a3d298.Messages.Add_Message(prefix, unknown_a3d3b4, p,
                                unknown_session_a3d298.Unknown_006715D0(unknown_a3d3b4), 0x4046, (int)(Rules->MessageDelay * 900.0), false);
                        } else {
                            unknown_session_a3d298.Messages.Add_Message(0, unknown_a3d3b4,
                                StringTable::Load_String("TXT_CANT_SEND_BLANK_PAGE", 0, "D:\\Ra2\\MainLoop.CPP", 2082),
                                unknown_session_a3d298.Unknown_006715D0(unknown_a3d3b4), 0x4046, (int)(Rules->MessageDelay * 900.0), false);
                        }
                        if (rc == 4) {
                            wchar_t *buf = unknown_session_a3d298.Messages.Get_Edit_Buf();
                            if (buf) {
                                swprintf(edit, StringTable::Load_String("TXT_FROM", 0, "D:\\Ra2\\MainLoop.CPP", 2094), unknown_player_a35db4->UIName);
                                if (shortform) {
                                    swprintf(rest, L"%s %s", command2, buf);
                                } else {
                                    swprintf(rest, L"%s %s", command, buf);
                                }
                                unknown_session_a3d298.Messages.Remove_Edit();
                                unknown_session_a3d298.Messages.Add_Edit(unknown_a3d3b4, 0x4046, edit, 0, -1);
                                buf = unknown_session_a3d298.Messages.Get_Edit_Buf();
                                if (buf) {
                                    wcscat(buf, rest);
                                }
                            }
                        }
                        }
                        unknown_session_a3d298.Messages.OverflowBuf[0] = 0;
                        return;
                    }
                }

                if (rc == 3 || rc == 4) {
                    unknown_session_a3d298.GPacket.Command = 12;
                }
                strcpy(unknown_session_a3d298.GPacket.Name, Unknown_006FA120(unknown_players_a3fa7c[0]->Name));
                unknown_session_a3d298.GPacket.Message.unknown_110 = unknown_session_a3d298.unknown_11c;
                unknown_session_a3d298.GPacket.Message.unknown_114 = Unknown_005bba50(unknown_session_a3d298.HostName_2380);
                unknown_session_a3d298.GPacket.Message.unknown_2f = 0;
                if (rc == 3) {
                    wcscpy(unknown_session_a3d298.GPacket.Message.Buf, unknown_session_a3d298.Messages.Get_Edit_Buf());
                } else if (rc == 4) {
                    wcscpy(unknown_session_a3d298.GPacket.Message.Buf, unknown_session_a3d298.Messages.OverflowBuf);
                    unknown_session_a3d298.Messages.OverflowBuf[0] = 0;
                }

                count = Houses.Count();
                if (unknown_int_a3d548 && (unknown_chat_target_a6ebe0 == 1 || unknown_chat_target_a6ebe0 == 2)) {
                    for (i = 0; i < count; i++) {
                        HouseClass *house = Houses[i];
                        if (house && house->Type->Multiplay
                            && ((!unknown_flags_a3f118[i] && unknown_chat_target_a6ebe0 == 1)
                                || (!Houses[unknown_players_a3fa7c[0]->ID]->Is_Ally(house) && unknown_chat_target_a6ebe0 == 2))) {
                            int scheme = Gadget_Color_Scheme();
                            unknown_session_a3d298.Messages.Add_Message(0, 0,
                                StringTable::Load_String("TXT_OBSERVER_CANT_SEND", 0, "D:\\Ra2\\MainLoop.CPP", 2167),
                                scheme, 0x16, (int)(Rules->MessageDelay * 900.0), true);
                            unknown_chat_target_a6ebe0 = 0;
                            break;
                        }
                    }
                }

                for (i = 0; i < count; i++) {
                    HouseClass *house = Houses[i];
                    if (house && house->Type->Multiplay
                        && ((unknown_flags_a3f118[i] && unknown_chat_target_a6ebe0 == 1)
                            || (Houses[unknown_players_a3fa7c[0]->ID]->Is_Ally(house) && unknown_chat_target_a6ebe0 == 2)
                            || unknown_chat_target_a6ebe0 == 3)) {
                        int connections = unknown_ipx_manager_a40978.Num_Connections();
                        for (int j = 0; j < connections; j++) {
                            int id = unknown_ipx_manager_a40978.Connection_ID(j);
                            if (wcscmp(house->UIName, unknown_ipx_manager_a40978.Connection_Name(id)) == 0) {
                                IPXAddressClass *address = unknown_ipx_manager_a40978.Connection_Address(id);
                                if (unknown_flag_a3fba8) {
                                    unknown_session_a3d298.GPacket.Message.unknown_2f |= unknown_OwnerTalkClass_00ab6d18.Unknown_0063F4C0(id);
                                } else {
                                    unknown_ipx_manager_a40978.Send_Global_Message(&unknown_session_a3d298.GPacket, 0x1C7, 1, address, 0, 0);
                                    unknown_ipx_manager_a40978.Service();
                                }
                            }
                        }
                    }
                }

                if (unknown_flag_a3fba8 && unknown_session_a3d298.GPacket.Message.unknown_2f) {
                    Debug_Printf("Sending chat, mask = %d\n", (unsigned char)unknown_session_a3d298.GPacket.Message.unknown_2f);
                    unknown_ipx_manager_a40978.Send_Global_Message(&unknown_session_a3d298.GPacket, 0x1C7, 1, &unknown_players_a3fa7c[0]->Address, 0, 0);
                    unknown_ipx_manager_a40978.Service();
                }

                wchar_t *from = Unknown_006FA180(unknown_session_a3d298.GPacket.Name);
                unknown_session_a3d298.Messages.Add_Message(from, unknown_session_a3d298.GPacket.Message.unknown_110,
                    unknown_session_a3d298.GPacket.Message.Buf, unknown_session_a3d298.Unknown_006715D0(unknown_session_a3d298.GPacket.Message.unknown_110),
                    0x4046, (int)(Rules->MessageDelay * 900.0), false);
                wcscpy(unknown_last_message_a3f122, unknown_session_a3d298.GPacket.Message.Buf);
            }
        }
        Map.Flag_To_Redraw(2);
    }

    if (rc == 3) {
        unknown_chat_target_a6ebe0 = 0;
    }
}
