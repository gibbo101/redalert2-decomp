// HRESULT BrainClass::Save(IStream *stream, BOOL clear_dirty) (0x00437D30)
// The neuron count, then each neuron.
#include "shared/neuron.hpp"

HRESULT BrainClass::Save(IStream *stream, BOOL clear_dirty)
{
    if (!stream) {
        return E_POINTER;
    }
    int count = Neurons.Count();
    HRESULT result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int i = 0; i < count; i++) {
        result = Neurons[i]->Save(stream, clear_dirty);
        if (FAILED(result)) {
            return result;
        }
    }
    return S_OK;
}
