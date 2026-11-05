// bool InfantryClass::unknown_508d00() (0x00508D00)
// True for a JumpJet infantry type whose locomotor's class ID is
// JumpjetLocomotionClass (asked through IPersist::GetClassID).
#include "shared/infantry.hpp"
#include "shared/com_ptr.hpp"
// @ref _CLSID_JumpjetLocomotionClass=007a2000
// @ref _unknown_uuid_IPersist_7cf208=007cf208
// @ref ?Release_Held@UnknownPersistPtr@@QAEXXZ=004a4d00
// @ref ?_com_issue_error@@YGXJ@Z=00795940

extern "C" GUID const CLSID_JumpjetLocomotionClass;    // 0x007A2000

// An IPersist pointer queried from the locomotor (the compiler's
// _com_ptr_t<IPersist> as comip.h expands it: Attach(NULL) on failure,
// Attach(pointer) on success, the release out of line, 0x004A4D00).


bool InfantryClass::unknown_508d00()
{
    if (!Type->JumpJet) {
        return false;
    }
    UnknownPersistPtr persist(Locomotor);
    GUID clsid;
    persist->GetClassID(&clsid);
    return clsid == CLSID_JumpjetLocomotionClass;
}
