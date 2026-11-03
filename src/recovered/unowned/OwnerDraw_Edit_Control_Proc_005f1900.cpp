// Edit control callback005F1900, native2075code+5padding. Ghidra's stack-probe prototype is false.
// @ref _unknown_combo_class_7e8dd4=007e8dd4
// @ref _unknown_crlf_7d7cec=007d7cec
// @ref _unknown_edit_buffer_a7393c=00a7393c
// @ref __imp__GetFocus@0=0079a460
// @ref __imp__GetUpdateRect@12=0079a474
// @ref __imp__GetNextDlgTabItem@12=0079a4fc
// @ref _wcsncpy=00783622
// @ref _wcslen=00783605
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/win32_window.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/crt_string.hpp"
extern "C" char const unknown_combo_class_7e8dd4[];
extern "C" char const unknown_crlf_7d7cec[];
extern "C" unsigned short unknown_edit_buffer_a7393c[0x1400];
extern "C" unsigned short *__cdecl wcsncpy(unsigned short *,unsigned short const *,unsigned int);
extern "C" unsigned int __cdecl wcslen(unsigned short const *);
extern "C" __declspec(dllimport) HWND __stdcall GetFocus();
extern "C" __declspec(dllimport) HWND __stdcall GetNextDlgTabItem(HWND,HWND,BOOL);
extern "C" __declspec(dllimport) BOOL __stdcall GetUpdateRect(HWND,RECT *,BOOL);
void __fastcall Unknown_006FA0F0(char *,unsigned short const *,int);
namespace OwnerDraw {
void __fastcall unknown_draw_dimmed_back_5fe490(Rect const &,HWND,int);
void __fastcall unknown_draw_edit_text_600830(Surface *,Rect &,wchar_t const *,int,
    BitFontClass *,unsigned int,int *,int,int,int,int);
LRESULT __stdcall unknown_edit_control_proc_5f1900(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    WNDPROC previous=0;
    WNDPROC *slot=unknown_window_procs_a73688.Find(window);
    if(slot)previous=*slot;
    UnknownControlRecord *data=unknown_registry_a73640.Find((unsigned int)window);
    char class_name[32];
    char narrow[0x800];
    unsigned short wide[0x800];
    if(!data) return CallWindowProcA(previous,window,message,wparam,lparam);
    if(GetFocus()==window && !data->unknown_f4) {
        data->unknown_f0=1;
        SetFocus(MainWindow);
    }
    LONG style=GetWindowLongA(window,-16);
    if((message==0x101 || message==0x100) && wparam==9)return 0;
    if(message==0x497) {
        RECT winrect,client,parentrect;
        GetWindowRect(window,&winrect);
        GetClientRect(window,&client);
        GetWindowRect(GetParent(window),&parentrect);
        MoveWindow(window,winrect.left-parentrect.left+1,winrect.top-parentrect.top+1,
            client.right-2,client.bottom-2,0);
        if(GetFocus()==window) {
            data->unknown_f0=1;
            SetFocus(MainWindow);
        }
        if(style&0x10000) {
            data->unknown_f8=1;
            SetWindowLongA(window,-16,style&~0x10000);
        }
        return 0;
    }
    if(message==7) {
        SendMessageA(window,0xb1,(WPARAM)-1,-1);
        if(!data->unknown_f4)PostMessageA(window,0x4b0,0,0);
        goto invalidate;
    }
    if(message==0x4b5 || message==0x4b3 || message==0xe) {
        wide[0]=0;
        unknown_edit_text_5f2120(window,wide,0x800,0);
        if(message==0xe)return wcslen(wide);
        if(message==0x4b3) {
            wcsncpy((unsigned short *)lparam,wide,wparam);
            ((unsigned short *)lparam)[wparam-1]=0;
            return wcslen((unsigned short *)lparam);
        }
        Unknown_006FA0F0((char *)lparam,wide,wparam);
        ((char *)lparam)[wparam-1]=0;
        return strlen((char *)lparam);
    }
    if(message==0x4b4 || message==0x4b2) {
        narrow[0]=0;
        if(data->text_28)WideCharToMultiByte(0,0,data->text_28,-1,narrow,0x800,0,0);
        return CallWindowProcA(previous,window,0xc,0,(LPARAM)narrow);
    }
    if(message==0x102) {
        if(wparam==0xd) {
            if(style&4) {
                unsigned int length=CallWindowProcA(previous,window,0xe,0,0)+3;
                char *text=new char[length];
                CallWindowProcA(previous,window,0xd,length,(LPARAM)text);
                strcat(text,unknown_crlf_7d7cec);
                CallWindowProcA(previous,window,0xc,0,(LPARAM)text);
                delete [] text;
                unsigned int id=GetWindowLongA(window,-12)&0xffff;
                SendMessageA(GetParent(window),0x111,id|0x5010000,(LPARAM)window);
                return 0;
            }
        } else if(wparam==9) {
            HWND next=window;
            HWND parent=GetParent(next);
            HWND tab=GetNextDlgTabItem(parent,next,0);
            if(tab)next=tab;
            SetFocus(next);
            return 0;
        }
        goto call_previous;
    }
    if(message==0x4af) {
        int pending=data->unknown_f0;
        data->unknown_f4=1;
        if(pending) {
            SetFocus(window);
            data->unknown_f0=0;
        }
        if(data->unknown_f8)SetWindowLongA(window,-16,style|0x10000);
        return 0;
    }
    if(message==0xf || message==0x14) {
        RECT display,update;
        Window_Rect_In_Main_Client(window,&display);
        GetClassNameA(GetParent(window),class_name,16);
        bool combo=strcmp(class_name,unknown_combo_class_7e8dd4)==0;
        if(message==0xf && GetUpdateRect(window,&update,0)) {
            update.left+=display.left;
            update.right+=display.left;
            update.top+=display.top;
            update.bottom+=display.top;
        }
        Rect background(display.left,display.top,display.right-display.left+1,display.bottom-display.top+1);
        unknown_draw_dimmed_back_5fe490(background,window,data->unknown_c8);
        if(!combo)unknown_5fdb20(unknown_surface_839958,background,1,-1);
        int caret=0;
        unknown_edit_text_5f2120(window,unknown_edit_buffer_a7393c,0x1400,&caret);
        Rect text(display.left,display.top,display.right-display.left+1,display.bottom-display.top+1);
        LONG text_style=GetWindowLongA(window,-16);
        unknown_draw_edit_text_600830(unknown_surface_839958,text,unknown_edit_buffer_a7393c,caret,
            data->font_64,unknown_color_a733e4,&data->unknown_44,data->unknown_38,((unsigned int)text_style>>5)&1,0,0);
        ValidateRect(window,0);
    }
    if(message==0x7b)return 1;
    if(message==0x200)return 1;
    if(message==0x100 || message==0x101 || message==0x104 || message==0x105 || message==0x106 || message==0x107 || message==8 || message==0x201) {
invalidate:
        GetClassNameA(GetParent(window),class_name,32);
        if(strcmp(class_name,unknown_combo_class_7e8dd4)==0)InvalidateRect(GetParent(window),0,0);
        InvalidateRect(window,0,0);
    }
call_previous:
    return CallWindowProcA(previous,window,message,wparam,lparam);
}
}
