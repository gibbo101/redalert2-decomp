// WorldDominationTour::Voices::Voices(int faction) (0x007314C0)
// Names the six voice groups after their INI key prefixes.
// First unit of the Voices population: the container member guards of the
// unit (see Load 0x007317A0) and the group name setter are defined here,
// before shared/vector_class.hpp and shared/wdt_voices.hpp are first included.
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#define WDT_VOICES_DECLARE_SET_NAME
#include "shared/vector_class.hpp"
#include "shared/wdt_voices.hpp"
// @ref ??_C@_08JKAL@OldCycle?$AA@=007fc6ec
// @ref ??_C@_07JFNM@History?$AA@=007fc6e4
// @ref ??_C@_06IOLI@Status?$AA@=007fc6dc
// @ref ??_C@_09FECI@Territory?$AA@=007fbf08
// @ref ??_C@_04EKBK@Game?$AA@=007fc6d4
// @ref ??_C@_08IIHM@Evacuate?$AA@=007fc6c8

namespace WorldDominationTour {

Voices::Voices(int faction) :
    Faction(faction),
    Idle(true),
    Pending(0),
    Stream(0)
{
    Audio_Get_Device();
    Groups[0].Set_Name("OldCycle");
    Groups[1].Set_Name("History");
    Groups[2].Set_Name("Status");
    Groups[3].Set_Name("Territory");
    Groups[4].Set_Name("Game");
    Groups[5].Set_Name("Evacuate");
}

}
