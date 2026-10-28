// void KamikazeTrackerClass::Detach(AbstractClass *target) (0x00531880)
// A missile that is gone is dropped from the list; missiles flying at a cell
// that is detached are sent at the target's cell instead.
#include "shared/kamikaze_tracker.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"

void KamikazeTrackerClass::Detach(AbstractClass *target)
{
    for (int index = Nodes.Count() - 1; index >= 0; index--) {
        KamikazeControl *node = Nodes[index];
        if (target == node->Unit) {
            delete Nodes[index];
            Nodes.Delete(index);
            return;
        }
        if (target == node->Cell) {
            CellClass *cell = &Map[Coord_Cell(target->Center_Coord())];
            Nodes[index]->Unit->unknown_slot220(cell);
            Nodes[index]->Unit->unknown_slot116(1, false);
            Nodes[index]->Cell = cell;
            return;
        }
    }
}
