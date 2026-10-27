#include "shared/win32_api.hpp"
#include "shared/debug_printf.hpp"
WIN32_IMPORT BOOL WINAPI SetDlgItemTextA(HWND window,int item,LPCSTR text);
WIN32_IMPORT HWND WINAPI SetFocus(HWND window);
WIN32_IMPORT BOOL WINAPI ShowWindow(HWND window,int command);
WIN32_IMPORT BOOL WINAPI EndDialog(HWND window,int result);
WIN32_IMPORT int WINAPI MessageBoxA(HWND window,LPCSTR text,LPCSTR caption,UINT type);
void __fastcall Unknown_Center_Window_00737080(HWND child,HWND parent);
void __fastcall Unknown_Dialog_Added_00522b20(HWND window);
void __fastcall Unknown_Dialog_Removed_00522b80(HWND window);
bool __fastcall unknown_moving_736d80(HWND window, WPARAM wparam, LPARAM lparam);
extern HWND game_window_00b263d8;
extern char exception_text_00855ba8[];
extern char const dialog_init_log_007d794c[];
extern char const abort_message_007d78d8[];
extern char const abort_caption_007d7944[];
// @ref ?Unknown_Center_Window_00737080@@=00737080
// @ref ?Unknown_Dialog_Added_00522b20@@=00522b20
// @ref ?Unknown_Dialog_Removed_00522b80@@=00522b80
// @ref ?unknown_moving_736d80@@=00736d80
// @ref ?game_window_00b263d8@@=00b263d8
// @ref ?exception_text_00855ba8@@=00855ba8
// @ref ?dialog_init_log_007d794c@@=007d794c
// @ref ?abort_message_007d78d8@@=007d78d8
// @ref ?abort_caption_007d7944@@=007d7944
int __stdcall Exception_Dialog_Procedure_004b7bf0(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    switch(message) {
    case 0x110:
        Debug_Printf(dialog_init_log_007d794c);
        SetDlgItemTextA(window,0x484,exception_text_00855ba8);
        SetFocus(window);
        if(game_window_00b263d8) Unknown_Center_Window_00737080(window,game_window_00b263d8);
        ShowWindow(window,1);
        Unknown_Dialog_Added_00522b20(window);
        return 0;
    case 0x10:
        EndDialog(window,0x481);
        Unknown_Dialog_Removed_00522b80(window);
        return 0;
    case 0x111:
        switch((unsigned short)wparam) {
        case 0x481: EndDialog(window,0x481); return 0;
        case 0x47d: MessageBoxA(window,abort_message_007d78d8,abort_caption_007d7944,0x30); return 0;
        }
        break;
    case 0x216: return unknown_moving_736d80(window,wparam,lparam);
    }
    return 0;
}
