// GraphicMenuItem *__fastcall Create_Menu_Item(Wstring const &section, INIClass &ini, void *unknown_a,
// Point2D const *offset) (0x004DFF80): the menu item a section's Type= names (Image 0x004DF810, Shortcut
// 0x004E0250, Anim 0x004DF350; none otherwise), with its SelectSound= when given. Names are
// hypotheses. unknown_a and offset pass through to the item factories (the anim item constructor
// hands its animation to unknown_a, 0x005B2D60; offset is added to the item's origin and area).
// @ref ??_C@_04FCOP@Type?$AA@=007d9eec
// @ref ??_C@_05LADG@Image?$AA@=007cfddc
// @ref ??_C@_08CGHL@Shortcut?$AA@=007d9ee0
// @ref ??_C@_04LFDA@Anim?$AA@=007cdea0
// @ref ??_C@_0M@CHBD@SelectSound?$AA@=007d9ed4
// @ref ?unknown_string_83c55c@@3PADA=0083c55c
// @ref ?Create_Image_Item@@YIPAVGraphicMenuItem@@ABVWstring@@AAVINIClass@@PAXPBUPoint2D@@@Z=004df810
// @ref ?Create_Anim_Item@@YIPAVGraphicMenuItem@@ABVWstring@@AAVINIClass@@PAXPBUPoint2D@@@Z=004df350
// @ref ?Create_Shortcut_Item@@YIPAVGraphicMenuItem@@ABVWstring@@AAVINIClass@@@Z=004e0250
#include "shared/ini_class.hpp"
#include "shared/graphic_menu.hpp"

extern char unknown_string_83c55c[];
GraphicMenuItem *__fastcall Create_Image_Item(Wstring const &section, INIClass &ini, void *unknown_a, Point2D const *offset);
GraphicMenuItem *__fastcall Create_Anim_Item(Wstring const &section, INIClass &ini, void *unknown_a, Point2D const *offset);
GraphicMenuItem *__fastcall Create_Shortcut_Item(Wstring const &section, INIClass &ini);

GraphicMenuItem *__fastcall Create_Menu_Item(Wstring const &section, INIClass &ini, void *unknown_a, Point2D const *offset)
{
    Wstring type;
    ini.Get_String(section, "Type", unknown_string_83c55c, type);
    GraphicMenuItem *item = 0;
    if (type == "Image") {
        item = Create_Image_Item(section, ini, unknown_a, offset);
    } else if (type == "Shortcut") {
        item = Create_Shortcut_Item(section, ini);
    } else if (type == "Anim") {
        item = Create_Anim_Item(section, ini, unknown_a, offset);
    }
    if (item) {
        Wstring sound;
        if (ini.Get_String(section, "SelectSound", unknown_string_83c55c, sound) > 0) {
            item->Sound = new MSSfxEntry("SelectSound", sound);
        }
    }
    return item;
}
