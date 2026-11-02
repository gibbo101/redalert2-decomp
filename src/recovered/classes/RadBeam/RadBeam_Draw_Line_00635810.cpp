// void RadBeam::Draw_Line(CoordStruct const &start, CoordStruct const &end, short color) (0x00635810)
// Draws one segment of the beam on the current surface, clipped to the
// tactical area, its ends' depths from the beam's Depth and their heights.
#include "shared/rad_beam_list.hpp"
#include "shared/tactical.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/tool_tip.hpp"


void RadBeam::Draw_Line(CoordStruct const &start, CoordStruct const &end, short color)
{
    Point2D first_pixel;
    Point2D second_pixel;
    unknown_tactical_83996c->Coord_To_Pixel(start, first_pixel);
    unknown_tactical_83996c->Coord_To_Pixel(end, second_pixel);
    Rect clip = unknown_rect_839630;
    if (Clip_Line(first_pixel, second_pixel, clip)) {
        int first_z = Depth - Unknown_006A2970(start.Z) - 2;
        int second_z = 0 - Unknown_006A2970(end.Z) - 2;
        unknown_surface_83995c->Draw_Depth_Shaded_Line(unknown_rect_839630, first_pixel, second_pixel,
                                                       color, first_z, second_z);
    }
}
