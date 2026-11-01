// Cell __fastcall RadarEventClass_unknown_newest_cell() -- 0x0063C6F0
// The newest cell of the radar event ring (0x00AB6788), made the current entry (0x00AB6818); the empty
// cell (0x00AB67A8) when the ring is empty. RA2 addition; names are hypotheses.
#include "shared/radar_event_class.hpp"
// @ref ?unknown_event_cells_ab6788@@3PAVCell@@A=00ab6788
// @ref ?unknown_event_empty_cell_ab67a8@@3VCell@@A=00ab67a8
// @ref ?unknown_event_last_ab67c8@@3HA=00ab67c8
// @ref ?unknown_event_current_ab6818@@3HA=00ab6818

Cell __fastcall RadarEventClass_unknown_newest_cell()
{
    if (unknown_event_last_ab67c8 == -1) {
        return unknown_event_empty_cell_ab67a8;
    }
    unknown_event_current_ab6818 = unknown_event_last_ab67c8;
    return unknown_event_cells_ab6788[unknown_event_last_ab67c8];
}
