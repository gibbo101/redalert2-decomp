// HRESULT __stdcall WeaponTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x00733DF0)
// The base object, then the two lists as counts and elements.
#include "shared/weapon_type.hpp"

HRESULT __stdcall WeaponTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractTypeClass::Save(stream, clear_dirty);
    if (FAILED(result)) {
        return result;
    }
    int count = Anim.Count();
    stream->Write(&count, sizeof(count), 0);
    for (int i = 0; i < count; i++) {
        stream->Write(&Anim[i], sizeof(AnimTypeClass *), 0);
    }
    count = unknown_bc.Count();
    stream->Write(&count, sizeof(count), 0);
    for (i = 0; i < count; i++) {
        stream->Write(&unknown_bc[i], sizeof(int), 0);
    }
    return S_OK;
}
