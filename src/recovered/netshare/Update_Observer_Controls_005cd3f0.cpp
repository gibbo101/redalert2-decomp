// void __fastcall Unknown_005cd3f0(HWND dialog) (0x005CD3F0)
#include "shared/lobby.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/string_table.hpp"
// @ref ??_C@_08GBFD@GUI?3Join?$AA@=007e742c
// @ref ??_C@_09JNIK@wolob?4pcx?$AA@=007e7444
// @ref ??_C@_0L@HFKB@wolnob?4pcx?$AA@=007e7438
// @ref ??_C@_0M@HDJ@GUI?3Observe?$AA@=007d9cb0
// @ref ??_C@_0N@LIDG@GUI?3JoinGame?$AA@=007e741c
// @ref ??_C@_0BE@EJOA@D?3?2Ra2?2netshare?4cpp?$AA@=007e6ebc

void __fastcall Unknown_005cd3f0(HWND dialog)
{
    if (dialog != 0) {
        HWND control = GetDlgItem(dialog, 0x760);
        if (control != 0) {
            SendMessageA(control, 0xF1, unknown_a72c68 != 0, 0);
        }
        Surface *image;
        if (unknown_a72c68) {
            image = unknown_bitmap_writer_a76378.Get_Image_0068ca40("wolob.pcx", 0);
        } else {
            image = unknown_bitmap_writer_a76378.Get_Image_0068ca40("wolnob.pcx", 0);
        }
        HWND picture = GetDlgItem(dialog, 0x75F);
        OwnerDraw::unknown_5e1f30(picture, image);
        control = GetDlgItem(dialog, 0x6CD);
        if (control != 0) {
            wchar_t const *text;
            if (unknown_a72c68) {
                text = StringTable::Load_String("GUI:Observe", 0, "D:\\Ra2\\netshare.cpp", 0x17B8);
            } else {
                text = StringTable::Load_String("GUI:Join", 0, "D:\\Ra2\\netshare.cpp", 0x17BA);
            }
            SendMessageA(control, 0x4B2, 0, (LPARAM)text);
            InvalidateRect(control, 0, 0);
        }
        control = GetDlgItem(dialog, 0x62D);
        if (control != 0) {
            wchar_t const *text;
            if (unknown_a72c68) {
                text = StringTable::Load_String("GUI:Observe", 0, "D:\\Ra2\\netshare.cpp", 0x17C3);
            } else if (Find_Dialog_00735940(0x113) == dialog) {
                text = StringTable::Load_String("GUI:JoinGame", 0, "D:\\Ra2\\netshare.cpp", 0x17C7);
            } else {
                text = StringTable::Load_String("GUI:Join", 0, "D:\\Ra2\\netshare.cpp", 0x17C9);
            }
            SendMessageA(control, 0x4B2, 0, (LPARAM)text);
            InvalidateRect(control, 0, 0);
        }
    }
}
