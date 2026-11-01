// GraphicMenu *GraphicMenu::Load(INIClass &ini, Wstring const &section) (0x004DE380): a new menu from the
// section: Background= names the picture (<name>.VQA, else <name>.BIK, else <name>.PCX plays as the background
// animation, whose origin offsets the items), Theme= the music, items in the keys 0..ItemMax (Create_Menu_Item).
// 0 when the section is missing.
#include "shared/graphic_menu_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ini_class.hpp"
#include "shared/ms_anim.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/crt_string.hpp"
// @ref _sprintf=007820f4
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_04DCKM@?4PCX?$AA@=007d9d84
// @ref ??_C@_0L@BJIH@Background?$AA@=007d9d8c
// @ref ??_C@_04MOHI@?4VQA?$AA@=007d9d7c
// @ref ??_C@_04HJCD@?4BIK?$AA@=007d9d74
// @ref ??_C@_07KDK@ItemMax?$AA@=007d9d64
// @ref ??0?$VectorClass@PAVGraphicMenuItem@@@@QAE@IPBQAVGraphicMenuItem@@@Z=004df2e0
// @ref ??_C@_05PDLI@Theme?$AA@=007d9d6c
// @ref ??0CCFileClass@@QAE@ABVWstring@@@Z=00468f90
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ?Create_Menu_Item@@YIPAVGraphicMenuItem@@ABVWstring@@AAVINIClass@@PAXPBUPoint2D@@@Z=004dff80
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ?unknown_8523e0@@3HA=008523e0
// @ref ?unknown_8523e4@@3HA=008523e4
GraphicMenuItem *__fastcall Create_Menu_Item(Wstring const &section, INIClass &ini, void *unknown_a, Point2D const *offset);

GraphicMenu *__fastcall GraphicMenu::Load(INIClass &ini, Wstring const &section)
{
    if (ini.Find_Section(section) == 0) {
        return 0;
    }
    GraphicMenu *menu = new GraphicMenu;
    if (menu == 0) {
        return 0;
    }

    Wstring value;
    bool found = ini.Get_String(section, "Background", "", value) > 0;
    Wstring background = value + ".PCX";
    menu->Set_Background(background);
    Point2D offset(0, 0);
    if (found) {
        Wstring vqa = value + ".VQA";
        MSAnim *anim = 0;
        if (CCFileClass(vqa).Is_Available()) {
            anim = new MSVQAnim(vqa, unknown_surface_839958, &menu->Engine.Anims, true);
        }
        if (anim == 0) {
            Wstring bik = value + ".BIK";
            if (CCFileClass(bik).Is_Available()) {
                Rect rect(0, 0, unknown_8523e0, unknown_8523e4);
                anim = new MSBinkAnim(bik, unknown_surface_839958, &menu->Engine.Anims, rect, true);
            }
        }
        if (anim == 0) {
            anim = new MSPCXAnim(background.Get(), &menu->Engine.Anims, true);
        }
        menu->Set_Anim(anim);
        // The items are placed relative to the animation's corner (read straight from the returned rectangle).
        offset = Offset_Point(Point2D(0, 0), anim->Get_Rect());
    }

    if (ini.Get_String(section, "Theme", "", value) > 0) {
        menu->Set_Theme(value);
    }

    char key[8];
    int max = ini.Get_Int(section, "ItemMax", 100);
    for (int index = 0; index <= max; index++) {
        sprintf(key, "%d", index);
        if (ini.Get_String(section, key, "", value) > 0) {
            GraphicMenuItem *item = Create_Menu_Item(value, ini, &menu->Engine, &offset);
            if (item) {
                menu->Add_Item(item);
            }
        }
    }
    return menu;
}
