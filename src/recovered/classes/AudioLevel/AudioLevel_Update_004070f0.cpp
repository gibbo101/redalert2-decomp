// Fixed-point audio ramp, original0x004070F0.
#include "shared/audio.hpp"
int __fastcall AudioLevel::Update()
{
    int remaining = (int)(Target - Current);
    if (remaining != 0) {
        if (Flags & AUDIO_LEVEL_PENDING) {
            Current = Target;
        } else {
            unsigned __int64 now = Audio_Now();
            unsigned __int64 elapsed = now - (unsigned __int64)LastTime;
            LastTime = now;
            if (elapsed > (unsigned __int64)MaxElapsed) elapsed = MaxElapsed;
            int movement = (int)(Step * (unsigned int)elapsed);
            if (remaining < 0) {
                if (movement > -remaining) Current += remaining;
                else Current -= movement;
            } else {
                if (movement > remaining) Current += remaining;
                else Current += movement;
            }
        }
        unsigned int changed_flags = Flags;
        changed_flags |= AUDIO_LEVEL_CHANGED;
        Flags = changed_flags;
        return 1;
    }
    return 0;
}
