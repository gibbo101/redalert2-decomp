// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Facing.hpp"
#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace ra2 {
// Recovered skirmish policy: slider 0..6 maps to 6..0 clock quanta; the original
// coarse clock is uint32(timeGetTime()) >> 4. Network/campaign scheduling differs.
constexpr std::uint32_t originalClock(std::uint32_t milliseconds) {return milliseconds>>4;}
inline int frameDelay(int slider) {
    if(slider<0||slider>6) throw std::invalid_argument("Game speed must be 0..6");
    return 6-slider;
}
struct FrameTimer {
    std::int32_t start=-1,duration=0;
    std::int32_t remaining(std::uint32_t milliseconds) const {
        if(start==-1) return duration;
        const auto elapsed=signed32(originalClock(milliseconds)-std::uint32_t(start));
        return elapsed>=duration?0:signed32(std::uint32_t(duration)-std::uint32_t(elapsed));
    }
};
class FramePacer {
    FrameTimer timer_;
    int speed_=3; // Original Options constructor default is delay 3 (slider 3).
    bool armed_=false,paused_=false;
public:
    explicit FramePacer(int speed=3) {setSpeed(speed);}
    void setSpeed(int speed) {(void)frameDelay(speed);speed_=speed;}
    int speed() const {return speed_;}
    bool ready(std::uint32_t now) const {return !paused_&&(!armed_||timer_.remaining(now)==0);}
    void begin(std::uint32_t now) {timer_={std::int32_t(originalClock(now)),frameDelay(speed_)};armed_=true;}
    // Original wait passes remaining coarse ticks as a millisecond Sleep argument.
    // Host event/render services are separate; no overdue-update catch-up loop.
    std::uint32_t sleepHint(std::uint32_t now) const {
        if(paused_) return 8;
        return armed_?std::uint32_t(std::max(0,timer_.remaining(now))):0;
    }
    void pause(bool paused) {
        if(paused_&&!paused) armed_=false; // Explicit host resume policy: no backlog.
        paused_=paused;
    }
    void reset() {armed_=false;}
};
}
