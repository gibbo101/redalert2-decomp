// Cell __fastcall RadarEventClass_unknown_previous_cell() -- 0x0063C720
// Steps the current entry of the radar event ring back by one (wrapping at eight) and returns its cell;
// when that entry is empty it starts again at the newest. The empty cell (0x00AB67A8) when the ring is
// empty. RA2 addition; names are hypotheses.
#include "shared/radar_event_class.hpp"
// @ref ?unknown_event_cells_ab6788@@3PAVCell@@A=00ab6788
// @ref ?unknown_event_empty_cell_ab67a8@@3VCell@@A=00ab67a8
// @ref ?unknown_event_last_ab67c8@@3HA=00ab67c8
// @ref ?unknown_event_current_ab6818@@3HA=00ab6818

Cell __fastcall RadarEventClass_unknown_previous_cell()
{
    if (unknown_event_last_ab67c8 == -1) {
        return unknown_event_empty_cell_ab67a8;
    }
    int index = unknown_event_current_ab6818 - 1;
    if (index < 0) {
        index += 8;
    }
    if (unknown_event_cells_ab6788[index] == unknown_event_empty_cell_ab67a8) {
        return RadarEventClass_unknown_newest_cell();
    }
    unknown_event_current_ab6818 = index;
    return unknown_event_cells_ab6788[index];
}
