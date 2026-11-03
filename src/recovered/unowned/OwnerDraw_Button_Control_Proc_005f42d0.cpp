// @ref ?Draw_0068cce0@UnknownBitmapWriter@@QAE_NABVRect@@PAVSurface@@1HH@Z=0068cce0
// @ref _unknown_button_left_format_7eadf4=007eadf4
// @ref _unknown_button_middle_format_7eade4=007eade4
// @ref _unknown_button_right_format_7eadd4=007eadd4
// @ref __imp__LockWindowUpdate@4=0079a454
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/win32_window.hpp"
#include "shared/surface.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/crt_string.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
extern "C" __declspec(dllimport) BOOL __stdcall LockWindowUpdate(HWND window);
extern "C" char const unknown_button_left_format_7eadf4[];
extern "C" char const unknown_button_middle_format_7eade4[];
extern "C" char const unknown_button_right_format_7eadd4[];
namespace OwnerDraw {
LRESULT __stdcall unknown_button_proc_5f42d0(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
{
    UnknownControlRecord *data=0;
    unknown_registry_a73640.Get((unsigned int)window,data);
    RECT display; memset(&display,0,sizeof(display));
    Window_Rect_In_Main_Client(window,&display);
    Rect origin;
    origin.X=display.left;origin.Y=display.top;
    origin.Width=display.right-display.left;origin.Height=display.bottom-display.top;
    RECT client; memset(&client,0,sizeof(client));
    GetClientRect(window,&client);
    int state=data->unknown_e8;
    LONG style=GetWindowLongA(window,-16);
    switch(message) {
    case 0xf: {
        Rect rect=origin;
        unsigned long color=unknown_color_a733e4;
        if(!data->surface_10) {
            BSurface *captured=new BSurface(client.right+1,client.bottom+1,2);
            data->surface_10=captured;
            ++unknown_surface_count_a763d8;
            Rect destination,source;
            destination.X=0;destination.Y=0;
            destination.Width=client.right+1;destination.Height=client.bottom+1;
            source.X=display.left;source.Y=display.top;
            source.Width=client.right+1;source.Height=client.bottom+1;
            captured->Copy_From(destination,*unknown_surface_839958,source,false,true);
        }
        if(data->image_14) {
            Surface *image=data->image_14;
            if((state & 1) && data->alternate_image_18)image=data->alternate_image_18;
            Rect source=rect;
            source.Y=source.X=0;
            unknown_surface_839958->Copy_From(rect,*image,source,false,true);
        } else {
            char updown='u';
            if(state & 1)updown='d';
            if(style & 0x08000000)updown='u';
            int widths[2]={7,7};
            int margins[2]={10,10};
            int heights[2]={24,30};
            unsigned index=0;
            for(unsigned i=0;i<2;i++) {
                if(heights[i]>rect.Height && i!=0)break;
                index=i;
            }
            int width=widths[index];
            int height=heights[index];
            int margin=margins[index];
            if(data->surface_10) {
                Rect source,destination;
                source.X=0;source.Y=0;
                source.Width=client.right+1;source.Height=client.bottom+1;
                destination.X=display.left;destination.Y=display.top;
                destination.Width=client.right+1;destination.Height=client.bottom+1;
                unknown_surface_839958->Copy_From(destination,*data->surface_10,source,false,true);
                InvalidateRect(window,0,0);
            }
            origin.Y+=(rect.Height-height)/2;
            if(state & 1)origin.Y+=2;
            char name[40];
            sprintf(name,unknown_button_left_format_7eadf4,updown,'e',height);
            Surface *image=unknown_bitmap_writer_a76378.Get_Image_0068ca40(name,0);
            origin.Height=image->Get_Height();
            Rect destination,source;
            destination=origin;
            destination.Width=width;
            source.Width=width;
            source.Y=0;
            source.X=0;
            destination.Height=height;
            source.Height=height;
            unknown_surface_839958->Copy_From(destination,*image,source,false,true);
            sprintf(name,unknown_button_middle_format_7eade4,updown,'e',height);
            image=unknown_bitmap_writer_a76378.Get_Image_0068ca40(name,0);
            Rect middle=origin;
            middle.X+=width;
            middle.Width-=margin;
            middle.Height=image->Get_Height();
            unknown_bitmap_writer_a76378.Draw_0068cce0(middle,unknown_surface_839958,image,0,0);
            sprintf(name,unknown_button_right_format_7eadd4,updown,'e',height);
            image=unknown_bitmap_writer_a76378.Get_Image_0068ca40(name,0);
            destination=origin;
            destination.X+=origin.Width-margin;
            destination.Width=margin;
            destination.Height=image->Get_Height();
            source.Width=destination.Width;
            source.Height=destination.Height;
            source.Y=0;
            source.X=0;
            unknown_surface_839958->Copy_From(destination,*image,source,false,true);
        }
        if(!data->image_14 && data->text_28) {
            RECT unused_client;
            GetClientRect(window,&unused_client);
            RECT text_rect;
            text_rect.left=origin.X;
            text_rect.top=origin.Y+1;
            text_rect.right=origin.Width+origin.X-2;
            text_rect.bottom=origin.Height+origin.Y-2;
            if(state & 1) {text_rect.left+=2;text_rect.top+=4;}
            unknown_draw_text_5fe020(unknown_surface_839958,data->text_28,&text_rect,data->font_64,color,5,0xc,0,0,0);
        }
        if(style & 0x08000000)Unknown_005feb60(&rect,unknown_surface_839958,0,128);
        ValidateRect(window,0);
        return 0;
    }
    case 0xf0:return data->unknown_e8;
    case 0xf1:
        data->unknown_e8=wparam;
        InvalidateRect(window,0,1);
        break;
    case 0x497: {
        WNDPROC previous=0;
        WNDPROC *slot=unknown_window_procs_a73688.Find(window);
        if(slot)previous=*slot;
        data->unknown_e8=CallWindowProcA(previous,window,0xf0,0,0);
        break;
    }
    case 0x201:case 0x203:
        if(!data->unknown_e8) {
            data->unknown_e8=1;
            InvalidateRect(window,0,1);
            Voc_Play(Rules->unknown_62c,1.0f,0x2000,0);
            break;
        }
        return 0;
    case 0x202: {
        LockWindowUpdate(GetParent(window));
        WNDPROC previous=0;
        WNDPROC *slot=unknown_window_procs_a73688.Find(window);
        if(slot)previous=*slot;
        LRESULT result=CallWindowProcA(previous,window,0x202,wparam,lparam);
        LockWindowUpdate(0);
        return result;
    }
    }
    WNDPROC previous=0;
    WNDPROC *slot=unknown_window_procs_a73688.Find(window);
    if(slot)previous=*slot;
    return CallWindowProcA(previous,window,message,wparam,lparam);
}
}
