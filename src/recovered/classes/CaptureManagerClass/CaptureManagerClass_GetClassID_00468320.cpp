// ?GetClassID@CaptureManagerClass@@UAGJPAUGUID@@@Z (0x00468320)
// The class identifier.
#include "shared/capture_manager.hpp"
// @ref _CLSID_CaptureManagerClass=007a1de0

HRESULT __stdcall CaptureManagerClass::GetClassID(GUID *classid)
{
    if (classid == 0) {
        return E_POINTER;
    }
    *classid = CLSID_CaptureManagerClass;
    return S_OK;
}
