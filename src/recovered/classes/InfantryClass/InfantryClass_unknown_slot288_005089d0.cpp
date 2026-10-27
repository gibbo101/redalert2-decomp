// Foot update plus a nearby jumpjet locomotor's IPersist class-ID query (0x005089D0).
#include "shared/infantry.hpp"
// @ref ?unknown_slot288@FootClass@@UAEXXZ=004ca880
// @ref ?unknown_5d4c00@ObjectClass@@QAEHPAVAbstractClass@@@Z=005d4c00
// @ref _unknown_uuid_IPersist_7cf208=007cf208
// @ref ?Release_Held@UnknownPersistPtr@@QAEXXZ=004a4d00
// @ref ?_com_issue_error@@YGXJ@Z=00795940
void InfantryClass::unknown_slot288()
{
    FootClass::unknown_slot288();
    if (unknown_494 != 0 && unknown_5d4c00(unknown_494) < 1024 && Type->JumpJet) {
        UnknownPersistPtr persist(Locomotor.Pointer);
        GUID clsid;
        persist->GetClassID(&clsid);
    }
}
