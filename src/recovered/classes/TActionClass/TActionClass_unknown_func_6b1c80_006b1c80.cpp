// bool TActionClass::unknown_func_6b1c80(...) (0x006B1C80)
// Resets the tactical zoom to the rules ZoomInFactor, clears keyboard input, hides the mouse, aborts a drag select, redraws and pauses a second; always true.
#include "shared/taction.hpp"
#include "shared/tactical.hpp"
#include "shared/rules.hpp"
#include "shared/keyboard.hpp"
#include "shared/mouse.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/win32_api.hpp"
// @ref __imp__Sleep@4=0079a1e4

bool TActionClass::unknown_func_6b1c80(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    unknown_tactical_83996c->unknown_c0 = Rules->ZoomInFactor;
    unknown_flag_a40d44 = true;
    WWKeyboard->Clear();
    WWMouse->Hide_Mouse();
    Map.unknown_slot35();
    Map.Flag_To_Redraw(0);
    Map.Render();
    Sleep(1000);
    return true;
}
