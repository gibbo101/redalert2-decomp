// int InfantryClass::unknown_509110() (0x00509110; no callers in the
// executable: InfantryClass slot 304 expands the same steps inline)
// A standing soldier plays sequence 27 (deploy-fire) and the delay is that
// sequence's frame count; a moving one stops its locomotor, sets +0x5CC and
// waits the mission control's rate in frames plus 0..2.
#include "shared/infantry.hpp"
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref __real@8@4008e100000000000000=0079b608

int InfantryClass::unknown_509110()
{
    if (!Locomotor.Checked()->Is_Moving()) {
        unknown_slot311(27, 0, 0);
        return Type->DoControls[27].Count;
    }
    Locomotor.Checked()->Stop_Moving();
    unknown_5cc = true;
    int delay = (int)(Control()->unknown_10 * 900.0);
    return delay + unknown_id_source_a3d290->Random()(0, 2);
}
