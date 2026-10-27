// VectorClass<rc_ptr<WDTTerritory>>::Resize (0x0072CBD0).
// Layout and behaviour: shared/vector_class.hpp.
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
// @ref ??0?$rc_ptr@VConflict@WorldDominationTour@@@@QAE@XZ=00727020
// @ref ??_7?$rc_ptr@VConflict@WorldDominationTour@@@@6B@=007aefec
// @ref ??0?$rc_ptr@VGameOption@WorldDominationTour@@@@QAE@XZ=00728460
// @ref ??_7?$rc_ptr@VGameOption@WorldDominationTour@@@@6B@=007af0dc
// @ref ??0?$rc_ptr@VTerritory@WorldDominationTour@@@@QAE@XZ=0072baf0
// @ref ??_7?$rc_ptr@VTerritory@WorldDominationTour@@@@6B@=007af27c
// @ref ??0?$rc_ptr@VWDTTerritory@@@@QAE@XZ=0072cf70
// @ref ??_7?$rc_ptr@VWDTTerritory@@@@6B@=007a452c
// @ref ??_E?$rc_ptr@VConflict@WorldDominationTour@@@@UAEPAXI@Z=00726f60
// @ref ??_E?$rc_ptr@VGameOption@WorldDominationTour@@@@UAEPAXI@Z=007283a0
// @ref ??_E?$rc_ptr@VTerritory@WorldDominationTour@@@@UAEPAXI@Z=0072b940
// @ref ??_E?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
#define VECTOR_IMPLEMENT_VECTOR_RESIZE
#include "shared/vector_class.hpp"
#include "shared/reference_counted.hpp"
namespace WorldDominationTour {
class Conflict;
class GameOption;
class Territory;
}
class WDTTerritory;


template class VectorClass<rc_ptr<WDTTerritory> >;
