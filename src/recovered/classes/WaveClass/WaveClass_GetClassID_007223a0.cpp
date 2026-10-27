// HRESULT __stdcall WaveClass::GetClassID(GUID *clsid) (0x007223A0)
#include "shared/wave.hpp"
// @ref _CLSID_WaveClass=007a1c90

HRESULT __stdcall WaveClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_WaveClass;
    return S_OK;
}
