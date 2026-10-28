// FoggedObjectClass::FoggedObjectClass() (0x004C0020)
// An empty fogged object, listed in Array.
#include "shared/fogged_object.hpp"
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ??_7FoggedObjectClass@@6BIPersistStream@@@=007a1148
// @ref ??_7FoggedObjectClass@@6BIRTTITypeInfo@@@=007a112c
// @ref ??_7FoggedObjectClass@@6BINoticeSink@@@=007a1124
// @ref ??_7FoggedObjectClass@@6BINoticeSource@@@=007a111c
// @ref ??_7?$DynamicVectorClass@UDrawRecord@FoggedObjectClass@@@@6B@=007a11b0
// @ref ?Array@FoggedObjectClass@@2V?$DynamicVectorClass@PAVFoggedObjectClass@@@@A=00865e90
FoggedObjectClass::FoggedObjectClass()
    : unknown_24(-1), unknown_28(0), unknown_2c(0), unknown_30(0), Coord(0, 0, 0),
      unknown_40(0, 0, 0, 0), unknown_50(0), unknown_54(-1), unknown_58(0), unknown_74(true)
{
    Array.Add(this);
}
