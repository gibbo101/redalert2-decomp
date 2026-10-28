// void KamikazeTrackerClass::Add(AircraftClass *missile, AbstractClass *target) (0x005316A0)
// A spawned missile is tracked flying at the target's cell (or the cell ahead
// of it without a target); any other aircraft gets slot 224 instead.
#include "shared/kamikaze_tracker.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/facing.hpp"
#include "shared/map_view.hpp"

void KamikazeTrackerClass::Add(AircraftClass *missile, AbstractClass *target)
{
    if (!missile->Type->MissileSpawn) {
        missile->unknown_slot224(0);
        return;
    }
    KamikazeControl *node = new KamikazeControl;
    node->Unit = missile;
    if (target == 0) {
        int facing = Dir_To_8(missile->unknown_2e0.Current());
        CellClass *here = (CellClass *)missile->unknown_slot105();
        node->Cell = &here->Adjacent_Cell(facing);
    } else {
        node->Cell = &Map[Coord_Cell(target->Center_Coord())];
    }
    missile->unknown_5b2 = true;
    missile->unknown_254 = 1;
    Nodes.Add(node);
}
