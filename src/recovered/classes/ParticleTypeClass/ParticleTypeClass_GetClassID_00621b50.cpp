// HRESULT __stdcall ParticleTypeClass::GetClassID(GUID *clsid) (0x00621B50, slot 3)
#include "shared/particle_system.hpp"
// @ref _CLSID_ParticleTypeClass=007a1c80

extern "C" GUID const CLSID_ParticleTypeClass;

HRESULT __stdcall ParticleTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_ParticleTypeClass;
    return S_OK;
}
