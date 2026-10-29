// bool __fastcall Receive_Remote_File_0066b520(char *file_name, unsigned int file_length, int gametype, bool progress)
// (0x0066B520): receives the host's 192-byte chunks (0x70 on the modem, 0x12 on the network) into a
// buffer, each once, restarting the timeout after every chunk, then writes the file (deleted again
// when the transfer did not complete). With progress set the progress screen shows the transfer;
// internet games use slower global channel timing meanwhile. Red Alert's Receive_Remote_File.
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/ipx_address.hpp"
#include "shared/serial_progress.hpp"
#include "shared/null_modem.hpp"
#include "shared/cd_timer.hpp"
#include "shared/debug_printf.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/progress_screen.hpp"
#include "shared/string_table.hpp"
#include "shared/keyboard.hpp"
#include "shared/crt_string.hpp"

#define RESPONSE_TIMEOUT 60 * 60        // ticks

// @ref ??_C@_0N@LJCA@PROGBARM?4SHP?$AA@=007f1fe8
// @ref ??_C@_0BA@HEOL@GUI?3MapTransfer?$AA@=007f2efc
// @ref ??_C@_0BE@KGIN@D?3?2Ra2?2SendFile?4CPP?$AA@=007f2ee8
// @ref ??_C@_0BG@FCCA@Download?5file?5closed?6?$AA@=007f2e48
// @ref ??_C@_0BG@LGME@Partial?5file?5deleted?6?$AA@=007f2e30
// @ref ??_C@_0BI@HMLH@Received?5file?5chunk?5?$CFd?6?$AA@=007f2ea0
// @ref ??_C@_0BM@MANJ@File?5download?5completed?5OK?6?$AA@=007f2e84
// @ref ??_C@_0BP@PDJD@Receiving?5download?5of?5file?5?$CFs?6?$AA@=007f2f0c
// @ref ??_C@_0CC@HJDA@File?5download?5failed?5to?5complete@=007f2e60
// @ref ??_C@_0DA@CEPB@Received?5file?5chunk?5?$CFd?1?$CFd?5with?5?$CF@=007f2eb8

bool __fastcall Receive_Remote_File_0066b520(char *file_name, unsigned int file_length, int gametype, bool progress)
{
    CDTimerClass<SystemTimerClass> response_timer;
    IPXAddressClass sender_address;
    unsigned short product_id;
    int packet_len;
    bool return_code = false;
    RemoteFileTransferType *receive_packet = (RemoteFileTransferType *)operator new(0x1E7);

    Debug_Printf("Receiving download of file %s\n", file_name);
    RawFileClass save_file(file_name);
    if (save_file.Is_Available()) {
        save_file.Delete();
    }
    save_file.Open(FILE_RIGHTS_WRITE);

    int total_blocks = file_length / 192;
    if (file_length % 192) {
        total_blocks++;
    }
    char *received = (char *)operator new(total_blocks);
    memset(received, 0, total_blocks);
    int blocks_received = 0;
    char *buffer = (char *)operator new(file_length);

    if (progress) {
        ProgressScreen.Init(100.0, 1, 0);
        ProgressScreen.Load_Shape("PROGBARM.SHP", 0, 0);
        ProgressScreen.Unknown_0061EFA0(Point2D(-1, -1), StringTable::Load_String("GUI:MapTransfer", 0, "D:\\Ra2\\SendFile.CPP", 358), false, true);
        unknown_5159b0(0, true);
        ProgressScreen.Draw_It(Point2D(-1, -1));
        ProgressScreen.Set_Progress_006201c0(0, 0.0, Point2D(-1, -1));
    }
    if (unknown_session_a3d298.Type == 4) {
        unknown_ipx_manager_a40978.unknown_slot16();
        unknown_ipx_manager_a40978.unknown_slot14(120, -1, 1200);
    }

    response_timer = Get_Timeout(gametype);
    int percent = 0;
    do {
        if (gametype == 1 || gametype == 2) {
            Unknown_005B5EE0();
            Service_Game_IO_00481fb0();
            if (serial_manager_00a40a28.Get_Message(receive_packet, &packet_len) > 0 && receive_packet->Command == 0x70) {
                if (received[receive_packet->BlockNumber] == 0) {
                    received[receive_packet->BlockNumber] = 1;
                    blocks_received++;
                    percent += 100;
                    response_timer = RESPONSE_TIMEOUT / 2;
                    Debug_Printf("Received file chunk %d\n", receive_packet->BlockNumber);
                    memcpy(buffer + receive_packet->BlockNumber * 192, receive_packet->RawData, receive_packet->BlockLength);
                    if (progress) {
                        ProgressScreen.Set_Progress_006201c0(0, percent / total_blocks, Point2D(-1, -1));
                    }
                    if (blocks_received == total_blocks) {
                        if (progress) {
                            ProgressScreen.Set_Progress_006201c0(0, 100.0, Point2D(-1, -1));
                        }
                        return_code = true;
                        break;
                    }
                }
            }
        } else {
            Unknown_005B5EE0();
            Service_Game_IO_00481fb0();
            int receive_packet_length = 0x1E7;
            if (unknown_ipx_manager_a40978.Get_Global_Message(receive_packet, &receive_packet_length, &sender_address, &product_id)) {
                bool from_host = sender_address.unknown_523690(unknown_address_a3db2c);
                if (unknown_session_a3d298.Type == 4) {
                    WOL::User *host = Unknown_0074DA60();
                    from_host = host != 0 && Compare_Narrow_00781f20(host->name, receive_packet->Name) == 0;
                }
                if (receive_packet->Command == 0x12 && from_host) {
                    if (received[receive_packet->BlockNumber] == 0) {
                        received[receive_packet->BlockNumber] = 1;
                        blocks_received++;
                        percent += 100;
                        response_timer = Get_Timeout(gametype) / 2;
                        Debug_Printf("Received file chunk %d/%d with %d seconds left\n", receive_packet->BlockNumber, total_blocks, (long)response_timer);
                        memcpy(buffer + receive_packet->BlockNumber * 192, receive_packet->RawData, receive_packet->BlockLength);
                        if (progress) {
                            ProgressScreen.Set_Progress_006201c0(0, percent / total_blocks, Point2D(-1, -1));
                        }
                        if (blocks_received == total_blocks) {
                            return_code = true;
                            if (progress) {
                                ProgressScreen.Set_Progress_006201c0(0, 100.0, Point2D(-1, -1));
                            }
                            break;
                        }
                    }
                }
            }
        }
    } while (response_timer);

    if (unknown_session_a3d298.Type == 4) {
        unknown_ipx_manager_a40978.unknown_slot17();
    }
    save_file.Write(buffer, file_length);
    operator delete(buffer);
    operator delete(received);
    if (return_code) {
        Debug_Printf("File download completed OK\n");
    } else {
        Debug_Printf("File download failed to complete\n");
    }
    save_file.Close();
    Debug_Printf("Download file closed\n");
    if (!return_code && save_file.Is_Available()) {
        save_file.Delete();
        Debug_Printf("Partial file deleted\n");
    }
    operator delete(receive_packet);
    return return_code;
}
