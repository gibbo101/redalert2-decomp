// @ref ??H@YI?AVWstring@@PBDABV0@@Z=0076f6b0
// @ref ??_C@_09FECI@Territory?$AA@=007fbf08
// @ref ??_C@_09FBNK@Animation?$AA@=007fbf14
// @ref ??_C@_04OKCJ@Logo?$AA@=007fbf20
// @ref ??_C@_0P@LNCF@DefaultPalette?$AA@=007fbf28
// @ref ??_C@_0O@GJKG@NameKeyPrefix?$AA@=007fbf38
// @ref ??_C@_04FGEK@WDT?3?$AA@=007fbf48
// @ref ??_C@_0P@GGFL@OverlayPalette?$AA@=007fbf50
// @ref ??_C@_0O@MGKE@OverlayPrefix?$AA@=007fbf60
// @ref ??_C@_0BG@MOID@BackButtonHighlighted?$AA@=007fbf70
// @ref ??_C@_0L@FLDE@BackButton?$AA@=007fbf88
// @ref ??_C@_0BJ@BJJM@BackButtonDepressedFrame?$AA@=007fbf94
// @ref ??_C@_0BG@IAGB@BackButtonNormalFrame?$AA@=007fbfb0
// @ref ??_C@_0BC@GHHL@BackButtonPalette?$AA@=007fbfc8
// @ref ??_C@_0N@EJBG@sdbtnanm?4pal?$AA@=007fbfdc
// @ref ??_C@_0BB@ECNH@BackButtonOrigin?$AA@=007fbfec
// @ref ??_C@_0BE@NKMC@BackButtonRectangle?$AA@=007fc000
// @ref ??_C@_07KKOL@HelpBar?$AA@=007fc014
// @ref ??_C@_07FLDC@SideBar?$AA@=007fc01c
// @ref ??_C@_08OADD@ClickMap?$AA@=007e5c24
// @ref ??_C@_0L@BJIH@Background?$AA@=007d9d8c
// @ref ??_C@_07KCJC@Opening?$AA@=007fc024
// @ref ??_C@_0N@GGBF@BackTextRect?$AA@=007fc02c
// @ref ??_C@_09LAKB@TitleRect?$AA@=007fc03c
// @ref ??_C@_0M@HIFL@TooltipRect?$AA@=007fc048
// @ref ??_C@_08MIOO@TextRect?$AA@=007e5a68
// @ref ??_C@_0M@OMFK@HelpBarSize?$AA@=007fc054
// @ref ??_C@_0M@JGGP@SideBarSize?$AA@=007fc060
// @ref ??_C@_04BBDK@Size?$AA@=007d5e28
// @ref ??_C@_07MPGH@Art_800?$AA@=007fc06c
// @ref ??_C@_04HBPG@Art_?$AA@=007fc074
// @ref ??_C@_04CKLG@MAPS?$AA@=007fc07c
// Loads the World Domination Tour map layout and animation set (0x00729510).
#define RA2_WDT_MAP_LOAD_LAYOUT
#define RA2_RECT_POINT_INLINE
#include "shared/wdt_map.hpp"
#include "shared/wdt_voices.hpp"
#include "shared/ms_anim.hpp"
#include "shared/cc_file_class.hpp"

namespace WorldDominationTour {
void Map::Load(INIClass &ini, MSEngine *engine, int unknown3)
{
    Wstring map_section;
    ini.Get_String("MAPS", Wstring_From_Integer(unknown_08), unknown_string_83c55c, map_section);
    Wstring faction_section;
    ini.Get_String(map_section, Faction_Name(unknown_10), unknown_string_83c55c, faction_section);
    Wstring art;
    bool found = ini.Get_String(faction_section, "Art_" + Wstring_From_Integer(unknown_8523e0), unknown_string_83c55c, art) > 0;
    if (unknown_8523e0 > 800 && !found) {
        ini.Get_String(faction_section, "Art_800", unknown_string_83c55c, art);
    }
    Point2D size(640, 400);
    size = ini.Get_Point(art, "Size", size);
    Point2D sidebar_size(0, 0);
    sidebar_size = ini.Get_Point(art, "SideBarSize", sidebar_size);
    Point2D helpbar_size(0, 0);
    helpbar_size = ini.Get_Point(art, "HelpBarSize", helpbar_size);
    unknown_44 = Point2D((unknown_surface_839954->Get_Width() - sidebar_size.X - size.X) / 2,
                         (unknown_surface_839954->Get_Height() - size.Y - helpbar_size.Y) / 2);
    unknown_4c = Point2D(unknown_44.X, unknown_44.Y + size.Y);
    (INIRect &)DescriptionRect = ini.Get_Rect(art, "TextRect", (INIRect &)DescriptionRect);
    DescriptionRect += unknown_44;
    (INIRect &)TooltipRect = ini.Get_Rect(art, "TooltipRect", (INIRect &)TooltipRect);
    TooltipRect += unknown_44;
    (INIRect &)PlayRect = ini.Get_Rect(art, "TitleRect", (INIRect &)PlayRect);
    PlayRect += unknown_44;
    (INIRect &)BackRect = ini.Get_Rect(art, "BackTextRect", (INIRect &)BackRect);
    BackRect += unknown_44;
    Wstring value;
    ini.Get_String(art, "Opening", unknown_string_83c55c, value);
    if (value.Length() > 0) {
        Rect rectangle(unknown_44, size.X, size.Y);
        unknown_18 = new MSBinkAnim(value, unknown_surface_839958, &engine->Anims, rectangle, false);
        engine->Add_Anim(unknown_18);
    }
    ini.Get_String(art, "Background", unknown_string_83c55c, value);
    unknown_1c = new MSPCXAnim(value, &engine->Anims, unknown_44, true);
    if (unknown_18 && unknown_1c) unknown_1c->Set_Unknown_0C(false);
    engine->Add_Anim(unknown_1c);
    ini.Get_String(art, "ClickMap", 0, value);
    CCFileClass file(value);
    unknown_24 = unknown_load_pcx_60d110(&file, 0, 0, 0);
    file.Close();
    {
        MSAnim *sidebar = 0;
        ini.Get_String(art, "SideBar", unknown_string_83c55c, value);
        if (value.Length() > 0) {
            int const &width = size.X;
            Point2D position(width, (unknown_surface_839954->Get_Height() - sidebar_size.Y) / 2);
            position.X += unknown_44.X;
            sidebar = new MSPCXAnim(value, &engine->Anims, position, true);
        }
        engine->Add_Anim(sidebar);
    }
    ini.Get_String(art, "HelpBar", unknown_string_83c55c, value);
    if (value.Length() > 0) unknown_20 = new MSPCXAnim(value, &engine->Anims, unknown_4c, true);
    engine->Add_Anim(unknown_20);
    (INIRect &)unknown_54 = ini.Get_Rect(art, "BackButtonRectangle", (INIRect &)unknown_54);
    Point2D back_origin = ini.Get_Point(art, "BackButtonOrigin", Point2D(unknown_54.Top_Left()));
    unknown_54 += unknown_44;
    back_origin += unknown_44;
    ini.Get_String(art, "BackButtonPalette", "sdbtnanm.pal", value);
    delete unknown_78;
    unknown_78 = unknown_load_drawer_5ac560(value);
    unknown_6c.unknown_0 = ini.Get_Int(art, "BackButtonNormalFrame", unknown_6c.unknown_0);
    unknown_6c.unknown_4 = ini.Get_Int(art, "BackButtonDepressedFrame", unknown_6c.unknown_4);
    ini.Get_String(art, "BackButton", unknown_string_83c55c, value);
    if (value.Length() > 0) {
        unknown_64.unknown_0 = new MSOverlayAnim(value, back_origin.X, back_origin.Y, unknown_78, 0,
                                               &engine->Anims, true, unknown_6c.unknown_0, false);
        engine->Add_Anim(unknown_64.unknown_0);
    }
    ini.Get_String(art, "BackButtonHighlighted", unknown_string_83c55c, value);
    ini.Get_String(art, "OverlayPrefix", 0, unknown_28);
    ini.Get_String(art, "OverlayPalette", 0, value);
    unknown_14 = unknown_load_drawer_5ac560(value);
    Wstring name_prefix = Wstring("WDT:") + map_section;
    ini.Get_String(faction_section, "NameKeyPrefix", name_prefix, name_prefix);
    {
        ConvertClass *drawer = 0;
        if (ini.Get_String(art, "DefaultPalette", 0, value) > 0) drawer = Get_Drawer(value);
        MSAnim *animation = Load_Anim(ini, art, "Logo", drawer);
        if (animation) engine->Add_Anim(animation);
        for (int index = 0; index < 10; ++index) {
            value = "Animation" + Wstring_From_Integer(index);
            MSAnim *anim = Load_Anim(ini, art, value, drawer);
            if (anim) engine->Add_Anim(anim);
        }
    }
    for (int index = 0; index < 100; ++index) {
        if (ini.Get_String(faction_section, "Territory" + Wstring_From_Integer(index, 2), 0, value) > 0) {
            rc_ptr<Territory> territory = Territory::Create(index, ini, value, unknown_28, name_prefix);
            Territories.Add(territory);
        }
    }
    for (int owner_index = 0; owner_index < Territories.Count(); ++owner_index) {
        Territories[owner_index]->Create_Owner_Anim(engine, unknown_14, unknown_44);
    }
    for (int highlight_index = 0; highlight_index < Territories.Count(); ++highlight_index) {
        Territories[highlight_index]->Create_Highlight_Anim(engine, unknown_14, unknown_44);
    }
}
}
