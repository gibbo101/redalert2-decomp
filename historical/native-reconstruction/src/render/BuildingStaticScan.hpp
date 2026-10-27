// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/FrameInvalidation.hpp"
namespace ra2 {
struct BuildingStaticObject {
    FrameInvalidationObject frame;
    const std::uint8_t& hidden5b7;
    std::function<void(PixelRect,std::int32_t,std::int32_t)> drawFc;
};
struct BuildingStaticRegistry {
    std::function<std::int32_t()> count;
    std::function<BuildingStaticObject(std::int32_t)> at;
};
// Complete6A9F60. Bounds/drawing remain explicit children; no scheduling or
// pixel-fidelity claim. Clip is reread for the copied drawing argument, viewport
// offset is saved before bounds, count/backing are live on each iteration.
void scanStaticBuildings(const PixelRect& dirty,const PixelRect& clip,std::int32_t force,
    const std::function<PixelPoint()>& offset,const std::function<std::uint8_t()>& bypass,
    const BuildingStaticRegistry&);
}
