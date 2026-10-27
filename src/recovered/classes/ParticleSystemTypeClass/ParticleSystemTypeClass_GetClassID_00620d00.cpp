// HRESULT __stdcall ParticleSystemTypeClass::GetClassID(GUID *clsid) (0x00620D00, slot 3)
#include "shared/particle_system.hpp"
// @ref _CLSID_ParticleSystemTypeClass=007a1c40

extern "C" GUID const CLSID_ParticleSystemTypeClass;

HRESULT __stdcall ParticleSystemTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_ParticleSystemTypeClass;
    return S_OK;
}
