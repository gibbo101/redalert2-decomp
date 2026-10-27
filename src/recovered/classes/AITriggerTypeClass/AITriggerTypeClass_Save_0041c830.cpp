// ?Save@AITriggerTypeClass@@UAGJPAUIStream@@H@Z (0x0041C830)
// Only the AbstractClass part.
#include "shared/ai_trigger_type.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall AITriggerTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
