// Call techno slot238 on units, infantry and aircraft occupying a cell.
// Free fastcall versus CellClass member source ownership remains a hypothesis.
#include "shared/building.hpp"
#include "shared/cell.hpp"
void __fastcall Cell_Occupants_Unknown_Slot238_0044fb10(CellClass *cell)
{
    for (ObjectClass *object = cell->OccupierPtr; object; object = object->unknown_30) {
        int kind = object->Kind_Of();
        if (kind == 1 || kind == 15 || kind == 2)
            ((TechnoClass *)object)->unknown_slot238();
    }
}
