// void TabClass::unknown_slot53() (0x006A0B70, slot 53)
// After the sidebar's, loads the 25 button shapes ("Button%02d.SHP") and
// derives the bar metrics from the first one and the layout rectangles.
#include "shared/tab.hpp"
// @ref ?unknown_slot53@SidebarClass@@UAEXXZ=0067bd90
// @ref ?sprintf@@YAHPADPBDZZ=007820f4
// @ref _sprintf=007820f4
// @ref ?Unknown_Load_Shape_00495270@@YIPBXPBDAA_N@Z=00495270
// @ref ??_C@_0P@ODHJ@Button?$CF02d?4SHP?$AA@=007f6850
// @ref ?unknown_int_abe2a8@@3HA=00abe2a8
// @ref ?unknown_int_abe2ac@@3HA=00abe2ac
// @ref ?unknown_int_abe37c@@3HA=00abe37c
// @ref ?unknown_int_abe374@@3HA=00abe374
// @ref ?unknown_int_abe388@@3HA=00abe388
// @ref ?unknown_int_abe460@@3HA=00abe460
// @ref ?unknown_int_abe478@@3HA=00abe478
// @ref ?unknown_rect_ac11fc@@3PBVRect@@B=00ac11fc
// @ref ?unknown_rect_ac120c@@3PBVRect@@B=00ac120c
// @ref ?unknown_rect_ac1210@@3PBVRect@@B=00ac1210

void TabClass::unknown_slot53()
{
    SidebarClass::unknown_slot53();
    bool allocated = false;
    for (int index = 0; index < 25; index++) {
        char name[256];
        sprintf(name, "Button%02d.SHP", index);
        ButtonShapes[index] = Unknown_Load_Shape_00495270(name, allocated);
        ButtonShapeAllocated[index] = allocated;
    }
    short const *header = (short const *)ButtonShapes[0];
    unknown_int_abe478 = header[1];
    unknown_int_abe2a8 = header[2];
    Rect slot = *unknown_rect_ac120c;
    unknown_int_abe37c = unknown_rect_ac1210->X - unknown_int_abe2ac * slot.Width;
    unknown_int_abe374 = unknown_rect_ac11fc->Y;
    unknown_int_abe460 = slot.Width - unknown_int_abe478;
    unknown_int_abe388 = unknown_int_abe460 + unknown_int_abe478;
    unknown_4eec.unknown_04 = 0;
}
