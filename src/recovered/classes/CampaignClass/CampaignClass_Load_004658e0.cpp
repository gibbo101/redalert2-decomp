// ?Load@CampaignClass@@UAGJPAUIStream@@@Z (0x004658E0)
// AbstractClass load, then the vtables.
#include "shared/campaign.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0AbstractTypeClass@@QAE@ABVNoInitClass@@@Z=004106e0

HRESULT __stdcall CampaignClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) CampaignClass(NoInitClass());
    return S_OK;
}
