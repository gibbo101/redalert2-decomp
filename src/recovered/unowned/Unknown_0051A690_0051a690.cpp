// ObjectClass *__fastcall Unknown_0051A690(Cell const *cell, ObjectClass *object) -- 0x0051A690
// Body 0x0051A690-0x0051A864 (469 bytes, nop padding to 0x0051A870). Called from 0x00630049/0x00630063
// and 0x00669984/0x006699A5.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/house.hpp"
#include "shared/techno.hpp"
#include "shared/object.hpp"
#include "shared/coord.hpp"
#include "shared/coord_distance.hpp"

// The selected object that best answers an order at the cell (or, without one, at the object): the
// highest priority wins, ties go to the nearest. Priority: 0 an object without unknown_14_bit0, 1 a
// techno with unknown_slot201, 2 the other flagged technos, 3 with unknown_slot163, 4 that and not a
// building (Kind_Of 6), 5 that and unknown_6c16f0(-1) > 0. The separate Count() > 0 guard is the
// original's (the count is tested twice before the loop).
ObjectClass *__fastcall Unknown_0051A690(Cell const *cell, ObjectClass *object)
{
    ObjectClass *best = 0;
    int best_priority = -1;
    int best_distance = 0x7FFFFFFF;
    if (unknown_objects_a40c60.Count() > 0) {
        for (int index = 0; index < unknown_objects_a40c60.Count(); index++) {
            ObjectClass *candidate = unknown_objects_a40c60[index];
            int priority = 0;
            bool flagged = false;
            if (candidate != 0) {
                flagged = candidate->unknown_14_bit0;
            }
            if (flagged) {
                TechnoClass *techno = (TechnoClass *)candidate;
                priority = 2;
                if (techno->unknown_slot201()) {
                    priority = 1;
                } else if (techno->unknown_slot163()) {
                    priority = 3;
                    if (techno->Kind_Of() != 6) {
                        priority = 4;
                        if (techno->unknown_6c16f0(-1) > 0) {
                            priority = 5;
                        }
                    }
                }
            }
            if (priority >= best_priority) {
                int distance = 0x7FFFFFFF;
                bool at_cell = cell != 0;
                if (at_cell || object != 0) {
                    CoordStruct coord = candidate->Center_Coord();
                    CoordStruct target;
                    if (at_cell) {
                        target = Cell_Coord(*cell);
                    } else {
                        target = object->Center_Coord();
                    }
                    distance = Coord_Distance(coord, target);
                }
                if (priority > best_priority) {
                    best_priority = priority;
                    best = candidate;
                    best_distance = distance;
                } else if (distance < best_distance) {
                    best = candidate;
                    best_distance = distance;
                }
            }
        }
    }
    return best;
}
