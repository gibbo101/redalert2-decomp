// TypeList<AnimTypeClass *>::TypeList, default constructor (0x00652B50; vtable 0x007A3B3C).
// Layout and behaviour: shared/type_list.hpp.
// @ref ??0?$TypeList@PAVAnimTypeClass@@@@QAE@XZ=00652b50
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVAnimTypeClass@@@@UBE_NABV0@@Z=0050b300
// @ref ??_7?$TypeList@PAVAnimTypeClass@@@@6B@=007a3b3c
// @ref ??_7?$VectorClass@PAVAnimTypeClass@@@@6B@=007a3b5c
// @ref ??_E?$TypeList@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b200
// @ref ??_E?$VectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b2b0
// @ref ??_G?$TypeList@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b200
// @ref ??_G?$VectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b2b0
// @ref ?Clear@?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEXXZ=0050b110
// @ref ?Clear@?$VectorClass@PAVAnimTypeClass@@@@UAEXXZ=0050b3f0
// @ref ?Fetch@?$VectorClass@PAVAnimTypeClass@@@@UBEPAVAnimTypeClass@@H@Z=0050b1f0
// @ref ?ID@?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEHABQAVAnimTypeClass@@@Z=0050b5e0
// @ref ?ID@?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEHPBQAVAnimTypeClass@@@Z=0050b140
// @ref ?ID@?$VectorClass@PAVAnimTypeClass@@@@UAEHABQAVAnimTypeClass@@@Z=0050b420
// @ref ?ID@?$VectorClass@PAVAnimTypeClass@@@@UAEHPBQAVAnimTypeClass@@@Z=0050b460
// @ref ?Resize@?$DynamicVectorClass@PAVAnimTypeClass@@@@UAE_NHPBQAVAnimTypeClass@@@Z=0050b4e0
// @ref ?Resize@?$VectorClass@PAVAnimTypeClass@@@@UAE_NHPBQAVAnimTypeClass@@@Z=0050b340
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#include "shared/type_list.hpp"

class AnimTypeClass;

// An empty list growing by 10.
template <>
TypeList<AnimTypeClass *>::TypeList()
{
}
