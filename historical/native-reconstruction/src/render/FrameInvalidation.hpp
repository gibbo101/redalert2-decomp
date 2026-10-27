// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/Composition.hpp"
#include <functional>
namespace ra2 {
struct FrameInvalidationObject {
    std::function<int()> type2c;
    std::uint8_t& redraw75;
    std::function<const PixelRect&()> bounds124;
    std::function<void()> cleared;
};
struct FrameInvalidationRegistry {
    std::function<std::int32_t()> count;
    std::function<FrameInvalidationObject(std::int32_t)> at;
};
// Complete6AA090. Register receives the original relative bounds by value and
// flag0. The actor byte clears after registration even if its queue rejects it.
void invalidateFrameBuildings(PixelRect requested,const PixelPoint& screenOffset,
    const FrameInvalidationRegistry&,const std::function<void(PixelRect,std::uint8_t)>& registerDirty);
}
