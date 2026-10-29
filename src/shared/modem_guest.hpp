// The modem guest's game setup dialog (ModemGst.cpp, 0x00595E20-0x00598C1F; the
// header statics are 0x00595E20-0x0059600F). The class name follows the
// "ModemGuest.Dialog" debug output (hypothesis); like ModemHost it is not
// polymorphic. The layout comes from ModemGuest::Dialog (0x00596010).
#ifndef RA2_SHARED_MODEM_GUEST_HPP
#define RA2_SHARED_MODEM_GUEST_HPP

#include "shared/win32_api.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/modem_host.hpp"
#include "shared/lobby.hpp"

struct UnknownSerialPacket;

class ModemGuest {
public:
    // Runs the dialog until the game starts (true) or the guest leaves (0x00596010).
    bool Dialog_00596010();
    // The dialog procedure (0x00596170; DWL_USER holds the ModemGuest).
    static int __stdcall Dialog_Proc_00596170(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
    // Fills the dialog's controls (0x00596540).
    void Init_Dialog_00596540();
    // Reads the guest's name and colour choices from the dialog (0x00596D50).
    void Read_Dialog_00596d50();
    // Sends the chat edit line (0x540) to the host and shows it in the chat list (0x53F) (0x00596E30).
    void Send_Chat_00596e30();
    // The colour combo (0x667): its row's colour entry (0x00596FC0).
    void Read_Color_Entry_00596fc0();
    // The colour list (0x405): the local colour, never the host's (0x00597010).
    void Read_Color_00597010();
    // The name edit (0x5C1): the local name, written back trimmed unless keep (0x005970B0).
    void Read_Name_005970b0(bool keep);
    // Shows the host's name, colour and country (0x668) (0x00597130).
    void Set_Host_00597130(unsigned short const *name, int color, int house);
    // Shows the session's options the host sent in the dialog's controls (0x00597220).
    void Show_Options_00597220();
    // Disables OK and sends command 0x74 to the host (0x005974F0).
    void Send_Ready_005974f0();
    // Services the connection: sends the guest's options when changed (at most every 30 ticks)
    // or when forced, and a timing packet every 40 ticks (0x00597550).
    void Service_00597550(bool force);
    // Handles the host's messages; true when the dialog ends (0x00597680).
    bool Process_Messages_00597680();
    // Sends the guest's options packet (command 0x65) (0x00598330).
    void Send_Options_00598330();
    // Sends a chat text to the host and shows it in the chat list (0x00598400).
    void Send_Chat_00598400(unsigned short const *text);
    // Shows a chat line "[name] text" in the player colour (0x00598510).
    void Show_Chat_00598510(unsigned short const *name, int color, unsigned short const *text);
    // Sends the sign-off to the host and waits up to 300 ticks for it to go out (or the host's
    // own sign-off), then shuts the modem down (0x00598590).
    void Sign_Off_00598590();
    // The host's GO: the guest and host player entries, the GO acknowledgement and the game
    // options; false when unknown is set or the player list is incomplete (0x005986F0).
    bool Start_Game_005986f0(bool unknown);
    // Takes the host's game options (command 0x65) into the session; false when nothing
    // changed. A new map clears the map preview (0x00597E50).
    bool Receive_Options_00597e50(UnknownSerialPacket const *packet);
    // The host's map preview: acknowledges preview mode, receives the image file and
    // makes the dialog's preview from it (0x005989B0).
    void Receive_Preview_005989b0();

    HWND Window;                    // +0x00 the dialog
    int Result;                     // +0x04 -1 while running, 1 start, 2 cancelled (hypothesis)
    bool Changed;                   // +0x08 the settings are saved on exit
    bool OptionsChanged;            // +0x09 the guest's options are sent to the host
    char unknown_0a[0x0C - 0x0A];
    unsigned long OptionsTime;      // +0x0C when the options were last sent
    unsigned long HostResponseTime; // +0x10 (10000)
    unsigned long ReceiveTime;      // +0x14 when the last message arrived
    unsigned long ReceiveTimeout;   // +0x18 (1200)
    unsigned long TimingTime;       // +0x1C when the last timing packet was sent
    unsigned short HostName[20];    // +0x20 the host's name as shown
    int HostColor;                  // +0x48 (-1 unknown)
    int HostHouse;                  // +0x4C (-1 unknown)
    int unknown_50;                 // +0x50 Unknown_006525F0 (the INI checksum sum)
    int unknown_54;                 // +0x54 unknown_art_ini_unique_id
    int unknown_58;                 // +0x58 unknown_ini_8397a0_unique_id
};

// Narrows a wide string into dst, stopping at the terminator or after limit characters (-1: none; 0x006FA0F0).
void __fastcall Unknown_006FA0F0(char *dst, unsigned short const *src, int limit);

// The row of a combo box whose item data is data, searching after the row start (0x00736E10).
int __fastcall Find_Combo_Item_Data_00736e10(HWND combo, int start, int data);

#endif
