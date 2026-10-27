// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <stdexcept>

namespace ra2 {
struct MissionAudioServices {
    // Base713DB0 and7158C0 remain named audio children. Keep the exact raw
    // arguments at this dispatcher boundary; playback and audio state are not
    // implemented here.
    std::function<void(std::int32_t,std::int32_t,std::uint32_t,const void*)> playSound;
    std::function<void(std::int32_t,std::int32_t,std::int32_t)> playSpeech;
};

// Complete base action19 branch6AE961..6AE980 around its named sound child.
inline bool executeMissionSoundAction(std::int32_t soundIndex,const MissionAudioServices& services) {
    if(!services.playSound)throw std::invalid_argument("Mission sound service required");
    services.playSound(soundIndex,0x2000,0x3f800000u,nullptr);
    return true;
}

// Complete base action21 branch6AEAD3..6AEAED around its named speech child.
inline bool executeMissionSpeechAction(std::int32_t speechIndex,const MissionAudioServices& services) {
    if(!services.playSpeech)throw std::invalid_argument("Mission speech service required");
    services.playSpeech(speechIndex,2,-1);
    return true;
}
}
