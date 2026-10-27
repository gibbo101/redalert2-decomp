// HRESULT __stdcall ParticleSystemClass::Save(IStream *stream, BOOL clear_dirty) (0x0060CEA0)
// AbstractClass::Save, then the particle count and the particle pointers.
#include "shared/particle_system.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall ParticleSystemClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        int count = Particles.Count();
        result = stream->Write(&count, sizeof(count), 0);
        if (SUCCEEDED(result)) {
            for (int index = 0; index < count; index++) {
                result = stream->Write(&Particles[index], sizeof(ParticleClass *), 0);
                if (FAILED(result)) {
                    break;
                }
            }
        }
    }
    return result;
}
