// void CellClass::unknown_478740() (0x00478740): calls ObjectClass slot 61
// on every occupant.
#include "shared/cell.hpp"
#include "shared/object.hpp"

void CellClass::unknown_478740()
{
    for (ObjectClass *object = OccupierPtr; object != 0; object = object->unknown_30) {
        object->unknown_slot61();
    }
}
