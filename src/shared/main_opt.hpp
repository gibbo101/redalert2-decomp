// The shell Options dialogs (MainOpt.cpp, 0x00541F60-0x00543CE6; the file name is the debug string at 0x007DFDE0).
// Names of the functions are hypotheses from the dialog resources and the strings they load.
#ifndef RA2_SHARED_MAIN_OPT_HPP
#define RA2_SHARED_MAIN_OPT_HPP

#include "shared/ms_message_box.hpp"
#include "shared/options.hpp"
#include "shared/string_table.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/video_mode_size.hpp"

// The copy of Options taken before the Options dialog opens (0x00A6EC38, constructed at 0x00542150).
extern OptionsClass unknown_options_a6ec38;

int __stdcall Try_Mode_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);    // 0x00542160
bool __fastcall Try_Mode_Dialog();                                                       // 0x00542210
void __fastcall Main_Options_Apply(HWND window);                                         // 0x00542280
void __fastcall Main_Options_Dialog();                                                            // 0x00542460
int __stdcall Main_Options_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);    // 0x00542590
int __stdcall Confirm_Mode_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);   // 0x00543C40
int __stdcall Main_Options_Proc2(HWND window, UINT message, WPARAM wparam, LPARAM lparam);   // 0x00542D60

void __fastcall Unknown_0066F3A0(UnknownSessionState *session);                          // 0x0066F3A0 (Read_MultiPlayer_Settings)

bool __fastcall Test_Display_Mode(int width, int height);                                // 0x00543A70
bool __fastcall Set_Display_Mode(int width, int height);                                 // 0x005434E0

int __stdcall Video_Mode_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);       // 0x00543CF0

// The video mode dialog's state: the mode list (0x00A6ED14, from Get_Display_Mode_Sizes; freed on close), the mode
// chosen (0x00A6EC58 x 0x00A6EC5C), and the list selection now and at the start (0x007DFDBC, 0x007DFDC0).
extern VideoModeSize *unknown_modes_a6ed14;
extern int unknown_video_width_a6ec58;
extern int unknown_video_height_a6ec5c;
extern int unknown_mode_selected_7dfdbc;
extern int unknown_mode_initial_7dfdc0;
extern bool unknown_mode_flag_7dfdc4;
VideoModeSize * __fastcall Get_Display_Mode_Sizes_004962a0(unsigned long minimum_width, unsigned long minimum_height,
                                                           unsigned long maximum_width, unsigned long maximum_height,
                                                           unsigned long depth);               // 0x004962A0
void Free_Memory_00781d3b(void *block);                                                  // 0x00781D3B (free in lobby.hpp is 0x007825E8)
void __fastcall Unknown_00737080(HWND dialog, HWND window);                              // 0x00737080

// The Options dialog's state: the mode list of its resolution combo box (0x00A6ED10, freed on close), set once
// the controls are filled (0x00A6ED0C; the sliders ignore scrolling until then), and the combo selection at the
// start (0x007DFDB4, -1).
extern VideoModeSize *unknown_modes_a6ed10;
extern bool unknown_options_ready_a6ed0c;
extern int unknown_mode_initial_7dfdb4;
// The slider labels: detail (0x007DFD80; low, medium, high), difficulty (0x007DFD8C) and scroll rate (0x007DFD98, slowest to fastest).
extern char const *unknown_detail_names_7dfd80[3];
extern char const *unknown_difficulty_names_7dfd8c[3];
extern char const *unknown_scroll_rate_names_7dfd98[7];
void __fastcall Unknown_Reset_Art_006F33B0(int width, int height);                         // 0x006F33B0

// Set_Display_Mode's callees.
long Wait_For_Surface_Blit_004961d0();                                                     // 0x004961D0
bool __fastcall Set_Video_Mode(HWND window, int width, int height, int bits);              // 0x00495C90
// Reallocates the off-screen surfaces for the visible rectangle (0x00519500; TS Allocate_Surfaces).
bool __fastcall Allocate_Surfaces(Rect *common, Rect *composite, Rect *tile, Rect *sidebar, bool clear);
// Rebuilds the colour remap tables from the old pixel format shifts (0x00486010).
void __fastcall Unknown_00486010(int red_right, int red_left, int green_right, int green_left, int blue_right, int blue_left);
void __fastcall Unknown_005FF380(HWND dialog);                                              // 0x005FF380
void __fastcall Unknown_005E9F00(HWND dialog, Point2D *old_size);                            // 0x005E9F00

#endif
