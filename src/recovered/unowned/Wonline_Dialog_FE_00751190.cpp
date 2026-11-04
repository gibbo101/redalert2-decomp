// Locale chooser00751190: native callback ABI and existing dialog-control result carrier.
#include "shared/dialog_default_proc.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/wol_chat.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/debug_printf.hpp"
WideString __fastcall Locale_Name_0073f1c0(int locale);
void __fastcall Unknown_005FF380(HWND window);
void __fastcall unknown_dialog_5e5f20(HWND window);

long __stdcall Wonline_Dialog_FE_00751190(HWND window,unsigned message,unsigned wparam,long lparam)
{
    if(message==0x110) {
        long initialization=lparam;
        if(initialization) SetWindowLongA(window,8,((long *)initialization)[1]);
    }
    int result=unknown_dialog_proc_5ffb00(window,message,wparam,lparam);
    if(!result) {
        OwnerDraw::DialogControl *control=(OwnerDraw::DialogControl *)GetWindowLongA(window,8);
        switch(message) {
        case 0x82:
            Unknown_005FF380(window);
            return 0;
        case 0xf:
            Unknown_005FEE70(window);
            unknown_dialog_5e5f20(window);
            ValidateRect(window,0);
            return 0;
        case 0x14:
            return 1;
        case 0x2b:
            Unknown_005FE380(lparam);
            return 1;
        case 0x497: {
            SendDlgItemMessageA(window,0x3f0,0x184,0,0);
            int count=0;
            unknown_chat_a72cfc->unknown_slot52(&count);
            if(count>0) {
                HWND list=GetDlgItem(window,0x3f0);
                for(int locale=count-1;locale>=0;--locale) {
                    WideString name=Locale_Name_0073f1c0(locale);
                    Debug_Printf("Adding country: %hs\n",name.Get());
                    int row;
                    if(locale<2) row=SendMessageA(list,0x4cc,0,(LPARAM)name.Get());
                    else row=SendMessageA(list,0x4cd,0,(LPARAM)name.Get());
                    SendMessageA(list,0x19a,row,locale);
                }
                SendMessageA(list,0x186,-1,0);
            }
            break;
        }
        case 0x111:
            switch(wparam&0xffff) {
            case 1: {
                HWND list=GetDlgItem(window,0x3f0);
                int selected=0;
                int row=SendMessageA(list,0x188,0,0);
                if(row!=-1) selected=SendMessageA(list,0x199,row,0);
                // Preserve the existing interface's HWND-typed numeric result carrier.
                control->Set_Window_006010f0((unsigned int)window,(HWND)selected);
                break;
            }
            case 2:
                control->Set_Window_006010f0((unsigned int)window,0);
                return 0;
            case 0x3f0:
                if((unsigned short)(wparam>>16)==1) {
                    int row=SendMessageA((HWND)lparam,0x188,0,0);
                    EnableWindow(GetDlgItem(window,1),row!=-1);
                    return 0;
                }
                break;
            }
            break;
        }
        result=0;
    }
    return result;
}

// @ref ??_C@_0BF@DHDL@Adding?5country?3?5?$CFhs?6?$AA@=007ff928
