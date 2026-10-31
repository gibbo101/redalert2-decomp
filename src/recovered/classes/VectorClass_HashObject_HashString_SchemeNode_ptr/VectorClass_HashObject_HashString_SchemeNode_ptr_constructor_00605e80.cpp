// VectorClass<HashObject<HashString, SchemeNode *>>::VectorClass(unsigned, T const *) (0x00605E80).
// The generic body of shared/vector_class.hpp written as an explicit specialization (VC6 cannot
// explicitly instantiate a constructor alone, and the whole-class instantiation would emit an
// out-of-line ~VectorClass the original does not have). Its vtable 0x007A7BD8 comes with it.
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
// @ref ??1?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@QAE@XZ=004ce940
// @ref ??_E?$DistributionObject@PAVCellClass@@@?$DiscreteDistributionClass@VCellClass@@@@QAEPAXI@Z=004ceaf0
// @ref ??0HashString@@QAE@XZ=004e1130
// @ref ??0HashString@@QAE@ABV0@@Z=004e1180
// @ref ??4HashString@@QAEAAV0@ABV0@@Z=004e11c0
// @ref ??8@YI_NABVHashString@@0@Z=004e1290
// @ref ??9@YI_NABVHashString@@0@Z=004e12a0
// @ref ?Fetch@?$VectorClass@U?$HashObject@VHashString@@PAVSchemeNode@@@@@@UBE?AU?$HashObject@VHashString@@PAVSchemeNode@@@@H@Z=00605810
// @ref ??8?$VectorClass@U?$HashObject@VHashString@@PAVSchemeNode@@@@@@UBE_NABV0@@Z=00605850
// @ref ?Resize@?$VectorClass@U?$HashObject@VHashString@@PAVSchemeNode@@@@@@UAE_NHPBU?$HashObject@VHashString@@PAVSchemeNode@@@@@Z=006058a0
// @ref ?Clear@?$VectorClass@U?$HashObject@VHashString@@PAVSchemeNode@@@@@@UAEXXZ=006059f0
// @ref ?ID@?$VectorClass@U?$HashObject@VHashString@@PAVSchemeNode@@@@@@UAEHABU?$HashObject@VHashString@@PAVSchemeNode@@@@@Z=00605a20
// @ref ?ID@?$VectorClass@U?$HashObject@VHashString@@PAVSchemeNode@@@@@@UAEHPBU?$HashObject@VHashString@@PAVSchemeNode@@@@@Z=00605a80
// @ref ??_E?$DistributionObject@PAVAITriggerTypeClass@@@?$DiscreteDistributionClass@VAITriggerTypeClass@@@@QAEPAXI@Z=006c0890
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_7?$VectorClass@U?$HashObject@VHashString@@PAVSchemeNode@@@@@@6B@=007a7bd8
// @ref ??_G?$VectorClass@U?$HashObject@VHashString@@PAVSchemeNode@@@@@@UAEPAXI@Z=00605e30
// @ref ??_E?$VectorClass@U?$HashObject@VHashString@@PAVSchemeNode@@@@@@UAEPAXI@Z=00605e30
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/vector_class.hpp"
#include "shared/hash_string.hpp"

template <>
VectorClass<HashObject<HashString, SchemeNode *> >::VectorClass(unsigned size, HashObject<HashString, SchemeNode *> const *array)
    : Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
{
    if (size) {
        if (array) {
            Vector = new ((void *)array) HashObject<HashString, SchemeNode *>[size];
        } else {
            Vector = new HashObject<HashString, SchemeNode *>[size];
            IsAllocated = true;
        }
    }
}
