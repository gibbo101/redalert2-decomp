// void GraphicMenuImageItem::Enabled_Changed(bool enabled) (0x004DFD60)
// Switches the three images (the first shows when visible and disabled, the second when
// visible and enabled, the third when hidden), tells the engine's animations about the
// item's area, repaints and plays the hover sound when the item became enabled.
#include "shared/graphic_menu.hpp"

void GraphicMenuImageItem::Enabled_Changed(bool enabled)
{
    if (unknown_image_24 != 0) {
        unknown_image_24->Set_Unknown_0C(Visible && !enabled);
    }
    if (unknown_image_28 != 0) {
        unknown_image_28->Set_Unknown_0C(Visible && enabled);
    }
    if (unknown_image_2c != 0) {
        unknown_image_2c->Set_Unknown_0C(!Visible);
    }
    Engine->Broadcast((int)&Area);
    Engine->Redraw();
    if (enabled && unknown_sound_30 != 0) {
        unknown_sound_30->Play();
    }
}
