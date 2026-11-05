#define RA2_COORD_EQUAL_MEMBER
// int Planning_Selection_Kind() (0x00616B40)
// Classifies the selection for planning mode: -1 when slot 274 accepts every
// selected techno, else the first refused object's kind: aircraft (0),
// building (1) or anything else, non-technos included (2).
#include "shared/planning.hpp"

// What kind of refused object this is.
inline int Planning_Object_Kind(ObjectClass *object)
{
    if (object != 0) {
        if (object->Kind_Of() == 2) {
            return 0;
        }
        if (object->Kind_Of() == 6) {
            return 1;
        }
    }
    return 2;
}

int Planning_Selection_Kind()
{
    int kind = -1;
    int count = unknown_objects_a40c60.Count();
    for (int i = 0; i < count; i++) {
        ObjectClass *object = unknown_objects_a40c60[i];
        bool techno;
        if (object != 0) {
            techno = object->AbstractFlags.IsTechno;
        }
        TechnoClass *candidate = (object != 0 && techno) ? (TechnoClass *)object : 0;
        if (candidate == 0 || !candidate->unknown_slot274()) {
            kind = Planning_Object_Kind(candidate);
            break;
        }
    }
    return kind;
}
