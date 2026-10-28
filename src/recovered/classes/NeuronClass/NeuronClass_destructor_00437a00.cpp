// NeuronClass::~NeuronClass() (0x00437A00)
// Leaves both lists.
#include "shared/neuron.hpp"
#include "shared/object_lists.hpp"
// @ref ??_7NeuronClass@@6BIPersistStream@@@=0079caf0
// @ref ??_7NeuronClass@@6BIRTTITypeInfo@@@=0079cad4
// @ref ??_7NeuronClass@@6BINoticeSink@@@=0079cacc
// @ref ??_7NeuronClass@@6BINoticeSource@@@=0079cac4
// @ref ??1AbstractClass@@UAE@XZ=0040ff90

NeuronClass::~NeuronClass()
{
    unknown_objects_ac0cb0.Delete(this);
    unknown_list_ac0c18.Delete(this);
}
