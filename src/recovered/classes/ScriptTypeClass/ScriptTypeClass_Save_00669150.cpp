// HRESULT __stdcall ScriptTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x00669150)
#include "shared/script.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall ScriptTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
