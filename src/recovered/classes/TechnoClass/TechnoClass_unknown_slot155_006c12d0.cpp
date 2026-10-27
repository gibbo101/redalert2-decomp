// bool TechnoClass::unknown_slot155() (0x006C12D0, slot 155)
// True for a current mission other than 0, 6 and 16 unless the type sets +0xAA0.
#include "shared/techno.hpp"

bool TechnoClass::unknown_slot155()
{
    if (unknown_slot91() && unknown_slot91() != 6 && unknown_slot91() != 16 && !unknown_slot32()->IsTrain) {
        return true;
    }
    return false;
}
