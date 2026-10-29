// bool __fastcall Get_File_From_Host_0066aef0(char *return_name, int gametype, bool progress) (0x0066AEF0):
// asks the host for its file (command 0x6E on the modem, 0x10 on the network: to the host's address in
// IPX games, to the World Online host by name otherwise), waits for the file info (0x6F / 0x11 from the
// host) and acknowledges it (0x71 / 0x15), then receives the file through Receive_Remote_File; each step
// fails after RESPONSE_TIMEOUT. Red Alert's Get_Scenario_File_From_Host.
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/ipx_address.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/null_modem.hpp"
#include "shared/modem_guest.hpp"
#include "shared/cd_timer.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_string.hpp"

// @ref ??_C@_04NCCD@true?$AA@=007d24d8
// @ref ??_C@_05NAGO@false?$AA@=007d24d0
// @ref ??_C@_0BB@ODNE@File?5name?5is?5?$CFs?6?$AA@=007f2d98
// @ref ??_C@_0BI@FHHC@Getting?5file?5from?5host?6?$AA@=007f2e18
// @ref ??_C@_0BK@DLM@Requesting?5file?5download?6?$AA@=007f2dfc
// @ref ??_C@_0BP@ILOB@Host?5responded?5with?5file?5info?6?$AA@=007f2dac
// @ref ??_C@_0CA@HKMA@Sending?5file?5info?5received?5ack?6?$AA@=007f2d3c
// @ref ??_C@_0CB@HLMN@Receive_Remote_File?5returned?5?$CFs?6@=007f2cf0
// @ref ??_C@_0CI@BGCO@Timeout?5waiting?5for?5FILE_INFO_AC@=007f2d14
// @ref ??_C@_0CO@ELHL@Timeout?5waiting?5for?5REQ_SCENARIO@=007f2dcc
// @ref ??_C@_0DK@DEGM@Timeout?5waiting?5for?5host?5to?5resp@=007f2d5c

#define RESPONSE_TIMEOUT 60 * 60        // ticks

bool __fastcall Get_File_From_Host_0066aef0(char *return_name, int gametype, bool progress)
{
    unsigned int file_length = 0;
    UnknownSerialPacket send_packet;
    UnknownSerialPacket receive_packet;
    UnknownGlobalPacket net_send_packet;
    UnknownGlobalPacket net_receive_packet;
    int packet_len;
    unsigned short product_id;
    IPXAddressClass sender_address;

    Debug_Printf("Getting file from host\n");
    CDTimerClass<SystemTimerClass> response_timer;

    Debug_Printf("Requesting file download\n");
    response_timer = RESPONSE_TIMEOUT;
    if (gametype == 1 || gametype == 2) {
        memset(&send_packet, 0, sizeof(send_packet));
        send_packet.Command = 0x6E;
        serial_manager_00a40a28.Send_Message(&send_packet, sizeof(send_packet), 1);
        while (serial_manager_00a40a28.Num_Send() > 0 && response_timer) {
            Service_Game_IO_00481fb0();
        }
    } else {
        memset(&net_send_packet, 0, sizeof(net_send_packet));
        net_send_packet.Command = 0x10;
        Unknown_006FA0F0(net_send_packet.Name, unknown_players_a3fa7c[0]->Name, -1);
        if (unknown_session_a3d298.Type == 3) {
            unknown_ipx_manager_a40978.Send_Global_Message(&net_send_packet, sizeof(net_send_packet), 1, &unknown_address_a3db2c, 0, 0);
        } else {
            WOL::User *host = Unknown_0074DA60();
            if (host != 0) {
                unknown_ipx_manager_a40978.unknown_5259a0(&net_send_packet, sizeof(net_send_packet), 1, Unknown_006FA180(host->name));
            }
        }
        while (unknown_ipx_manager_a40978.Global_Num_Send() > 0 && response_timer) {
            Service_Game_IO_00481fb0();
        }
    }
    if (!response_timer) {
        Debug_Printf("Timeout waiting for REQ_SCENARIO packet send\n");
        return false;
    }

    response_timer = RESPONSE_TIMEOUT;
    if (gametype == 1 || gametype == 2) {
        do {
            Service_Game_IO_00481fb0();
            if (serial_manager_00a40a28.Get_Message(&receive_packet, &packet_len) > 0 && receive_packet.Command == 0x6F) {
                strcpy(return_name, receive_packet.Options.FileName);
                file_length = receive_packet.Options.FileLength;
                Debug_Printf("Host responded with file info\n");
                Debug_Printf("File name is %s\n", return_name);
                break;
            }
        } while (response_timer);
    } else {
        do {
            Service_Game_IO_00481fb0();
            int receive_packet_length = sizeof(net_receive_packet);
            if (unknown_ipx_manager_a40978.Get_Global_Message(&net_receive_packet, &receive_packet_length, &sender_address, &product_id)) {
                bool from_host = sender_address.unknown_523690(unknown_address_a3db2c);
                if (unknown_session_a3d298.Type == 4) {
                    WOL::User *host = Unknown_0074DA60();
                    from_host = host != 0 && Compare_Narrow_00781f20(host->name, net_receive_packet.Name) == 0;
                }
                if (net_receive_packet.Command == 0x11 && from_host) {
                    strcpy(return_name, net_receive_packet.ScenarioInfo.ShortFileName);
                    file_length = net_receive_packet.ScenarioInfo.FileLength;
                    Debug_Printf("Host responded with file info\n");
                    Debug_Printf("File name is %s\n", return_name);
                    break;
                }
            }
        } while (response_timer);
    }
    if (!response_timer) {
        Debug_Printf("Timeout waiting for host to respond to file info request\n");
        return false;
    }

    Debug_Printf("Sending file info received ack\n");
    response_timer = RESPONSE_TIMEOUT;
    if (gametype == 1 || gametype == 2) {
        memset(&send_packet, 0, sizeof(send_packet));
        send_packet.Command = 0x71;
        serial_manager_00a40a28.Send_Message(&send_packet, sizeof(send_packet), 1);
        while (serial_manager_00a40a28.Num_Send() > 0 && response_timer) {
            Service_Game_IO_00481fb0();
        }
    } else {
        memset(&net_send_packet, 0, sizeof(net_send_packet));
        net_send_packet.Command = 0x15;
        strcpy(net_send_packet.Name, Unknown_006FA120(unknown_players_a3fa7c[0]->Name));
        if (unknown_session_a3d298.Type == 4) {
            WOL::User *host = Unknown_0074DA60();
            if (host != 0) {
                unknown_ipx_manager_a40978.unknown_5259a0(&net_send_packet, sizeof(net_send_packet), 1, Unknown_006FA180(host->name));
            }
        } else {
            unknown_ipx_manager_a40978.Send_Global_Message(&net_send_packet, sizeof(net_send_packet), 1, &unknown_address_a3db2c, 0, 0);
        }
        while (unknown_ipx_manager_a40978.Global_Num_Send() > 0 && response_timer) {
            Service_Game_IO_00481fb0();
        }
    }
    if (!response_timer) {
        Debug_Printf("Timeout waiting for FILE_INFO_ACK send\n");
        return false;
    }

    bool result = Receive_Remote_File_0066b520(return_name, file_length, gametype, progress);
    Debug_Printf("Receive_Remote_File returned %s\n", result ? "true" : "false");
    return result;
}
