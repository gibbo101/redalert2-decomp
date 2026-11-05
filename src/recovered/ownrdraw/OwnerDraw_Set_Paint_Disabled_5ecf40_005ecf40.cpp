// @ref ?Grow_Table@?$WolDictionary@IUUnknownControlRecord@OwnerDraw@@@@QAEXXZ=00601f70
// @ref ?Set_Wide_Text_600510@UnknownControlRecord@OwnerDraw@@QAEXPBG@Z=00600510
#include "shared/win32_api.hpp"
#include "shared/wide_string.hpp"
#include "shared/wol_dictionary.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Sets one window's paint suppression flag, giving it a record when it has none (TibSun SetUserData2).
BOOL __stdcall Set_Paint_Disabled_5ecf40(HWND window, LPARAM lparam)
{
    UnknownControlRecord *data = 0;
    if (!unknown_control_table_a73640.Get_Pointer((unsigned int const &)window, &data)) {
        UnknownControlRecord temp;
        unknown_control_table_a73640.Add((unsigned int const &)window, temp);
        unknown_control_table_a73640.Get_Pointer((unsigned int const &)window, &data);
    }
    data->unknown_20 = lparam;
    return TRUE;
}

}
