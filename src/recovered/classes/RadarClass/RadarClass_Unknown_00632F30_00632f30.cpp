// void RadarClass::Unknown_00632F30(bool on, bool sound) (0x00632F30)
// Switches the radar on (state 3, from off or deactivated) or off (state 2),
// clearing its list at +0x14BC, with the rules' activate/deactivate sound.
#include "shared/radar.hpp"
#include "shared/object.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_00406070@UnknownList14BC@@QAEXXZ=00406070
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0BD@FFAB@Radar?3?5ACTIVATING?6?$AA@=007ee310
// @ref ??_C@_0BD@LLJP@Radar?3?5DEACTIVING?6?$AA@=007ee2fc

// Not expanded into its callers in the original (kept out of line).
#pragma auto_inline(off)
void RadarClass::Unknown_00632F30(bool on, bool sound)
{
    if (on == true) {
        if (unknown_14a8 == 0 || unknown_14a8 == 2) {
            unknown_14a8 = 3;
            unknown_14bc.Unknown_00406070();
            if (sound) {
                Voc_Play(Rules->unknown_610, 1.0f, 0x2000, 0);
            }
            Debug_Printf("Radar: ACTIVATING\n");
        }
    } else {
        unknown_14bc.Unknown_00406070();
        unknown_14a8 = 2;
        if (sound) {
            Voc_Play(Rules->unknown_614, 1.0f, 0x2000, 0);
        }
        Debug_Printf("Radar: DEACTIVING\n");
    }
}
#pragma auto_inline(on)
