// void NeuronClass::Compute_CRC(WWCRCEngine &crc) const (0x00437B90, slot 13)
// Adds the neuron's age in frames.
#include "shared/neuron.hpp"
#include "shared/cd_timer.hpp"
// @ref ??_7NeuronClass@@6BIPersistStream@@@=0079caf0
// @ref ??_7NeuronClass@@6BIRTTITypeInfo@@@=0079cad4
// @ref ??_7NeuronClass@@6BINoticeSink@@@=0079cacc
// @ref ??_7NeuronClass@@6BINoticeSource@@@=0079cac4
// @ref ?Compute_CRC@AbstractClass@@UBEXAAVWWCRCEngine@@@Z=004101b0
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ?Frame@@3HA=00a40d2c

void NeuronClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    crc((long)(Frame - CreationFrame));
}
