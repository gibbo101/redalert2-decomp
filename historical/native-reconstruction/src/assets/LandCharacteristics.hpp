// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <array>
#include <cstdint>
#include <functional>

namespace ra2 {
enum class LandSpeed : unsigned {Foot, Track, Wheel, Hover, Winged, Float, Amphibious, FloatBeach};
inline constexpr std::array<const char*,12> landSections{
    "Clear","Road","Water","Rock","Wall","Tiberium","Beach","Rough","Ice","Railroad","Tunnel","Weeds"};
inline constexpr std::array<const char*,8> landSpeedKeys{
    "Foot","Track","Wheel","Hover","Winged","Float","Amphibious","FloatBeach"};
struct LandCharacteristic {
    std::array<float,8> speed{};
    std::uint8_t buildable=0;
};
struct LandCharacteristicServices {
    std::function<bool(unsigned)> hasSection;
    std::function<double(unsigned,LandSpeed,double)> readSpeed;
    std::function<std::uint8_t(unsigned,std::uint8_t)> readBuildable;
    // Field 0..7 identifies a speed; field 8 is the one-byte Buildable store.
    std::function<void(unsigned,unsigned,std::uint32_t)> store;
};
// Complete assignment parent on supplied INI results and initial table state.
// Preserve the caller's FP rounding mode: the original parent does not set it.
// Text parsing, static initialization and rules layering remain separate.
void loadLandCharacteristics(std::array<LandCharacteristic,12>&,
    const LandCharacteristicServices&);
}
