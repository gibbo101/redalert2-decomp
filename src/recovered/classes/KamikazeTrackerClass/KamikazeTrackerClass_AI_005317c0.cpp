// void KamikazeTrackerClass::AI() (0x005317C0)
// Every 30 frames each tracked missile is sent (again) at its cell, or at the
// cell ahead of it when it has none (each branch makes both calls; VC6
// shares their tail).
#include "shared/kamikaze_tracker.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/facing.hpp"

void KamikazeTrackerClass::AI()
{
    if (Timer == 0) {
        Timer = 30;
        for (int index = 0; index < Nodes.Count(); index++) {
            KamikazeControl *node = Nodes[index];
            CellClass *cell = node->Cell;
            AircraftClass *missile = node->Unit;
            missile->unknown_254 = 1;
            if (cell == 0) {
                int facing = Dir_To_8(missile->unknown_2e0.Current());
                CellClass *here = (CellClass *)missile->unknown_slot105();
                CellClass *adjacent = &here->Adjacent_Cell(facing);
                missile->unknown_slot220(adjacent);
                missile->unknown_slot116(1, false);
            } else {
                missile->unknown_slot220(cell);
                missile->unknown_slot116(1, false);
            }
        }
    }
}
