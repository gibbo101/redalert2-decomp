// void __fastcall Audio_Level_Set_Combine(AudioLevelSet *set, AudioLevelSet *other) -- 0x004010C0
// Purpose: combines another level set into this one: volume and frequency
// multiply (16.16 values; 0x4000 and 100 are unity), the pan moves by the
// other's offset from centre, clamped to 0..0x4000.
#include "shared/audio.hpp"

void __fastcall Audio_Level_Set_Combine(AudioLevelSet *set, AudioLevelSet *other)
{
    set->Volume.Set(((other->Volume.Current >> 16) * (set->Volume.Current >> 16)) >> 14);
    set->Volume.Update();
    set->Frequency.Set((int)((other->Frequency.Current >> 16) * (set->Frequency.Current >> 16)) / 100);
    set->Frequency.Update();
    int pan = (other->Pan.Current >> 16) - 0x2000;
    if (pan != 0) {
        pan += set->Pan.Current >> 16;
        if (pan < 0) {
            pan = 0;
        } else if ((unsigned)pan > 0x4000) {
            pan = 0x4000;
        }
        set->Pan.Set(pan);
    }
    set->Pan.Update();
}
