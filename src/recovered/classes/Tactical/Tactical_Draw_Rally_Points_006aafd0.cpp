// void Tactical::Draw_Rally_Points(bool inshroud) (0x006AAFD0): for every selected factory of the player's house
// with a rally target (+0x1B0), a marching dashed line from the building to the target (ground height, lifted
// onto a bridge): one line 2 pixels low in the planning colour, then two in the house colour (TibSun Draw_Rally_Points). The
// `offset` local and the two sums it feeds count as inline sites: they push Coord_To_Pixel_Absolute out of line
// at the first Coord_To_Pixel and Point2D::operator-= out of line at the second.
#include "shared/tactical.hpp"
#include "shared/display.hpp"
#include "shared/building_class.hpp"
#include "shared/house.hpp"
#include "shared/hicolor.hpp"
#include "shared/planning.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref _unknown_geometry_j=00abe5e0
// @ref ??ZPoint2D@@QAEAAU0@ABU0@@Z=006ac850
// @ref ?Draw_Rally_Pattern@@3PA_NA=007f6954

extern bool Draw_Rally_Pattern[];

void Tactical::Draw_Rally_Points(bool inshroud)
{
    int phase = (0x7FFFFFFF - Frame) % 15;
    int shadow = Build_Hicolor_Pixel(unknown_rgb_ab6841.Red, unknown_rgb_ab6841.Green, unknown_rgb_ab6841.Blue);
    for (int index = unknown_objects_a40c60.Count() - 1; index >= 0; index--) {
        ObjectClass *object = unknown_objects_a40c60[index];
        if (object->Kind_Of() == 6 && object->unknown_7d && object->unknown_77) {
            BuildingClass *building = (BuildingClass *)object;
            if (building->House == unknown_player_a35db4 && building->unknown_slot153() && building->unknown_1b0 != 0) {
                CoordStruct center = building->Center_Coord();
 Point2D start;
 Coord_To_Pixel(center, start);
 start += Point2D(unknown_rect_839630.X, unknown_rect_839630.Y);
                CoordStruct rally = building->unknown_1b0->Center_Coord();
                rally.Z = Map.Unknown_0055A280(rally);
                if (Map[rally].unknown_140 & 0x100) {
                    rally.Z += unknown_geometry_j;
                }
                Point2D end;
                Coord_To_Pixel(rally, end);
                end += Point2D(unknown_rect_839630.X, unknown_rect_839630.Y);
                Point2D offset(0, 2);
 start += offset;
 end += offset;
                if (Clip_Line(start, end, unknown_rect_839630)) {
                    unknown_surface_83995c->Draw_Dashed_Line_Depth_Masked(start, end, shadow, Draw_Rally_Pattern, phase, inshroud);
                }
                RGBClass &rgb = building->House->unknown_55e9;
 int color = Build_Hicolor_Pixel(rgb.Red, rgb.Green, rgb.Blue);
                start.Y--;
                end.Y--;
                if (Clip_Line(start, end, unknown_rect_839630)) {
                    unknown_surface_83995c->Draw_Dashed_Line_Depth_Masked(start, end, color, Draw_Rally_Pattern, phase, inshroud);
                }
                start.Y--;
                end.Y--;
                if (Clip_Line(start, end, unknown_rect_839630)) {
                    unknown_surface_83995c->Draw_Dashed_Line_Depth_Masked(start, end, color, Draw_Rally_Pattern, phase, inshroud);
                }
              }
        }
    }
}
