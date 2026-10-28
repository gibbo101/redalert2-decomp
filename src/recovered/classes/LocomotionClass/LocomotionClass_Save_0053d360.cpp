// HRESULT __stdcall LocomotionClass::Save(IStream *stream, BOOL clear_dirty) (0x0053D360, IPersistStream)
// Writes the object's own address (the swizzle key Load registers), then
// the whole object (Size() bytes).
#include "shared/locomotion.hpp"

HRESULT __stdcall LocomotionClass::Save(IStream *stream, BOOL clear_dirty)
{
    if (!stream) {
        return E_POINTER;
    }
    LocomotionClass *self = this;
    HRESULT result = stream->Write(&self, sizeof(self), 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Write(this, Size(), 0);
    if (FAILED(result)) {
        return result;
    }
    if (clear_dirty) {
        Dirty = false;
    }
    return result;
}
