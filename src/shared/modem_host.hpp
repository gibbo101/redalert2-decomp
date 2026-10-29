// The modem host's game setup dialog (ModemHst.cpp, 0x00598C20-0x0059D58F; the
// header statics are 0x00598C20-0x00598E0F). The class name follows the
// "ModemHost.Dialog" debug output (hypothesis); Select_Serial_Dialog keeps the
// object on its stack. The layout comes from ModemHost::Dialog (0x00598E10).
#ifndef RA2_SHARED_MODEM_HOST_HPP
#define RA2_SHARED_MODEM_HOST_HPP

#include "shared/win32_api.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/gdlg_supp.hpp"

// The colour shown for a player colour outside 0..7 (0x007A737C, 0x0040FFFF).
extern int unknown_color_7a737c;

// The RGB value of a player colour (unknown_color_values_7e6d94; others show unknown_color_7a737c).
inline int Player_Color_RGB(int color)
{
    return (color >= 0 && color < 8) ? unknown_color_values_7e6d94[color] : unknown_color_7a737c;
}

class ModemHost {
public:
    // Runs the dialog until the game starts (true) or the host leaves (0x00598E10).
    bool Dialog_00598e10();
    // The dialog procedure (0x00598FA0; DWL_USER holds the ModemHost).
    static int __stdcall Dialog_Proc_00598fa0(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
    // Fills the dialog's controls from the session (0x00599920).
    void Init_Dialog_00599920();
    // Reads the dialog's controls into the session; false (with a message) when the map has
    // fewer start positions than the players (0x0059A310).
    bool Read_Dialog_0059a310();
    // Starts the game: the player list, the GO handshake and the scenario transfer; false
    // when the game does not start (0x0059C290).
    bool Start_Game_0059c290(bool load_game);
    // The option controls: each reads its control into the session and marks
    // the options for sending (0x0059AC80-0x0059B050).
    void Read_Unit_Count_0059ac80();
    void Read_Tech_Level_0059acb0();
    void Read_Credits_0059ace0();
    void Read_AI_Players_0059ad10();
    void Read_Game_Speed_0059ad40();
    void Read_AI_Difficulty_0059ad80();
    void Read_MCV_Redeploy_0059adb0();
    void Read_Bases_0059adf0();
    void Read_Crates_0059ae60();
    void Read_Fog_Of_War_0059aea0();
    void Read_Bridge_Destroy_0059aee0();
    void Read_Harvester_Truce_0059af20();
    void Read_Short_Game_0059af60();
    void Read_unknown_2b_0059afd0();
    void Read_Short_Game_0059b010();
    void Read_Crap_Engineers_0059b050();
    // Sends the chat edit line (0x540) to the guest and shows it in the chat list (0x53F) (0x0059A880).
    void Send_Chat_0059a880();
    // The colour combo (0x667): its row's colour entry (0x0059AA20).
    void Read_Color_Entry_0059aa20();
    // The colour list (0x405): the local colour (0x0059AA80).
    void Read_Color_0059aa80();
    // The name edit (0x5C1): the local name, written back trimmed unless keep (0x0059AAF0).
    void Read_Name_0059aaf0(bool keep);
    // Shows the guest's name, colour and country (0x668) when they change (0x0059AB80).
    void Set_Guest_0059ab80(unsigned short const *name, int color, int house);

    // Sends a chat text to the guest and shows it in the chat list (0x0059BFA0).
    void Send_Chat_0059bfa0(unsigned short const *text);
    // Shows a chat line "[name] text" in the player colour (0x0059C0B0).
    void Show_Chat_0059c0b0(unsigned short const *name, int color, unsigned short const *text);
    // Services the connection: sends the options when changed (at most every 30 ticks) or
    // when forced, and a timing packet every 40 ticks (0x0059B560).
    void Service_0059b560(bool force);
    // Sends the game options packet (0x0059BC90).
    void Send_Options_0059bc90();
    // Answers the guest's preview request (command 0x77): uploads the map preview (0x0059C8B0).
    void Send_Preview_0059c8b0();
    // Handles the guest's messages; true when the guest timed out (a message box unless quiet) (0x0059B690).
    bool Process_Messages_0059b690(bool quiet);
    // Sends the sign-off to the guest and waits up to 300 ticks for it to go out (or the guest's
    // own sign-off), then shuts the modem down (0x0059C130).
    void Sign_Off_0059c130();
    // The idle callback while another dialog waits: services the host dialog (0x0059C880).
    static bool Idle_0059c880();

    HWND Window;                    // +0x00 the dialog
    int Result;                     // +0x04 -1 while running, 1 start, 2 cancelled (hypothesis)
    bool Changed;                   // +0x08 the settings are saved on exit
    bool OptionsChanged;            // +0x09 the options are sent to the guest
    char unknown_0a[0x0C - 0x0A];
    unsigned long OptionsTime;      // +0x0C when the options were last sent
    unsigned long GuestResponseTime;    // +0x10 from the guest's timing packet (10000)
    unsigned long ReceiveTime;      // +0x14 when the last message arrived
    unsigned long ReceiveTimeout;   // +0x18 (1200)
    unsigned long TimingTime;       // +0x1C when the last timing packet was sent
    bool unknown_20;                // +0x20
    unsigned short GuestName[20];   // +0x22 the guest's name as shown
    int GuestColor;                 // +0x4C (-1 unknown)
    int GuestHouse;                 // +0x50 (-1 unknown)
    int unknown_54;                 // +0x54 Unknown_006525F0 (the INI checksum sum)
    int unknown_58;                 // +0x58 unknown_art_ini_unique_id
    int unknown_5c;                 // +0x5C unknown_ini_8397a0_unique_id
};

// INI checksums (shared/modem_host.hpp declares them for the dialog; sources in unowned/).
int __fastcall Unknown_006525F0();      // 0x006525F0
void __fastcall Read_Art_INI();         // 0x00652730
int unknown_art_ini_unique_id();        // 0x00652710
int unknown_ini_8397a0_unique_id();     // 0x00652720

// The running host dialog (0x00A70DE4; null outside ModemHost::Dialog).
extern ModemHost *unknown_modem_host_a70de4;

#endif
