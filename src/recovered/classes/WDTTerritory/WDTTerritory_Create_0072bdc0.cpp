// rc_ptr<WDTTerritory> __fastcall WDTTerritory::Create() (0x0072BDC0): a new territory, counted.
// First source of the unit: the vector members the WDTState constructor and destructor expand, and
// the guarded WDTState declarations (shared/wdt_state.hpp), are defined here before any include.
// @ref ??_7?$rc_ptr@VWDTTerritory@@@@6B@=007a452c
// @ref ??_E?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
// @ref ??_G?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define WDT_STATE_DECLARE_CONSTRUCTORS
#include "shared/wdt_territory.hpp"

rc_ptr<WDTTerritory> __fastcall WDTTerritory::Create()
{
    return rc_ptr<WDTTerritory>(new WDTTerritory());
}
