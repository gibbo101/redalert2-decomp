// BlowfishEngine::BlowfishEngine() (0x00435580)
// Starts the Blowfish COM server and obtains its interface; failures other
// than a missing interface are raised as COM errors.
// @ref _CLSID_Blowfish=007a1a70
// @ref _IID_IUnknown=007ce610
// @ref _IID_IBlowfish=007cf5b0
// @ref __imp__CoCreateInstance@20=0079a5f0
// @ref __imp__OleRun@4=0079a5f4
// @ref ?_com_issue_error@@YGXJ@Z=00795940
#include "shared/blowfish_engine.hpp"

BlowfishEngine::BlowfishEngine() :
    Interface(0)
{
    IUnknown *unknown;
    HRESULT result = CoCreateInstance(CLSID_Blowfish, 0, CLSCTX_ALL, IID_IUnknown, (void **)&unknown);
    if (SUCCEEDED(result)) {
        result = OleRun(unknown);
        if (SUCCEEDED(result)) {
            result = unknown->QueryInterface(IID_IBlowfish, (void **)&Interface);
        }
        unknown->Release();
    }
    if (FAILED(result) && result != E_NOINTERFACE) {
        _com_issue_error(result);
    }
}
