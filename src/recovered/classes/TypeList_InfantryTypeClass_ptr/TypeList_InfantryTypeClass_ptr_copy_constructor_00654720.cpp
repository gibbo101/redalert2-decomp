// TypeList<InfantryTypeClass *>::TypeList, copy constructor (0x00654720; vtable 0x007A30F8).
// Layout and behaviour: shared/type_list.hpp.
// @ref ??0?$TypeList@PAVInfantryTypeClass@@@@QAE@ABV0@@Z=00654720
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVInfantryTypeClass@@@@UBE_NABV0@@Z=004fa910
// @ref ??_7?$TypeList@PAVInfantryTypeClass@@@@6B@=007a30f8
// @ref ??_7?$VectorClass@PAVInfantryTypeClass@@@@6B@=007a3118
// @ref ??_E?$TypeList@PAVInfantryTypeClass@@@@UAEPAXI@Z=004fa6c0
// @ref ??_E?$VectorClass@PAVInfantryTypeClass@@@@UAEPAXI@Z=004fa7b0
// @ref ??_G?$TypeList@PAVInfantryTypeClass@@@@UAEPAXI@Z=004fa6c0
// @ref ??_G?$VectorClass@PAVInfantryTypeClass@@@@UAEPAXI@Z=004fa7b0
// @ref ?Clear@?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEXXZ=004fa570
// @ref ?Clear@?$VectorClass@PAVInfantryTypeClass@@@@UAEXXZ=004faa00
// @ref ?Fetch@?$VectorClass@PAVInfantryTypeClass@@@@UBEPAVInfantryTypeClass@@H@Z=004fa5c0
// @ref ?ID@?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEHABQAVInfantryTypeClass@@@Z=004fac40
// @ref ?ID@?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEHPBQAVInfantryTypeClass@@@Z=004fa5a0
// @ref ?ID@?$VectorClass@PAVInfantryTypeClass@@@@UAEHABQAVInfantryTypeClass@@@Z=004faa30
// @ref ?ID@?$VectorClass@PAVInfantryTypeClass@@@@UAEHPBQAVInfantryTypeClass@@@Z=004faa70
// @ref ?Resize@?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAE_NHPBQAVInfantryTypeClass@@@Z=004fab40
// @ref ?Resize@?$VectorClass@PAVInfantryTypeClass@@@@UAE_NHPBQAVInfantryTypeClass@@@Z=004fa950
#define VECTOR_IMPLEMENT_VECTOR_COPY_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/type_list.hpp"

class InfantryTypeClass;

// Deep copy of the storage and both counters.
template <>
TypeList<InfantryTypeClass *>::TypeList(TypeList<InfantryTypeClass *> const &list)
    : DynamicVectorClass<InfantryTypeClass *>(list)
{
}
