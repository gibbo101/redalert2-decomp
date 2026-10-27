// void GraphicMenuItem::Set_Visible(bool visible) -- 0x004E0180
// Stores the flag and notifies the item (virtual Visible_Changed) when it changes.
#include "shared/graphic_menu.hpp"

void GraphicMenuItem::Set_Visible(bool visible)
{
    if (visible != Visible) {
        Visible = visible;
        Visible_Changed(visible);
    }
}
