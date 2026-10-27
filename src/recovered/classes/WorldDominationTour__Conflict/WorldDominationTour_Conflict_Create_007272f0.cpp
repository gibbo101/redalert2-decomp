// Conflict.cpp (unit 0x00727100-0x0072847F): one battle of the World
// Domination Tour campaign and the shared list of battle options.
// @ref ??_E?$rc_ptr@VConflict@WorldDominationTour@@@@UAEPAXI@Z=00726f60
// @ref ??_7?$rc_ptr@VConflict@WorldDominationTour@@@@6B@=007aefec
// @ref ??_7Conflict@WorldDominationTour@@6B@=007af07c
// @ref ??_7ReferenceCounted@@6B@=007a8d14
// @ref ??_7?$rc_ptr@VWDTTerritory@@@@6B@=007a452c
// @ref ??_E?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
// @ref ??1ReferenceCounted@@UAE@XZ=00639710
#define VECTOR_IMPLEMENT_ALL
#include "shared/wdt_game_options.hpp"

// The shared list of battle options (0x00B256C0), filled by Init_Options.
DynamicVectorClass<rc_ptr<WorldDominationTour::GameOption> > unknown_game_options_b256c0;

namespace WorldDominationTour {

rc_ptr<Conflict> __fastcall Conflict::Create(rc_ptr<WDTTerritory> const &territory)
{
    return rc_ptr<Conflict>(new Conflict(territory));
}
