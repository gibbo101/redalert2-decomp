// GraphicMenuItem *__fastcall Create_Anim_Item(Wstring const &section, INIClass &ini, void *unknown_a,
// Point2D const *offset) (0x004DF350): a GraphicMenuAnimItem from a menu INI section (ID, Image,
// Palette, Origin, ActiveRect, Loop, Rate); none without an ID, image or palette. Origin and the
// active rectangle are moved by offset. Names are hypotheses. The literals convert implicitly to
// the Wstring overloads; Loop goes through the char const * Get_Bool (Wstring 0x0076E730).
// @ref ??_C@_02GMH@ID?$AA@=007d52a8
// @ref ??_C@_05LADG@Image?$AA@=007cfddc
// @ref ??_C@_07NBFD@Palette?$AA@=007d9e2c
// @ref ??_C@_06GKHB@Origin?$AA@=007d9e24
// @ref ??_C@_0L@JDPA@ActiveRect?$AA@=007d9e18
// @ref ??_C@_04PHFA@Loop?$AA@=007d9e10
// @ref ??_C@_04GGHG@Rate?$AA@=007cef5c
// @ref ?unknown_string_83c55c@@3PADA=0083c55c
// @ref ?Get_Point@INIClass@@QBE?AUINIPoint2D@@ABVWstring@@0ABUPoint2D@@@Z=0050f800
// @ref ?Get_Rect@INIClass@@QBE?AUINIRect@@ABVWstring@@0ABU2@@Z=0050df70
// @ref ??0GraphicMenuAnimItem@@QAE@HPAXABUPoint2D@@ABUINIRect@@ABVWstring@@3H_N@Z=004df5f0
#include "shared/ini_class.hpp"
#include "shared/graphic_menu.hpp"

extern char unknown_string_83c55c[];

GraphicMenuItem *__fastcall Create_Anim_Item(Wstring const &section, INIClass &ini, void *unknown_a, Point2D const *offset)
{
    int id = ini.Get_Int(section, "ID", -1);
    if (id == -1) {
        return 0;
    }
    Wstring image;
    ini.Get_String(section, "Image", unknown_string_83c55c, image);
    if (!image.Length()) {
        return 0;
    }
    Wstring palette;
    ini.Get_String(section, "Palette", unknown_string_83c55c, palette);
    if (!palette.Length()) {
        return 0;
    }
    Point2D origin(0, 0);
    origin = ini.Get_Point(section, "Origin", origin);
    origin.X += offset->X;
    origin.Y += offset->Y;
    INIRect area;
    area.X = 0;
    area.Y = 0;
    area.Width = 0;
    area.Height = 0;
    area = ini.Get_Rect(section, "ActiveRect", area);
    area.X += offset->X;
    area.Y += offset->Y;
    bool loop = ini.Get_Bool(section.Peek_Buffer(), "Loop", true);
    int rate = ini.Get_Int(section, "Rate", 5);
    return new GraphicMenuAnimItem(id, unknown_a, origin, area, image, palette, rate, loop);
}
