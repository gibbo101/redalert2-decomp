// ??1ParasiteClass@@UAE@XZ (0x00606370)
// Releases the victim, leaves the update list and the unit list.


#include "shared/parasite.hpp"
// @ref ??1AbstractClass@@UAE@XZ=0040ff90
// @ref ?unknown_abstracts_ac0bf8@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0bf8

ParasiteClass::~ParasiteClass()
{
    Unknown_006064C0();
    unknown_ParasiteClass_list_00a76430.Delete(this);
}
