// bool BuildingClass::unknown_449930() (0x00449930)
// Whether an object other than the building stands in any cell of its
// foundation (slot 64's offsets from the slot 104 cell).
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

static inline bool Is_List_End(Cell const *offset)
{
    return offset->X == 0x7FFF && offset->Y == 0x7FFF;
}

bool BuildingClass::unknown_449930()
{
    Cell cell = unknown_slot104();
    Cell const *offset = unknown_slot64(0);
    bool found = false;
    while (!Is_List_End(offset)) {
        Cell position = *offset + cell;
        offset++;
        ObjectClass *object = Map[position].OccupierPtr;
        while (object) {
            if (this != object) {
                found = true;
                break;
            }
            object = object->unknown_30;
        }
    }
    return found;
}
