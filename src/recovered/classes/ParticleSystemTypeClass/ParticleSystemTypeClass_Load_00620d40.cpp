// HRESULT __stdcall ParticleSystemTypeClass::Load(IStream *stream) (0x00620D40)
// Loads the object type and restores the type in place; always reports
// success.
#include "shared/particle_system.hpp"
// @ref ??_GParticleSystemTypeClass@@UAEPAXI@Z=00620ec0
// @ref ?Load@ObjectTypeClass@@UAGJPAUIStream@@@Z=005d7c30
// @ref ??0ObjectTypeClass@@QAE@ABVNoInitClass@@@Z=005d5a80
// @ref ??_7ParticleSystemTypeClass@@6BIPersistStream@@@=007a8480
// @ref ??_7ParticleSystemTypeClass@@6BIRTTITypeInfo@@@=007a8464
// @ref ??_7ParticleSystemTypeClass@@6BINoticeSink@@@=007a845c
// @ref ??_7ParticleSystemTypeClass@@6BINoticeSource@@@=007a8454

HRESULT __stdcall ParticleSystemTypeClass::Load(IStream *stream)
{
    if (SUCCEEDED(ObjectTypeClass::Load(stream))) {
        new (this) ParticleSystemTypeClass(NoInitClass());
    }
    return S_OK;
}
