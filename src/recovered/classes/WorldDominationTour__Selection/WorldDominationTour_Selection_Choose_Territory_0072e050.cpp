// rc_ptr<Territory> Selection::Choose_Territory() (0x0072E050)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
#include "shared/lobby.hpp"
namespace WorldDominationTour {
rc_ptr<Territory> Selection::Choose_Territory()
{
    Show_Campaign();
    bool canceled = false;
    bool selected = false;
    WWKeyboard->Clear();
    do {
        Unknown_0073e100();
        Check_Focus();
        Point2D point(WWMouse->Get_Mouse_X(), WWMouse->Get_Mouse_Y());
        if (WWKeyboard->Check()) {
            int key = WWKeyboard->Get();
            if (key == 1) {
                Click(point, selected);
            } else if (key == 0x801) {
                TheMap->Set_Unknown_74(this, false);
                if (Region(point) == 2) {
                    Play_Sound("Canceled");
                    canceled = true;
                }
            }
        } else if (point != LastMouse) {
            LastMouse = point;
            int region = Region(point);
            if (unknown_454 != region) {
                switch (unknown_454) {
                case 1:
                    Leave_Territory();
                    break;
                case 2:
                    Uncancel();
                    break;
                }
            }
            switch (region) {
            case 1:
                if (unknown_454 != 1) {
                    Play_Map_Enter();
                }
                Hover_2(point);
                break;
            case 2:
                if (unknown_454 != 2) {
                    Cancel();
                }
                break;
            }
            unknown_454 = region;
        }
        Run(1);
    } while (!canceled && !selected);
    return selected ? unknown_464 : rc_ptr<Territory>();
}
}
// @ref ??_C@_0BC@PBP@D?3?2Ra2?2WDTSel?4cpp?$AA@=007fc31c
// @ref ??_C@_0BL@MEDD@WDT?3TerritorySelectToolTip?$AA@=007fc454
// @ref ??_C@_08FEAE@Canceled?$AA@=007fc448
// @ref ??_C@_08DLBG@MapLeave?$AA@=007fc43c
// @ref ??_C@_08EJJK@MapEnter?$AA@=007fc430
// @ref ?Click@Selection@WorldDominationTour@@QAEXABUPoint2D@@AA_N@Z=0072e430
// @ref ?Set_Unknown_74@Map@WorldDominationTour@@QAEXPAVMSEngine@@_N@Z=0072a6d0
// @ref ?Is_Inside@Map@WorldDominationTour@@QBE_NABUPoint2D@@@Z=0072a770
// @ref ?Unknown_0073e100@@YA_NXZ=0073e100
// @ref ??C?$rc_ptr@VCampaignProperties@WorldDominationTour@@@@QBEPAVCampaignProperties@WorldDominationTour@@XZ=007302d0
// @ref ??C?$rc_ptr@VMap@WorldDominationTour@@@@QBEPAVMap@WorldDominationTour@@XZ=00730330
// @ref ?Get_Territory@Map@WorldDominationTour@@QAE?AV?$rc_ptr@VTerritory@WorldDominationTour@@@@H@Z=007302b0
// @ref ??0?$rc_ptr@VTerritory@WorldDominationTour@@@@QAE@XZ=0072baf0
// @ref ??0?$rc_ptr@VTerritory@WorldDominationTour@@@@QAE@ABV0@@Z=007302e0
// @ref ??1?$rc_ptr@VTerritory@WorldDominationTour@@@@UAE@XZ=00730310
