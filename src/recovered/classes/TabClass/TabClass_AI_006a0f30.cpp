// void TabClass::AI(int &input, Point2D const &xy) (0x006A0F30, slot 10)
// The command bar's input: redraws when its timer runs to 1, shows the
// normal mouse over the bar, runs the command of a pressed button (the team
// buttons select, assign or recall their group; with the shift form they
// clear it), opens (0x80F1, 0x006A1EC0) or closes (0x80F0, 0x006A1F10) the
// bar with its sound, then the sidebar's AI.
#include "shared/tab.hpp"
#include "shared/rules.hpp"
#include "shared/tool_tip.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?AI@SidebarClass@@UAEXAAHABUPoint2D@@@Z=0067dc90
// @ref ?Override_Mouse_Shape@MouseClass@@UAE_NH_N@Z=0059f250
// @ref ?Unknown_00494650@UnknownTab4EEC@@QAEXH@Z=00494650
// @ref ?Unknown_00713DB0@@YIHHMHH@Z=00713db0
// @ref ?Unknown_006A0D80@TabClass@@QAEXXZ=006a0d80
// @ref ?Unknown_006A1AB0@TabClass@@QAEXXZ=006a1ab0
// @ref ?Unknown_006F6570@@YAXXZ=006f6570
// @ref ?Unknown_006F64B0@@YAXXZ=006f64b0
// @ref ?Unknown_006F5C50@@YAXXZ=006f5c50
// @ref ?Unknown_006F5940@@YAXXZ=006f5940
// @ref ?Unknown_006F5B10@@YAXXZ=006f5b10
// @ref ?Unknown_006F64D0@@YIX_N@Z=006f64d0
// @ref ?Unknown_006F64F0@@YIX_N@Z=006f64f0
// @ref ?Unknown_006F5BC0@@YAXXZ=006f5bc0
// @ref ?Unknown_006F5870@@YIHH@Z=006f5870
// @ref ?Unknown_006F5D90@@YIXH@Z=006f5d90
// @ref ?Unknown_006F5800@@YI_NH@Z=006f5800
// @ref ?Unknown_006F60D0@@YIXH@Z=006f60d0
// @ref ?Unknown_006F5F00@@YIXH@Z=006f5f00
// @ref ?Unknown_006F7360@@YAXXZ=006f7360
// @ref ?Unknown_006F5E10@@YIXH@Z=006f5e10
// @ref ?unknown_int_abe464@@3HA=00abe464
// @ref ?unknown_int_abe294@@3HA=00abe294
// @ref ?unknown_int_abd910@@3HA=00abd910
// @ref ?unknown_int_abe278@@3HA=00abe278
// @ref ?unknown_int_abe2b8@@3HA=00abe2b8
// @ref ?unknown_int_abe36c@@3HA=00abe36c
// @ref ?unknown_int_abe2bc@@3HA=00abe2bc
// @ref ?unknown_int_abe290@@3HA=00abe290
// @ref ?unknown_int_a3d548@@3HA=00a3d548
// @ref ?unknown_int_7add84@@3HA=007add84
// @ref ?unknown_int_839638@@3HA=00839638
// @ref ??_C@_0BA@GHMH@Tip?3ThumbClosed?$AA@=007f6860
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Remove@ToolTipManager@@QAEXI@Z=006eba10

void TabClass::AI(int &input, Point2D const &xy)
{
    if (unknown_4f08.Value() == 1) {
        unknown_4f15 = true;
        Flag_To_Redraw(false);
    }
    Rect rect(unknown_rect_ac11fc->X, unknown_rect_ac11fc->Y, unknown_int_839638, unknown_int_7add84 - 2);
    if (rect.Is_Point_Within(xy)) {
        Map.Override_Mouse_Shape(0, false);
    }
    int key = input;
    if (key >= 0x80D6 && key < 0x80EF) {
        int id = (key & ~0x8000) - 0xD6;
        if (id == unknown_int_abe464) {
            Unknown_006F6570();
        } else if (id == unknown_int_abe294) {
            Unknown_006F64B0();
        } else if (id == unknown_int_abd910) {
            Unknown_006F5C50();
        } else if (id == unknown_int_abe278) {
            Unknown_006F5940();
        } else if (id == unknown_int_abe2b8) {
            Unknown_006F5B10();
        } else if (id == unknown_int_abe36c) {
            if (Unknown_006A0600(unknown_int_abe36c)->IsOn) {
                Unknown_006F64D0(true);
            } else {
                Unknown_006F64F0(true);
            }
        } else if (id == unknown_int_abe2bc) {
            Unknown_006F5BC0();
        } else if (Unknown_006A06B0(id)) {
            int group = Unknown_006A06D0(id);
            if (Unknown_006F5870(group) == 0) {
                Unknown_006F5D90(group);
            } else if (Unknown_006F5800(group)) {
                Unknown_006F60D0(group);
            } else {
                Unknown_006F5F00(group);
            }
        } else if (id == unknown_int_abe290) {
            Unknown_006F7360();
        }
    } else if (key == 0x80F0) {
        Unknown_Play_Sound(Rules->unknown_190);
        Unknown_006A1F10();
    } else if (key == 0x80F1) {
        if (unknown_int_a3d548 == 0) {
            Unknown_Play_Sound(Rules->unknown_18c);
            Unknown_006A1EC0();
        }
    } else if (key >= 0xC0D6 && key < 0xC0EF) {
        int id = (key & ~0xC000) - 0xD6;
        if (Unknown_006A06B0(id)) {
            Unknown_006F5E10(Unknown_006A06D0(id));
        }
    }
    unknown_4eec.Unknown_00494650(0);
    SidebarClass::AI(input, xy);
}
