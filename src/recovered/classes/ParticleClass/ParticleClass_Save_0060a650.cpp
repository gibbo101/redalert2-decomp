// HRESULT __stdcall ParticleClass::Save(IStream *stream, BOOL clear_dirty) (0x0060A650)
// Saves through AbstractClass::Save and marks the particle saved (+0x120).
#include "shared/particle.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall ParticleClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    unknown_120 = true;
    return result;
}
