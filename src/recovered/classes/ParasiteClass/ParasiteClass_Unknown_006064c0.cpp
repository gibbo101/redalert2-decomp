// void ParasiteClass::Unknown_006064C0() (0x006064C0)
// Clears the counters, releases the victim and leaves the update list.
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/parasite.hpp"

void ParasiteClass::Unknown_006064C0()
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
}
