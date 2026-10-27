#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#include "shared/fogged_object.hpp"
// @ref ??0AbstractClass@@QAE@ABVNoInitClass@@@Z=0040ff60
// @ref ??_7FoggedObjectClass@@6BIPersistStream@@@=007a1148
// @ref ??_7FoggedObjectClass@@6BIRTTITypeInfo@@@=007a112c
// @ref ??_7FoggedObjectClass@@6BINoticeSink@@@=007a1124
// @ref ??_7FoggedObjectClass@@6BINoticeSource@@@=007a111c
// @ref ??_7?$DynamicVectorClass@UDrawRecord@FoggedObjectClass@@@@6B@=007a11b0
FoggedObjectClass::FoggedObjectClass(NoInitClass const &noinit)
    : AbstractClass(noinit), unknown_50(noinit)
{
}
