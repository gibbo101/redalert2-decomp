// void AnimTypeClass::unknown_slot24(int theater) (0x004253C0)
// Reloads this type's theater-specific image when the theater changes.
#include "shared/anim_type.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"

void AnimTypeClass::unknown_slot24(int theater)
{
    if (!unknown_a40d13 && theater == unknown_loaded_theater_7d88dc) {
        return;
    }
    if (unknown_1fc && !DemandLoad) {
        if (unknown_a4 != 0 && unknown_a8) {
            operator delete(unknown_a4);
            unknown_a8 = false;
        }
        unknown_a4 = 0;
        char fullname[512];
        _makepath(fullname, 0, 0, ID, Theaters[theater].Suffix);
        unknown_a4 = (void *)MixFileClass<CCFileClass>::Retrieve(fullname);
        return;
    }
    if (unknown_207) {
        unknown_slot40(theater);
    }
}
