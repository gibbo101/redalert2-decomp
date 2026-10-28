// void ThemeClass::Stop(bool fade) -- 0x006E81A0
// Purpose: stops the playing theme: with `fade` and a sample attached the sample is faded out when that is
// possible (logged "- Fading"), otherwise it is stopped at once; the current, playing and queued themes
// are forgotten.
#include "shared/theme.hpp"
#include "shared/debug_printf.hpp"
#include "shared/sound_available.hpp"

// @ref ?unknown_sound_enabled_a40c18@@3DA=00a40c18
// @ref ?unknown_flag_a40d0c@@3DA=00a40d0c
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_stop_sample_407e60@@YIXPAX@Z=00407e60
// @ref ?unknown_sample_407f90@@YIHPAX@Z=00407f90
// @ref ?unknown_sample_407fe0@@YIXPAX@Z=00407fe0
// @ref ?unknown_sample_407ff0@@YIHPAX@Z=00407ff0
// @ref ??_C@_0BB@CDIM@Theme?3?3Stop?$CI?$CFd?$CJ?6?$AA@=007f83ec
// @ref ??_C@_0BK@GOIH@Theme?3?3Stop?$CI?$CFd?$CJ?5?9?5Fading?6?$AA@=007f8400

extern char unknown_sound_enabled_a40c18;
extern char unknown_flag_a40d0c;
void __fastcall unknown_stop_sample_407e60(void *sample);
int __fastcall unknown_sample_407f90(void *sample);
void __fastcall unknown_sample_407fe0(void *sample);
int __fastcall unknown_sample_407ff0(void *sample);

void ThemeClass::Stop(bool fade)
{
    if (!unknown_sound_enabled_a40c18 || !unknown_check_406f30() || unknown_flag_a40d0c || Current == -1) {
        return;
    }
    bool ready = false;
    if (fade && Sample != 0) {
        if (unknown_11 && !unknown_sample_407ff0(Sample)) {
            unknown_stop_sample_407e60(Sample);
        }
        ready = unknown_sample_407f90(Sample);
    }
    if (ready == true) {
        Debug_Printf("Theme::Stop(%d) - Fading\n", Score);
        if (Sample != 0) {
            unknown_sample_407fe0(Sample);
        }
        unknown_11 = true;
    } else {
        Debug_Printf("Theme::Stop(%d)\n", Score);
        if (Sample != 0) {
            unknown_stop_sample_407e60(Sample);
        }
    }
    Current = -1;
    Score = -1;
    Pending = -1;
}
