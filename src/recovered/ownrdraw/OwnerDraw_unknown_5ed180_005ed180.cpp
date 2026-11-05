// @ref __imp__GetClassNameA@12=0079a4e0
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__SetWindowLongA@12=0079a488
// @ref __imp__GetClientRect@8=0079a4b8
// @ref __imp__CallWindowProcA@20=0079a4c0
// @ref __imp__SendMessageA@16=0079a4a0
// @ref ?Unknown_Add_Modeless_Dialog_00522b20@@YIXPAUHWND__@@@Z=00522b20
// @ref ?Window_Rect_In_Main_Client@@YIHPAUHWND__@@PAUtagRECT@@@Z=00735690
// @ref ?Get_Red_Right@@YAHXZ=004abb40
// @ref ?Get_Red_Left@@YAHXZ=004abb30
// @ref ?Get_Green_Right@@YAHXZ=004abb60
// @ref ?Get_Green_Left@@YAHXZ=004abb50
// @ref ?Get_Blue_Right@@YAHXZ=004abb80
// @ref ?Get_Blue_Left@@YAHXZ=004abb70
// @ref ?Load_Dialog_Images_5fc8a0@@YIXXZ=005fc8a0
// @ref ?unknown_masks_ready_a763f8@OwnerDraw@@3HA=00a763f8
// @ref ?unknown_green_mask_a763de@OwnerDraw@@3GA=00a763de
// @ref ?Load_String@StringTable@@SIPB_WPBDPAD1H@Z=006f9ec0
// @ref ??_C@_09PCGO@ScrollBar?$AA@=007eadb4
// @ref ??_C@_07NOMM@ListBox?$AA@=007e8de0
// @ref ??_C@_08DGFB@ComboBox?$AA@=007e8dd4
// @ref ??_C@_0BC@JD@msctls_trackbar32?$AA@=007eada0
// @ref ??_C@_0BC@DLJF@msctls_progress32?$AA@=007ead8c
// @ref ??_C@_07FHL@NewEdit?$AA@=007e8de8
// @ref ??_C@_04EDLP@Edit?$AA@=007e8df0
// @ref ??_C@_06KCJP@Static?$AA@=007ead84
// @ref ??_C@_0BA@PACF@SysTabControl32?$AA@=007ead74
// @ref ??_C@_06LKP@Button?$AA@=007ead6c
// @ref ??_C@_0BA@ILJA@msctls_hotkey32?$AA@=007ead5c
// @ref ??_C@_0BE@JKJB@D?3?2Ra2?2ownrdraw?4cpp?$AA@=007e8df8
// @ref ?unknown_scroll_proc_5f9fb0@OwnerDraw@@YGJPAUHWND__@@IIJ@Z=005f9fb0
// @ref ?unknown_list_proc_5f6690@OwnerDraw@@YGJPAUHWND__@@IIJ@Z=005f6690
// @ref ?unknown_combo_proc_5f4ba0@OwnerDraw@@YGJPAUHWND__@@IIJ@Z=005f4ba0
// @ref ?unknown_track_proc_5fb270@OwnerDraw@@YGJPAUHWND__@@IIJ@Z=005fb270
// @ref ?unknown_new_edit_proc_5f22a0@OwnerDraw@@YGJPAUHWND__@@IIJ@Z=005f22a0
// @ref ?unknown_static_proc_5f2b50@OwnerDraw@@YGJPAUHWND__@@IIJ@Z=005f2b50
// @ref ?unknown_tab_proc_5f0f40@OwnerDraw@@YGJPAUHWND__@@IIJ@Z=005f0f40
// @ref ?unknown_button_proc_5f0320@OwnerDraw@@YGJPAUHWND__@@IIJ@Z=005f0320
// @ref ?unknown_control_proc_5ee460@OwnerDraw@@YGJPAUHWND__@@IIJ@Z=005ee460
// @ref ?Grow_Table@?$WolDictionary@PAUHWND__@@P6GJPAU1@IIJ@Z@@QAEXXZ=00601b90
// @ref ?Grow_Table@?$WolDictionary@IUUnknownControlRecord@OwnerDraw@@@@QAEXXZ=00601f70
// @ref ?Get_Pointer@?$WolDictionary@PAUHWND__@@P6GJPAU1@IIJ@Z@@QBE_NABQAUHWND__@@PAPAP6GJPAU2@IIJ@Z@Z=006018e0
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/crt_string.hpp"
#include "shared/wide_string.hpp"
#include "shared/wol_dictionary.hpp"
#include "shared/hicolor.hpp"
#include "shared/mono_window.hpp"
#include "shared/string_table.hpp"
#include "shared/owner_draw_images.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

extern int unknown_masks_ready_a763f8;
LRESULT __stdcall unknown_scroll_proc_5f9fb0(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
LRESULT __stdcall unknown_list_proc_5f6690(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
LRESULT __stdcall unknown_combo_proc_5f4ba0(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
LRESULT __stdcall unknown_track_proc_5fb270(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
LRESULT __stdcall unknown_new_edit_proc_5f22a0(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
LRESULT __stdcall unknown_static_proc_5f2b50(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
LRESULT __stdcall unknown_tab_proc_5f0f40(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
LRESULT __stdcall unknown_button_proc_5f0320(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
LRESULT __stdcall unknown_control_proc_5ee460(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
LRESULT __stdcall unknown_default_proc_5f0210(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
LRESULT __stdcall unknown_button_proc_5f42d0(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
LRESULT __stdcall unknown_checkbox_proc_5f3cf0(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
LRESULT __stdcall unknown_edit_control_proc_5f1900(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
LRESULT __stdcall unknown_progress_proc_5faff0(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
void unknown_5de880();
void unknown_5fc820();

// Prepares one control for owner drawing (TibSun InitializeCtrl): its class picks the control kind and paint
// procedure, 0x005EE460 replaces the window procedure, and the record takes lparam and the window text.
BOOL __stdcall unknown_5ed180(HWND window, LPARAM lparam)
{
    char class_name[128];
    GetClassNameA(window, class_name, sizeof(class_name));
    LONG style = GetWindowLongA(window, GWL_STYLE);
    RECT rect1;
    Window_Rect_In_Main_Client(window, &rect1);
    RECT rect2;
    GetClientRect(window, &rect2);
    Unknown_Add_Modeless_Dialog_00522b20(window);
    unknown_5de880();
    if (!unknown_masks_ready_a763f8) {
        unknown_5fc820();
        Load_Dialog_Images_5fc8a0();
        unknown_masks_ready_a763f8 = 1;
    }
    WNDPROC custom_proc = 0;
    int kind = 0xb;
    LONG *user_data = (LONG *)GetWindowLongA(window, -21);
    if (user_data) {
        strcpy(class_name, (char const *)user_data[0]);
    }
    if (strcmp(class_name, "ScrollBar") == 0) {
        custom_proc = unknown_scroll_proc_5f9fb0;
        kind = 8;
    } else if (strcmp(class_name, "ListBox") == 0) {
        custom_proc = unknown_list_proc_5f6690;
        kind = 4;
    } else if (strcmp(class_name, "ComboBox") == 0) {
        custom_proc = unknown_combo_proc_5f4ba0;
        kind = 3;
    } else if (strcmp(class_name, "msctls_trackbar32") == 0) {
        custom_proc = unknown_track_proc_5fb270;
        kind = 7;
    } else if (strcmp(class_name, "msctls_progress32") == 0) {
        custom_proc = unknown_progress_proc_5faff0;
        kind = 6;
    } else if (strcmp(class_name, "NewEdit") == 0) {
        custom_proc = unknown_new_edit_proc_5f22a0;
        kind = 1;
    } else if (strcmp(class_name, "Edit") == 0) {
        custom_proc = unknown_edit_control_proc_5f1900;
        kind = 1;
    } else if (strcmp(class_name, "Static") == 0) {
        custom_proc = unknown_static_proc_5f2b50;
        kind = 2;
    } else if (strcmp(class_name, "SysTabControl32") == 0) {
        custom_proc = unknown_tab_proc_5f0f40;
        kind = 0xa;
    } else if (strcmp(class_name, "Button") == 0) {
        if ((style & (unsigned char)7) == (unsigned char)7) {
            custom_proc = unknown_group_box_proc_5fc020;
        } else if ((style & (unsigned char)0xb) == (unsigned char)0xb) {
            custom_proc = unknown_button_proc_5f0320;
        } else if ((style & (unsigned char)3) == (unsigned char)3) {
            custom_proc = unknown_checkbox_proc_5f3cf0;
        } else if ((style & (unsigned char)9) == (unsigned char)9) {
            custom_proc = unknown_button_proc_5f42d0;
        }
        kind = 0;
    } else if (strcmp(class_name, "msctls_hotkey32") == 0) {
        custom_proc = unknown_hotkey_proc_5fc330;
        kind = 9;
    } else {
        custom_proc = unknown_default_proc_5f0210;
    }
    WNDPROC original_proc = (WNDPROC)SetWindowLongA(window, -4, (LONG)unknown_control_proc_5ee460);
    if (!unknown_window_table_a73400.Contains(window)) {
        unknown_window_table_a73400.Add(window, custom_proc);
    }
    if (!unknown_window_proc_table_a73688.Contains(window)) {
        unknown_window_proc_table_a73688.Add(window, original_proc);
    }
    UnknownControlRecord *data = 0;
    if (!unknown_control_table_a73640.Get_Pointer((unsigned int const &)window, &data)) {
        UnknownControlRecord temp;
        unknown_control_table_a73640.Add((unsigned int const &)window, temp);
        unknown_control_table_a73640.Get_Pointer((unsigned int const &)window, &data);
    }
    data->unknown_00 = lparam;
    data->unknown_68 = kind;
    if (user_data) {
        data->unknown_54 = user_data[1];
    }
    WNDPROC proc = 0;
    unknown_window_proc_table_a73688.Get_Value(window, proc);
    char text[2048];
    text[0] = 0;
    CallWindowProcA(proc, window, WM_GETTEXT, sizeof(text), (LPARAM)text);
    if (text[0]) {
        data->Set_Wide_Text_600510(StringTable::Load_String(text, 0, "D:\\Ra2\\ownrdraw.cpp", 0x1a47));
    } else {
        data->Set_Wide_Text_600510(0);
    }
    data->unknown_2c = 0;
    SendMessageA(window, 0x497, 0, 0);
    return TRUE;
}

}
