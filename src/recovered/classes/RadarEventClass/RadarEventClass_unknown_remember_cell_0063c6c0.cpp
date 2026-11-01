// void __fastcall RadarEventClass_unknown_remember_cell(Cell const &cell) -- 0x0063C6C0
// Appends a cell to the eight-entry ring of radar event cells (0x00AB6788): advances the newest entry
// (0x00AB67C8) modulo 8, stores the cell there and makes it the current entry (0x00AB6818). RA2's
// replacement for TS's LastRadarEventCell; names are hypotheses.
#include "shared/radar_event_class.hpp"
// @ref ?unknown_event_cells_ab6788@@3PAVCell@@A=00ab6788
// @ref ?unknown_event_last_ab67c8@@3HA=00ab67c8
// @ref ?unknown_event_current_ab6818@@3HA=00ab6818

void __fastcall RadarEventClass_unknown_remember_cell(Cell const &cell)
{
    unknown_event_last_ab67c8 = (unknown_event_last_ab67c8 + 1) % 8;
    unknown_event_cells_ab6788[unknown_event_last_ab67c8] = cell;
    unknown_event_current_ab6818 = unknown_event_last_ab67c8;
}
