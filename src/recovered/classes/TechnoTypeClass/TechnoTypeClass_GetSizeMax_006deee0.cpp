// HRESULT __stdcall TechnoTypeClass::GetSizeMax(ULARGE_INTEGER *size) (0x006DEEE0)
// The base size plus a count and the elements of sixteen lists.
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?GetSizeMax@ObjectTypeClass@@UAGJPATULARGE_INTEGER@@@Z=005d7e80

HRESULT __stdcall TechnoTypeClass::GetSizeMax(ULARGE_INTEGER *size)
{
    HRESULT result = ObjectTypeClass::GetSizeMax(size);
    if (FAILED(result)) {
        return result;
    }
    size->LowPart += VoiceSelect.Count() * sizeof(int) + sizeof(int);
    size->LowPart += VoiceMove.Count() * sizeof(int) + sizeof(int);
    size->LowPart += VoiceAttack.Count() * sizeof(int) + sizeof(int);
    size->LowPart += VoiceSpecialAttack.Count() * sizeof(int) + sizeof(int);
    size->LowPart += VoiceDie.Count() * sizeof(int) + sizeof(int);
    size->LowPart += VoiceFeedback.Count() * sizeof(int) + sizeof(int);
    size->LowPart += MoveSound.Count() * sizeof(int) + sizeof(int);
    size->LowPart += DieSound.Count() * sizeof(int) + sizeof(int);
    size->LowPart += Explosion.Count() * sizeof(AnimTypeClass *) + sizeof(int);
    size->LowPart += DestroyAnim.Count() * sizeof(AnimTypeClass *) + sizeof(int);
    size->LowPart += DebrisTypes.Count() * sizeof(VoxelAnimTypeClass *) + sizeof(int);
    size->LowPart += DebrisAnims.Count() * sizeof(AnimTypeClass *) + sizeof(int);
    size->LowPart += Dock.Count() * sizeof(BuildingTypeClass *) + sizeof(int);
    size->LowPart += DebrisMaximums.Count() * sizeof(int) + sizeof(int);
    size->LowPart += DamageParticleSystems.Count() * sizeof(ParticleSystemTypeClass *) + sizeof(int);
    size->LowPart += DestroyParticleSystems.Count() * sizeof(ParticleSystemTypeClass *) + sizeof(int);
    return S_OK;
}
