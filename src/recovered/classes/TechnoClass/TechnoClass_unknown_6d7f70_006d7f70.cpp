// bool TechnoClass::unknown_6d7f70() (0x006D7F70)
// Follows up the contact at +0x3F8 (hypothesis: a dock or repair partner):
// dropped once it is inactive; when it answers message 2, message 15 decides
// between mission 7 toward it and no mission with message 3, both dropping
// it; an aircraft at a building whose type has UnitReload but not
// UnitRepair sends message 14 instead (FootClass 0x004C984C).
#include "shared/techno.hpp"
#include "shared/aircraft.hpp"

bool TechnoClass::unknown_6d7f70()
{
    if (unknown_3f8 == 0) {
        return false;
    }
    if (((ObjectClass *)unknown_3f8)->unknown_7d) {
        AbstractClass *contact = unknown_3f8;
        if (contact != 0 && contact->unknown_14_bit0) {
            TechnoClass *techno = (TechnoClass *)contact;
            if (unknown_slot150(2, techno) == 1) {
                if (unknown_slot150(15, techno) == 1) {
                    unknown_slot116(7, false);
                    unknown_slot260(techno, 1);
                    unknown_3f8 = 0;
                    return true;
                }
                unknown_slot116(-1, false);
                unknown_slot260(0, 1);
                unknown_3f8 = 0;
                unknown_slot150(3, techno);
                return true;
            }
            if (techno->Kind_Of() == 6 && Kind_Of() == 2) {
                BuildingTypeClass *type = ((BuildingClass *)techno)->Type;
                if (type->unknown_134a && !type->unknown_1349) {
                    unknown_slot150(14, techno);
                }
            }
        }
    } else {
        unknown_3f8 = 0;
    }
    return false;
}
