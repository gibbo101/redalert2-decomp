// The multiplayer lobby's slot tables (Lobby code around 0x005C8950-0x005CF000;
// names are hypotheses from the slot logic). Seven fixed lobby entries (open,
// closed, computer, ...: NodeNameType-shaped records) and eight player slots,
// each pointing at one of those entries or at a session node.
#ifndef RA2_SHARED_LOBBY_HPP
#define RA2_SHARED_LOBBY_HPP

#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/unknown_player_entry.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/wstring.hpp"
#include "shared/network_tests.hpp"
#include "shared/win32_api.hpp"
#include "shared/wide_string.hpp"
class MultiplayerGameMode;

// The first six fixed entries (0x00A72D2C..0x00A72D40, separate objects: the compiler keeps them in
// registers as scalars); the seventh is unknown_player_a72d44 (OpenObserver). Their names follow the
// lobby names Unknown_Lobby_Entry_Name_005cd0e0 gives them. The eight player slots are
// unknown_player_slots_a3fa98 and the session list unknown_players_a3fa7c.
extern NodeNameType *unknown_open_entry_a72d2c;
extern NodeNameType *unknown_closed_entry_a72d30;
extern NodeNameType *unknown_easy_ai_entry_a72d34;
extern NodeNameType *unknown_medium_ai_entry_a72d38;
extern NodeNameType *unknown_hard_ai_entry_a72d3c;
extern NodeNameType *unknown_waiting_entry_a72d40;
// The slot before the table (0x00A3FA94; -1 after a reset).
extern int unknown_lobby_a3fa94;
// The slot names as Unknown_Slot_Names_005c8cf0 writes them (0x00A72734) and their previous value
// (0x00A728E4); a reset empties both, 0x005CA000 compares them (lengths not recovered).
extern wchar_t unknown_slot_names_old_a728e4[];
extern wchar_t unknown_slot_names_a72734[];
// The object at 0x00A3D2B0 (session +0x18) and its member 0x00672810 (hypothesis).
class UnknownLobbyState {
public:
    void Unknown_00672810();                    // 0x00672810
};
extern UnknownLobbyState unknown_lobby_state_a3d2b0;
// Three per-slot setting tables, -1 when a slot is cleared (0x00A3D2DC, 0x00A3D2FC,
// 0x00A3D31C; session +0x44, +0x64, +0x84: AIDifficulty, AICountry, AIColor).
extern int unknown_lobby_a3d2dc[8];
extern int unknown_lobby_a3d2fc[8];
extern int unknown_lobby_a3d31c[8];
// Refreshes one slot's display in the lobby dialog (0x005C9B90; hypothesis).
void __fastcall Unknown_005c9b90(HWND dialog, int slot, bool redraw);
// The names of the fixed lobby entries (pointers at 0x007E6DE8..0x007E6E00: "Open",
// "Closed", "Waiting", "EasyAI", "MediumAI", "HardAI", "OpenObserver").
extern char const *unknown_lobby_names_7e6de8[7];
// The dialog manager's current dialog ID (0x00735B20) and the dialog window with an ID, or 0
// (0x00735940); hypotheses from the one lobby caller.
int Current_Dialog_Id_00735b20();
// The selected row of the lobby campaign list (0x553 in the dialog 0x00A728E0; LB_GETCURSEL) (0x005C67A0).
int Selected_Campaign_005c67a0();
HWND __fastcall Find_Dialog_00735940(int id);
// 0 until the lobby is set up (0x007E6D90, initialised -1; hypothesis).
extern int unknown_lobby_flag_7e6d90;
// Sends a game options text to the other players (0x005C3C60; it passes the string to strncpy and the
// chat/pregame packet).
void __fastcall Send_Game_Options_005c3c60(char const *text);
// Selects the multiplayer map with this unknown_multi_missions_a3d8d8 index (-1: none) (0x005C7C30).
bool __fastcall Select_Scenario_005c7c30(int index);
// The lobby entry with this name (0x005CD1B0) and the fixed entry or session node whose name text equals
// the name (0x005C8B20).
NodeNameType *__fastcall Unknown_Find_Lobby_Entry_005cd1b0(WideString const &name);
NodeNameType *__fastcall Unknown_Find_Lobby_Name_005c8b20(wchar_t const *name);
// Seats the comma-separated lobby names in the player slots (0x005C8DD0).
void __fastcall Set_Slot_Names_005c8dd0(wchar_t const *names);
// Downloads the host's map preview image into the dialogs' map preview (0x005C7970).
void __fastcall Download_Map_Preview_005c7970();

// Wide-string comparison, 0 when equal (0x007837D3; the CRT's _wcsicmp).
int Compare_Wide_007837d3(wchar_t const *first, wchar_t const *second);
// Widens a narrow string into a rotating buffer (0x006FA180).
wchar_t *__fastcall Unknown_006FA180(char const *text);
// Case-insensitive comparison, 0 when equal (0x00781F20; the CRT's _stricmp).
int Compare_Narrow_00781f20(char const *first, char const *second);
// Frees a block (0x00781D3B; the CRT's free).
void Free_Memory_00781d3b(void *block);
// Frees every element of the list and clears it (0x005A7480).
void __fastcall Free_Pointers_005a7480(DynamicVectorClass<NodeNameType *> *list);

// Shows a game mode's description in a lobby dialog (0x005C3450; the mode's unknown_name_20).
void __fastcall Unknown_005c3450(HWND dialog, MultiplayerGameMode *mode);
// Sets a lobby dialog's text 0x5A8 from the session (0x005C34B0).
void __fastcall Unknown_005c34b0(HWND dialog);
// Refreshes a lobby dialog (0x005C7570).
void __fastcall Unknown_005c7570(HWND dialog);
// Sends the lobby state (0x005C3810; flags not recovered).
void __fastcall Unknown_005c3810(bool unknown_1, bool unknown_2);
// Starts a multiplayer game's pregame state (0x005C74F0).
void Unknown_Pregame_Setup_005c74f0();

// The index-matched player's value (+0x67) for a nick name, 1 for the host's own name, -1 when unknown (0x005BCC60).
int __fastcall Unknown_Find_Player_By_Name_005bcc60(char const *name);

// The name of a fixed lobby entry ("Waiting" for any other entry; 0x005CD0E0).
Wstring __fastcall Unknown_Lobby_Entry_Name_005cd0e0(NodeNameType *entry);

// The netshare.cpp slot helpers (0x005C6520..0x005CA540; names are hypotheses from the slot logic).
// The number of usable player slots: 2 or 4 in game mode 4 (by the network tests), else 8 (0x005C6520).
int Lobby_Slot_Limit_005c6520();
// The slot limit plus one, at most 4 in game mode 4 and 8 otherwise (0x005C6550).
int Lobby_Slot_Limit_Plus_One_005c6550();
// A multiplayer map's slot limit: its player count, lowered by the game mode's limit (slot 32)
// and by the game mode 4 network tests; 8 for no map (-1) (0x005C65A0).
int __fastcall Scenario_Slot_Limit_005c65a0(int scenario);
// Answers whether the local nick name is the host's name (0x005C86A0).
bool Is_Host_005c86a0();
// Answers whether a name is the local nick name (0x005C86C0).
int __fastcall Is_Local_Name_005c86c0(wchar_t const *name);
// The usable slots get the open entry and the rest the closed entry (0x005C8A10).
void Fill_Slots_005c8a10();
// Empties the four slot setting strings (0x005C8A70).
void Clear_Slot_Lists_005c8a70();
// The slots' colours and countries as "%d," lists (0x00A726D4, 0x00A726F8) and their previous
// values (0x00A726B0, 0x00A72A44); 0x005CA000 rebuilds them and compares (lengths not recovered).
extern char unknown_color_list_old_a726b0[];
extern char unknown_color_list_a726d4[];
extern char unknown_country_list_old_a72a44[];
extern char unknown_country_list_a726f8[];
// The slot holding the entry with this name, -1 when none (0x005C8C30).
int __fastcall Find_Slot_By_Name_005c8c30(wchar_t const *name);
// The slot of the first session player, -1 when there are none (0x005C8C70).
int Find_First_Player_Slot_005c8c70();
// Puts an entry into the first open slot (an observer entry, Team -1, into the first observer
// slot); the slot, or -1 when none (0x005C9170).
int __fastcall Assign_Slot_005c9170(NodeNameType *entry);
// Answers whether no open slot is left among the players (0x005C9440).
bool Slots_Filled_005c9440();
// Answers whether no slot holds the observer entry (0x005C9490).
bool No_Observer_Slot_005c9490();
// Answers whether the player in slot unknown_lobby_flag_7e6d90 is an observer (Team -1) (0x005C94B0).
bool Unknown_005c94b0();
// The kind of a slot entry: 2..6 for the first five fixed entries, 7 for the observer entry,
// 2 otherwise (0x005C9650).
int __fastcall Entry_Kind_005c9650(NodeNameType *entry);
// A slot's combo box ID (0x411..0x418; -1 for no slot) (0x005C97A0).
int __fastcall Slot_Control_Id_005c97a0(int slot);
// The slot of a combo box ID (-1 for none) (0x005C9800).
int __fastcall Control_Slot_005c9800(int id);
// A slot's colour: the computer entries' table value, -2 for the fixed entries, the
// player's colour otherwise (0x005CA480).
int __fastcall Slot_Color_005ca480(int slot);
// A slot's colour combo box ID (0x6D2..0x6D9; -1 for no slot) (0x005CA4E0).
int __fastcall Slot_Color_Control_Id_005ca4e0(int slot);
// Updates a dialog's observer controls from the observer mode switch: the check box 0x760, the
// image 0x75F (wolob.pcx or wolnob.pcx) and the texts of 0x6CD and 0x62D (Observe, Join or JoinGame) (0x005CD3F0).
void __fastcall Unknown_005cd3f0(HWND dialog);
// Updates the observer controls of a dialog and of the dialogs 0x116, 0x113 and 0xBB (0x005CD540).
void __fastcall Unknown_005cd540(HWND dialog);

// The netshare.cpp slot helpers (0x005C6520..0x005CA540; names are hypotheses from the slot logic).
// The number of usable player slots: 2 or 4 in game mode 4 (by the network tests), else 8 (0x005C6520).
int Lobby_Slot_Limit_005c6520();
// The slot limit plus one, at most 4 in game mode 4 and 8 otherwise (0x005C6550).
int Lobby_Slot_Limit_Plus_One_005c6550();
// A multiplayer map's slot limit: its player count, lowered by the game mode's limit (slot 32)
// and by the game mode 4 network tests; 8 for no map (-1) (0x005C65A0).
int __fastcall Scenario_Slot_Limit_005c65a0(int scenario);
// Answers whether the local nick name is the host's name (0x005C86A0).
bool Is_Host_005c86a0();
// Answers whether a name is the local nick name (0x005C86C0).
int __fastcall Is_Local_Name_005c86c0(wchar_t const *name);
// The usable slots get the open entry and the rest the closed entry (0x005C8A10).
void Fill_Slots_005c8a10();
// Empties the four slot setting strings (0x005C8A70).
void Clear_Slot_Lists_005c8a70();
// The slots' colours and countries as "%d," lists (0x00A726D4, 0x00A726F8) and their previous
// values (0x00A726B0, 0x00A72A44); 0x005CA000 rebuilds them and compares (lengths not recovered).
extern char unknown_color_list_old_a726b0[];
extern char unknown_color_list_a726d4[];
extern char unknown_country_list_old_a72a44[];
extern char unknown_country_list_a726f8[];
// The slot holding the entry with this name, -1 when none (0x005C8C30).
int __fastcall Find_Slot_By_Name_005c8c30(wchar_t const *name);
// The slot of the first session player, -1 when there are none (0x005C8C70).
int Find_First_Player_Slot_005c8c70();
// Puts an entry into the first open slot (an observer entry, Team -1, into the first observer
// slot); the slot, or -1 when none (0x005C9170).
int __fastcall Assign_Slot_005c9170(NodeNameType *entry);
// Answers whether no open slot is left among the players (0x005C9440).
bool Slots_Filled_005c9440();
// Answers whether no slot holds the observer entry (0x005C9490).
bool No_Observer_Slot_005c9490();
// Answers whether the player in slot unknown_lobby_flag_7e6d90 is an observer (Team -1) (0x005C94B0).
bool Unknown_005c94b0();
// The kind of a slot entry: 2..6 for the first five fixed entries, 7 for the observer entry,
// 2 otherwise (0x005C9650).
int __fastcall Entry_Kind_005c9650(NodeNameType *entry);
// A slot's combo box ID (0x411..0x418; -1 for no slot) (0x005C97A0).
int __fastcall Slot_Control_Id_005c97a0(int slot);
// The slot of a combo box ID (-1 for none) (0x005C9800).
int __fastcall Control_Slot_005c9800(int id);
// A slot's colour: the computer entries' table value, -2 for the fixed entries, the
// player's colour otherwise (0x005CA480).
int __fastcall Slot_Color_005ca480(int slot);
// A slot's colour combo box ID (0x6D2..0x6D9; -1 for no slot) (0x005CA4E0).
int __fastcall Slot_Color_Control_Id_005ca4e0(int slot);
// Updates a dialog's observer controls from the observer mode switch: the check box 0x760, the
// image 0x75F (wolob.pcx or wolnob.pcx) and the texts of 0x6CD and 0x62D (Observe, Join or JoinGame) (0x005CD3F0).
void __fastcall Unknown_005cd3f0(HWND dialog);
// Updates the observer controls of a dialog and of the dialogs 0x116, 0x113 and 0xBB (0x005CD540).
void __fastcall Unknown_005cd540(HWND dialog);
// A slot's country: the computer entries' table value, the game mode's default (slot 10 in game
// modes 3 and 4, else -2) for the fixed entries, -3 for the observer entry, the player's otherwise (0x005CA3F0).
int __fastcall Slot_Country_005ca3f0(int slot);
// Stores a side combo box's choice: the host's own country, or a computer slot's table value
// (other slots clear their three table values) (0x005C9A10).
void __fastcall Set_Slot_Country_005c9a10(HWND dialog, int id);
// Enables every slot's combo box and refreshes the slots, the given one last with a redraw (0x005C9CF0).
void __fastcall Refresh_Slots_005c9cf0(HWND dialog, int slot);
// Answers whether the channel is full: more session players (an observer in the observer slot
// not counted) than the map allows (0x005C9510).
bool Channel_Full_005c9510();
// Loads the map preview of a random map (RandMap.img) when the selected map is one, then
// repaints the dialog; refreshes the dialog otherwise or when there is no preview (0x005CC800).
void __fastcall Load_Random_Map_Preview_005cc800(HWND dialog);
// The string of a slot entry's type (STT:PlayerOpen .. STT:PlayerOpenObserver, STT:PlayerHuman for
// a player) (0x005C9870).
wchar_t const *__fastcall Entry_Type_Name_005c9870(NodeNameType *entry);
// Stores a colour combo box's choice: the host's own colour (random when taken), or a slot's
// table value (0x005C9AB0).
void __fastcall Set_Slot_Color_005c9ab0(HWND dialog, int id);
// Answers whether a colour is taken by a player slot or a slot table value (-2 never is) (0x005C95D0).
bool __fastcall Unknown_Is_Color_Taken_005c95d0(int color);
// Puts a fixed entry into a slot's combo box (0x005CBF20; the last argument hypothesised as a
// send-update flag).
void __fastcall Unknown_005cbf20(HWND dialog, int id, NodeNameType *entry, int update);
// Opens or closes the slots from first on (open within the slot limit, closed beyond; the observer
// slot keeps its entry), refreshes the rows and sends the lobby state (0x005CB7C0).
void __fastcall Reset_Slots_From_005cb7c0(HWND dialog, int first);
// Adds count slots from first on (0x005CAE00), and shows the observer slot's row (the side and colour
// combo boxes hidden for an observer) (0x005CAFD0).
void __fastcall Unknown_005cae00(HWND dialog, int first, int count);
void __fastcall Unknown_005cafd0(HWND dialog);
// Changes the number of slot rows from old_count to new_count (each limited to the slot limit
// unless the game mode lifts it) (0x005CB300).
void __fastcall Change_Slot_Count_005cb300(HWND dialog, int old_count, int new_count, UnknownSessionA3D29C *mode);
// The chat's lobby refresh (0x007412F0) and the LAN one (0x005BBDC0, a thunk to 0x005BBDD0).
void unknown_call_73fee0_default();
void Unknown_005bbdc0();
// Records a player's map state (0: no map, 2: transfer; the host's own name always reads 1) and
// announces the missing map or its transfer; 0 is the local nick name (0x005C3F00).
void __fastcall Set_Player_Map_State_005c3f00(char const *name, int state);
// Disables every slot's combo box and refreshes the slots, then enables the given one and
// refreshes it with a redraw (0x005C9DA0).
void __fastcall Lock_Slots_005c9da0(HWND dialog, int slot);
// The lobby campaign dialog (0x6B): its procedure (0x005C69E0), its timer callback (0x005C67C0),
// and the opener (0x005C6960) that creates it over parent, keeps it in unknown_lobby_dialog_a728e0,
// shows it and starts the callback.
long __stdcall Lobby_Dialog_Proc_005c69e0(HWND window, unsigned message, unsigned wparam, long lparam);
bool Lobby_Dialog_Update_005c67c0();
int __fastcall Open_Lobby_Dialog_005c6960(HWND parent);
extern HWND unknown_lobby_dialog_a728e0;
// The dialog manager: creates a dialog from a template (0x00735700), prepares a created dialog
// (0x005FF7E0) and runs a dialog's update callback (0x007359E0; the last three arguments unknown; it returns
// the dialog's result, which 0x005C3230 returns).
typedef long (__stdcall *UnknownDialogProc)(HWND window, unsigned message, unsigned wparam, long lparam);
void *__fastcall unknown_create_dialog_735700(void *instance, int id, HWND parent, UnknownDialogProc procedure, long arg);
void __fastcall unknown_show_dialog_5ff7e0(void *dialog, int id);
int __fastcall Unknown_007359e0(HWND dialog, bool (*callback)(), int unknown_1, int unknown_2, int unknown_3);
// Shows each slot's status image: the host's (wolhost.pcx) for the host's own slot, the accepted
// one (wolacpt.pcx) for computer slots and players that accepted, none otherwise (0x005C9EC0).
void __fastcall Refresh_Slot_Images_005c9ec0(HWND dialog);
// The two status image names (0x007E6DB8 "wolhost.pcx", 0x007E6DBC "wolacpt.pcx").
extern char const *unknown_host_image_7e6db8;
extern char const *unknown_accept_image_7e6dbc;
// Answers whether the slots from count on (count + 1 without an observer slot) hold a player whose
// country is set, or (unless the flags say otherwise) a computer or an observer (0x005CBDB0;
// the two flags are hypotheses).
bool __fastcall Unknown_005cbdb0(HWND dialog, int count, bool unknown_1, bool unknown_2);
// Refills count slot combo boxes from first on with their entries (players kept, the others open
// within the slot limit and closed beyond; the observer slot untouched), then adds them (0x005CB3F0).
void __fastcall Unknown_005cb3f0(HWND dialog, int first, int count);
// Selects every slot's colour in its colour combo box, the local player's slot first (0x005CA540).
void __fastcall Refresh_Slot_Colors_005ca540(HWND dialog);
// The lobby dialog's selected map (unknown_multi_missions_a3d8d8 index; 0x00A728D0), the map the
// session takes when it changes (0x00A72C80; hypothesis) and the selected row's text (0x00A72A68).
extern int unknown_lobby_map_a728d0;
extern int unknown_lobby_map_a72c80;
extern wchar_t unknown_lobby_map_name_a72a68[];
// The random map's identity text: the CRC of the map generator's seed options (0x140 bytes from Theater, the
// description buffer cleared while it runs) as "%08X" in a new 12-character buffer (0x005C8420).
char *Random_Map_CRC_005c8420();
// The per-mode services the lobby dialog runs (LAN 0x005BBD10, World Online 0x0073E100,
// modem/serial 0x0059C880; hypotheses from the game modes).
bool Unknown_005bbd10();
bool Unknown_0073e100();
bool Unknown_0059c880();

// Answers whether a slot's entry has accepted: a computer entry, or a player whose unknown_67 is 1
// (0x005CA3B0).
int __fastcall Is_Accepted_Slot_005ca3b0(int slot);
// Refreshes the slots' flags, side and colour combo boxes; with full set first rebuilds the slot rows
// (0x005CA6C0), else only redoes what changed since the last call: the status images, the slot names
// (0x00A728E4 old, 0x00A72734 new), the countries and the colours (0x005CA000).
void __fastcall Refresh_Slot_Settings_005ca000(HWND dialog, bool full);
void __fastcall Unknown_005ca6c0(HWND dialog);
// Writes the names of the eight slots' entries, each followed by a comma (0x005C8CF0).
void __fastcall Unknown_Slot_Names_005c8cf0(wchar_t *list);
// The World Online lobby's slot refresh (0x0075B0C0; game mode 4).
void Unknown_0075b0c0();
extern "C" wchar_t *__cdecl wcscpy(wchar_t *dest, wchar_t const *source);   // 0x00783689
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);       // 0x007820F4
extern "C" char *__cdecl strcpy(char *dest, char const *source);
extern "C" char *__cdecl strcat(char *dest, char const *source);
extern "C" int __cdecl strcmp(char const *first, char const *second);

// Rotating hashes of a narrow and a wide name (0x005C2BA0, 0x005C2BF0; the WOL hash tables take their addresses).
unsigned int __fastcall Hash_Name_005c2ba0(Wstring const &name);
unsigned int __fastcall Hash_Wide_Name_005c2bf0(WideString const &name);
// The first open dialog of 0xC2, 0xC9, 0xBC, 0xBD (0x005C2C40).
HWND Find_Lobby_Window_005c2c40();
// The session's game mode object, else the first registered mode (0x005C34D0).
MultiplayerGameMode *Current_Game_Mode_005c34d0();
// Runs slot 31 of the selected (dialog 0x6B) or the session's game mode (0x005C34F0).
void __fastcall Unknown_005c34f0();
// A lobby flag (0x00A3FAB8, session +0x2820) that 0x005C3C20 sets and 0x005C3C40 clears before running the
// chat's (0x0075C980, 0x0075CA00) or the LAN's (0x005C28E0, 0x005C2940) handlers.
extern bool unknown_lobby_flag_a3fab8;
void Unknown_005c3c20();
void Unknown_005c3c40();
void Unknown_0075c980();
void Unknown_0075ca00();
// Unknown_005c28e0 is __fastcall: its own register setups come before its pushes (0x005C28E0 tells the
// joiners that the host started the game, GUI:HostGameStartJoiner, unless the local player is the host).
void __fastcall Unknown_005c28e0();
void Unknown_005c2940();

// The dialog manager's window before this one in its stack, 0 for none (0x007359B0; keys are windows here).
int __fastcall unknown_previous_key(int key);
extern "C" int __cdecl vswprintf(wchar_t *buffer, wchar_t const *format, char *arguments);   // 0x00783A58

// Sends every other player a global packet 0x28 with the local nick name (0x005C3AE0); game mode 3 does
// that and game mode 4 runs 0x0075C960 (0x005C3B70).
void Unknown_005c3ae0();
void Unknown_005c3b70();
void Unknown_0075c960();
// A plain lobby message dialog's procedure (0x005C33A0).
long __stdcall Unknown_Dialog_Proc_005c33a0(HWND window, unsigned message, unsigned wparam, long lparam);

// A window's wide text (0x00600E50).
LRESULT __fastcall unknown_get_window_wide_text(HWND window, WideString &text);
// An edit control's text limited for a lobby name: 0x78 characters, or for text that is not narrow the
// run of characters up to 0x100 less one (at least 0x28); the control gets the shortened text, and the
// result has trailing line breaks removed (0x005CCF50).
WideString __fastcall Limit_Name_Text_005ccf50(HWND control);

class HouseClass;
// Counts the teams among the live houses (0x005C3150).
int __fastcall Count_Teams_005c3150(HouseClass *exclude);

// A list box item's wide text (0x00600F10).
LRESULT __fastcall unknown_get_list_item_wide_text(HWND window, WPARAM index, WideString &text);
// Adds a progress dot to the last line of the current dialog's chat list 0x53F (a new line after 0x24
// characters) (0x005C3040).
void __fastcall Add_Chat_Dot_005c3040();

extern "C" wchar_t *__cdecl wcsncpy(wchar_t *dest, wchar_t const *source, unsigned int count);   // 0x00783622
extern "C" wchar_t *__cdecl wcschr(wchar_t const *string, wchar_t character);                   // 0x00783AC6
// The line buffer of Add_List_Text_005c2f20 (0x00A71EA8).
extern wchar_t unknown_list_text_a71ea8[0x200];
// Adds length characters of text (cut at the first line break) as a line of a list box, colour -1 the
// default; the oldest line goes beyond 500, and the list stays scrolled to the bottom when it was (0x005C2F20).
void __fastcall Add_List_Text_005c2f20(HWND list, wchar_t const *text, int length, int color);

extern "C" unsigned int __cdecl wcslen(wchar_t const *string);     // 0x00783605
// A button helper of the message box (0x005E8FA0; with the flag on the OK button).
void __fastcall Unknown_005e8fa0(HWND button);
// Shows a lobby message box with text and runs it with callback: kind 0 an OK button, 1 OK and Cancel, 4 Yes
// and No (dialog 0x126; 0xD0, 0xFC and 0xFB otherwise, 0xFB with flag); 0 for no text, else the result
// (0x005C3230).
int __fastcall Message_Box_005c3230(wchar_t const *text, int kind, bool (*callback)(), bool flag);

extern "C" wchar_t *__cdecl _wcsdup(wchar_t const *string);       // 0x00797033
extern "C" void __cdecl free(void *block);                         // 0x007825E8
extern "C" int __cdecl iswgraph(unsigned short character);          // 0x00784AE6 (ctype mask 0x117)

// The fixed entries' display texts, loaded once (0x00A72D0C..0x00A72D24: GUI:Open, GUI:Closed, GUI:AIEasy,
// GUI:AINormal, GUI:AIHard, GUI:Waiting, GUI:OpenObserver).
extern wchar_t const *unknown_lobby_texts_a72d0c[7];
// Loads those texts and makes each missing fixed entry with its text as the name (0x005C86E0).
void __fastcall Init_Lobby_Entries_005c86e0();

// The netdlg2.cpp network dialog helpers (0x005BBD20..0x005C2933; names follow Red Alert's
// NETDLG.CPP where the body matches, hypotheses otherwise).
// Refreshes the LAN lobby; false from every netdlg2.cpp caller (0x005BBDD0).
void __fastcall Unknown_005bbdd0(bool unknown);
// Sends the slot names (global packet 0x16) to every other session player (0x005BBD20).
void Send_Slot_Names_005bbd20();
// Sets the country and colour of the slot whose entry has a name, updating the side and colour
// combo boxes of the dialog 0xBC (or 0xBD) when the observer choice changes; whether the
// country changed (0x005BCCF0).
int __fastcall Set_Slot_Country_Color_005bccf0(char const *name, int country, int color);
// The serial number: "Serial" under HKLM\SOFTWARE\Westwood\Red Alert 2 (22 '0's by default),
// decoded digit by digit with woldata.key; false without the key file (0x005BCE90).
bool __fastcall Get_Serial_005bce90(char *serial);
// Set while the options dialog is being filled: its procedure ignores messages (0x00A71E98).
extern bool unknown_lock_a71e98;
// The game options dialog's procedure: reads the speed, money and unit sliders and the option
// check boxes into the session (0x005BF9B0).
long __stdcall Options_Dialog_Proc_005bf9b0(HWND window, unsigned message, unsigned wparam, long lparam);
// Sends the chat line of the edit box 0x540 (longer than two characters) to the session players
// (join state 2) or the chat players, and shows it in colour (0x005BEE20).
void __fastcall Send_Chat_Message_005bee20(HWND dialog, int color, int unknown);
// Session flags (0x00A3F614, 0x00A3F616, session +0x237C/+0x237E; +0x237E is sent as the game's
// IsOpen) and 0x00A40D04 (session +0x3A6C); meanings not recovered.
extern bool unknown_session_a3f614;
extern bool unknown_session_a3f616;
extern bool unknown_session_a40d04;
// The narrow string a NET_ANSWER_PLAYER carries at +0x18 (0x00A71BC4).
extern char unknown_a71bc4[];
// The host's answers to NET_QUERY_GAME (NET_ANSWER_GAME) and NET_QUERY_PLAYER (NET_ANSWER_PLAYER,
// then the lobby state when the query names the first player); whether the packet was one of
// them (0x005C05F0; from Red Alert's Process_Global_Packet).
bool __fastcall Answer_Query_005c05f0(UnknownGlobalPacket *packet, IPXAddressClass *address);
// Looks for the scenario among the local maps (0x0066C5B0; Red Alert's Find_Local_Scenario) and asks
// the host for it (0x0066AEF0); both hypotheses.
bool __fastcall Find_Local_Scenario_0066c5b0(char *filename, int length, char *digest, bool official, bool unknown);
bool __fastcall Unknown_0066aef0(char *filename, int unknown_1, bool unknown_2);
// Sends a file to the other player ("Send_Remote_File" in the modem host's preview upload; 0x0066BB20).
bool __fastcall Send_Remote_File_0066bb20(char const *filename, int unknown_1, int unknown_2, int unknown_3);
// A joiner's start of the game: the scenario is found or fetched (NET_READY_TO_GO 0x13 to the host),
// the IPX timing is set from the response time; otherwise TXT_UNABLE_PLAY_WAAUGH and a sign-off
// (0x005BE3B0; from Red Alert's Net_Join_Dialog).
bool __fastcall Start_Joined_Game_005be3b0();
// Three join request values (0x00A71E9C, 0x00A71EA0, 0x00A71EA4) and 0x00737AF0's (meanings not recovered).
extern int unknown_a71e9c;
extern int unknown_a71ea0;
extern int unknown_a71ea4;
int Unknown_00737af0();
// The version object (0x00A40C88; its two values go into a join request, 0x007131B0/0x007131C0).
struct UnknownVersionObject {
    // Resets the version clipping range (0x00713160; Red Alert's Init_Clipping).
    void Init_Clipping_00713160();
    // The version both sides can play for a peer's range: 0 when the peer is too old, -1
    // when this game is (0x00713170; Red Alert's VersionClass::Clip_Version).
    int Clip_Version_00713170(unsigned long min, unsigned long max);
    // The protocol of a version (0x00713130; Red Alert's Version_Protocol).
    int Version_Protocol_00713130(int version);
    unsigned long Unknown_007131b0();       // 0x007131B0 the minimum version (0x20000)
    unsigned long Unknown_007131c0();       // 0x007131C0 the maximum version (0x20000)
};
extern UnknownVersionObject version_object_00a40c88;
// Asks the host of a game to let the player join (NET_QUERY_JOIN); refused with a chat message and the
// SystemError sound without a game, with no name, a reserved name or a closed game (0x005BFC40; Red
// Alert's Request_To_Join).
int __fastcall Request_To_Join_005bfc40(int game, bool unknown);
// Whether a name is one of the seven fixed lobby entry names (0x005CD2F0).
bool __fastcall Unknown_Is_Lobby_Name_005cd2f0(Wstring const &name);
// Turns a joiner down (NET_REJECT_JOIN, REJECT_BY_OWNER; 0x005BC3E0).
void __fastcall Reject_Join_005bc3e0(NodeNameType *node);
// Unknown_005cbdb0 on the dialog 0xBC (0x005BC430).
bool __fastcall Unknown_005bc430(int count, bool unknown_1, bool unknown_2);
// Starts the IPX manager and resets the lobby (0x005BC460; Red Alert's Init_Network).
bool Init_Network_005bc460();
// Frees the lobby entries, clears the host's name and deletes the packet transport
// (0x005BC4D0; Red Alert's Shutdown_Network).
void Shutdown_Network_005bc4d0();
// Stores a value (+0x67) on the session player with a name (0 is the local nick name;
// the host's own name stores 1) and refreshes the lobby (0x005BCBC0).
void __fastcall Set_Player_Value_005bcbc0(char const *name, int value);
// Signs off (NET_SIGN_OFF) to the session players, the game's host and everyone, then
// clears the slots, the session list and the host's name (0x005C00B0; Red Alert's Unjoin_Game).
void __fastcall Unjoin_Game_005c00b0(int game);
// Frees the fixed lobby entries (0x005C8950) and resets the slots (0x005C8A90).
void Unknown_Free_Lobby_Entries_005c8950();
void Unknown_Reset_Slots_005c8a90();
// The join state of the network join dialog (0x00A71E94; 1 and 2 are joined or waiting,
// Red Alert's JOIN_CONFIRMED and JOIN_WAITING, hypothesis).
extern int unknown_join_state_a71e94;
// The players in the network chat (0x00A3FA4C, session +0x27B4; Red Alert's Session.Chat).
extern DynamicVectorClass<NodeNameType *> unknown_chat_a3fa4c;
// The selected game of the join dialog's list (0x00A71E90; Red Alert's game_index, hypothesis).
extern int unknown_game_index_a71e90;
// Removes the games and chat players not heard from: a game after 300 ticks (refreshing the
// game list, and leaving it when it is the selected one or above), a chat player after 360
// ticks, with a NET_CHAT_REQUEST after 300 (0x005BC500; from Red Alert's Net_Join_Dialog).
void __fastcall Process_Timeouts_005bc500();
// Refills the join dialog's (0xBB) game list 0x549: TXT_LOBBY, then each game, keeping
// the selection and the top row (0x005BC790).
void __fastcall Refresh_Game_List_005bc790();
// Sends the join dialog's queries (0x005C01D0; Red Alert's Send_Join_Queries): the game query every 120
// ticks or now (not from the dialog 0xBC), the player query of the selected game every 35 ticks or now,
// the chat announcement every 83 ticks (below join state 2) or now; init restarts the three timers.
void __fastcall Unknown_005c01d0(int gamenow, int playernow, int chatnow, int init);
// The games the join dialog has heard of (0x00A3FA64, session +0x27CC; Red Alert's Session.Games).
extern DynamicVectorClass<NodeNameType *> unknown_games_a3fa64;
// The text label of a dialog control's tool tip, or 0 (0x005E22B0; hypothesis).
char const *__fastcall Unknown_005e22b0(HWND dialog, HWND control);
// Sends a player's side and colour choice ("R<side>,<colour>") from the host's name (0x005C3D90).
void __fastcall Unknown_005c3d90(char const *name, char const *text);
// A dialog helper for message 0x4EC (0x005E8710).
void __fastcall Unknown_005e8710(HWND dialog);
// Cleared when the game lobby dialog gets message 0x497 (0x00A72D52).
extern bool unknown_a72d52;
// The network dialogs' result (0x00A71E8C; 2 on IDCANCEL, else the pressed button's id).
extern int unknown_lobby_result_a71e8c;
// The join dialog's game list accepts a selection (0x007E699C, initially true; set on message 0x497).
extern bool unknown_join_list_7e699c;
// Set from the observer mode when the join dialog's button 0x6CC is pressed (0x00A71E99).
extern bool unknown_a71e99;
// Message 0x4DB of the join dialog (0x005DEF80; hypothesis).
bool __fastcall Unknown_005def80(long lparam, bool flag);
// The LAN join dialog's procedure (0xBB; from Red Alert's Net_Join_Dialog): paint, tool tips, the game
// list 0x549, the name edit 0x541, the chat line 0x540, the buttons 0x5C0, 0x6CC..0x6CE and the observer
// radio buttons 0x75F/0x760, setup message 0x497 (0x005BE6B0).
long __stdcall Join_Dialog_Proc_005be6b0(HWND window, unsigned message, unsigned wparam, long lparam);
// The joined player's game lobby dialog procedure: destroy, paint, tool tips, the player row combo boxes,
// the chat line, the ready button 0x59F and the setup message 0x497 (0x005C2330).
long __stdcall Join_Lobby_Dialog_Proc_005c2330(HWND window, unsigned message, unsigned wparam, long lparam);


#endif
