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
// Two lobby words cleared by a reset (0x00A728E4, 0x00A72734).
extern unsigned short unknown_lobby_a728e4;
extern unsigned short unknown_lobby_a72734;
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
void __fastcall Select_Scenario_005c7c30(int index);

// Wide-string comparison, 0 when equal (0x007837D3; the CRT's _wcsicmp).
int Compare_Wide_007837d3(wchar_t const *first, wchar_t const *second);
// Narrows a wide string into a rotating buffer (0x006FA120).
char *__fastcall Unknown_006FA120(unsigned short const *string);
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
int Is_Host_005c86a0();
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
int Is_Host_005c86a0();
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
void __fastcall Open_Lobby_Dialog_005c6960(HWND parent);
extern HWND unknown_lobby_dialog_a728e0;
// The dialog manager: creates a dialog from a template (0x00735700), prepares a created dialog
// (0x005FF7E0) and runs a dialog's update callback (0x007359E0; the last three arguments unknown).
typedef long (__stdcall *UnknownDialogProc)(HWND window, unsigned message, unsigned wparam, long lparam);
void *__fastcall unknown_create_dialog_735700(void *instance, int id, HWND parent, UnknownDialogProc procedure, long arg);
void __fastcall unknown_show_dialog_5ff7e0(void *dialog, int id);
void __fastcall Unknown_007359e0(HWND dialog, bool (*callback)(), int unknown_1, int unknown_2, int unknown_3);
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
// The per-mode services the lobby dialog runs (LAN 0x005BBD10, World Online 0x0073E100,
// modem/serial 0x0059C880; hypotheses from the game modes).
bool Unknown_005bbd10();
bool Unknown_0073e100();
bool Unknown_0059c880();

#endif
