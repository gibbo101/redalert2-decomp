#include "shared/text_print.hpp"
#include "shared/string_table.hpp"
#include "shared/techno_type.hpp"
#include "shared/dsurface.hpp"
extern wchar_t const type_name_format_007d627c[];
extern wchar_t const type_cost_format_007d6268[];
extern wchar_t const type_cost_unavailable_007d6254[];
extern wchar_t const type_armament_format_007d6238[];
extern wchar_t const type_armament_none_007d6218[];
extern wchar_t const type_armor_format_007d6204[];
extern char const type_green_scheme_007d61fc[];
extern char const type_red_scheme_007d61f8[];
ColorScheme *__fastcall unknown_color_scheme_663d30(char const *name,int kind);
void __fastcall unknown_blit_49f3a0(Surface &dest,void *convert,Surface &source,Rect const &sourcerect,
    RectPoint2D const &destpoint,Rect const &destclip,int unknown1,int unknown2,int unknown3,int unknown4,int unknown5,int unknown6);
// @ref ?type_name_format_007d627c@@=007d627c
// @ref ?type_cost_format_007d6268@@=007d6268
// @ref ?type_cost_unavailable_007d6254@@=007d6254
// @ref ?type_armament_format_007d6238@@=007d6238
// @ref ?type_armament_none_007d6218@@=007d6218
// @ref ?type_armor_format_007d6204@@=007d6204
// @ref ?type_green_scheme_007d61fc@@=007d61fc
// @ref ?type_red_scheme_007d61f8@@=007d61f8
// @ref ?ArmorNames@@=0079de28
// @ref ?unknown_surface_83995c@@=0083995c
// @ref ?unknown_surface_839954@@=00839954
// @ref ?unknown_color_scheme_663d30@@=00663d30
// @ref ?unknown_blit_49f3a0@@=0049f3a0
// @ref ?Get_Weapon@TechnoTypeClass@@=006df5c0
// @ref ?Select_Blitter_00485AA0@ConvertClass@@=00485aa0
// @ref ??0Rect@@QAE@ABURectPoint2D@@HH@Z=00453e40
// @ref ??HRectPoint2D@@=00435540
// @ref _swprintf=00783764
void __fastcall Draw_Type_Details_004a97b0(Surface *background, ConvertClass *converter,
    TechnoTypeClass *type, bool show_cost)
{
    RectPoint2D offset;
    {
    Rect source_area = Rect(450,300,190,80);
    offset = RectPoint2D((unknown_surface_839954->Get_Width()-background->Get_Width())/2,
                   (unknown_surface_839954->Get_Height()-background->Get_Height())/2);
    RectPoint2D top_left = RectPoint2D(450,300);
    Rect clip = Rect(top_left+offset,190,80);
    RectPoint2D zero(0,0);
    // Preserve the existing unresolved blit prototype's 32-bit payload spelling.
    unknown_blit_49f3a0(*unknown_surface_839954,converter,*background,source_area,
        zero,clip,0,reinterpret_cast<int>(converter->Select_Blitter_00485AA0(0)),0,0,1000,0);
    }
    if (type) {
        wchar_t name[40];
        wchar_t cost[20];
        wchar_t armament[40];
        wchar_t armor[30];
        swprintf(name,type_name_format_007d627c,(char const *)type->Name);
        if (show_cost) swprintf(cost,type_cost_format_007d6268,type->Raw_Cost());
        else swprintf(cost,type_cost_unavailable_007d6254);
        if (type->Get_Weapon(0)->WeaponType)
            swprintf(armament,type_armament_format_007d6238,(char const *)type->Get_Weapon(0)->WeaponType->Name);
        else swprintf(armament,type_armament_none_007d6218);
        swprintf(armor,type_armor_format_007d6204,ArmorNames[type->unknown_9c]);
        ColorScheme *scheme;
        if(show_cost) scheme=unknown_color_scheme_663d30(type_green_scheme_007d61fc,1);
        else scheme=unknown_color_scheme_663d30(type_red_scheme_007d61f8,1);
        {
            Point2D position = Point2D(offset.X+450,offset.Y+300);
            Fancy_Text_Printf(name,unknown_surface_839954,&unknown_surface_839954->Get_Rect(),
                &position,scheme,0,0x46);
        }
        {
            Point2D position = Point2D(offset.X+450,offset.Y+315);
            Fancy_Text_Printf(armament,unknown_surface_839954,&unknown_surface_839954->Get_Rect(),
                &position,scheme,0,0x46);
        }
        {
            Point2D position = Point2D(offset.X+450,offset.Y+330);
            Fancy_Text_Printf(armor,unknown_surface_839954,&unknown_surface_839954->Get_Rect(),
                &position,scheme,0,0x46);
        }
        {
            Point2D position = Point2D(offset.X+450,offset.Y+345);
            Fancy_Text_Printf(cost,unknown_surface_839954,&unknown_surface_839954->Get_Rect(),
                &position,scheme,0,0x46);
        }
    }
}
