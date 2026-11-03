// Checkbox callback005F3CF0: complete native1393code+104switch/alignment+7padding.
// @ref _unknown_checkbox_format_7eaec0=007eaec0
// @ref _unknown_checkbox_unchecked_7eaecc=007eaecc
// @ref _unknown_checkbox_right_7eaed8=007eaed8
// @ref _unknown_checkbox_left_7eaee4=007eaee4
// @ref _unknown_checkbox_checked_7eaef0=007eaef0
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/win32_window.hpp"
#include "shared/surface.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/crt_string.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
extern "C" char const unknown_checkbox_format_7eaec0[];
extern "C" char const unknown_checkbox_unchecked_7eaecc[];
extern "C" char const unknown_checkbox_right_7eaed8[];
extern "C" char const unknown_checkbox_left_7eaee4[];
extern "C" char const unknown_checkbox_checked_7eaef0[];
namespace OwnerDraw {
LRESULT __stdcall unknown_checkbox_proc_5f3cf0(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    unsigned int key=(unsigned int)window;
    UnknownControlRecord *record=0;
    UnknownControlRecord *&data=record;
    unknown_registry_a73640.Get(key,data);
    if(data) {
    switch(message) {
    case 0xf:
        if(data->unknown_20)break;
        {
            RECT client;
            struct PaintBounds { RECT display; RECT text; } bounds;
            GetClientRect(window,&client);
            Window_Rect_In_Main_Client(window,&bounds.text);
            Window_Rect_In_Main_Client(window,&bounds.display);
            Rect destination;
            destination=Rect(bounds.display.left,bounds.display.top,bounds.display.right-bounds.display.left,bounds.display.bottom-bounds.display.top);
            destination.Width=18;
            destination.Height=18;
            LONG style=GetWindowLongA(window,-16);
            int state=data->unknown_e8;
            bool special=data->unknown_d9;
            bool alternate=data->unknown_da;
            bool checked=state==1;
            char image_name[64];
            if(special) {
                if(checked) {
                    if(alternate)strcpy(image_name,unknown_checkbox_checked_7eaef0);
                    else strcpy(image_name,unknown_checkbox_left_7eaee4);
                } else {
                    if(alternate)strcpy(image_name,unknown_checkbox_right_7eaed8);
                    else strcpy(image_name,unknown_checkbox_unchecked_7eaecc);
                }
            } else {
                char letter='u';
                if(checked)letter='c';
                sprintf(image_name,unknown_checkbox_format_7eaec0,letter);
            }
            Surface *image=unknown_bitmap_writer_a76378.Get_Image_0068ca40(image_name,0);
            int height=image->Get_Height();
            Rect source(0,0,image->Get_Width(),height);
            unknown_surface_839958->Copy_From(destination,*image,source,false,true);
            if(style & 0x08000000)Unknown_005feb60(&destination,unknown_surface_839958,0,unknown_color_a763b8);
            wchar_t *text=data->text_28;
            bounds.text.left+=26;
            if(text) {
                unsigned int color=unknown_color_a733e4;
                if(style & 0x08000000)color=unknown_color_a737ec;
                unknown_draw_text_5fe020(unknown_surface_839958,text,&bounds.text,data->font_64,color,4,0xc,0,0,0);
            }
            ValidateRect(window,0);
        }
zero_result:
        return 0;
    case 0xf0:return data->unknown_e8;
    case 0xf1:
        data->unknown_e8=wparam;
        InvalidateRect(window,0,0);
        return 0;
    case 7:case 8:InvalidateRect(window,0,0);break;
    case 0x201:case 0x203: {
        Point2D click((unsigned int)lparam & 0xffff,(unsigned int)lparam>>16);
        if(click.X>=18)goto zero_result;
        if(click.Y>=18)goto zero_result;
        int checked=data->unknown_e8!=1;
        data->unknown_e8=checked;
        InvalidateRect(window,0,0);
        Voc_Play(Rules->GUICheckboxSound,1.0f,0x2000,0);
        HWND parent=GetParent(window);
        SendMessageA(parent,0x111,(unsigned int)(unsigned short)GetWindowLongA(window,-12)|((unsigned int)(unsigned short)checked<<16),(LPARAM)window);
        return 0;
    }
    case 0x497: {
        WNDPROC previous=0;
        WNDPROC *slot=unknown_window_procs_a73688.Find(window);
        if(slot)previous=*slot;
        data->unknown_e8=CallWindowProcA(previous,window,0xf0,0,0);
        break;
    }
    case 0x4e5: {
        bool previous=data->unknown_da;
        data->unknown_d9=lparam!=0;
        if(previous!=data->unknown_d9)InvalidateRect(window,0,0);
        break;
    }
    case 0x4e6: {
        bool previous=data->unknown_da;
        data->unknown_da=lparam!=0;
        if(previous!=data->unknown_da)InvalidateRect(window,0,0);
        break;
    }
    case 0x4e7:return data->unknown_da;
    }
    WNDPROC previous=0;
    WNDPROC *slot=unknown_window_procs_a73688.Find(window);
    if(slot)previous=*slot;
    return CallWindowProcA(previous,window,message,wparam,lparam);
    }
    return 0;
}
}
