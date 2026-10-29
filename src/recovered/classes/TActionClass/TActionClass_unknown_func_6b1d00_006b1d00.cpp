// bool TActionClass::unknown_func_6b1d00(...) (0x006B1D00)
// Undoes 0x006B1C80: tactical zoom 1.0, keyboard cleared, the input flag from the pause flag, mouse shown, redraw; always true.
#include "shared/taction.hpp"
#include "shared/tactical.hpp"
#include "shared/keyboard.hpp"
#include "shared/mouse.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_globals.hpp"

bool TActionClass::unknown_func_6b1d00(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    unknown_tactical_83996c->unknown_c0 = 1.0;
    WWKeyboard->Clear();
    unknown_flag_a40d44 = unknown_id_source_a3d290->unknown_2306;
    WWMouse->Show_Mouse();
    Map.Flag_To_Redraw(0);
    Map.Render();
    return true;
}
