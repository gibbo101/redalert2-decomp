// DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass *>>::DynamicVectorClass(unsigned, T const *) (0x004CE710).
// The generic body of shared/vector_class.hpp written as an explicit specialization (VC6 cannot
// explicitly instantiate a constructor alone, and the whole-class instantiation would emit an
// out-of-line ~DynamicVectorClass the original does not have). The VectorClass and
// DynamicVectorClass vtables (0x007A17D4, 0x007A17FC) come with it, with their scalar deleting destructors (the next rows).
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
// @ref ?Fetch@?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UBE?AV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@H@Z=004cdf10
// @ref ??8?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UBE_NABV0@@Z=004ce4f0
// @ref ?Resize@?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAE_NHPBV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@Z=004ce550
// @ref ?Clear@?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEXXZ=004ce660
// @ref ?ID@?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEHPBV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@Z=004ce6f0
// @ref ??1?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@QAE@XZ=004ce940
// @ref ??_E?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@QAEPAXI@Z=004ceaf0
// @ref ??0HashString@@QAE@XZ=004e1130
// @ref ??0HashString@@QAE@ABV0@@Z=004e1180
// @ref ??4HashString@@QAEAAV0@ABV0@@Z=004e11c0
// @ref ??8@YI_NABVHashString@@0@Z=004e1290
// @ref ??9@YI_NABVHashString@@0@Z=004e12a0
// @ref ??_E?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@QAEPAXI@Z=006c0890
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??2@YAPAXI@Z=00782017
// @ref ?Clear@?$DynamicVectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEXXZ=004ce7c0
// @ref ?ID@?$DynamicVectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEHPBV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@Z=004ce800
// @ref ?Resize@?$DynamicVectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAE_NHPBV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@Z=004ce820
// @ref ??_7?$VectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@6B@=007a17d4
// @ref ??_7?$DynamicVectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@6B@=007a17fc
// @ref ?ID@?$DynamicVectorClass@V?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@@UAEHABV?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@@Z=004ce9b0
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#include "shared/vector_class.hpp"
#include "shared/discrete_distribution.hpp"
class CellClass;

template <>
DynamicVectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass *> >::DynamicVectorClass(unsigned size, DiscreteDistributionClass<CellClass>::DistributionObject<CellClass *> const *array)
    : VectorClass<DiscreteDistributionClass<CellClass>::DistributionObject<CellClass *> >(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}
