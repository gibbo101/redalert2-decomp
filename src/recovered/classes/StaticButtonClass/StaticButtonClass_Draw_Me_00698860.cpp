// int StaticButtonClass::Draw_Me(int forced) (0x00698860, slot 27)
#include "shared/gadget.hpp"

int StaticButtonClass::Draw_Me(int forced)
{
    if (GadgetClass::Draw_Me(forced)) {
        Draw_Background();
        Draw_Text(Text);
        return true;
    }
    return false;
}
