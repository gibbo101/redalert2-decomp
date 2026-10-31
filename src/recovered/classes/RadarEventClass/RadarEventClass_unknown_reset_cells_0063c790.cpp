// void __cdecl RadarEventClass_unknown_reset_cells() -- 0x0063C790
// Purpose: empties the eight-entry ring of radar event cells (0x00AB6788,
// see 0x0063C6C0): the ring position (0x00AB67C8) and the current entry
// (0x00AB6818) become -1 and every entry the cell at 0x00AB67A8.
// Assumptions: 0x00AB67A8 (the cell after the ring) is an empty/invalid
// cell constant; all names are hypotheses.

#include "shared/coord.hpp"

extern Cell unknown_event_cells_ab6788[8];
extern Cell unknown_event_empty_cell_ab67a8;
extern int unknown_event_last_ab67c8;
extern int unknown_event_current_ab6818;
// @ref ?unknown_event_cells_ab6788@@3PAVCell@@A=00ab6788
// @ref ?unknown_event_empty_cell_ab67a8@@3VCell@@A=00ab67a8
// @ref ?unknown_event_last_ab67c8@@3HA=00ab67c8
// @ref ?unknown_event_current_ab6818@@3HA=00ab6818

void RadarEventClass_unknown_reset_cells()
{
    unknown_event_last_ab67c8 = -1;
    unknown_event_current_ab6818 = -1;
    for (int i = 0; i < 8; i++) {
        unknown_event_cells_ab6788[i] = unknown_event_empty_cell_ab67a8;
    }
}
