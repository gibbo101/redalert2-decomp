// HRESULT __stdcall ParticleSystemTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x00620D90, slot 6)
// The object type's save; always S_OK.
#include "shared/particle_system.hpp"
// @ref ?Save@ObjectTypeClass@@UAGJPAUIStream@@H@Z=005d7e60

HRESULT __stdcall ParticleSystemTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    ObjectTypeClass::Save(stream, clear_dirty);
    return S_OK;
}
