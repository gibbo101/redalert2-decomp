// Draw the current firing/destination action line (004CAB90).
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/tactical.hpp"
#include "shared/surface.hpp"
#include "shared/hicolor.hpp"
extern Rect unknown_rect_839630;
extern int unknown_approach_bridge_height_865f60;
extern bool const unknown_action_line_pattern_7d81dc[];
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_approach_bridge_height_865f60@@3HA=00865f60
// @ref ?unknown_action_line_pattern_7d81dc@@3QB_NB=007d81dc
// @ref ??0Rect@@QAE@ABURectPoint2D@@HH@Z=00453e40

// DSurface's RGB overload (TibSun dsurface.h), expressed beside the existing
// free three-channel overload. It performs the real channel conversion.
inline int Build_Hicolor_Pixel(RGBClass const &rgb)
{
    return ((rgb.Get_Red() >> unknown_shift_852fbc) << unknown_shift_852fb8)
         | ((rgb.Get_Green() >> unknown_shift_852fcc) << unknown_shift_852fc8)
         | ((rgb.Get_Blue() >> unknown_shift_852fc4) << unknown_shift_852fc0);
}

// By-value area explains the native rectangle copies around the intersection.
// The inline helper's original declaration and name remain hypotheses.
static inline void Clipped_Fill(Rect area, int pixel)
{
    Rect clipped = Intersect(unknown_rect_839630, area);
    unknown_surface_839964->Fill_Rect(clipped, pixel);
}

void FootClass::unknown_4cab90()
{
    RGBClass white(255, 255, 255);
    RGBClass color;
    if (unknown_228 == 0 && unknown_494 == 0) return;
    CoordStruct start_coord;
    CoordStruct end_coord;
    if (unknown_228 != 0) {
        start_coord = unknown_slot181(0);
        end_coord = unknown_6d65b0();
    } else {
        start_coord = Coord;
        if (unknown_478.Count() == 0) {
            end_coord = unknown_494->Center_Coord();
        } else {
            end_coord = unknown_478[unknown_478.Count() - 1]->Center_Coord();
        }
        if (Map.Unknown_0054AAB0(Coord_Cell(end_coord)) && (Map[end_coord].unknown_140 & 0x100)) {
            end_coord.Z = Map.Unknown_0055A280(end_coord) + unknown_approach_bridge_height_865f60;
        }
    }
    Point2D start;
    Point2D end;
    unknown_tactical_83996c->Coord_To_Pixel(start_coord, start);
    unknown_tactical_83996c->Coord_To_Pixel(end_coord, end);
    start.Y += unknown_rect_839630.Y;
    end.Y += unknown_rect_839630.Y;
    color = House->unknown_55e9;
    int pixel = Build_Hicolor_Pixel(color);
    Clipped_Fill(Rect(RectPoint2D(start.X - 2, start.Y - 2), 3, 3), pixel);
    Clipped_Fill(Rect(RectPoint2D(end.X - 2, end.Y - 2), 3, 3), pixel);
    Rect clip = unknown_rect_839630;
    if (Clip_Line(start, end, clip)) {
        unsigned long tick = timeGetTime();
        unsigned amount = tick & 0x3ff;
        if (!(amount & 0x200)) {
            if (amount & 0x100) amount ^= 0xff;
            color.Adjust(amount & 0xff, white);
        }
        unknown_surface_839964->Draw_Dashed_Line_Depth_Masked(start, end, Build_Hicolor_Pixel(color), unknown_action_line_pattern_7d81dc, ((-(int)tick) >> 5) & 15, false);
    }
}
