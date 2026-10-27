// void __fastcall RadarEventClass_unknown_remember_cell(Cell const &cell) -- 0x0063C6C0
// Purpose: appends a cell to the eight-entry ring at 0x00AB6788 (radar
// event locations): advances the ring position (0x00AB67C8) modulo 8,
// stores the cell there and makes it the current entry (0x00AB6818).
// Assumptions: the ring's use (the cells the "go to last event" key cycles
// through) and all names are hypotheses; the cell is read as one 4-byte
// Cell.

#include "shared/coord.hpp"

extern Cell unknown_event_cells_ab6788[8];
extern int unknown_event_last_ab67c8;
extern int unknown_event_current_ab6818;
// @ref ?unknown_event_cells_ab6788@@3PAVCell@@A=00ab6788
// @ref ?unknown_event_last_ab67c8@@3HA=00ab67c8
// @ref ?unknown_event_current_ab6818@@3HA=00ab6818

void __fastcall RadarEventClass_unknown_remember_cell(Cell const &cell)
{
    unknown_event_last_ab67c8 = (unknown_event_last_ab67c8 + 1) % 8;
    unknown_event_cells_ab6788[unknown_event_last_ab67c8] = cell;
    unknown_event_current_ab6818 = unknown_event_last_ab67c8;
}
