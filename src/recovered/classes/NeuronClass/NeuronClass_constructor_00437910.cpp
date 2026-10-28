// NeuronClass::NeuronClass() (0x00437910)
// Joins the list 0x00AC0C18 and the abstract list 0x00AC0CB0.
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"
#include "shared/neuron.hpp"
#include "shared/object_lists.hpp"
#include "shared/cd_timer.hpp"
// @ref ??_7NeuronClass@@6BIPersistStream@@@=0079caf0
// @ref ??_7NeuronClass@@6BIRTTITypeInfo@@@=0079cad4
// @ref ??_7NeuronClass@@6BINoticeSink@@@=0079cacc
// @ref ??_7NeuronClass@@6BINoticeSource@@@=0079cac4
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_list_ac0c18@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00ac0c18
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0

NeuronClass::NeuronClass() :
    unknown_24(0),
    unknown_28(0),
    Brain(0),
    CreationFrame(Frame)
{
    unknown_list_ac0c18.Add((TechnoClass *)this);
    unknown_objects_ac0cb0.Add(this);
}
