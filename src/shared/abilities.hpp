// AbilitiesStruct: the eighteen veterancy abilities (VeteranAbilities=,
// EliteAbilities=; names FASTER .. CRUSHER, table 0x007F9978).
#ifndef RA2_SHARED_ABILITIES_HPP
#define RA2_SHARED_ABILITIES_HPP

#include "shared/crt_memory.hpp"

class NoInitClass;

// The default constructor clears the flags one by one (TechnoTypeClass's
// constructor 0x006D9B40 shows the unrolled stores); assignment copies the
// block unless it is the same object (Read_INI 0x006DD66E).
struct AbilitiesStruct {
    AbilitiesStruct()
    {
        for (int index = 0; index < 18; index++) {
            Ability[index] = false;
        }
    }
    AbilitiesStruct(NoInitClass const &noinit) {}
    AbilitiesStruct &operator=(AbilitiesStruct const &abilities)
    {
        if (this != &abilities) {
            memcpy(this, &abilities, sizeof(*this));
        }
        return *this;
    }
    bool Ability[18];
};

#endif
