// ??1ParasiteClass@@UAE@XZ (0x00606370)
// Releases the victim, leaves the update list and the unit list.
#include "shared/parasite.hpp"
// @ref ??1AbstractClass@@UAE@XZ=0040ff90
// @ref ?unknown_abstracts_ac0bf8@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0bf8

ParasiteClass::~ParasiteClass()
{
    unknown_4c = 0;
    unknown_50 = 0;
    unknown_48 = 0;
    if (Victim != 0) {
        Victim->unknown_slot60();
        Victim = 0;
    }
    if (unknown_54) {
        unknown_abstracts_ac0bf8.Delete(this);
        unknown_54 = false;
    }
    unknown_ParasiteClass_list_00a76430.Delete(this);
}
