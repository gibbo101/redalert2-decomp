// ?GetClassID@CampaignClass@@UAGJPAUGUID@@@Z (0x00465860)
// The class identifier.
#include "shared/campaign.hpp"
// @ref _CLSID_CampaignClass=007a1e40

HRESULT __stdcall CampaignClass::GetClassID(GUID *classid)
{
    if (classid == 0) {
        return E_POINTER;
    }
    *classid = CLSID_CampaignClass;
    return S_OK;
}
