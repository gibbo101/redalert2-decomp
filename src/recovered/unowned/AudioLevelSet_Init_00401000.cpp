// void AudioLevelSet::Init() (0x00401000)
// Starts the three levels at full volume (0x4000), 100% frequency and the
// centre pan (0x2000) and sets their ramp rates (frequency 10 per second,
// volume and pan 0x4000 per second), then jumps the volume to full.
#include "shared/audio.hpp"

void __fastcall AudioLevelSet::Init()
{
    Volume.Init(0x4000);
    Frequency.Init(100);
    Pan.Init(0x2000);
    Frequency.Set_Rate(1000, 10);
    Volume.Set_Rate(1000, 0x4000);
    Pan.Set_Rate(1000, 0x4000);
    Volume.Set(0x4000);
}
