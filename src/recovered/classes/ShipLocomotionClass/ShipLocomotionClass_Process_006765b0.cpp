// bool __stdcall ShipLocomotionClass::Process() (0x006765B0, ILocomotion 16)
#include "shared/ship_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
// @ref ?unknown_coord_ab91c8@@3UCoordStruct@@A=00ab91c8
// @ref ?While_Moving@ShipLocomotionClass@@QAE_N_N@Z=00676f60
// @ref ?Start_Of_Move@ShipLocomotionClass@@QAE_NAA_N_N1@Z=006785c0
// @ref ??0?$CDTimerClass@VFrameTimerClass@@@@QAE@J@Z=00463f80
// @ref __real@8@00000000000000000000=0079b610

bool __stdcall ShipLocomotionClass::Process()
{
    Set_Slope(static_cast<CellClass *>(LinkedTo->unknown_slot105())->unknown_11c);
    if (unknown_58 != -1 && unknown_63) {
        if (While_Moving(false) || !LinkedTo->unknown_7d) {
            return false;
        }
        if (unknown_58 == -1 && (Is_Moving() || LinkedTo->unknown_4d0 != -1)
            && (LinkedTo->Kind_Of() != 1 || !((UnitClass *)LinkedTo)->unknown_5b9)) {
            bool stop = false;
            Start_Of_Move(stop, true, false);
            if (stop || !LinkedTo->unknown_7d) {
                return false;
            }
            While_Moving(true);
            if (!LinkedTo->unknown_7d) {
                return false;
            }
        }
    } else {
        if (LinkedTo->unknown_494 != 0 && LinkedTo->unknown_494->Kind_Of() == 11) {
            CellClass *cell = (CellClass *)LinkedTo->unknown_494;
            if (LinkedTo->unknown_slot104() == cell->Fetch_CellID()) {
                unknown_67a7a0();
                return false;
            }
        }
        if (LinkedTo->Mission == 5 && !unknown_63 && unknown_34 != unknown_coord_ab91c8 && Object_Coord(LinkedTo) == unknown_34) {
            unknown_67a7a0();
            return false;
        }
        if (LinkedTo->unknown_2e0.Is_Rotating()) {
            unknown_62 = true;
        } else {
            if (unknown_62) {
                unknown_62 = false;
                LinkedTo->unknown_slot93(0);
                if (!LinkedTo->unknown_7d || LinkedTo->unknown_76 || LinkedTo->unknown_7a) {
                    return false;
                }
            }
            if ((LinkedTo->unknown_slot91() != 5 || Is_Moving()) && LinkedTo->unknown_slot91() != 16) {
                if (Is_Moving() || LinkedTo->unknown_4d0 != -1) {
                    if (LinkedTo->unknown_32d && LinkedTo->unknown_slot91() != 7 && Is_Moving() && !LinkedTo->unknown_slot171(unknown_34)) {
                        Stop_Driver();
                        if (unknown_67a7a0()) {
                            return false;
                        }
                    } else {
                        bool stop = false;
                        Start_Of_Move(stop, true, false);
                        if (stop) {
                            return false;
                        }
                        if (!LinkedTo->unknown_7d) {
                            return false;
                        }
                        While_Moving(false);
                        if (!LinkedTo->unknown_7d) {
                            return false;
                        }
                    }
                } else if (LinkedTo->unknown_325) {
                    Stop_Driver();
                    unknown_50 = 0;
                } else if (LinkedTo->unknown_494 != 0) {
                    Move_To(LinkedTo->unknown_494->unknown_slot19(LinkedTo));
                }
            }
        }
    }
    if (Is_Moving_Now() && Frame % 8 == 0 && !LinkedTo->unknown_slot32()->Underwater && !LinkedTo->unknown_79
        && static_cast<CellClass *>(LinkedTo->unknown_slot105())->Land_Type() == 2 && Rules->unknown_09c != 0) {
        new AnimClass(Rules->unknown_09c, Object_Coord(LinkedTo), 0, 1, 0x600, 0);
    }
    if (unknown_34 == unknown_coord_ab91c8 && unknown_40 == unknown_coord_ab91c8 && LinkedTo->unknown_4d0 == -1 && LinkedTo->unknown_468 > 0.0) {
        LinkedTo->unknown_slot306(0.0);
    }
    return Is_Moving();
}
