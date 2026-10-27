// MSFont::~MSFont() (0x005B3F70)
// The last font releases the shared slots, the drawer and an owned shape.
#include "shared/msfont.hpp"
// @ref ?unknown_font_count_a71858@@3HA=00a71858
// @ref ?unknown_font_slots_a71860@@3PAUMSFontSlot@@A=00a71860

#pragma auto_inline(off)
MSFont::~MSFont()
{
    if (--unknown_font_count_a71858 == 0) {
        for (int index = 0; index < 3; index++) {
            if (unknown_font_slots_a71860[index].unknown_00 != 0) {
                unknown_font_slots_a71860[index].unknown_00 = 0;
                unknown_font_slots_a71860[index].unknown_04 = false;
            }
        }
        delete Drawer;
        if (Shape != 0 && OwnsShape == true) {
            operator delete(Shape);
        }
        Shape = 0;
        OwnsShape = false;
    }
}
#pragma auto_inline(on)
