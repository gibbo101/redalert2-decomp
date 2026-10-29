// @ref ??_C@_0BD@BOLI@TXT_SENDING_GO_ACK?$AA@=007e22a4
// Complete guest start handshake and install both player entries (0x005986F0).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/modem_guest.hpp"
#include "shared/queue.hpp"
#include "shared/serial_progress.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/campaign.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/null_dlg.hpp"
#include "shared/id_source.hpp"
#include "shared/special.hpp"
#include "shared/session_state.hpp"
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);

bool ModemGuest::Start_Game_005986f0(bool unknown)
{
    if (unknown == true) {
        return false;
    }
    Read_Dialog_00596d50();
    unknown_session_a3d55c = 0;
    NodeNameType *node = new NodeNameType;
    if (node) {
        Unknown_006FA0C0(node->Name, unknown_name_a3d3a0, -1);
        node->unknown_4b = unknown_a3d3bc;
        node->unknown_53 = unknown_a3d3b4;
        node->unknown_63 = -1;
        unknown_players_a3fa7c.Add(node);
        unknown_session_a3d55c++;
    }
    node = new NodeNameType;
    if (node) {
        wcscpy(node->Name, HostName);
        node->unknown_4b = HostHouse;
        node->unknown_53 = HostColor;
        node->unknown_63 = -1;
        unknown_players_a3fa7c.Add(node);
        unknown_session_a3d55c++;
    }
    if (unknown_session_a3d55c != 2) {
        return false;
    }
    HWND dialog = unknown_cancel_dialog_6001e0(
        StringTable::Load_String("TXT_SENDING_GO_ACK", 0, "D:\\Ra2\\ModemGst.cpp", 0x6F3), 0, 0);
    if (dialog) {
        unknown_dialog_5ff7c0(dialog);
    }
    unsigned long start = TickCount.Time();
    while ((serial_manager_00a40a28.Num_Send() && TickCount.Time() - start < 1800) || TickCount.Time() - start < 60) {
        Service_Game_IO_00481fb0();
        Unknown_005B5EE0();
        serial_manager_00a40a28.Service();
    }
    if (dialog) {
        unknown_dialog_5ff6e0(dialog);
    }
    serial_manager_00a40a28.Init_Send_Queue();
    unknown_session_a3f616 = 0;
    int techLevel = unknown_session_a3d298.ScenarioIndex;
    unknown_id_source_a3d290->TechLevel = techLevel;
    unknown_session_a3d55c = unknown_players_a3fa7c.Count();
    Frame = 0;
    unknown_session_a3d2ac = 2;
    unknown_special_a40920.DestroyableBridges = unknown_session_a3d298.unknown_28;
    unknown_special_a40920.HarvesterImmune = unknown_session_a3d298.unknown_a5;
    unknown_special_a40920.TiberiumGrows = true;
    unknown_special_a40920.TiberiumSpreads = true;
    unknown_special_a40920.Unknown_0068B410();
    return true;
}
