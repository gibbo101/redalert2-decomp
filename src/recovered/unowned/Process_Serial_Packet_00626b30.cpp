// RetcodeType __fastcall Process_Serial_Packet(char *multi_packet_buf, int first_time)
// (0x00626B30; Red Alert's Process_Serial_Packet).
#include "shared/queue.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/gadget.hpp"
#include "shared/session_state.hpp"
// @ref ?Add_Message@MessageListClass@@QAEPAVUnknownMessageNode@@PBGH0HIH_N@Z=005b4da0
// @ref ?Concat_Message@MessageListClass@@QAEHPBGH0H@Z=005b51c0
// @ref ?Destroy_Null_Connection@@YIXHH@Z=005ceba0
// @ref ?unknown_last_message_a3f122@@3PAGA=00a3f122

RetcodeType __fastcall Process_Serial_Packet(char *multi_packet_buf, int first_time)
{
    UnknownSerialPacket *serial_packet = (UnknownSerialPacket *)multi_packet_buf;
    int player_gone = 0;

    if (first_time) {
        if (serial_packet->Command == 0x66) {
            player_gone = 1;
        }
    } else {
        if (serial_packet->Command == 0x66 || serial_packet->Command == 0x69 || serial_packet->Command == 0x6A) {
            player_gone = 1;
        }
    }
    if (player_gone) {
        Destroy_Null_Connection(serial_packet->ScenarioInfo.Color, 0);
        return RC_PLAYER_LEFT;
    }

    if (serial_packet->Command == 0x68) {
        wchar_t *name = Unknown_006FA180(serial_packet->Name);
        if (!unknown_session_a3d298.Messages.Concat_Message(name, serial_packet->ID,
                serial_packet->Message, Rules->MessageDelay * 900)) {
            name = Unknown_006FA180(serial_packet->Name);
            unknown_session_a3d298.Messages.Add_Message(name, serial_packet->ID,
                serial_packet->Message, serial_packet->ID, 0x4046, Rules->MessageDelay * 900, false);
            Voc_Play(Rules->IncomingMessage, 1.0f, 0x2000, 0);
        }
        if (wcslen(serial_packet->Message)) {
            wcscpy(unknown_last_message_a3f122, serial_packet->Message);
        }
        Map.Flag_To_Redraw(2);
        return RC_SERIAL_PROCESSED;
    }

    if (serial_packet->Command == 0x78) {
        if ((unknown_flag_a3f120 && unknown_session_a3d298.Type == 3) || (unknown_flag_a3f121 && unknown_session_a3d298.Type == 4)) {
            Unknown_Play_Taunt_00715fb0(serial_packet->Taunt);
            return RC_SERIAL_PROCESSED;
        }
        return RC_SERIAL_PROCESSED;
    }

    if ((serial_packet->Command >= 100 && serial_packet->Command < 0x6D)
        || (serial_packet->Command >= 0x6E && serial_packet->Command <= 0x74)
        || unknown_session_a3d55c == 1) {
        return RC_SERIAL_PROCESSED;
    }

    EventClass *event = (EventClass *)multi_packet_buf;
    if (event->Type <= 0 || event->Type >= 0x2E) {
        return RC_SERIAL_PROCESSED;
    }
    if ((char)event->House == unknown_player_a35db4->ArrayIndex) {
        return RC_HUNG_UP;
    }
    return RC_NORMAL;
}
