#include "shared/wol_sink.hpp"
#include "shared/wonline_dialog_control.hpp"
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_dialog_5e5f20(HWND);
LRESULT __fastcall unknown_get_window_text(HWND,Wstring &);
extern "C" long __cdecl time(long *timer);
extern char wol_empty_name_83c55c[];
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?wol_empty_name_83c55c@@3PADA=0083c55c
long __stdcall Add_Buddy_Dialog_00758210(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    if(message==0x110 && lparam) SetWindowLongA(window,8,*(long *)(lparam+4));
    long result=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(result) return result;
    OwnerDraw::DialogControl *control=(OwnerDraw::DialogControl *)GetWindowLongA(window,8);
    switch(message) {
    case 0xf:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        ValidateRect(window,0);
    case 0x14: return 1;
    case 0x2b: Unknown_005FE380(lparam); return 1;
    case 0x111:
        switch(wparam&0xffff) {
        case 0x540:
            switch((unsigned short)(wparam>>16)) {
            case 0: break;
            default: {
                Wstring name;
                unknown_get_window_text((HWND)lparam,name);
                EnableWindow(GetDlgItem(window,0x702),Unknown_00756790(name));
                break;
            }
            }
            break;
        case 0x686:
            control->Set_Window_006010f0((unsigned)window,(HWND)0x686);
            break;
        case 0x702: {
            Wstring name;
            HWND edit=GetDlgItem(window,0x540);
            unknown_get_window_text(edit,name);
            SendMessageA(edit,0x4b4,0,(LPARAM)wol_empty_name_83c55c);
            if(Unknown_00756790(name)) {
                if(Unknown_00756790(name)) {
                    WOL::User user;
                    memset(&user,0,sizeof(user));
                    strncpy(user.name,name.Peek_Buffer(),9);
                    unknown_chat_a72cfc->unknown_slot56(&user);
                    if(Unknown_00756790(name)) {
                        Wstring friend_name(name);
                        unknown_strings_b26920.Add(friend_name);
                        unknown_strings_b29838.Add(friend_name);
                        unknown_strings_b2a7d8.Add(friend_name);
                        bool request=true;
                        if(unknown_wstring_b26944.Length()>0) {
                            if((unsigned long)(time(0)-unknown_b2a7f8)<5) request=false;
                            else unknown_wstring_b26944.Release();
                        }
                        if(request && unknown_strings_b29838.Count!=0) {
                            if(unknown_strings_b29838.Get_007662c0(unknown_wstring_b26944,0))
                                unknown_strings_b29838.Remove_007661f0(0);
                            unknown_b2a7f8=time(0);
                            WOL::User query;
                            memset(&query,0,sizeof(query));
                            strcpy(query.name,unknown_wstring_b26944.Get());
                            unknown_chat_a72cfc->unknown_slot24(&query);
                        }
                    }
                    Unknown_00757380();
                }
            }
            InvalidateRect(edit,0,0);
            control->Set_Window_006010f0((unsigned)window,(HWND)0x702);
            break;
        }
        }
        break;
    case 0x497: {
        HWND edit=GetDlgItem(window,0x540);
        SendMessageA(edit,0xc5,9,0);
        SendMessageA(edit,0x4d1,1,0);
        SendMessageA(edit,0x4b4,0,(LPARAM)wol_empty_name_83c55c);
        EnableWindow(GetDlgItem(window,0x702),0);
        break;
    }
    case 0x4da:
        PostMessageA(GetDlgItem(window,0x702),0xf5,0,0);
        break;
    }
    return 0;
}
