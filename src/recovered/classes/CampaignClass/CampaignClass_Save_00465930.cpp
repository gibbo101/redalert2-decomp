// ?Save@CampaignClass@@UAGJPAUIStream@@H@Z (0x00465930)
// Only the AbstractClass part.
#include "shared/campaign.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall CampaignClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
