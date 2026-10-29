// bool __fastcall Send_Remote_File_0066bb20(char const *file_name, int gametype, bool to_players, bool progress)
// (0x0066BB20): sends the file info (0x6F on the modem, 0x11 on the network to every other player or to
// the session's scenario requests), waits for the acknowledgements, then sends the file in 192-byte
// chunks (0x70 / 0x12) while the connection's send queue is short, until the queue drains or the
// timeout runs out. Red Alert's Send_Remote_File.
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/ipx_address.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/null_modem.hpp"
#include "shared/cd_timer.hpp"
#include "shared/debug_printf.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/progress_screen.hpp"
#include "shared/string_table.hpp"
#include "shared/keyboard.hpp"
#include "shared/crt_string.hpp"

// @ref ??_C@_0N@LJCA@PROGBARM?4SHP?$AA@=007f1fe8
// @ref ??_C@_07HFL@failure?$AA@=007f2f48
// @ref ??_C@_07IGMM@success?$AA@=007f2f50
// @ref ??_C@_0BJ@CPAL@Send?5file?5?$CFs?5to?5clients?6?$AA@=007f3040
// @ref ??_C@_0BK@FKDD@File?5info?5send?5timed?5out?6?$AA@=007f2fdc
// @ref ??_C@_0BM@LKIN@File?5upload?5completed?5?9?5?$CFs?6?$AA@=007f2f2c
// @ref ??_C@_0BO@OLMH@Sending?5file?5info?5to?5clients?6?$AA@=007f3020
// @ref ??_C@_0CF@NINP@Client?5responded?5with?5file?5info?5@=007f2fb4
// @ref ??_C@_0CH@EMII@Sending?5file?5chunk?5?$CFd?1?$CFd?0?5?$CFd?5sec@=007f2f8c
// @ref ??_C@_0CH@JACN@Sending?5file?5info?5packet?5to?5play@=007f2ff8
// @ref ??_C@_0DB@BACP@We?5sent?5the?5file?5properly?5with?5?$CF@=007f2f58

bool __fastcall Send_Remote_File_0066bb20(char const *file_name, int gametype, bool to_players, bool progress)
{
    CDTimerClass<SystemTimerClass> response_timer;
    int percent = 0;
    bool return_code = false;
    UnknownSerialPacket file_info;
    UnknownSerialPacket receive_packet;
    UnknownGlobalPacket net_file_info;
    UnknownGlobalPacket net_receive_packet;
    RemoteFileTransferType send_packet;
    int packet_len;
    unsigned short product_id;

    Debug_Printf("Send file %s to clients\n", file_name);
    CCFileClass file(file_name);
    if (!file.Is_Available()) {
        return false;
    }
    int file_length = file.Size();

    response_timer = RESPONSE_TIMEOUT;
    Debug_Printf("Sending file info to clients\n");
    if (gametype == 1 || gametype == 2) {
        file_info.Command = 0x6F;
        strcpy(file_info.Options.FileName, file_name);
        file_info.Options.FileLength = file_length;
        serial_manager_00a40a28.Send_Message(&file_info, sizeof(file_info), 1);
        while (serial_manager_00a40a28.Num_Send() > 0 && response_timer) {
            Service_Game_IO_00481fb0();
        }
    } else {
        net_file_info.Command = 0x11;
        strcpy(net_file_info.ScenarioInfo.ShortFileName, file_name);
        net_file_info.ScenarioInfo.FileLength = file_length;
        strcpy(net_file_info.Name, Unknown_006FA120(unknown_players_a3fa7c[0]->Name));
        if (to_players) {
            for (int i = 1; i < unknown_players_a3fa7c.Count(); i++) {
                do {
                    Service_Game_IO_00481fb0();
                } while (!unknown_ipx_manager_a40978.unknown_5259a0(&net_file_info, sizeof(net_file_info), 1, unknown_players_a3fa7c[i]->Name) && response_timer);
            }
        } else {
            for (int i = 0; i < unknown_session_a3d298.RequestCount; i++) {
                do {
                    Service_Game_IO_00481fb0();
                    Debug_Printf("Sending file info packet to player %d\n", unknown_players_a3fa7c[unknown_session_a3d298.ScenarioRequests[i]]->Name);
                } while (!unknown_ipx_manager_a40978.unknown_5259a0(&net_file_info, sizeof(net_file_info), 1, unknown_players_a3fa7c[unknown_session_a3d298.ScenarioRequests[i]]->Name) && response_timer);
            }
        }
        while (unknown_ipx_manager_a40978.Global_Num_Send() > 0 && response_timer) {
            Service_Game_IO_00481fb0();
        }
    }
    if (!response_timer) {
        Debug_Printf("File info send timed out\n");
        return false;
    }

    IPXAddressClass sender_address;
    int acks = 0;
    int clients = to_players ? unknown_players_a3fa7c.Count() - 1 : unknown_session_a3d298.RequestCount;
    response_timer = RESPONSE_TIMEOUT;
    if (gametype == 1 || gametype == 2) {
        do {
            Service_Game_IO_00481fb0();
            if (serial_manager_00a40a28.Get_Message(&receive_packet, &packet_len) > 0 && receive_packet.Command == 0x71) {
                Debug_Printf("Client responded with file info ack\n");
                break;
            }
        } while (response_timer && acks < clients);
    } else {
        do {
            Service_Game_IO_00481fb0();
            int receive_packet_length = sizeof(net_receive_packet);
            if (unknown_ipx_manager_a40978.Get_Global_Message(&net_receive_packet, &receive_packet_length, &sender_address, &product_id) && net_receive_packet.Command == 0x15) {
                acks++;
            }
        } while (response_timer && acks < clients);
    }

    int total_blocks = (file_length + 192 - 1) / 192;
    file.Open(FILE_RIGHTS_READ);
    int block_number = 0;
    if (progress) {
        ProgressScreen.Init(100.0, 1, 0);
        ProgressScreen.Load_Shape("PROGBARM.SHP", 0, 0);
        ProgressScreen.Unknown_0061EFA0(Point2D(-1, -1), StringTable::Load_String("GUI:MapTransfer", 0, "D:\\Ra2\\SendFile.CPP", 659), false, true);
        unknown_5159b0(0, true);
        ProgressScreen.Draw_It(Point2D(-1, -1));
        ProgressScreen.Set_Progress_006201c0(0, 0.0, Point2D(-1, -1));
    }
    if (unknown_session_a3d298.Type == 4) {
        unknown_ipx_manager_a40978.unknown_slot16();
        unknown_ipx_manager_a40978.unknown_slot14(240, -1, 1200);
    }

    response_timer = Get_Timeout(gametype);
    percent = 0;
    while (response_timer) {
        if (gametype == 1 || gametype == 2) {
            Unknown_005B5EE0();
            Service_Game_IO_00481fb0();
            if (block_number < total_blocks) {
                if (serial_manager_00a40a28.Num_Send() < 2) {
                    send_packet.Command = 0x70;
                    send_packet.BlockNumber = block_number;
                    send_packet.BlockLength = file_length;
                    if (file_length >= 192) {
                        send_packet.BlockLength = 192;
                    }
                    file_length -= send_packet.BlockLength;
                    if (file.Read(send_packet.RawData, send_packet.BlockLength) == send_packet.BlockLength) {
                        Debug_Printf("Sending file chunk %d/%d, %d sec left\n", block_number, total_blocks, (long)response_timer);
                        serial_manager_00a40a28.Send_Message(&send_packet, sizeof(send_packet), 1);
                    }
                    block_number++;
                    percent += 100;
                    if (progress) {
                        ProgressScreen.Set_Progress_006201c0(0, percent / total_blocks, Point2D(-1, -1));
                    }
                }
            } else if (serial_manager_00a40a28.Num_Send() == 0) {
                return_code = true;
                if (progress) {
                    ProgressScreen.Set_Progress_006201c0(0, 100.0, Point2D(-1, -1));
                }
                break;
            }
        } else {
            Unknown_005B5EE0();
            Service_Game_IO_00481fb0();
            if (block_number < total_blocks) {
                if (unknown_ipx_manager_a40978.Global_Num_Send() < 10) {
                    send_packet.Command = 0x12;
                    send_packet.BlockNumber = block_number;
                    send_packet.BlockLength = file_length;
                    if (file_length >= 192) {
                        send_packet.BlockLength = 192;
                    }
                    strcpy(send_packet.Name, Unknown_006FA120(unknown_players_a3fa7c[0]->Name));
                    file_length -= send_packet.BlockLength;
                    if (file.Read(send_packet.RawData, send_packet.BlockLength) == send_packet.BlockLength) {
                        Debug_Printf("Sending file chunk %d/%d, %d sec left\n", block_number, total_blocks, (long)response_timer);
                        if (to_players) {
                            for (int i = 1; i < unknown_players_a3fa7c.Count(); i++) {
                                int sent;
                                do {
                                    sent = unknown_ipx_manager_a40978.unknown_5259a0(&send_packet, sizeof(send_packet), 1, unknown_players_a3fa7c[i]->Name);
                                    Service_Game_IO_00481fb0();
                                } while (!sent);
                            }
                        } else {
                            for (int i = 0; i < unknown_session_a3d298.RequestCount; i++) {
                                int sent;
                                do {
                                    sent = unknown_ipx_manager_a40978.unknown_5259a0(&send_packet, sizeof(send_packet), 1, unknown_players_a3fa7c[unknown_session_a3d298.ScenarioRequests[i]]->Name);
                                    Service_Game_IO_00481fb0();
                                } while (!sent);
                            }
                        }
                    }
                    block_number++;
                    percent += 100;
                    if (progress) {
                        ProgressScreen.Set_Progress_006201c0(0, percent / total_blocks, Point2D(-1, -1));
                    }
                }
            } else if (unknown_ipx_manager_a40978.Global_Num_Send() == 0) {
                if (unknown_ipx_manager_a40978.Global_Num_Send() == 0) {
                    Debug_Printf("We sent the file properly with %d seconds left!\n", (long)response_timer);
                    return_code = true;
                    if (progress) {
                        ProgressScreen.Set_Progress_006201c0(0, 100.0, Point2D(-1, -1));
                    }
                    break;
                }
            }
        }
    }
    if (unknown_session_a3d298.Type == 4) {
        unknown_ipx_manager_a40978.unknown_slot17();
    }
    Debug_Printf("File upload completed - %s\n", return_code ? "success" : "failure");
    return return_code;
}
