// TypeList<SmudgeTypeClass *>::TypeList, copy constructor (0x00654600; vtable 0x007A90D8).
// Layout and behaviour: shared/type_list.hpp.
// @ref ??0?$TypeList@PAVSmudgeTypeClass@@@@QAE@ABV0@@Z=00654600
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVSmudgeTypeClass@@@@UBE_NABV0@@Z=006535b0
// @ref ??_7?$TypeList@PAVSmudgeTypeClass@@@@6B@=007a90d8
// @ref ??_7?$VectorClass@PAVSmudgeTypeClass@@@@6B@=007a9138
// @ref ??_E?$TypeList@PAVSmudgeTypeClass@@@@UAEPAXI@Z=00653040
// @ref ??_E?$VectorClass@PAVSmudgeTypeClass@@@@UAEPAXI@Z=00654430
// @ref ??_G?$TypeList@PAVSmudgeTypeClass@@@@UAEPAXI@Z=00653040
// @ref ??_G?$VectorClass@PAVSmudgeTypeClass@@@@UAEPAXI@Z=00654430
// @ref ?Clear@?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAEXXZ=00652cd0
// @ref ?Clear@?$VectorClass@PAVSmudgeTypeClass@@@@UAEXXZ=006536a0
// @ref ?Fetch@?$VectorClass@PAVSmudgeTypeClass@@@@UBEPAVSmudgeTypeClass@@H@Z=00652db0
// @ref ?ID@?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAEHABQAVSmudgeTypeClass@@@Z=00653890
// @ref ?ID@?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAEHPBQAVSmudgeTypeClass@@@Z=00652d00
// @ref ?ID@?$VectorClass@PAVSmudgeTypeClass@@@@UAEHABQAVSmudgeTypeClass@@@Z=006536d0
// @ref ?ID@?$VectorClass@PAVSmudgeTypeClass@@@@UAEHPBQAVSmudgeTypeClass@@@Z=00653710
// @ref ?Resize@?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAE_NHPBQAVSmudgeTypeClass@@@Z=00653790
// @ref ?Resize@?$VectorClass@PAVSmudgeTypeClass@@@@UAE_NHPBQAVSmudgeTypeClass@@@Z=006535f0
#define VECTOR_IMPLEMENT_VECTOR_COPY_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/type_list.hpp"

class SmudgeTypeClass;

// Deep copy of the storage and both counters.
template <>
TypeList<SmudgeTypeClass *>::TypeList(TypeList<SmudgeTypeClass *> const &list)
    : DynamicVectorClass<SmudgeTypeClass *>(list)
{
}
