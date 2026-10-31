// Behind animation and fallback targeting reticle, original 006D9080.
// Arg1 is independently observed as two dwords (Point2D); arg2 is an
// address passed by the original caller but never read by this body.
// Its nominal pointee type is unknown; keep the unused pointer opaque.
#include "shared/techno.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/convert.hpp"
#include "shared/surface.hpp"
#include "shared/color_scheme.hpp"
#include "shared/hicolor.hpp"
extern ConvertClass *unknown_drawer_8323c4;
extern DynamicVectorClass<AbstractClass *> unknown_abstracts_ac0bf8;
extern bool unknown_a40b33;
// @ref ?unknown_a40b33@@3_NA=00a40b33
void TechnoClass::unknown_6d9080(Point2D const &center, void const *unused)
{
    if (unknown_slot25(false,0)==0 && !unknown_108) {
        if (Rules->Behind) {
            unknown_108=new AnimClass(Rules->Behind,Center_Coord(),0,1,0x600,0);
            if (unknown_108) {
                if (Kind_Of()!=6) {
                    unknown_abstracts_ac0bf8.Delete((AbstractClass *)this);
                    unknown_abstracts_ac0bf8.Add(this);
                }
                ((AnimClass *)unknown_108)->Attach_To(this);
                if (!unknown_a40b33) ((AnimClass *)unknown_108)->unknown_17d=true;
            }
        } else {
            int color=unknown_drawer_8323c4->Convert(12);
            Point2D origin=center;
            int outside,inside;
            if (Frame&8) { outside=12; inside=8; }
            else { outside=10; inside=6; }
            for (int pass=0;pass<2;++pass) {
                unknown_surface_83995c->Draw_Line(origin+Point2D(-outside,-outside),origin+Point2D(-inside,-outside),color);
                unknown_surface_83995c->Draw_Line(origin+Point2D(inside,-outside),origin+Point2D(outside,-outside),color);
                unknown_surface_83995c->Draw_Line(origin+Point2D(outside,-outside),origin+Point2D(outside,-inside),color);
                unknown_surface_83995c->Draw_Line(origin+Point2D(outside,inside),origin+Point2D(outside,outside),color);
                unknown_surface_83995c->Draw_Line(origin+Point2D(outside,outside),origin+Point2D(inside,outside),color);
                unknown_surface_83995c->Draw_Line(origin+Point2D(-inside,outside),origin+Point2D(-outside,outside),color);
                unknown_surface_83995c->Draw_Line(origin+Point2D(-outside,outside),origin+Point2D(-outside,inside),color);
                unknown_surface_83995c->Draw_Line(origin+Point2D(-outside,-inside),origin+Point2D(-outside,-outside),color);
                unknown_surface_83995c->Draw_Line(origin+Point2D(-4,0),origin+Point2D(4,0),color);
                unknown_surface_83995c->Draw_Line(origin+Point2D(0,-4),origin+Point2D(0,4),color);
                ++origin.X;
                ++origin.Y;
                RGBClass rgb=ColorSchemes[unknown_player_a35db4->ColorSchemeIndex]->BaseColor.To_RGB();
                color=Build_Hicolor_Pixel(rgb.Red,rgb.Green,rgb.Blue);
            }
        }
    }
}
