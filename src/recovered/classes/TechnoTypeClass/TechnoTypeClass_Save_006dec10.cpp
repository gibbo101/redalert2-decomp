// HRESULT __stdcall TechnoTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x006DEC10)
// The base, then every list (count and elements).
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?Save@ObjectTypeClass@@UAGJPAUIStream@@H@Z=005d7e60
// @ref ?Save@?$TypeList@H@@QAEXPAUIStream@@@Z=00652c00
// @ref ?Save@?$TypeList@PAVAnimTypeClass@@@@QAEXPAUIStream@@@Z=00652b80
// @ref ?Save@?$TypeList@PAVParticleSystemTypeClass@@@@QAEXPAUIStream@@@Z=006df7f0

HRESULT __stdcall TechnoTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = ObjectTypeClass::Save(stream, clear_dirty);
    if (FAILED(result)) {
        return result;
    }
    Dock.Save(stream);
    DebrisTypes.Save(stream);
    DebrisAnims.Save(stream);
    VoiceSelect.Save(stream);
    VoiceMove.Save(stream);
    VoiceAttack.Save(stream);
    VoiceSpecialAttack.Save(stream);
    VoiceDie.Save(stream);
    VoiceFeedback.Save(stream);
    MoveSound.Save(stream);
    DieSound.Save(stream);
    Explosion.Save(stream);
    DestroyAnim.Save(stream);
    DebrisMaximums.Save(stream);
    Prerequisite.Save(stream);
    PrerequisiteOverride.Save(stream);
    DamageParticleSystems.Save(stream);
    DestroyParticleSystems.Save(stream);
    return S_OK;
}
