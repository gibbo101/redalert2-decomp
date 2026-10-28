// DynamicVectorClass<TechnoClass *>::DynamicVectorClass(unsigned size, TechnoClass *const *array) (0x006F8A80; vtable 0x0079A79C)
// The sized constructor kept in this unit: VectorClass storage (the array in
// place, or allocated and owned), growth step 10, no active entries.
// @ref ??0?$DynamicVectorClass@PAVTechnoClass@@@@QAE@IPBQPAVTechnoClass@@@Z=006f8a80
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVTechnoClass@@@@UBE_NABV0@@Z=0040b870
// @ref ??_7?$DynamicVectorClass@PAVTechnoClass@@@@6B@=0079a79c
// @ref ??_7?$VectorClass@PAVTechnoClass@@@@6B@=0079a7fc
// @ref ??_E?$DynamicVectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bbc0
// @ref ??_G?$DynamicVectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bbc0
// @ref ??_E?$VectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bb70
// @ref ??_G?$VectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bb70
// @ref ?Clear@?$DynamicVectorClass@PAVTechnoClass@@@@UAEXXZ=0040b5b0
// @ref ?Clear@?$VectorClass@PAVTechnoClass@@@@UAEXXZ=0040b960
// @ref ?Fetch@?$VectorClass@PAVTechnoClass@@@@UBEPAVTechnoClass@@H@Z=0040b600
// @ref ?ID@?$DynamicVectorClass@PAVTechnoClass@@@@UAEHABQPAVTechnoClass@@@Z=0040baa0
// @ref ?ID@?$DynamicVectorClass@PAVTechnoClass@@@@UAEHPBQPAVTechnoClass@@@Z=0040b5e0
// @ref ?ID@?$VectorClass@PAVTechnoClass@@@@UAEHABQPAVTechnoClass@@@Z=0040b990
// @ref ?ID@?$VectorClass@PAVTechnoClass@@@@UAEHPBQPAVTechnoClass@@@Z=0040b9d0
// @ref ?Resize@?$DynamicVectorClass@PAVTechnoClass@@@@UAE_NHPBQPAVTechnoClass@@@Z=0040b9f0
// @ref ?Resize@?$VectorClass@PAVTechnoClass@@@@UAE_NHPBQPAVTechnoClass@@@Z=0040b8b0
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#include "shared/vector_class.hpp"

class TechnoClass;

template <>
DynamicVectorClass<TechnoClass *>::DynamicVectorClass(unsigned size, TechnoClass *const *array)
    : VectorClass<TechnoClass *>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}
