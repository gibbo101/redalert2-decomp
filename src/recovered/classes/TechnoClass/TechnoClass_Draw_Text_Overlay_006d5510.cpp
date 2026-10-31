// @ref ??_C@_07CBAG@TXT_PRI?$AA@=007f7154
// @ref ??_C@_0M@KHJI@TXT_PRIMARY?$AA@=007f715c
// @ref ??_C@_0BB@MNCD@TXT_POWER_DRAIN2?$AA@=007f7168
// @ref ??_C@_0BC@GBPC@D?3?2Ra2?2Techno?4CPP?$AA@=007f717c
// Draw power figures and the primary-factory label over the object.
#include "shared/techno.hpp"
#include "shared/text_print.hpp"
#include "shared/string_table.hpp"
#include "shared/surface.hpp"
#include "shared/hicolor.hpp"
void TechnoClass::unknown_slot251(Point2D const &point,Point2D const &center,Rect const &window)
{
    if(Kind_Of()==6 && static_cast<BuildingClass *>(this)->Type->Power>0) {
        if(!unknown_32b) {
            wchar_t text[128];
            swprintf(text,StringTable::Load_String("TXT_POWER_DRAIN2",0,"D:\\Ra2\\Techno.CPP",0x3517),House->Power_Output(),House->Power_Drain());
            Rect background=Text_Rect(text,center.X,center.Y,0x149,4,2);
            background=background.Intersect(window);
            RGBClass const &color=House->unknown_55e9;
            unsigned pixel=Build_Hicolor_Pixel(color.Red,color.Green,color.Blue);
            unknown_surface_83995c->Fill_Rect(background,0);
            unknown_surface_83995c->Draw_Rect(background,pixel);
            Simple_Text_Print(text,unknown_surface_83995c,&window,const_cast<Point2D *>(&center),pixel,0,0x149,1);
        }
    }
    if(unknown_32b) {
        wchar_t const *label=StringTable::Load_String("TXT_PRIMARY",0,"D:\\Ra2\\Techno.CPP",0x352a);
        if(Kind_Of()==6 && static_cast<BuildingClass *>(this)->Type->Width()==1) label=StringTable::Load_String("TXT_PRI",0,"D:\\Ra2\\Techno.CPP",0x352c);
        Rect background=Text_Rect(label,center.X,center.Y,0x149,4,2);
        background=background.Intersect(window);
        RGBClass const &color=House->unknown_55e9;
        unsigned pixel=Build_Hicolor_Pixel(color.Red,color.Green,color.Blue);
        unknown_surface_83995c->Fill_Rect(background,0);
        unknown_surface_83995c->Draw_Rect(background,pixel);
        Simple_Text_Print(label,unknown_surface_83995c,&window,const_cast<Point2D *>(&center),pixel,0,0x149,1);
    }
}
