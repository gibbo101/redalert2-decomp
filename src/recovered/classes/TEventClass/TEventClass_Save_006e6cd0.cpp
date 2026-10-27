// HRESULT __stdcall TEventClass::Save(IStream *stream, BOOL clear_dirty) (0x006E6CD0)
#include "shared/object.hpp"

HRESULT __stdcall TEventClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
