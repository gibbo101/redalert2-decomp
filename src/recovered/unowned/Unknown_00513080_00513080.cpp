// int __stdcall Unknown_00513080(HWND, UINT, WPARAM, LPARAM) -- 0x00513080
#include "shared/win32_api.hpp"
#include "shared/ms_message_box.hpp"
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/ccini_class.hpp"

// @ref ??_C@_07NDNK@General?$AA@=007dbb78
// @ref ??_C@_04EFNI@Name?$AA@=007ce2a4
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ?unknown_dialog_help_736880@@YIXJ@Z=00736880
// @ref ?unknown_dialog_context_menu_7368a0@@YIXI@Z=007368a0
// @ref ?unknown_dialog_init_737060@@YIXPAUHWND__@@@Z=00737060

void __fastcall unknown_dialog_help_736880(LPARAM lparam);            // 0x00736880 WM_HELP
void __fastcall unknown_dialog_context_menu_7368a0(WPARAM wparam);    // 0x007368A0 WM_CONTEXTMENU
void __fastcall unknown_dialog_init_737060(HWND window);              // 0x00737060

// The battle file chooser's dialog procedure (pointer only, 0x005129C0): the list 0x4A3 shows
// each INI's [General] Name; cancel (2) or 0x4A4 ends the dialog with the selection.
int __stdcall Unknown_00513080(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    char buffer[128];
    switch (message) {
    case 0x7B:
        unknown_dialog_context_menu_7368a0(wparam);
        return 0;
    case 0x53:
        unknown_dialog_help_736880(lparam);
        return 0;
    case 0x110:
        {
            unknown_dialog_init_737060(window);
            HWND list = GetDlgItem(window, 0x4A3);
            DynamicVectorClass<CCINIClass *> *files = (DynamicVectorClass<CCINIClass *> *)lparam;
            for (int index = 0; index < files->Count(); index++) {
                (*files)[index]->Get_String("General", "Name", "", buffer, sizeof(buffer));
                SendMessageA(list, 0x180, 0, (LPARAM)buffer);
            }
            SendMessageA(list, 0x186, 0, 0);
        }
        return 0;
    case 0x216:
        return unknown_moving_736d80(window, wparam, lparam);
    case 0x111:
        switch (wparam & 0xFFFF) {
        case 2:
        case 0x4A4:
            if ((unsigned short)(wparam >> 16) == 0) {
                HWND list = GetDlgItem(window, 0x4A3);
                EndDialog(window, SendMessageA(list, 0x188, 0, 0));
                DestroyWindow(window);
            }
            break;
        }
        break;
    }
    return 0;
}
