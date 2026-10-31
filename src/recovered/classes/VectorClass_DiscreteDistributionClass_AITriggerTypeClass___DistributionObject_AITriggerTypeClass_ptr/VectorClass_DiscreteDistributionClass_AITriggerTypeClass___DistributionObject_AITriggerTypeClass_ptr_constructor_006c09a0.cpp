// VectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass *>>::VectorClass(unsigned, T const *) (0x006C09A0).
// The generic body of shared/vector_class.hpp written as an explicit specialization (VC6 cannot
// explicitly instantiate a constructor alone, and the whole-class instantiation would emit an
// out-of-line ~VectorClass the original does not have). Its vtable 0x007ACA60 comes with it, with its scalar deleting destructor 0x006C0830 (the next row).
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
// @ref ??1?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@QAE@XZ=004ce940
// @ref ??_E?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@QAEPAXI@Z=004ceaf0
// @ref ??0HashString@@QAE@XZ=004e1130
// @ref ??0HashString@@QAE@ABV0@@Z=004e1180
// @ref ??4HashString@@QAEAAV0@ABV0@@Z=004e11c0
// @ref ??8@YI_NABVHashString@@0@Z=004e1290
// @ref ??9@YI_NABVHashString@@0@Z=004e12a0
// @ref ?Fetch@?$VectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UBE?AV?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@H@Z=006c03c0
// @ref ??8?$VectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UBE_NABV0@@Z=006c0440
// @ref ?Resize@?$VectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UAE_NHPBV?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@Z=006c04a0
// @ref ?Clear@?$VectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@UAEXXZ=006c05b0
// @ref ??_E?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@QAEPAXI@Z=006c0890
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_7?$VectorClass@V?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@@@6B@=007aca60
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/vector_class.hpp"
#include "shared/discrete_distribution.hpp"
class AITriggerTypeClass;

template <>
VectorClass<DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass *> >::VectorClass(unsigned size, DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass *> const *array)
    : Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
{
    if (size) {
        if (array) {
            Vector = new ((void *)array) DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass *>[size];
        } else {
            Vector = new DiscreteDistributionClass<AITriggerTypeClass>::DistributionObject<AITriggerTypeClass *>[size];
            IsAllocated = true;
        }
    }
}
