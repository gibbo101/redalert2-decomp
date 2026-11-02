// rc_ptr<Map> __fastcall WorldDominationTour::Map::Create(int, int, int) (0x007292E0)
// A new map, returned counted.
// @ref ??0Map@WorldDominationTour@@QAE@HHH@Z=00729330
// @ref ??_7?$rc_ptr@VMap@WorldDominationTour@@@@6B@=007af1e4
// @ref ??0rc_ptr_base@@QAE@XZ=006394e0
// @ref ?Set@rc_ptr_base@@IAEXPAVReferenceCounted@@@Z=00639530
// @ref ??_E?$rc_ptr@VMap@WorldDominationTour@@@@UAEPAXI@Z=0072b0c0
// @ref ??_G?$rc_ptr@VMap@WorldDominationTour@@@@UAEPAXI@Z=0072b0c0
#include "shared/wdt_map.hpp"

namespace WorldDominationTour {

rc_ptr<Map> __fastcall Map::Create(int unknown_08, int unknown_0c, int unknown_10)
{
    return rc_ptr<Map>(new Map(unknown_08, unknown_0c, unknown_10));
}

}
