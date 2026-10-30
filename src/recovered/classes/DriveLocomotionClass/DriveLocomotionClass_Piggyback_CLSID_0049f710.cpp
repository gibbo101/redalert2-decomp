// HRESULT __stdcall DriveLocomotionClass::Piggyback_CLSID(GUID *classid) (0x0049F710, IPiggyback 6)
// The class ID of the carried locomotor, or this locomotor's own when none is
// carried; each is queried for IPersist (TibSun Drive.cpp Piggyback_CLSID).
#include "shared/drive_locomotion.hpp"
#include "shared/com_ptr.hpp"
// @ref ?Query@?$UnknownComPtr@UIPersist@@$1?unknown_uuid_IPersist_7cf208@@3UGUID@@B@@QAEJABUUnknownLocomotionPtr@@@Z=00454bf0
// @ref ?Release_Held@?$UnknownComPtr@UIPersist@@$1?unknown_uuid_IPersist_7cf208@@3UGUID@@B@@QAEXXZ=004a4d00
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref _unknown_uuid_IPersist_7cf208=007cf208

HRESULT __stdcall DriveLocomotionClass::Piggyback_CLSID(GUID *classid)
{
    if (classid == 0) {
        return E_POINTER;
    }
    if (Piggybacker) {
        UnknownComPtr<IPersist, &unknown_uuid_IPersist_7cf208> persist(Piggybacker);
        if (persist == 0) {
            return E_FAIL;
        }
        return persist->GetClassID(classid);
    }
    UnknownHeldComPtr<IPersist, &unknown_uuid_IPersist_7cf208> persist(static_cast<IPersistStream *>(this));
    if (persist == 0) {
        return E_FAIL;
    }
    return persist->GetClassID(classid);
}
