// void ThemeClass::AI() -- 0x006E7CD0 (name hypothesis after the "Theme::AI" debug text)
// Purpose: when sound is enabled and the volume is above zero, lets a playing sample run on (a fading one
// is stopped first once its fade has ended); with nothing playing, starts the queued theme: -2 picks the
// next one (0x006E7D80), -1 and -3 start nothing, and a live-object count other than zero holds the music
// back. The queue is cleared to -2 after the start.
#include "shared/theme.hpp"
#include "shared/debug_printf.hpp"
#include "shared/sound_available.hpp"
#include "shared/unknown_globals.hpp"

// @ref ?unknown_sound_enabled_a40c18@@3DA=00a40c18
// @ref ?unknown_flag_a40d0c@@3DA=00a40d0c
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_stop_sample_407e60@@YIXPAX@Z=00407e60
// @ref ?unknown_sample_407f90@@YIHPAX@Z=00407f90
// @ref ?unknown_sample_407fe0@@YIXPAX@Z=00407fe0
// @ref ?unknown_sample_407ff0@@YIHPAX@Z=00407ff0
// @ref ??_C@_0BL@CLMO@Theme?3?3AI?$CINext?5song?5?$DN?5?$CFd?$CJ?6?$AA@=007f8388
// @ref ?Pick_Next_Song@ThemeClass@@QAEHH@Z=006e7d80
// @ref ?Play_Song@ThemeClass@@QAEHH@Z=006e7eb0
// @ref ?unknown_a40774@@3HA=00a40774

extern char unknown_sound_enabled_a40c18;
extern char unknown_flag_a40d0c;
void __fastcall unknown_stop_sample_407e60(void *sample);
int __fastcall unknown_sample_407f90(void *sample);
int __fastcall unknown_sample_407ff0(void *sample);

void ThemeClass::AI()
{
    if (unknown_check_406f30() && !unknown_flag_a40d0c && unknown_sound_enabled_a40c18 && Volume > 0) {
        bool ready = false;
        if (Sample != 0) {
            if (unknown_11 && !unknown_sample_407ff0(Sample)) {
                unknown_stop_sample_407e60(Sample);
            }
            ready = unknown_sample_407f90(Sample);
        }
        if (ready) {
            return;
        }
        ThemeType theme = Pending;
        if (theme != -1 && theme != -3 && unknown_a40774 == 0) {
            if (theme == -2) {
                Pending = Pick_Next_Song(Score);
                Debug_Printf("Theme::AI(Next song = %d)\n", Pending);
            }
            Play_Song(Pending);
            Pending = -2;
        }
    }
}
