// int Buddy_Dialog_Proc(HWND, UINT, WPARAM, LPARAM) (0x00758750): the buddy list dialog run by 0x00759370.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/crt_string.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/wonline_dialog_control.hpp"
#include "shared/win_util.hpp"
#ifndef LOWORD
#define LOWORD(l) ((unsigned short)(l))
#define HIWORD(l) ((unsigned short)(((unsigned long)(l) >> 16) & 0xFFFF))
#endif
extern "C" long __cdecl time(long *);
extern HANDLE wol_wait_events_b264f8[18];
extern int buddy_column_b29460, buddy_column_b26cb4;
extern int buddy_columns_7fd308[6];
extern unsigned long buddy_refresh_time_b2a6f0;
extern char wol_label_7eb2cc[], wol_label_7eb2c0[];
extern HWND game_window_00b263d8;
extern void *unknown_instance_b26180;
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_dialog_5e5f20(HWND);
bool __fastcall Request_Game_Channel_List_0073df10(unsigned char autoping,bool wait);
bool __fastcall Can_Join_Selected_Buddy_00755ef0();
bool Selected_Buddy_Unavailable_00756140();
void __fastcall Update_Buddy_Buttons_007561c0(HWND dialog);
void __fastcall Update_Buddy_Profile_007562b0(HWND dialog);
void Service_Buddy_Find_Queue_00756610();
void Reset_Buddy_Name_List_00757530();
void __fastcall Unknown_00755180(HWND dialog);
void Refresh_Buddy_Status_007570e0();
void __fastcall Reset_Buddy_State_00757720();
void __fastcall Unknown_00756e10(Wstring const &name);
void __fastcall unknown_show_dialog_5ff7e0(void *handle,int kind);
int __fastcall Run_Control_Dialog_006011a0(int,DLGPROC,OwnerDraw::DialogControl *);
LRESULT __fastcall unknown_get_window_text(HWND,Wstring &);
LRESULT __fastcall unknown_get_window_item_text(HWND,WPARAM,Wstring &);
long __stdcall Add_Buddy_Dialog_00758210(HWND,UINT,WPARAM,LPARAM);
int __stdcall Page_Dialog_Proc_00757d80(HWND,UINT,WPARAM,LPARAM);
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ?buddy_column_b29460@@3HA=00b29460
// @ref ?buddy_column_b26cb4@@3HA=00b26cb4
// @ref ?buddy_columns_7fd308@@3PAHA=007fd308
// @ref ?buddy_refresh_time_b2a6f0@@3KA=00b2a6f0
// @ref ?wol_label_7eb2cc@@3PADA=007eb2cc
// @ref ?wol_label_7eb2c0@@3PADA=007eb2c0
// @ref ?game_window_00b263d8@@3PAUHWND__@@A=00b263d8
// @ref ?unknown_instance_b26180@@3PAXA=00b26180

inline void Run_Add_Buddy_Dialog(HWND window)
{
    SimpleWonlineDialogControl add;
    Run_Control_Dialog_006011a0(0x115, (DLGPROC)Add_Buddy_Dialog_00758210, &add);
    Unknown_00755180(window);
}

inline void Start_Buddy_Refresh(HWND window,HWND refresh)
{
    SendMessageA(refresh, 0x4aa, 0, (LPARAM)unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_label_7eb2c0, 0));
    Reset_Buddy_State_00757720();
    SetTimer(window, 0, 1000, 0);
}

int __stdcall Buddy_Dialog_Proc_00758750(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == 0x110 && lparam) SetWindowLongA(window, 8, *(long *)(lparam + 4));
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result) return result;
    OwnerDraw::DialogControl *control = (OwnerDraw::DialogControl *)GetWindowLongA(window, 8);
    switch (message) {
    case 0x14:
        return 1;
    case 0xf:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        ValidateRect(window, 0);
        return 1;
    case 2:
        KillTimer(window, 0);
        KillTimer(window, 0x704);
        Unknown_005CD3A0();
        return 0;
    case 0x2b:
        Unknown_005FE380(lparam);
        return 1;
    case 0x111:
        if (control->unknown_slot2()) return 0;
        switch (LOWORD(wparam)) {
        case 0x5c2: {
            HWND page = (HWND)unknown_create_dialog_735700(unknown_instance_b26180, 0x11e, game_window_00b263d8, (UnknownDialogProc)Page_Dialog_Proc_00757d80, 0);
            unknown_show_dialog_5ff7e0(page, 0x11e);
            SendMessageA(page, 0x4a9, 0, 1);
            ShowWindow(page, 1);
            Dialog_Loop_007359e0(page, Unknown_0073e100, 0, true, true);
            return 0;
        }
        case 0x540:
            if (HIWORD(wparam) == 0x300) {
                Wstring text;
                unknown_get_window_text((HWND)lparam, text);
                EnableWindow(GetDlgItem(window, 0x702), text.Length() != 0);
            }
            return 0;
        case 0x62b:
            control->Set_Window_006010f0((unsigned)window, (HWND)0x62b);
            return 0;
        case 0x686:
            control->Set_Window_006010f0((unsigned)window, (HWND)0x686);
            return 0;
        case 0x62d:
            control->Set_Window_006010f0((unsigned)window, (HWND)0x62d);
            return 0;
        case 0x689:
            switch (wparam >> 16) {
            case 2:
                if (Can_Join_Selected_Buddy_00755ef0()) {
                    SendMessageA(GetDlgItem(window, 0x62d), 0xf5, 0, 0);
                    return 0;
                }
                if (Selected_Buddy_Unavailable_00756140()) {
                    SendMessageA(GetDlgItem(window, 0x5c2), 0xf5, 0, 0);
                }
                return 0;
            case 1: {
                int selected = SendMessageA((HWND)lparam, 0x188, 0, 0);
                if (selected == -1) unknown_wstring_b29cd4.Release();
                else unknown_get_window_item_text((HWND)lparam, selected, unknown_wstring_b29cd4);
                Update_Buddy_Buttons_007561c0(window);
                Update_Buddy_Profile_007562b0(window);
                return 0;
            }
            }
            return 0;
        case 0x760:
        case 0x75f: {
            int checked = 0;
            HWND button = GetDlgItem(window, 0x760);
            if (button) checked = SendMessageA(button, 0xf0, 0, 0);
            if ((short)wparam == 0x75f) checked = !checked;
            unknown_a72c68 = checked;
            Unknown_005cd540(0);
            return 0;
        }
        case 0x702:
            Run_Add_Buddy_Dialog(window);
            return 0;
        case 0x703: {
            HWND list = GetDlgItem(window, 0x689);
            int selected = SendMessageA(list, 0x188, 0, 0);
            if (selected != -1) {
                Wstring name;
                unknown_get_window_item_text(list, selected, name);
                Unknown_00756e10(name);
                SendMessageA(list, 0x182, selected, 0);
                unknown_wstring_b29cd4.Release();
                Unknown_00755180(window);
            }
            return 0;
        }
        case 0x704:
            EnableWindow((HWND)lparam, 0);
            Refresh_Buddy_Status_007570e0();
            SetTimer(window, 0x704, 3000, 0);
            return 0;
        }
        return 0;
    case 0x113:
        switch (wparam) {
        case 0x704:
            KillTimer(window, 0x704);
            EnableWindow(GetDlgItem(window, 0x704), 1);
            return 0;
        case 0:
            if ((unsigned long)(time(0) - buddy_refresh_time_b2a6f0) > 30) {
                Refresh_Buddy_Status_007570e0();
            }
            return 0;
        }
        return 0;
    case 0x497: {
        Unknown_005cd540(window);
        HWND list = GetDlgItem(window, 0x689);
        SendMessageA(list, 0x4a6, buddy_column_b29460, buddy_columns_7fd308[0]);
        SendMessageA(list, 0x4a6, 0, buddy_columns_7fd308[1]);
        SendMessageA(list, 0x4a6, 0, buddy_columns_7fd308[2]);
        SendMessageA(list, 0x4a6, 0, buddy_columns_7fd308[3]);
        SendMessageA(list, 0x4a6, buddy_column_b26cb4, buddy_columns_7fd308[4]);
        SendMessageA(list, 0x4a6, 0, buddy_columns_7fd308[5]);
        HWND refresh = GetDlgItem(window, 0x704);
        SendMessageA(refresh, 0x49c, 0, (LPARAM)unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_label_7eb2cc, 0));
        Start_Buddy_Refresh(window, refresh);
        return 0;
    }
    }
    return 0;
}
