// void ThemeClass::Queue_Song(ThemeType theme) -- 0x006E7E20
// Purpose: remembers the theme to play next (+0x08); a real theme other than the current one is logged and,
// while a sample is attached, fades it out (a fade that has ended is stopped first).
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
// @ref ??_C@_0BG@IALJ@Theme?3?3QueueSong?$CI?$CFd?$CJ?6?$AA@=007f83a4

extern char unknown_sound_enabled_a40c18;
extern char unknown_flag_a40d0c;
void __fastcall unknown_stop_sample_407e60(void *sample);
int __fastcall unknown_sample_407f90(void *sample);
void __fastcall unknown_sample_407fe0(void *sample);
int __fastcall unknown_sample_407ff0(void *sample);

void ThemeClass::Queue_Song(ThemeType theme)
{
    if (unknown_sound_enabled_a40c18 && unknown_check_406f30() && !unknown_flag_a40d0c) {
        Pending = theme;
        if (theme != -1 && theme != -2 && theme != Score) {
            Debug_Printf("Theme::QueueSong(%d)\n", theme);
            bool ready = false;
            if (Sample != 0) {
                if (unknown_11 && !unknown_sample_407ff0(Sample)) {
                    unknown_stop_sample_407e60(Sample);
                }
                ready = unknown_sample_407f90(Sample);
            }
            if (ready == true) {
                if (Sample != 0) {
                    unknown_sample_407fe0(Sample);
                }
                unknown_11 = true;
            }
        }
    }
}
