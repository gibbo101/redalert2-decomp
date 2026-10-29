// WorldDominationTour::Map::Map(int, int, int) (0x00729330): every member cleared, the name
// from the shared string at 0x0083C55C and both lists empty. The unit emits the VectorClass<rc_ptr<Territory>>
// constructor 0x0072BB10 (called here out of line, see shared/wdt_map.hpp).
// @ref ?unknown_string_83c55c@@3PADA=0083c55c
// @ref ??0?$VectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@QAE@IPBV?$rc_ptr@VTerritory@WorldDominationTour@@@@@Z=0072bb10
// @ref ??_7?$VectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@6B@=007af23c
// @ref ??_7?$DynamicVectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@6B@=007af21c
// @ref ??_7?$DynamicVectorClass@PAVAnimationPalette@Map@WorldDominationTour@@@@6B@=007af1fc
// @ref ??1Map@WorldDominationTour@@UAE@XZ=007293f0
// @ref ??1ReferenceCounted@@UAE@XZ=00639710
// @ref ??_7Map@WorldDominationTour@@6B@=007af1ec
// @ref ??_7ReferenceCounted@@6B@=007a8d14
// @ref ??_7?$VectorClass@PAVAnimationPalette@Map@WorldDominationTour@@@@6B@=007af25c
// @ref ??_7?$rc_ptr@VTerritory@WorldDominationTour@@@@6B@=007af27c
// @ref ?Clear@?$VectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@UAEXXZ=0072b280
// @ref ?Clear@?$VectorClass@PAVAnimationPalette@Map@WorldDominationTour@@@@UAEXXZ=0072b550
// @ref ??_GReferenceCounted@@UAEPAXI@Z=00639750
// @ref ??_GMap@WorldDominationTour@@UAEPAXI@Z=0072af30
// @ref ??_G?$DynamicVectorClass@PAVAnimationPalette@Map@WorldDominationTour@@@@UAEPAXI@Z=0072ba50
// @ref ??_G?$VectorClass@PAVAnimationPalette@Map@WorldDominationTour@@@@UAEPAXI@Z=0072ba00
// @ref ??0rc_ptr_base@@QAE@XZ=006394e0
// @ref ??1rc_ptr_base@@UAE@XZ=00639510
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#include "shared/wdt_map.hpp"

namespace WorldDominationTour {

Map::Map(int unknown_08, int unknown_0c, int unknown_10) :
    unknown_08(unknown_08),
    unknown_0c(unknown_0c),
    unknown_10(unknown_10),
    unknown_14(0),
    unknown_18(0),
    unknown_1c(0),
    unknown_20(0),
    unknown_24(0),
    unknown_28(unknown_string_83c55c),
    Territories(0, 0),
    unknown_78(0),
    Palettes(0, 0)
{
}

}
