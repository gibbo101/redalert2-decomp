#include "shared/wol_sink.hpp"
#include "shared/wonline_dialog_control.hpp"
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_dialog_5e5f20(HWND);
extern int unknown_online_option_a3d2a8;
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?unknown_online_option_a3d2a8@@3HA=00a3d2a8
extern char wol_standard_icon_007eb1fc[];
// @ref ?wol_standard_icon_007eb1fc@@3PADA=007eb1fc
extern char wol_tournament_icon_007eb25c[];
// @ref ?wol_tournament_icon_007eb25c@@3PADA=007eb25c
extern char wol_clan_icon_007eb228[];
// @ref ?wol_clan_icon_007eb228@@3PADA=007eb228
extern char wol_reserved_icon_007eafb4[];
// @ref ?wol_reserved_icon_007eafb4@@3PADA=007eafb4
extern char wol_observer_icon_007e7444[];
// @ref ?wol_observer_icon_007e7444@@3PADA=007e7444
extern char wol_private_icon_007eb234[];
// @ref ?wol_private_icon_007eb234@@3PADA=007eb234
extern char wol_ping_good_icon_007eafa8[];
// @ref ?wol_ping_good_icon_007eafa8@@3PADA=007eafa8
extern char wol_ping_medium_icon_007eaf9c[];
// @ref ?wol_ping_medium_icon_007eaf9c@@3PADA=007eaf9c
extern char wol_ping_poor_icon_007eaf90[];
// @ref ?wol_ping_poor_icon_007eaf90@@3PADA=007eaf90
long __stdcall Wonline_Mode_Menu_Dialog_00752950(HWND window,UINT message,WPARAM wparam,LPARAM lparam)
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
        return 1;
    case 0x14: return 1;
    case 0x2b: Unknown_005FE380(lparam); return 1;
    case 0x111:
        switch(wparam&0xffff) {
        case 0x6e0:
            unknown_a3d2a4=1;
            control->Set_Window_006010f0((unsigned)window,(HWND)0x6e0);
            return 0;
        case 0x6e1:
            unknown_a3d2a4=3;
            control->Set_Window_006010f0((unsigned)window,(HWND)0x6e1);
            return 0;
        case 0x6e2:
            unknown_a3d2a4=4;
            unknown_online_option_a3d2a8=0;
            control->Set_Window_006010f0((unsigned)window,(HWND)0x6e2);
            return 0;
        case 0x6e3:
            unknown_a3d2a4=2;
            control->Set_Window_006010f0((unsigned)window,(HWND)0x6e3);
            return 0;
        case 0x686:
            unknown_a3d2a4=0;
            control->Set_Window_006010f0((unsigned)window,(HWND)0x686);
            break;
        }
        break;
    case 0x497: {
        HWND image_control=GetDlgItem(window,0x746);
        Surface *image=unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_standard_icon_007eb1fc,0);
        if(image_control && image) OwnerDraw::unknown_5e1f30(image_control,image);
        image_control=GetDlgItem(window,0x747);
        image=unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_tournament_icon_007eb25c,0);
        if(image_control && image) OwnerDraw::unknown_5e1f30(image_control,image);
        image_control=GetDlgItem(window,0x748);
        image=unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_clan_icon_007eb228,0);
        if(image_control && image) OwnerDraw::unknown_5e1f30(image_control,image);
        image_control=GetDlgItem(window,0x749);
        image=unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_reserved_icon_007eafb4,0);
        if(image_control && image) OwnerDraw::unknown_5e1f30(image_control,image);
        image_control=GetDlgItem(window,0x74a);
        image=unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_observer_icon_007e7444,0);
        if(image_control && image) OwnerDraw::unknown_5e1f30(image_control,image);
        image_control=GetDlgItem(window,0x752);
        image=unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_private_icon_007eb234,0);
        if(image_control && image) OwnerDraw::unknown_5e1f30(image_control,image);
        image_control=GetDlgItem(window,0x75c);
        image=unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_ping_good_icon_007eafa8,0);
        if(image_control && image) OwnerDraw::unknown_5e1f30(image_control,image);
        image_control=GetDlgItem(window,0x75d);
        image=unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_ping_medium_icon_007eaf9c,0);
        if(image_control && image) OwnerDraw::unknown_5e1f30(image_control,image);
        image_control=GetDlgItem(window,0x75e);
        image=unknown_bitmap_writer_a76378.Get_Image_0068ca40(wol_ping_poor_icon_007eaf90,0);
        if(image_control && image) OwnerDraw::unknown_5e1f30(image_control,image);
        break;
    }
    }
    return 0;
}
