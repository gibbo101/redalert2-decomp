// HRESULT NeuronClass::Save(IStream *stream, BOOL clear_dirty) (0x00437B70, slot 6)
#include "shared/neuron.hpp"
// @ref ??_7NeuronClass@@6BIPersistStream@@@=0079caf0
// @ref ??_7NeuronClass@@6BIRTTITypeInfo@@@=0079cad4
// @ref ??_7NeuronClass@@6BINoticeSink@@@=0079cacc
// @ref ??_7NeuronClass@@6BINoticeSource@@@=0079cac4
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall NeuronClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
