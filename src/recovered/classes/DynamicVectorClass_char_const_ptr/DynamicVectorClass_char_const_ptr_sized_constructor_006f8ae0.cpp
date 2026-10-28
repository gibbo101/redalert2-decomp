// DynamicVectorClass<char const *>::DynamicVectorClass(unsigned size, char const *const *array) (0x006F8AE0; vtable 0x007A65E4)
// The sized constructor kept in this unit: VectorClass storage (the array in
// place, or allocated and owned), growth step 10, no active entries.
// @ref ??0?$DynamicVectorClass@PBD@@QAE@IPBQBD@Z=006f8ae0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PBD@@UBE_NABV0@@Z=005a2020
// @ref ??_7?$DynamicVectorClass@PBD@@6B@=007a65e4
// @ref ??_7?$VectorClass@PBD@@6B@=007a6604
// @ref ??_E?$DynamicVectorClass@PBD@@UAEPAXI@Z=005a22d0
// @ref ??_G?$DynamicVectorClass@PBD@@UAEPAXI@Z=005a22d0
// @ref ??_E?$VectorClass@PBD@@UAEPAXI@Z=005a2280
// @ref ??_G?$VectorClass@PBD@@UAEPAXI@Z=005a2280
// @ref ?Clear@?$DynamicVectorClass@PBD@@UAEXXZ=005a1fc0
// @ref ?Clear@?$VectorClass@PBD@@UAEXXZ=005a2110
// @ref ?Fetch@?$VectorClass@PBD@@UBEPBDH@Z=005a2010
// @ref ?ID@?$DynamicVectorClass@PBD@@UAEHABQBD@Z=005a2250
// @ref ?ID@?$DynamicVectorClass@PBD@@UAEHPBQBD@Z=005a1ff0
// @ref ?ID@?$VectorClass@PBD@@UAEHABQBD@Z=005a2140
// @ref ?ID@?$VectorClass@PBD@@UAEHPBQBD@Z=005a2180
// @ref ?Resize@?$DynamicVectorClass@PBD@@UAE_NHPBQBD@Z=005a21a0
// @ref ?Resize@?$VectorClass@PBD@@UAE_NHPBQBD@Z=005a2060
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#include "shared/vector_class.hpp"



template <>
DynamicVectorClass<char const *>::DynamicVectorClass(unsigned size, char const *const *array)
    : VectorClass<char const *>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}
