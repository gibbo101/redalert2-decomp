// HRESULT NeuronClass::Load(IStream *stream) (0x00437B00, slot 5)
#include "shared/neuron.hpp"
// @ref ??_7NeuronClass@@6BIPersistStream@@@=0079caf0
// @ref ??_7NeuronClass@@6BIRTTITypeInfo@@@=0079cad4
// @ref ??_7NeuronClass@@6BINoticeSink@@@=0079cacc
// @ref ??_7NeuronClass@@6BINoticeSource@@@=0079cac4
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0AbstractClass@@QAE@ABVNoInitClass@@@Z=0040ff60
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall NeuronClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) NeuronClass(NoInitClass());
    Swizzle_Pointer(unknown_28);
    Swizzle_Pointer(unknown_24);
    Swizzle_Pointer(Brain);
    return S_OK;
}
