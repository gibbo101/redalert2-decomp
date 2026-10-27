// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
namespace ra2 {
struct CellDirtyEffectInput {
    std::int32_t overlay44=-1;
    std::uint8_t overlayData11e=0;
    std::uint8_t slope11c=0;
    std::uint32_t flags140=0;
    bool hasPrimaryResident=false;
};
enum class CellDirtyEffectExit : std::uint8_t {Overlay,OverlayData,Slope,Flags,Empty};
// Exact early-return prefix of base47BB30. The resident-bearing effect remains
// outside this bounded kernel and is explicitly refused.
CellDirtyEffectExit applyCellDirtyEffectPrefix(const CellDirtyEffectInput&);
}
