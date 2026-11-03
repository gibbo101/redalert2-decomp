// Real original atexit function for the active-message pair-keyed dictionary.
// Its existing accepted Remove_Entry00602040 proves key8/value1/next12 layout.
// @ref _unknown_active_messages_a73398=00a73398
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/wol_dictionary.hpp"
typedef WolDictionary<OwnerDraw::UnknownPairKey,bool> ActiveMessageDictionary_5f00e0;
extern "C" ActiveMessageDictionary_5f00e0 unknown_active_messages_a73398;
void unknown_active_messages_atexit_5f00e0()
{
    unknown_active_messages_a73398.~ActiveMessageDictionary_5f00e0();
}
