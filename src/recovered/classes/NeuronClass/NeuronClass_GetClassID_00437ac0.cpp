// HRESULT NeuronClass::GetClassID(GUID *clsid) (0x00437AC0, slot 3)
#include "shared/neuron.hpp"
// @ref ??_7NeuronClass@@6BIPersistStream@@@=0079caf0
// @ref ??_7NeuronClass@@6BIRTTITypeInfo@@@=0079cad4
// @ref ??_7NeuronClass@@6BINoticeSink@@@=0079cacc
// @ref ??_7NeuronClass@@6BINoticeSource@@@=0079cac4
// @ref _CLSID_NeuronClass=007a1ec0

HRESULT __stdcall NeuronClass::GetClassID(GUID *clsid)
{
    if (!clsid) {
        return E_POINTER;
    }
    *clsid = CLSID_NeuronClass;
    return S_OK;
}
