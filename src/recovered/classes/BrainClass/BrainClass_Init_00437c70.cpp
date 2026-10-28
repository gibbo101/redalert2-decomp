// void BrainClass::Init(int value, int max_neurons) (0x00437C70)
#include "shared/neuron.hpp"

void BrainClass::Init(int value, int max_neurons)
{
    Clear();
    unknown_1c = value;
    MaxNeurons = max_neurons;
}
