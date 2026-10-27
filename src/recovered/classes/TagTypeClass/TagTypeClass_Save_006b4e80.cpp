// HRESULT __stdcall TagTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x006B4E80)
#include "shared/object.hpp"

HRESULT __stdcall TagTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
