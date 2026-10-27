// bool WaveClass::unknown_slot52() (0x007224D0, slot 52)
// While the game runs (0x00A40958) and the wave is placed: slots 54(1) and
// 71(0), off the map and the 0x00832470 list, slot 69; then marks it removed.
#include "shared/wave.hpp"
// @ref ?Remove@MouseClass@@QAEXPAVObjectClass@@@Z=00499a90
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Remove@UnknownList832470@@QAEXPAVObjectClass@@@Z=0053e370
// @ref ?unknown_list_832470@@3VUnknownList832470@@A=00832470
// @ref ?unknown_flag_a40958@@3_NA=00a40958

bool WaveClass::unknown_slot52()
{
    if (unknown_flag_a40958 && !unknown_76) {
        unknown_slot54(1);
        unknown_slot71(0);
        Map.Remove(this);
        unknown_list_832470.Remove(this);
        unknown_slot69();
        unknown_76 = true;
        unknown_75 = false;
        return true;
    }
    return false;
}
