// bool ThemeClass::Still_Playing() const (0x006E82D0)
// The stream is still playing (one that should fade but no longer fades is
// stopped first).
#define THEME_CONTROL_RECORD
#include "shared/theme.hpp"
// @ref ?unknown_stop_sample_407e60@@YIXPAX@Z=00407e60
// @ref ?unknown_sample_407f90@@YIHPAX@Z=00407f90
// @ref ?unknown_sample_407ff0@@YIHPAX@Z=00407ff0

void __fastcall unknown_stop_sample_407e60(void *sample);
int __fastcall unknown_sample_407f90(void *sample);
int __fastcall unknown_sample_407ff0(void *sample);

bool ThemeClass::Still_Playing() const
{
    if (Sample != 0) {
        if (unknown_11 && !unknown_sample_407ff0(Sample)) {
            unknown_stop_sample_407e60(Sample);
        }
        return unknown_sample_407f90(Sample) != 0;
    }
    return false;
}
