// int Buddy_List_Main(bool first_time) (0x00759370): the buddy list screen, run from Wonline_Main.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/crt_string.hpp"
#include "shared/string_table.hpp"
#include "shared/debug_printf.hpp"
#include "shared/wonline_dialog_control.hpp"
#include "shared/wol_main.hpp"
extern "C" __declspec(dllimport) DWORD __stdcall WaitForMultipleObjects(DWORD, HANDLE *, BOOL, DWORD);
extern "C" long __cdecl atol(char const *);
extern HANDLE wol_wait_events_b264f8[18];
extern int wol_lan_leave_b2abf0;
extern int unknown_b2abec;
extern int unknown_online_option_a3d2a8;
extern bool unknown_7fd354;
extern int unknown_a72c68;
extern char wol_source_file_007fd62c[];
extern char wol_youre_discon_label_7fe1fc[];
extern char lobby_prefix_007fd358[];
extern char buddy_host_failed_7ffd50[], buddy_host_abort_7ffd30[], buddy_host_exit_7ffd10[], buddy_host_stop_7ffcfc[];
extern char buddy_guest_list_failed_7ffcd0[], buddy_guest_find_failed_7ffca0[], buddy_guest_join_failed_7ffc7c[];
extern char buddy_guest_abort_7ffc5c[], buddy_guest_exit_7ffc3c[], buddy_guest_error_7ffc1c[], buddy_guest_join_fail_7ffbf0[];
extern char buddy_guest_timeout_7ffbd0[], buddy_guest_done_7ffbb4[], buddy_skirmish_7ffb98[], buddy_host_start_7ffb74[], buddy_guest_start_7ffb50[];
bool __fastcall Queue_Channel_List_Request_0073db20(int channel_type,unsigned char autoping,bool wait);
bool __fastcall Request_Game_Channel_List_0073df10(unsigned char autoping,bool wait);
bool __fastcall Leave_Current_Channel_00744610(unsigned int flags,bool show);
bool __fastcall Join_Game_Channel_00745780(WOL::Channel const *,bool);
bool __fastcall Host_Game_007459a0();
bool __fastcall Find_Channel_By_Name_007592d0(Wstring const &name,WolChannelArray const &channels,WOL::Channel &channel);
bool __fastcall Request_Chat_Channel_List_0073dd20(bool wait);
bool connection_wait_callback_0073c120();
HWND __fastcall unknown_create_dialog_5ff610(int,DLGPROC,int);
void __fastcall unknown_dialog_5ff7c0(HWND);
void __fastcall unknown_dialog_5ff6e0(HWND);
void __fastcall unknown_517370(bool);
bool __fastcall End_Dialog_007357e0(HWND dialog,int result);
int __stdcall Buddy_Dialog_Proc_00758750(HWND,UINT,WPARAM,LPARAM);
inline void __fastcall Close_Wonline_Wait(unsigned int flags);
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ?wol_lan_leave_b2abf0@@3HA=00b2abf0
// @ref ?unknown_b2abec@@3HA=00b2abec
// @ref ?unknown_online_option_a3d2a8@@3HA=00a3d2a8
// @ref ?unknown_7fd354@@3_NA=007fd354
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?wol_youre_discon_label_7fe1fc@@3PADA=007fe1fc
// @ref ?lobby_prefix_007fd358@@3PADA=007fd358
// @ref ?buddy_host_failed_7ffd50@@3PADA=007ffd50
// @ref ?buddy_host_abort_7ffd30@@3PADA=007ffd30
// @ref ?buddy_host_exit_7ffd10@@3PADA=007ffd10
// @ref ?buddy_host_stop_7ffcfc@@3PADA=007ffcfc
// @ref ?buddy_guest_list_failed_7ffcd0@@3PADA=007ffcd0
// @ref ?buddy_guest_find_failed_7ffca0@@3PADA=007ffca0
// @ref ?buddy_guest_join_failed_7ffc7c@@3PADA=007ffc7c
// @ref ?buddy_guest_abort_7ffc5c@@3PADA=007ffc5c
// @ref ?buddy_guest_exit_7ffc3c@@3PADA=007ffc3c
// @ref ?buddy_guest_error_7ffc1c@@3PADA=007ffc1c
// @ref ?buddy_guest_join_fail_7ffbf0@@3PADA=007ffbf0
// @ref ?buddy_guest_timeout_7ffbd0@@3PADA=007ffbd0
// @ref ?buddy_guest_done_7ffbb4@@3PADA=007ffbb4
// @ref ?buddy_skirmish_7ffb98@@3PADA=007ffb98
// @ref ?buddy_host_start_7ffb74@@3PADA=007ffb74
// @ref ?buddy_guest_start_7ffb50@@3PADA=007ffb50
// @ref ?Buddy_Dialog_Proc_00758750@@YGHPAUHWND__@@IIJ@Z=00758750
// @ref ?Host_Game_007459a0@@YI_NXZ=007459a0
// @ref ?End_Dialog_007357e0@@YI_NPAUHWND__@@H@Z=007357e0

inline bool Refresh_Game_List()
{
    if (!Request_Game_Channel_List_0073df10(0, true)) {
        Debug_Printf(buddy_guest_list_failed_7ffcd0);
        SetEvent(wol_wait_events_b264f8[5]);
        return false;
    }
    return true;
}

inline void Disconnected(HWND dialog, int line)
{
    Close_Wonline_Wait(~0u);
    unknown_dialog_5ff6e0(dialog);
    unknown_online_option_a3d2a8 = 0;
    Message_Box_005c3230(StringTable::Load_String(wol_youre_discon_label_7fe1fc, 0, wol_source_file_007fd62c, line), 0, connection_wait_callback_0073c120, false);
}

inline bool Request_Chat_Channels()
{
    return Queue_Channel_List_Request_0073db20(0, 0, true);
}

inline void Reset_Wait_Event(DWORD event)
{
    ResetEvent(wol_wait_events_b264f8[event]);
}

int __fastcall Unknown_00759370(bool first_time)
{
    unknown_b2abd9 = false;
    unknown_b2ac40 = 0;
    Unknown_00514EE0();
    if (!Request_Chat_Channels()) {
        unknown_online_option_a3d2a8 = 0;
        return 0;
    }
    Leave_Current_Channel_00744610(0x40, true);
    unknown_channels_b29478.Clear_00766400();
    for (;;) {
        SimpleWonlineDialogControl control;
        Reset_Wait_Events();
        HWND dialog = unknown_create_dialog_5ff610(0x116, Buddy_Dialog_Proc_00758750, (int)&control);
        unknown_dialog_5ff7c0(dialog);
        while (!control.unknown_slot2()) {
            DWORD event = WaitForMultipleObjects(18, wol_wait_events_b264f8, 0, 100);
            while (event == 0x102 && !control.unknown_slot2()) {
                Unknown_0073e100();
                event = WaitForMultipleObjects(18, wol_wait_events_b264f8, 0, 100);
            }
            Reset_Wait_Event(event);
            if (event == 0) {
                Disconnected(dialog, 0x63f1);
                return 0;
            }
            if (event == 5) {
                Disconnected(dialog, 0x63f9);
                return 0;
            }
            unknown_517370(false);
        }
        unknown_dialog_5ff6e0(dialog);
        switch ((int)control.Get_Window_00601180()) {
        case 0x62b:
            Reset_Wait_Events();
            if (!Host_Game_007459a0()) {
                Debug_Printf(buddy_host_failed_7ffd50);
            } else {
                wol_lan_leave_b2abf0 = 0;
                do {
                    DWORD event;
                    do {
                        event = WaitForMultipleObjects(18, wol_wait_events_b264f8, 0, 20);
                        if (event == 0x102) {
                            Unknown_0073e100();
                        }
                    } while (event == 0x102 && !wol_lan_leave_b2abf0);
                    Reset_Wait_Event(event);
                    if (event == 0) {
                        Debug_Printf(buddy_host_abort_7ffd30);
                        wol_lan_leave_b2abf0 = 1;
                    }
                    if (event == 6) {
                        Debug_Printf(buddy_host_exit_7ffd10);
                        wol_lan_leave_b2abf0 = 1;
                    }
                    if (event == 15) {
                        Debug_Printf(buddy_skirmish_7ffb98);
                        unknown_b2ac04 = false;
                        unknown_server_error_b2a8ec[0] = 0;
                        unknown_b2abd9 = false;
                        return 2;
                    } else if (event == 7) {
                        Debug_Printf(buddy_host_start_7ffb74);
                        unknown_b2ac04 = false;
                        unknown_chat_a72cfc->unknown_slot09();
                        unknown_server_error_b2a8ec[0] = 0;
                        unknown_b2abd9 = true;
                        wol_lan_leave_b2abf0 = 0;
                        return 1;
                    }
                } while (!wol_lan_leave_b2abf0);
                Debug_Printf(buddy_host_stop_7ffcfc);
                wol_lan_leave_b2abf0 = 0;
            }
            Close_Wonline_Wait(~0u);
            Reset_Wait_Events();
            if (unknown_server_error_b2a8ec[0]) {
                Message_Box_005c3230(unknown_server_error_b2a8ec, 0, connection_wait_callback_0073c120, false);
            }
            while (End_Dialog_007357e0(0, 0)) {
            }
            unknown_b2abd9 = false;
            break;
        case 0x62d: {
            WOL::Channel channel;
            memset(&channel, 0, sizeof(channel));
            if (unknown_wstring_b29cd4.Length() > 0) {
                bool have_channel;
                {
                    WOL::Channel *found = 0;
                    have_channel = unknown_channels_b29478.Get_Pointer_00767cf0(unknown_wstring_b29cd4, &found);
                    if (have_channel && found) channel = *found;
                }
                if (have_channel) {
                    int kind = 0;
                    bool have_kind;
                    {
                        unsigned int *value = 0;
                        have_kind = unknown_names_b29848.Get_Pointer_00767bb0(unknown_wstring_b29cd4, &value);
                        if (have_kind && value) kind = *value;
                    }
                    if (have_kind) {
                        switch (kind) {
                        case 4: {
                            WOL::Channel lobby;
                            memset(&lobby, 0, sizeof(lobby));
                            unknown_online_option_a3d2a8 = 3;
                            for (int i = 0; i < unknown_lobbies_b26c88.Count; i++) {
                                unknown_lobbies_b26c88.Get(lobby, i);
                                if (!_stricmp(lobby.name, channel.name)) {
                                    unknown_b2abec = atol(channel.name + strlen(lobby_prefix_007fd358));
                                    unknown_7fd354 = false;
                                    return 0;
                                }
                            }
                            return 0;
                        }
                        case 5: {
                            Wstring name(channel.name);
                            WOL::Channel game;
                            if (!Find_Channel_By_Name_007592d0(name, unknown_games_b29990, game)) {
                                bool const &ok = Refresh_Game_List() ? Find_Channel_By_Name_007592d0(name, unknown_games_b29990, game) : false;
                                if (!ok) {
                                    Debug_Printf(buddy_guest_find_failed_7ffca0);
                                    goto guest_done;
                                }
                            }
                            if (!Join_Game_Channel_00745780(&game, unknown_a72c68)) {
                                Debug_Printf(buddy_guest_join_failed_7ffc7c);
                            } else {
                                wol_lan_leave_b2abf0 = 0;
                                int timeout = 500;
                                do {
                                    DWORD event = WaitForMultipleObjects(18, wol_wait_events_b264f8, 0, 20);
                                    while (event == 0x102 && !wol_lan_leave_b2abf0) {
                                        Unknown_0073e100();
                                        event = WaitForMultipleObjects(18, wol_wait_events_b264f8, 0, 20);
                                    }
                                    Reset_Wait_Event(event);
                                    if (event == 0) {
                                        Debug_Printf(buddy_guest_abort_7ffc5c);
                                        wol_lan_leave_b2abf0 = 1;
                                    }
                                    if (event == 6) {
                                        Debug_Printf(buddy_guest_exit_7ffc3c);
                                        wol_lan_leave_b2abf0 = 1;
                                    }
                                    if (event == 5) {
                                        Debug_Printf(buddy_guest_error_7ffc1c);
                                        wol_lan_leave_b2abf0 = 1;
                                    }
                                    if (event == 10) {
                                        Debug_Printf(buddy_guest_join_fail_7ffbf0);
                                        wol_lan_leave_b2abf0 = 1;
                                    }
                                    if (event == 7) {
                                        Debug_Printf(buddy_guest_start_7ffb50);
                                        unknown_b2ac04 = false;
                                        unknown_chat_a72cfc->unknown_slot09();
                                        unknown_server_error_b2a8ec[0] = 0;
                                        unknown_b2abd9 = true;
                                        wol_lan_leave_b2abf0 = 0;
                                        return 1;
                                    }
                                    if (timeout-- < 0) {
                                        Debug_Printf(buddy_guest_timeout_7ffbd0);
                                        break;
                                    }
                                } while (!wol_lan_leave_b2abf0);
                                wol_lan_leave_b2abf0 = 0;
                                Debug_Printf(buddy_guest_done_7ffbb4);
                            }
                            guest_done:
                            break;
                        }
                        }
                    }
                }
            }
            break;
        }
        case 0x5c0:
        case 0x686:
            if (unknown_online_option_a3d2a8 == 3) {
                unknown_7fd354 = false;
            }
            return 0;
        default:
            break;
        }
    }
}
