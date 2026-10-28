// HRESULT __stdcall ParticleSystemClass::Load(IStream *stream) (0x0060CD30)
// Restores the system in place, swizzles its pointers, then reads the
// particle count and pointers back into Particles.
#include "shared/particle_system.hpp"
// @ref ?Load@ObjectClass@@UAGJPAUIStream@@@Z=005d4760
// @ref ??0ObjectClass@@QAE@ABVNoInitClass@@@Z=005d2500
// @ref ??0?$VectorClass@PAVParticleClass@@@@QAE@IPBQAVParticleClass@@@Z=0060d0a0
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall ParticleSystemClass::Load(IStream *stream)
{
    HRESULT result = ObjectClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) ParticleSystemClass(NoInitClass());
    SwizzleManager.Swizzle((void **)&Class);
    SwizzleManager.Swizzle((void **)&unknown_d0);
    SwizzleManager.Swizzle((void **)&Owner);

    int count = 0;
    result = stream->Read(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    while (count--) {
        ParticleClass *particle = 0;
        unsigned long read;
        result = stream->Read(&particle, sizeof(particle), &read);
        if (FAILED(result)) {
            return result;
        }
        Particles.Add(particle);
    }
    for (int index = 0; index < Particles.Count(); index++) {
        SwizzleManager.Swizzle((void **)&Particles[index]);
    }
    return S_OK;
}
