// ObjectClass *CellClass::Find_Object(int kind, bool alt) const (0x00471760):
// the first occupant (alt: of the alternate list) whose Kind_Of is kind;
// none while unknown_flag_a40958 is clear.
#include "shared/cell.hpp"
#include "shared/object.hpp"

ObjectClass *CellClass::Find_Object(int kind, bool alt) const
{
    if (unknown_flag_a40958) {
        for (ObjectClass *object = alt ? AltOccupierPtr : OccupierPtr; object != 0; object = object->unknown_30) {
            if (object->Kind_Of() == kind) {
                return object;
            }
        }
    }
    return 0;
}
