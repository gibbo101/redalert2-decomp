// HRESULT __stdcall ApplicationClass::unknown_slot6_scenario_name(BSTR *name) -- 0x00426DB0
// IApplication slot: the scenario name (+0x83C of the scenario at 0x00A3D290) as a new BSTR.
#include "shared/application.hpp"
// @ref __imp__SysAllocString@4=0079a360
// @ref __imp__MultiByteToWideChar@24=0079a1b8

HRESULT __stdcall ApplicationClass::unknown_slot6_scenario_name(BSTR *name)
{
    if (name == 0) {
        return E_POINTER;
    }
    wchar_t text[32];
    MultiByteToWideChar(0, 1, unknown_id_source_a3d290->FileName, -1, text, 32);
    *name = SysAllocString(text);
    return S_OK;
}
