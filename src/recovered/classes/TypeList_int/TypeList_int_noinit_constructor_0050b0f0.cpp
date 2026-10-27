// TypeList<int>::TypeList, noinit constructor (0x0050B0F0; vtable 0x0079D9F4).
// Layout and behaviour: shared/type_list.hpp.
// @ref ??0?$TypeList@H@@QAE@ABVNoInitClass@@@Z=0050b0f0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@H@@UBE_NABV0@@Z=0046d070
// @ref ??_7?$TypeList@H@@6B@=0079d9f4
// @ref ??_7?$VectorClass@H@@6B@=0079d9d4
// @ref ??_E?$TypeList@H@@UAEPAXI@Z=0046cdd0
// @ref ??_E?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ??_G?$TypeList@H@@UAEPAXI@Z=0046cdd0
// @ref ??_G?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ?Clear@?$DynamicVectorClass@H@@UAEXXZ=0046cc80
// @ref ?Clear@?$VectorClass@H@@UAEXXZ=0046d160
// @ref ?Fetch@?$VectorClass@H@@UBEHH@Z=0046ccd0
// @ref ?ID@?$DynamicVectorClass@H@@UAEHABH@Z=0046d350
// @ref ?ID@?$DynamicVectorClass@H@@UAEHPBH@Z=0046ccb0
// @ref ?ID@?$VectorClass@H@@UAEHABH@Z=0046d190
// @ref ?ID@?$VectorClass@H@@UAEHPBH@Z=0046d1d0
// @ref ?Resize@?$DynamicVectorClass@H@@UAE_NHPBH@Z=0046d250
// @ref ?Resize@?$VectorClass@H@@UAE_NHPBH@Z=0046d0b0
#define VECTOR_IMPLEMENT_DYNAMIC_NOINIT_CONSTRUCTOR
#include "shared/type_list.hpp"

// Installs the vtable only.
template <>
TypeList<int>::TypeList(NoInitClass const &noinit)
    : DynamicVectorClass<int>(noinit)
{
}
