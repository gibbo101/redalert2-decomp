// void BrainClass::Clear() (0x00437C30)
// Deletes the neurons and empties the list.
#include "shared/neuron.hpp"

void BrainClass::Clear()
{
    int count = Neurons.Count();
    for (int i = 0; i < count; i++) {
        delete Neurons[i];
        Neurons[i] = 0;
    }
    Neurons.Clear();
}
