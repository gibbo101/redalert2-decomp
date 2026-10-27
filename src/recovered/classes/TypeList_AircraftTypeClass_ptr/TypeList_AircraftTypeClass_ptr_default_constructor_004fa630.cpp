// TypeList<AircraftTypeClass *>::TypeList, default constructor (0x004FA630; vtable 0x007A30B8).
// Layout and behaviour: shared/type_list.hpp.
// @ref ??0?$TypeList@PAVAircraftTypeClass@@@@QAE@XZ=004fa630
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVAircraftTypeClass@@@@UBE_NABV0@@Z=004fb0b0
// @ref ??_7?$TypeList@PAVAircraftTypeClass@@@@6B@=007a30b8
// @ref ??_7?$VectorClass@PAVAircraftTypeClass@@@@6B@=007a3158
// @ref ??_E?$TypeList@PAVAircraftTypeClass@@@@UAEPAXI@Z=004fa760
// @ref ??_E?$VectorClass@PAVAircraftTypeClass@@@@UAEPAXI@Z=004fa850
// @ref ??_G?$TypeList@PAVAircraftTypeClass@@@@UAEPAXI@Z=004fa760
// @ref ??_G?$VectorClass@PAVAircraftTypeClass@@@@UAEPAXI@Z=004fa850
// @ref ?Clear@?$DynamicVectorClass@PAVAircraftTypeClass@@@@UAEXXZ=004fa660
// @ref ?Clear@?$VectorClass@PAVAircraftTypeClass@@@@UAEXXZ=004fb1a0
// @ref ?Fetch@?$VectorClass@PAVAircraftTypeClass@@@@UBEPAVAircraftTypeClass@@H@Z=004fa6b0
// @ref ?ID@?$DynamicVectorClass@PAVAircraftTypeClass@@@@UAEHABQAVAircraftTypeClass@@@Z=004fb3e0
// @ref ?ID@?$DynamicVectorClass@PAVAircraftTypeClass@@@@UAEHPBQAVAircraftTypeClass@@@Z=004fa690
// @ref ?ID@?$VectorClass@PAVAircraftTypeClass@@@@UAEHABQAVAircraftTypeClass@@@Z=004fb1d0
// @ref ?ID@?$VectorClass@PAVAircraftTypeClass@@@@UAEHPBQAVAircraftTypeClass@@@Z=004fb210
// @ref ?Resize@?$DynamicVectorClass@PAVAircraftTypeClass@@@@UAE_NHPBQAVAircraftTypeClass@@@Z=004fb2e0
// @ref ?Resize@?$VectorClass@PAVAircraftTypeClass@@@@UAE_NHPBQAVAircraftTypeClass@@@Z=004fb0f0
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#include "shared/type_list.hpp"

class AircraftTypeClass;

// An empty list growing by 10.
template <>
TypeList<AircraftTypeClass *>::TypeList()
{
}
