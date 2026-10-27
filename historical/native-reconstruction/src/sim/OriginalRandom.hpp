// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <array>
#include <cstdint>
namespace ra2 {
// Supplied state for the recovered 250-word XOR generator step. Seeding and
// association with the original global/scenario generators are separate.
struct OriginalRandomState {
    std::uint8_t disabled=0;
    int next1=0,next2=103;
    std::array<std::uint32_t,250> table{};
};
std::uint32_t nextOriginalRandom(OriginalRandomState&);
}
