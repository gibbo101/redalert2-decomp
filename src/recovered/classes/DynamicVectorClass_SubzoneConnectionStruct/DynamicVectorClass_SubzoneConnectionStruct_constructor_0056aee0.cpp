// DynamicVectorClass<SubzoneConnectionStruct>::DynamicVectorClass(unsigned, SubzoneConnectionStruct const *)
// (0x0056AEE0): the out-of-line copy of the Map unit (shared/vector_class.hpp). The vtables and their
// slot functions it emits are the copies kept at their recorded addresses.
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ?Fetch@?$VectorClass@USubzoneConnectionStruct@@@@UBE?AUSubzoneConnectionStruct@@H@Z=0040b050
// @ref ??8?$VectorClass@USubzoneConnectionStruct@@@@UBE_NABV0@@Z=0040b070
// @ref ?Resize@?$VectorClass@USubzoneConnectionStruct@@@@UAE_NHPBUSubzoneConnectionStruct@@@Z=0040b0b0
// @ref ?Clear@?$VectorClass@USubzoneConnectionStruct@@@@UAEXXZ=0040b1a0
// @ref ?ID@?$VectorClass@USubzoneConnectionStruct@@@@UAEHABUSubzoneConnectionStruct@@@Z=0040b1d0
// @ref ?ID@?$VectorClass@USubzoneConnectionStruct@@@@UAEHPBUSubzoneConnectionStruct@@@Z=0040b210
// @ref ??_E?$VectorClass@USubzoneConnectionStruct@@@@UAEPAXI@Z=0040b230
// @ref ??_G?$VectorClass@USubzoneConnectionStruct@@@@UAEPAXI@Z=0040b230
// @ref ?Clear@?$DynamicVectorClass@USubzoneConnectionStruct@@@@UAEXXZ=0056aa70
// @ref ?ID@?$DynamicVectorClass@USubzoneConnectionStruct@@@@UAEHPBUSubzoneConnectionStruct@@@Z=0056aaa0
// @ref ??_E?$DynamicVectorClass@USubzoneConnectionStruct@@@@UAEPAXI@Z=0056ae90
// @ref ??_G?$DynamicVectorClass@USubzoneConnectionStruct@@@@UAEPAXI@Z=0056ae90
// @ref ?Resize@?$DynamicVectorClass@USubzoneConnectionStruct@@@@UAE_NHPBUSubzoneConnectionStruct@@@Z=0056af70
// @ref ?ID@?$DynamicVectorClass@USubzoneConnectionStruct@@@@UAEHABUSubzoneConnectionStruct@@@Z=0056b0b0
// @ref ??_7?$VectorClass@USubzoneConnectionStruct@@@@6B@=0079a76c
// @ref ??_7?$DynamicVectorClass@USubzoneConnectionStruct@@@@6B@=007a5ad8
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#include "shared/vector_class.hpp"
#include "shared/map_elements.hpp"

// The generic body of shared/vector_class.hpp, written as an explicit specialization (VC6
// cannot explicitly instantiate a constructor alone; the whole-class instantiation would also
// emit an out-of-line ~DynamicVectorClass the original does not have).
template <>
DynamicVectorClass<SubzoneConnectionStruct>::DynamicVectorClass(unsigned size, SubzoneConnectionStruct const *array)
    : VectorClass<SubzoneConnectionStruct>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}
