// HRESULT BrainClass::Load(IStream *stream) (0x00437DA0)
#include "shared/neuron.hpp"
#include "shared/class_factory.hpp"
// @ref ??2@YAPAXI@Z=00782017

HRESULT BrainClass::Load(IStream *stream)
{
    if (!stream) {
        return E_POINTER;
    }
    int count = 0;
    HRESULT result = stream->Read(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int i = 0; i < count; i++) {
        NeuronClass *neuron = new NeuronClass;
        if (!neuron) {
            return E_OUTOFMEMORY;
        }
        result = neuron->Load(stream);
        if (FAILED(result)) {
            return result;
        }
        Add(neuron);
    }
    return S_OK;
}
