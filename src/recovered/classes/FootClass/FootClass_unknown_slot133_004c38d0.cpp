// int FootClass::unknown_slot133() (0x004C38D0)
// A stopped unit without a pending mission and nothing at +0x494 gives up
// (slot 261) and is called again next frame; otherwise the mission's rate
// in frames (minutes times 900) plus a random 0..2.
#include "shared/foot.hpp"
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref __real@8@4008e100000000000000=0079b608
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

int FootClass::unknown_slot133()
{
    if (unknown_494 == 0 && !Locomotor.Checked()->Is_Moving() && MissionQueue == -1) {
        unknown_slot261(0, true);
        return 1;
    }
    int delay = (int)(Control()->unknown_10 * 900.0);
    return delay + unknown_id_source_a3d290->Random()(0, 2);
}
