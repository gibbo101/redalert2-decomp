// HRESULT __stdcall ObjectTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x005D7E60)
#include "shared/object_type.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall ObjectTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
