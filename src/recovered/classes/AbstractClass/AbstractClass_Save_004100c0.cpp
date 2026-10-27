// HRESULT __stdcall AbstractClass::Save(IStream *stream, BOOL clear_dirty) (0x004100C0)
// IPersistStream: writes the object pointer (for swizzling), then Size_Of() bytes of the object.
#include "shared/abstract.hpp"

HRESULT __stdcall AbstractClass::Save(IStream *stream, BOOL clear_dirty)
{
    if (stream == 0) {
        return E_POINTER;
    }
    AbstractClass *self = this;
    HRESULT result = stream->Write(&self, sizeof(self), 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Write(this, Size_Of(), 0);
    if (SUCCEEDED(result) && clear_dirty) {
        Dirty = false;
    }
    return result;
}
