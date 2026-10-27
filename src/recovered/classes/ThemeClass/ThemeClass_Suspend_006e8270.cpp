// void ThemeClass::Suspend() -- 0x006E8270 (name from the "Theme::Suspend(%d)" debug text)
// Purpose: when sound is enabled (0x00A40C18) and available (0x00406F30)
// and unknown_a40d0c is clear, stops the playing theme: logs it, stops its
// sample (0x00407E60) if one is attached, forgets the current theme and
// keeps it as the one to resume (+0x08).
// Assumptions: layout from this function (+0x00 current, +0x04 playing,
// +0x08 suspended, +0x2C sample); the object is Theme (0x00A35D78).
// @ref ?unknown_sound_enabled_a40c18@@3DA=00a40c18
// @ref ?unknown_flag_a40d0c@@3DA=00a40d0c
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_stop_sample_407e60@@YIXPAX@Z=00407e60
// @ref ??_C@_0BE@KPIN@Theme?3?3Suspend?$CI?$CFd?$CJ?6?$AA@=007f841c
#include "shared/debug_printf.hpp"
#include "shared/sound_available.hpp"

extern char unknown_sound_enabled_a40c18;
extern char unknown_flag_a40d0c;
void __fastcall unknown_stop_sample_407e60(void *sample);

class ThemeClass {
public:
    void Suspend();

    int Current;                    // +0x00
    int Playing;                    // +0x04
    int Suspended;                  // +0x08
    char unknown_0c[0x2C - 0x0C];
    void *Sample;                   // +0x2C
};

void ThemeClass::Suspend()
{
    if (unknown_sound_enabled_a40c18 && unknown_check_406f30() && !unknown_flag_a40d0c && Current != -1) {
        Debug_Printf("Theme::Suspend(%d)\n", Playing);
        if (Sample != 0) {
            unknown_stop_sample_407e60(Sample);
        }
        Current = -1;
        Suspended = Playing;
        Playing = -1;
    }
}
