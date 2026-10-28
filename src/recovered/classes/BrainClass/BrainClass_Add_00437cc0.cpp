// bool BrainClass::Add(NeuronClass *neuron) (0x00437CC0)
// Adds the neuron while the brain is below its cap.
#include "shared/neuron.hpp"

bool BrainClass::Add(NeuronClass *neuron)
{
    if (Neurons.Count() < MaxNeurons) {
        Neurons.Add(neuron);
        neuron->Brain = this;
        return true;
    }
    return false;
}
