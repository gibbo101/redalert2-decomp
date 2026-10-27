// void GraphicMenuItem::Set_Enabled(bool enabled) -- 0x004E0160
// Stores the flag and notifies the item (virtual Enabled_Changed) when it changes.
#include "shared/graphic_menu.hpp"

void GraphicMenuItem::Set_Enabled(bool enabled)
{
    if (enabled != Enabled) {
        Enabled = enabled;
        Enabled_Changed(enabled);
    }
}
