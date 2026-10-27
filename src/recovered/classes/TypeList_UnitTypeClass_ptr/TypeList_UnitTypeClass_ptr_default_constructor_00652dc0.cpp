// TypeList<UnitTypeClass *>::TypeList, default constructor (0x00652DC0; vtable 0x007A30D8).
// Layout and behaviour: shared/type_list.hpp.
// @ref ??0?$TypeList@PAVUnitTypeClass@@@@QAE@XZ=00652dc0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVUnitTypeClass@@@@UBE_NABV0@@Z=004face0
// @ref ??_7?$TypeList@PAVUnitTypeClass@@@@6B@=007a30d8
// @ref ??_7?$VectorClass@PAVUnitTypeClass@@@@6B@=007a3138
// @ref ??_E?$TypeList@PAVUnitTypeClass@@@@UAEPAXI@Z=004fa710
// @ref ??_E?$VectorClass@PAVUnitTypeClass@@@@UAEPAXI@Z=004fa800
// @ref ??_G?$TypeList@PAVUnitTypeClass@@@@UAEPAXI@Z=004fa710
// @ref ??_G?$VectorClass@PAVUnitTypeClass@@@@UAEPAXI@Z=004fa800
// @ref ?Clear@?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEXXZ=004fa5d0
// @ref ?Clear@?$VectorClass@PAVUnitTypeClass@@@@UAEXXZ=004fadd0
// @ref ?Fetch@?$VectorClass@PAVUnitTypeClass@@@@UBEPAVUnitTypeClass@@H@Z=004fa620
// @ref ?ID@?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEHABQAVUnitTypeClass@@@Z=004fb010
// @ref ?ID@?$DynamicVectorClass@PAVUnitTypeClass@@@@UAEHPBQAVUnitTypeClass@@@Z=004fa600
// @ref ?ID@?$VectorClass@PAVUnitTypeClass@@@@UAEHABQAVUnitTypeClass@@@Z=004fae00
// @ref ?ID@?$VectorClass@PAVUnitTypeClass@@@@UAEHPBQAVUnitTypeClass@@@Z=004fae40
// @ref ?Resize@?$DynamicVectorClass@PAVUnitTypeClass@@@@UAE_NHPBQAVUnitTypeClass@@@Z=004faf10
// @ref ?Resize@?$VectorClass@PAVUnitTypeClass@@@@UAE_NHPBQAVUnitTypeClass@@@Z=004fad20
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#include "shared/type_list.hpp"

class UnitTypeClass;

// An empty list growing by 10.
template <>
TypeList<UnitTypeClass *>::TypeList()
{
}
