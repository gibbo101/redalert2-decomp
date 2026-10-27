// GraphicMenuItem *__fastcall Create_Image_Item(Wstring const &section, INIClass &ini, void *unknown_a,
// Point2D const *offset) (0x004DF810): a GraphicMenuImageItem from a menu INI section (ID, Origin,
// ActiveRect, Image, Highlighted, Disabled, HighlightSound, SelectVQ); none without an ID. Origin
// and the active rectangle are moved by offset. Names are hypotheses.
// @ref ??_C@_02GMH@ID?$AA@=007d52a8
// @ref ??_C@_06GKHB@Origin?$AA@=007d9e24
// @ref ??_C@_0L@JDPA@ActiveRect?$AA@=007d9e18
// @ref ??_C@_05LADG@Image?$AA@=007cfddc
// @ref ?unknown_string_83c55c@@3PADA=0083c55c
// @ref ?Get_Point@INIClass@@QBE?AUINIPoint2D@@ABVWstring@@0ABUPoint2D@@@Z=0050f800
// @ref ?Get_Rect@INIClass@@QBE?AUINIRect@@ABVWstring@@0ABU2@@Z=0050df70
// @ref ??_C@_0M@PBGM@Highlighted?$AA@=007d9ea4
// @ref ??_C@_08FGLH@Disabled?$AA@=007d9e98
// @ref ??_C@_0P@GEHN@HighlightSound?$AA@=007d9e88
// @ref ??_C@_08JGEI@SelectVQ?$AA@=007d9e7c
// @ref ??0GraphicMenuImageItem@@QAE@HPAXABUPoint2D@@ABUINIRect@@ABVWstring@@3333@Z=004dfb30
#include "shared/ini_class.hpp"
#include "shared/graphic_menu.hpp"

extern char unknown_string_83c55c[];

GraphicMenuItem *__fastcall Create_Image_Item(Wstring const &section, INIClass &ini, void *unknown_a, Point2D const *offset)
{
    int id = ini.Get_Int(section, "ID", -1);
    if (id == -1) {
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
    Wstring image;
    Wstring highlighted;
    Wstring disabled;
    ini.Get_String(section, "Image", unknown_string_83c55c, image);
    ini.Get_String(section, "Highlighted", unknown_string_83c55c, highlighted);
    ini.Get_String(section, "Disabled", unknown_string_83c55c, disabled);
    Wstring sound;
    ini.Get_String(section, "HighlightSound", unknown_string_83c55c, sound);
    Wstring vq;
    ini.Get_String(section, "SelectVQ", unknown_string_83c55c, vq);
    return new GraphicMenuImageItem(id, unknown_a, origin, area, image, highlighted, disabled, sound, vq);
}
