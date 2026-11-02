// rc_ptr<WDTState> __fastcall WDTState::Create(unsigned char *data) (0x0072BEB0): a new state
// read from the WOL state block, counted.
// @ref ??0WDTState@@QAE@PAE@Z=0072bfa0
#include "shared/wdt_state.hpp"

rc_ptr<WDTState> __fastcall WDTState::Create(unsigned char *data)
{
    return rc_ptr<WDTState>(new WDTState(data));
}
