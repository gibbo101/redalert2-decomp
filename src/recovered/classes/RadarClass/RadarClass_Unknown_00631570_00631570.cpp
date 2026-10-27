// void RadarClass::Unknown_00631570(Cell const &cell) (0x00631570)
// Queues a cell for the radar to redraw (newest first in the search), and
// notes that cells are pending (+0x14D5).
#include "shared/radar.hpp"

void RadarClass::Unknown_00631570(Cell const &cell)
{
    for (int index = unknown_1220.Count() - 1; index >= 0; index--) {
        if (unknown_1220[index] == cell) {
            return;
        }
    }
    unknown_1220.Add(cell);
    unknown_14d5 = true;
}
