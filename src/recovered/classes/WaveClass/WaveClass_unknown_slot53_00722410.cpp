// bool WaveClass::unknown_slot53(CoordStruct const *coord, int dir) (0x00722410)
// Places the wave at the coordinate (while the game runs, when it was
// taken off the map), marks it mapped and submits it to the layer lists.
#include "shared/wave.hpp"
// @ref ?Submit@MouseClass@@QAEXPAVObjectClass@@@Z=00499a40
// @ref ?Submit@UnknownList832470@@QAE_NPAVObjectClass@@_N@Z=0053e330
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

bool WaveClass::unknown_slot53(CoordStruct const *coord, int dir)
{
    if (unknown_flag_a40958 && unknown_76 && !unknown_74) {
        if (unknown_a40774 == 0 && unknown_slot101(&Map[*coord], -1, coord->Z, 0, 1) != 0) {
            return false;
        }
        unknown_76 = false;
        unknown_75 = false;
        unknown_slot103(*coord);
        if (unknown_slot71(1)) {
            if (unknown_7d) {
                if (unknown_slot29() != -1) {
                    Map.Submit(this);
                }
                unknown_list_832470.Submit(this, false);
            }
            return true;
        }
    }
    return false;
}
