// int ThemeClass::Play_Song(ThemeType theme) -- 0x006E7EB0 (name after Tiberian Sun)
// Purpose: starts `theme` now: the playing theme is stopped first unless it is the same one and still
// playing; a real theme with a volume above zero is opened on the sample (when the CD drive answers,
// or all files are local), otherwise it is queued.
#define THEME_CONTROL_RECORD
#include "shared/theme.hpp"
#include "shared/debug_printf.hpp"
#include "shared/sound_available.hpp"
#include "shared/cd.hpp"

// @ref ?unknown_sound_enabled_a40c18@@3DA=00a40c18
// @ref ?unknown_flag_a40d0c@@3DA=00a40d0c
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_stop_sample_407e60@@YIXPAX@Z=00407e60
// @ref ?unknown_sample_407f90@@YIHPAX@Z=00407f90
// @ref ?unknown_sample_407fe0@@YIXPAX@Z=00407fe0
// @ref ?unknown_sample_407ff0@@YIHPAX@Z=00407ff0
// @ref ?Audio_Stream_Open@@YIHPAUAudioStreamPlayer@@PBDH@Z=00407a90
// @ref ?Unknown_0046E4C0@@YIHH@Z=0046e4c0
// @ref ?IsLocal@CD@@2_NA=00850828
// @ref ?Theme@@3VThemeClass@@A=00a35d78
// @ref __makepath=007831f0
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_04KFC@?4WAV?$AA@=007f8338
// @ref ??_C@_0BB@CDIM@Theme?3?3Stop?$CI?$CFd?$CJ?6?$AA@=007f83ec
// @ref ??_C@_0BG@IALJ@Theme?3?3QueueSong?$CI?$CFd?$CJ?6?$AA@=007f83a4
// @ref ??_C@_0BK@EJAP@Theme?3?3PlaySong?$CI?$CFd?$CJ?5?9?5?$CFs?6?$AA@=007f83bc
// @ref ??_C@_09FMGB@Repeating?$AA@=007f83d8
// @ref ??_C@_07HIAE@Playing?$AA@=007f83e4

extern char unknown_sound_enabled_a40c18;
extern char unknown_flag_a40d0c;
void __fastcall unknown_stop_sample_407e60(void *sample);
int __fastcall unknown_sample_407f90(void *sample);
void __fastcall unknown_sample_407fe0(void *sample);
int __fastcall unknown_sample_407ff0(void *sample);
struct AudioStreamPlayer;
int __fastcall Audio_Stream_Open(AudioStreamPlayer *stream, char const *name, int raw);

int ThemeClass::Play_Song(ThemeType theme)
{
    if (unknown_sound_enabled_a40c18 && unknown_check_406f30() && !unknown_flag_a40d0c) {
        if (Still_Playing() && Score == theme) {
            return Current;
        }
        Stop();
        unknown_11 = false;
        if (theme != THEME_NONE && theme != -3) {  // -3: Tiberian Sun's THEME_QUIET
            if (theme > THEME_NONE && Volume > 0) {
                Score = theme;
                int cd = CD::IsLocal ? 0 : Unknown_0046E4C0(0);
                if (Sample != 0 && cd > -1) {
                    Audio_Stream_Open((AudioStreamPlayer *)Sample, Theme_File_Name(theme), true);
                    Current = theme;
                } else {
                    Current = THEME_NONE;
                    if (Sample != 0 && cd <= -1 && Pending == THEME_NONE) {
                        Theme.Queue_Song(theme);
                    }
                }
                Debug_Printf("Theme::PlaySong(%d) - %s\n", Score, IsRepeat == true || Themes[theme]->unknown_289 == true ? "Repeating" : "Playing");
                if (IsRepeat == true || Themes[theme]->unknown_289 == true) {
                    Pending = theme;
                }
            } else {
                Pending = theme;
            }
        }
    }
    return Current;
}
