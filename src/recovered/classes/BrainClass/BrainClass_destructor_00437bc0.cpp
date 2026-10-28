// BrainClass::~BrainClass() (0x00437BC0)
// Deletes its neurons.
#include "shared/neuron.hpp"
// @ref ??_7BrainClass@@6B@=0079cb74
// @ref ??_7?$VectorClass@PAVNeuronClass@@@@6B@=0079cb54
// @ref ??3@YAXPAX@Z=00781d3b

BrainClass::~BrainClass()
{
    Clear();
}
