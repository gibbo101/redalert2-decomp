// void AudioLevelSet::Update() (0x00401080)
// Advances the volume, frequency and pan levels (each AudioLevel::Update
// 0x004070F0; the last is a tail call).
// @ref ?Update@AudioLevel@@QAIHXZ=004070f0
#include "shared/audio.hpp"

void AudioLevelSet::Update()
{
    Volume.Update();
    Frequency.Update();
    Pan.Update();
}
