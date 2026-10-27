// TypeList<ParticleSystemTypeClass *>::TypeList, copy constructor (0x006DF9E0; vtable 0x007AD144).
// Layout and behaviour: shared/type_list.hpp.
// @ref ??0?$TypeList@PAVParticleSystemTypeClass@@@@QAE@ABV0@@Z=006df9e0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVParticleSystemTypeClass@@@@UBE_NABV0@@Z=00453ed0
// @ref ??_7?$TypeList@PAVParticleSystemTypeClass@@@@6B@=007ad144
// @ref ??_7?$VectorClass@PAVParticleSystemTypeClass@@@@6B@=0079d0ac
// @ref ??_E?$TypeList@PAVParticleSystemTypeClass@@@@UAEPAXI@Z=006df840
// @ref ??_E?$VectorClass@PAVParticleSystemTypeClass@@@@UAEPAXI@Z=00454710
// @ref ??_G?$TypeList@PAVParticleSystemTypeClass@@@@UAEPAXI@Z=006df840
// @ref ??_G?$VectorClass@PAVParticleSystemTypeClass@@@@UAEPAXI@Z=00454710
// @ref ?Clear@?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@UAEXXZ=00453cc0
// @ref ?Clear@?$VectorClass@PAVParticleSystemTypeClass@@@@UAEXXZ=00453fc0
// @ref ?Fetch@?$VectorClass@PAVParticleSystemTypeClass@@@@UBEPAVParticleSystemTypeClass@@H@Z=00453d10
// @ref ?ID@?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@UAEHABQAVParticleSystemTypeClass@@@Z=00454100
// @ref ?ID@?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@UAEHPBQAVParticleSystemTypeClass@@@Z=00453cf0
// @ref ?ID@?$VectorClass@PAVParticleSystemTypeClass@@@@UAEHABQAVParticleSystemTypeClass@@@Z=00453ff0
// @ref ?ID@?$VectorClass@PAVParticleSystemTypeClass@@@@UAEHPBQAVParticleSystemTypeClass@@@Z=00454030
// @ref ?Resize@?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@UAE_NHPBQAVParticleSystemTypeClass@@@Z=00454050
// @ref ?Resize@?$VectorClass@PAVParticleSystemTypeClass@@@@UAE_NHPBQAVParticleSystemTypeClass@@@Z=00453f10
#define VECTOR_IMPLEMENT_VECTOR_COPY_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/type_list.hpp"

class ParticleSystemTypeClass;

// Deep copy of the storage and both counters.
template <>
TypeList<ParticleSystemTypeClass *>::TypeList(TypeList<ParticleSystemTypeClass *> const &list)
    : DynamicVectorClass<ParticleSystemTypeClass *>(list)
{
}
