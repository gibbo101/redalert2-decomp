// void CellClass::unknown_47a160() (0x0047A160): takes up to ten occupants,
// calls their slot 109 with 0 and passes +0x11C to the locomotor of each unit
// or aircraft (ILocomotion::Force_New_Slope). No direct callers.
#include "shared/cell.hpp"
#include "shared/foot.hpp"

void CellClass::unknown_47a160()
{
    ObjectClass *objects[10];
    int count = 0;
    for (ObjectClass *object = OccupierPtr; object != 0 && count < 10; object = object->unknown_30) {
        objects[count++] = object;
    }
    for (int index = 0; index < count; index++) {
        ObjectClass *occupant = objects[index];
        occupant->unknown_slot109(0);
        if (occupant->Kind_Of() == 1 || occupant->Kind_Of() == 2) {
            ((FootClass *)occupant)->Locomotor.Checked()->Force_New_Slope(unknown_11c);
        }
    }
}
