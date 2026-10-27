// HRESULT __stdcall TagClass::Save(IStream *stream, BOOL clear_dirty) (0x006B41D0)
#include "shared/object.hpp"

HRESULT __stdcall TagClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
