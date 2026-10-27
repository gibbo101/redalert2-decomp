// void FootClass::unknown_4c8bb0(AbstractClass *target) (0x004C8BB0)
// Queues a destination at +0x49C; queueing the unit itself while the queue
// is not empty turns on looping (+0x59B), which an empty queue resets. In
// mission 5 with nothing at +0x494, slot 261 follows unless the radio
// contact is a building whose type sets +0x1357.
#include "shared/foot.hpp"
#include "shared/building_type.hpp"
#include "shared/building_type.hpp"
#include "shared/aircraft.hpp"
// @ref ?Contact@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e10

void FootClass::unknown_4c8bb0(AbstractClass *target)
{
    if (target != 0) {
        if (target == this && unknown_49c.Count() > 0) {
            unknown_59b = true;
        } else {
            if (unknown_49c.Count() == 0) {
                unknown_59b = false;
            }
            unknown_49c.Add(target);
        }
        if (unknown_494 == 0 && unknown_slot91() == 5) {
            TechnoClass *contact = Contact(0);
            if (contact == 0 || contact->Kind_Of() != 6 || !((BuildingClass *)contact)->Type->WeaponsFactory) {
                unknown_slot261(0, true);
            }
        }
    }
}
