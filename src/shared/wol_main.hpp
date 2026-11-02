// The Westwood Online entry loop (0x0073A300, its own unit 0x0073A0F0-0x0073A6EF
// before WOnline.cpp) and the WOnline.cpp screens it runs. Each screen returns
// 1 to start a game, 0 to go back; the loop moves between them through the
// online session state unknown_a3d2a4 (0 selection, 1/2 the two game kinds,
// 3, 4 and 5 lobby). Names are hypotheses.
#ifndef RA2_SHARED_WOL_MAIN_HPP
#define RA2_SHARED_WOL_MAIN_HPP

class Wstring;

extern int unknown_a3d2a4;              // 0x00A3D2A4 (also shared/wol_sink.hpp, options_dialog.hpp)
extern int unknown_a3d2a8;              // 0x00A3D2A8 the state to return to from state 4
extern int unknown_b264f0;              // 0x00B264F0 the session kind logged in (0: none)

int unknown_session_kind();                                 // 0x0073A2E0 (0, 1 or 2 from unknown_a3d2a4)
int __fastcall Wonline_Main(bool first_time);               // 0x0073A300

void Unknown_00753F10();                                    // 0x00753F10
void Unknown_0073C990();                                    // 0x0073C990
int Unknown_00742FD0();                                     // 0x00742FD0 (log in: 1 done, 0 cancelled)
void __fastcall Logout_Wonline_00741ea0();                  // 0x00741EA0
void Shutdown_Wonline_00742080();                           // 0x00742080
int Open_Wonline_Selection_00753110();                      // 0x00753110
int Unknown_00759E20();                                     // 0x00759E20
void Open_Buddy_Dialog_0075cba0();                          // 0x0075CBA0
int __fastcall Unknown_00743720(struct HWND__ *window, bool first_time);  // 0x00743720
int __fastcall Unknown_00759370(bool first_time);           // 0x00759370
int __fastcall Open_Wonline_Lobby_00753f70();               // 0x00753F70 (-1, -2: leave online)
void __fastcall unknown_close_all_dialogs();                // 0x00753F50
int __fastcall WDT_Setup_Game_00768e90(bool first_time);   // 0x00768E90
Wstring __fastcall WOL_Auto_Login_Persona();                // 0x007390B0
Wstring __fastcall WOL_Last_Valid_Persona();                // 0x00739330

#endif
