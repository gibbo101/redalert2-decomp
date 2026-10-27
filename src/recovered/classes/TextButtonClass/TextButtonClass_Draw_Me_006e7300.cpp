// int TextButtonClass::Draw_Me(int forced) (0x006E7300, slot 27)
#include "shared/gadget.hpp"
// @ref ?Draw_Me@ControlClass@@UAEHH@Z=00483530

int TextButtonClass::Draw_Me(int forced)
{
    if (ControlClass::Draw_Me(forced)) {
        Draw_Background();
        Draw_Text(String);
        return true;
    }
    return false;
}
