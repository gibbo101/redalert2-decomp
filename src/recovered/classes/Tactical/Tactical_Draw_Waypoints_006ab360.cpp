// void Tactical::Draw_Waypoints(bool inshroud) (0x006AB360): the player's waypoint paths over the view: the cursor
// and the index of every waypoint on screen on the requested side of the shroud, and a line to the next waypoint,
// marching dashes on the selected path. The four table entries the dashed line cycles are saved around the drawing
// (TibSun Draw_Waypoints). `offset` holds the rectangle's Y only, in a Point2D. Print_Label is a file-local wrapper:
// it charges the inline budget that keeps the second Coord_To_Pixel's Rectangular_To_Isometric out of line.
#include "shared/tactical.hpp"
#include "shared/display.hpp"
#include "shared/house.hpp"
#include "shared/waypoint_path.hpp"
#include "shared/convert.hpp"
#include "shared/palette.hpp"
#include "shared/text_print.hpp"
#include "shared/string_table.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/color_scheme.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ??_C@_09JKEA@MOUSE?4SHP?$AA@=007db964
// @ref ?unknown_drawer_8323c8@@3PAVConvertClass@@A=008323c8
// @ref ?Waypoint_Line_Style@@3PA_NA=007f6964
// @ref ?Waypoint_Mouse_Shapes@@3PAXA=00abfd74
// @ref ?Waypoint_Text@@3PAGA=00abe4c8
// @ref ??_C@_15KLDP@?$AA?$CF?$AAd?$AA?$AA@=007d1598

extern ConvertClass *unknown_drawer_8323c8;

// The four table entries the dashed line cycles (the table at +2 as a block).
struct Dash_Entries {
    int Value[4];
};
extern bool Waypoint_Line_Style[];
extern void *Waypoint_Mouse_Shapes;
extern wchar_t Waypoint_Text[];

static inline void Print_Label(Point2D *point, ColorScheme *scheme)
{
    Fancy_Text_Print(Waypoint_Text, unknown_surface_83995c, &unknown_rect_839630, point, scheme, 0, 0x109);
}
void Tactical::Draw_Waypoints(bool inshroud)
{
    int phase = (0x7FFFFFFF - Frame) % 15;
    int start_frame = Map.Get_Mouse_Start(0x3C);
    int frame = unknown_da0 % Map.Get_Mouse_Count(0x3C) + start_frame;
    if (unknown_flag_a40d13) {
        return;
    }
    Dash_Entries *dashtable = (Dash_Entries *)((unsigned short *)unknown_drawer_8323c8->Table + 1);
    Dash_Entries dashsave = *(Dash_Entries *)((unsigned short *)unknown_drawer_8323c8->Table + 1);
    if (Waypoint_Mouse_Shapes == 0) {
        Waypoint_Mouse_Shapes = (void *)MixFileClass::Retrieve("MOUSE.SHP");
    }
    Point2D offset(0, unknown_rect_839630.Y + 1);
    int coloridx = unknown_id_source_a3d290->Theater != 1 ? 14 : 12;
    for (int path = 0; path < 12; path++) {
        unknown_player_a35db4->Make_Waypoint_Path(path);
        int count = unknown_player_a35db4->WaypointPaths[path]->Waypoints.Count();
        if (count != 0) {
            Map.Unknown_0049EB40(path);
        }
        for (int index = 0; index < count; index++) {
            WaypointClass *waypoint = unknown_player_a35db4->WaypointPaths[path]->Get_Waypoint(index);
            Point2D pixel;
            bool onscreen;
            if (Coord_To_Pixel(waypoint->Coord, pixel) && ((inshroud && Map.Unknown_00568140(waypoint->Coord)) || (!inshroud && !Map.Unknown_00568140(waypoint->Coord)))) {
                onscreen = true;
            } else {
                onscreen = false;
            }
            pixel.Y += unknown_rect_839630.Y;
            if (onscreen) {
                CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323c8, (ShapeFileStruct const *)Waypoint_Mouse_Shapes, frame, pixel - offset, unknown_rect_839630, 0x600, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
                swprintf(Waypoint_Text, L"%d", index);
                Point2D label = pixel - offset + Point2D(-1, -25);
                Print_Label(&label, ColorSchemes[coloridx]);
            }
            WaypointClass *next = unknown_player_a35db4->WaypointPaths[path]->Next_Waypoint(waypoint);
            if (next != 0) {
                Point2D nextpixel;
                Coord_To_Pixel(next->Coord, nextpixel);
                nextpixel.Y += unknown_rect_839630.Y;
                if (Clip_Line(pixel, nextpixel, unknown_rect_839630)) {
                    if (path == unknown_player_a35db4->unknown_154) {
                        phase = unknown_surface_83995c->Draw_Dashed_Line_Depth_Masked(pixel, nextpixel, unknown_drawer_8323c8->Convert(3), Waypoint_Line_Style, phase, inshroud);
                    } else {
                        unknown_surface_83995c->Draw_Line_Depth_Masked(pixel, nextpixel, unknown_drawer_8323c8->Convert(3), inshroud);
                    }
                }
            }
        }
    }
    *dashtable = dashsave;
}
