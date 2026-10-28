// void GraphicMenuImageItem::Visible_Changed(bool visible) (0x004DFDF0)
// Switches the three images (the first shows when visible and disabled, the second when
// visible and enabled, the third when hidden), tells the engine's animations about the
// item's area and repaints.
#include "shared/graphic_menu.hpp"

void GraphicMenuImageItem::Visible_Changed(bool visible)
{
    if (unknown_image_24 != 0) {
        unknown_image_24->Set_Unknown_0C(visible && !Enabled);
    }
    if (unknown_image_28 != 0) {
        unknown_image_28->Set_Unknown_0C(visible && Enabled);
    }
    if (unknown_image_2c != 0) {
        unknown_image_2c->Set_Unknown_0C(!visible);
    }
    Engine->Broadcast((int)&Area);
    Engine->Redraw();
}
