// HRESULT __stdcall OverlayTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x005DCF10)
#include "shared/overlay_type.hpp"
// @ref ?Save@ObjectTypeClass@@UAGJPAUIStream@@H@Z=005d7e60

HRESULT __stdcall OverlayTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = ObjectTypeClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
