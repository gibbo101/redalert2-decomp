// The game window unit (0x007371B0-0x0073841F; C&C's WinStub.cpp role): the main
// window class and procedure, focus loss and restore, and the input method editor
// (IME) state the text entry gadgets read. Function and global names are
// hypotheses (Focus_Loss/Focus_Restore are its debug strings).
#ifndef RA2_SHARED_WIN_STUB_HPP
#define RA2_SHARED_WIN_STUB_HPP

#include "shared/win32_window.hpp"

extern bool unknown_mouse_captured_b263e8;   // 0x00B263E8 the mouse was captured when focus was lost
extern HICON unknown_icon_b263d4;            // 0x00B263D4 the window class icon
extern HCURSOR unknown_cursor_b263d0;        // 0x00B263D0 the window class cursor
extern int unknown_command_show_b263cc;      // 0x00B263CC WinMain's show command
extern FILETIME const unknown_build_time_7d8940;   // 0x007D8940 the build time stamp (after "Date3Here4")

// IME state: the composition text, its length and caret, whether a composition
// is open, the committed text, and the result DefWindowProcA gave a handled message.
extern HIMC IMEContext;                          // 0x00B263E4
extern unsigned short IMECompositionString[256]; // 0x00B261A8
extern unsigned short unknown_b263a8;            // 0x00B263A8 (cleared after each conversion)
extern int IMECompositionLength;                 // 0x00B263EC
extern int IMECursorPosition;                    // 0x00B263F0
extern int IMEComposing;                         // 0x00B263F4
extern unsigned short IMEResultString[];         // 0x00B25F7C
extern LRESULT IMEDefaultResult;                 // 0x00B263F8

void Focus_Loss();                                                                   // 0x007373A0
LRESULT WINAPI Windows_Procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam);   // 0x007375A0
// The build time stamp (0x007D8940) as "MM/DD/YYYY - hh:mm:ss"; size is not read.
void __fastcall Build_Time_Text(char *buffer, int size);                             // 0x00737A60
void __fastcall Create_Main_Window(HINSTANCE instance, int command_show, int width, int height);   // 0x00737BD0
void IME_Reset();                                                                    // 0x00737D90
void IME_Update_Composition();                                                       // 0x00737E30
// Sends each character of the IME result string to window as message 0x4D9.
void __fastcall IME_Send_Result(HWND window);                                        // 0x00737F20
// Handles the IME window messages (TRUE: IMEDefaultResult holds the result).
BOOL __fastcall IME_Process_Message(HWND window, UINT message, WPARAM wparam, LPARAM lparam);   // 0x00737FC0

#endif
