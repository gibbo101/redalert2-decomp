// 004499D0: gate mission state machine.
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/tactical.hpp"
#include "shared/rules.hpp"
#include "shared/progress_timer.hpp"
#include "shared/sound_play.hpp"
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref _unknown_id_source_a3d290=00a3d290
// @ref __real@8@4008e100000000000000=0079b608
int BuildingClass::unknown_slot143()
{
    CoordStruct closing_position;
    if (Type->Gate) {
        switch (unknown_a8) {
        case 0:
            if (unknown_2a8.unknown_496b30()) {
                GateTimer = (int)(Type->GateCloseDelay * 900.0);
                unknown_a8 = 2;
            } else {
                if (!unknown_2a8.unknown_496a90()) {
                    if (unknown_2a8.unknown_496ab0()) {
                        unknown_2a8.Reverse_00496C10();
                    } else {
                        unknown_2a8.unknown_496b70(Type->DeployTime);
                        CoordStruct position = Coord;
                        Voc_Play_At(Rules->GateDown, position, 0);
                        unknown_tactical_83996c->Register_Dirty_Area(unknown_slot73(), 0);
                    }
                }
                unknown_a8 = 1;
                GateTimer = ProgressTimerClass<FrameTimerClass>((int)(Type->GateCloseDelay * 900.0));
                return 0;
            }
            break;
        case 3:
            unknown_2a8.unknown_496bc0(Type->DeployTime);
            unknown_a8 = 4;
            closing_position = Coord;
            Voc_Play_At(Rules->GateUp, closing_position, 0);
            return 0;
        case 2:
            if (!unknown_449930()) {
                if (GateTimer.Progress() == 1.0) unknown_a8 = 3;
            } else {
                GateTimer = ProgressTimerClass<FrameTimerClass>((int)(Type->GateCloseDelay * 900.0));
            }
            break;
        case 1:
            if (unknown_2a8.unknown_496b30()) unknown_a8 = 2;
            // Fall through to the animation refresh.
        case 4:
            if (unknown_2a8.unknown_496b50()) {
                unknown_slot261(false, true);
                unknown_a8 = 5;
                unknown_75 = true;
            }
            if (unknown_2a8.unknown_496a90() || unknown_2a8.unknown_496ab0() || unknown_2a8.unknown_496b30()) {
                int stage = (int)(unknown_2a8.Progress_00496C70() * Type->GateStages);
                if (stage != unknown_5c7) {
                    unknown_5c7 = (char)stage;
                    unknown_75 = true;
                }
            }
            return 0;
        }
        int delay = (int)(Control()->unknown_10 * 900.0);
        return delay + unknown_id_source_a3d290->Random()(0, 2);
    }
    unknown_slot116(5, false);
    return 1;
}

