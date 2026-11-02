// void Unknown_006F88F0() (0x006F88F0; the jump-to-radar-event command 0x0051C640): centres the view on the
// newest radar event cell, or on the previous one when pressed again within 50 frames, lifted by half the cell
// height; then (when 0x00833684 is set) calls 0x004994D0 with the unit's header-static cell (unknown_geometry_k
// at 0x00AC12D0; the result is dropped into the cell local).
#include "shared/uicmnds.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/radar_event_class.hpp"
#include "shared/tactical.hpp"
#include "shared/cell_class.hpp"
#include "shared/cd_timer.hpp"
// @ref ?unknown_radar_jump_frame_7f8bd4@@3HA=007f8bd4
// @ref ?unknown_833684@@3HA=00833684
extern int unknown_radar_jump_frame_7f8bd4;     // 0x007F8BD4 the frame of the last jump
extern int unknown_833684;                      // 0x00833684

void Unknown_006F88F0()
{
    Cell cell;
    if (Frame - unknown_radar_jump_frame_7f8bd4 < 50) {
        cell = RadarEventClass_unknown_previous_cell();
    } else {
        cell = RadarEventClass_unknown_newest_cell();
    }
    unknown_radar_jump_frame_7f8bd4 = Frame;
    if (cell.X != unknown_geometry_k.X || cell.Y != unknown_geometry_k.Y) {
        CoordStruct coord(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
        int height = Map[coord].unknown_11b * 256 / 2;
        coord -= CoordStruct(height, height, 0);
        unknown_tactical_83996c->Unknown_006A66B0(coord);
        if (unknown_833684 != 0) {
            Map.Unknown_004994D0(unknown_geometry_k);
        }
    }
}
