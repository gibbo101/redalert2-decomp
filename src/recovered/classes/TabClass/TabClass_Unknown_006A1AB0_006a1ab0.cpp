// @ref ??_C@_0P@BNNL@Tip?3AttackMove?$AA@=007f6904
// @ref ??_C@_0O@PKIE@Tip?3ThumbOpen?$AA@=007f6870
// @ref ??_C@_0P@KDME@Tip?3TypeSelect?$AA@=007f6880
// @ref ??_C@_0L@MCEK@Tip?3Team03?$AA@=007f6890
// @ref ??_C@_0L@GINN@Tip?3Team02?$AA@=007f689c
// @ref ??_C@_0L@JHGE@Tip?3Team01?$AA@=007f68a8
// @ref ??_C@_08HADJ@Tip?3Stop?$AA@=007f68b4
// @ref ??_C@_0BB@OEPN@Tip?3PlanningMode?$AA@=007f68c0
// @ref ??_C@_09MMAJ@Tip?3Guard?$AA@=007f68d4
// @ref ??_C@_0L@KHG@Tip?3Deploy?$AA@=007f68e0
// @ref ??_C@_09JGJD@Tip?3Cheer?$AA@=007f68ec
// @ref ??_C@_0L@NFIE@Tip?3Beacon?$AA@=007f68f8
#include "shared/tab.hpp"
#include "shared/tool_tip.hpp"
void TabClass::Unknown_006A1AB0()
{
    Unknown_006A0D50();
    Add_A_Button(unknown_button_abe400);
    Unknown_006A1270(Unknown_006A0600(unknown_int_abe464), "Tip:AttackMove");
    Unknown_006A1270(Unknown_006A0600(unknown_int_abe294), "Tip:Beacon");
    Unknown_006A1270(Unknown_006A0600(unknown_int_abd910), "Tip:Cheer");
    Unknown_006A1270(Unknown_006A0600(unknown_int_abe278), "Tip:Deploy");
    Unknown_006A1270(Unknown_006A0600(unknown_int_abe2b8), "Tip:Guard");
    Unknown_006A1270(Unknown_006A0600(unknown_int_abe36c), "Tip:PlanningMode");
    {
        ShapeButtonClass *button = Unknown_006A0600(unknown_int_abe2bc);
        Unknown_006A1270(button, "Tip:Stop");
    }
    {
        ShapeButtonClass *button = Unknown_006A0600(unknown_int_abe370);
        Unknown_006A1270(button, "Tip:Team01");
    }
    {
        ShapeButtonClass *button = Unknown_006A0600(unknown_int_abe378);
        Unknown_006A1270(button, "Tip:Team02");
    }
    {
        ShapeButtonClass *button = Unknown_006A0600(unknown_int_abe468);
        Unknown_006A1270(button, "Tip:Team03");
    }
    {
        ShapeButtonClass *button = Unknown_006A0600(unknown_int_abe290);
        Unknown_006A1270(button, "Tip:TypeSelect");
    }
    Unknown_006A1270(&unknown_button_abe400, "Tip:ThumbOpen");
}
