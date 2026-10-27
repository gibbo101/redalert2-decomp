// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <algorithm>
#include <cstdint>
#include <cstdlib>

namespace ra2 {
// Recovered from the fingerprinted base RA2 GAME.EXE; see docs/RECOVERY.md.
// Deliberately preserves x86 truncation order and 16-bit angular wrapping.
constexpr int signed16(std::uint16_t n) { return n < 0x8000 ? n : int(n) - 0x10000; }
constexpr std::int32_t signed32(std::uint32_t n) {
    return n < 0x80000000u ? std::int32_t(n) : std::int32_t(std::int64_t(n) - 0x100000000LL);
}
struct Facing {
    std::uint16_t desired = 0, start = 0;
    std::int32_t timerStart = 0, duration = 0;
    std::uint16_t rate = 0;
    void setRate(int rot) { rate = std::uint16_t(std::uint32_t(std::min(rot,127)) << 8); }
    int difference() const { return signed16(std::uint16_t(desired - start)); }
    std::int32_t left(std::int32_t tick) const {
        if (timerStart == -1) return duration;
        const auto elapsed = signed32(std::uint32_t(tick) - std::uint32_t(timerStart));
        return elapsed >= duration ? 0 : signed32(std::uint32_t(duration) - std::uint32_t(elapsed));
    }
    bool rotating(std::int32_t tick) const { return signed16(rate) > 0 && left(tick) != 0; }
    std::uint16_t current(std::int32_t tick) const {
        if (!rotating(tick)) return desired;
        const int diff = difference();
        const int steps = signed16(std::uint16_t(std::abs(diff) / signed16(rate)));
        if (steps <= 0) return desired;
        // The original executes IDIV, THEN IMUL. Do not rearrange this expression.
        const auto decrement = std::uint32_t(diff / steps) * std::uint32_t(left(tick));
        return std::uint16_t(std::uint32_t(desired) - decrement);
    }
    bool setDesired(std::uint16_t value, std::int32_t tick) {
        if (desired == value) return false;
        start = current(tick);
        desired = value;
        if (signed16(rate) > 0) {
            timerStart = tick;
            duration = std::abs(difference()) / signed16(rate);
        }
        return true;
    }
    bool setCurrent(std::uint16_t value, std::int32_t tick) {
        const bool changed = current(tick) != value;
        if (changed) desired = start = value;
        timerStart = tick;
        duration = 0;
        return changed;
    }
};
}
