// HRESULT __stdcall AnimTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x004262A0)
#include "shared/anim_type.hpp"

HRESULT __stdcall AnimTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = ObjectTypeClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
