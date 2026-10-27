// Rect __fastcall TabClass::Unknown_006A0620(int slot) (0x006A0620)
// Screen rectangle of slot: the 0x00AC120C rectangle moved down by the
// mapped button's row.
#include "shared/tab.hpp"
// @ref ?SlotButton@TabClass@@2PAHA=00abe2c8
// @ref ?unknown_int_abe388@@3HA=00abe388
// @ref ?unknown_int_abe374@@3HA=00abe374
// @ref ?unknown_rect_ac120c@@3PBVRect@@B=00ac120c

Rect __fastcall TabClass::Unknown_006A0620(int slot)
{
    Rect rect = *unknown_rect_ac120c;
    return Rect(SlotButton[slot] * unknown_int_abe388 + rect.X, unknown_int_abe374, rect.Width, rect.Height);
}
