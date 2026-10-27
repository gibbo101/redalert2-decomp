// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/Composition.hpp"
#include "render/UnitTypeVisibility.hpp"
#include <functional>
namespace ra2 {
std::uint32_t unitDisguiseDrawFlags(const UnitDisguiseState&,int currentFrame,
                                  std::uint32_t flags,const std::function<bool()>& ownerVisible);
// Initialized converter, original mask 0x3000, flags 0x2800 plus bits 1..3.
// Returns a converter slot offset, not a host pointer or converter ownership.
unsigned unitSurfaceBlitterSlot(std::uint32_t flags);
struct UnitSurfaceInputs {
    PixelPoint point{};
    PixelRect clip{},dirty{};
    int brightness=0,layerFourValue=0;
    std::uint8_t typeBAE=0; // Nonzero alternate two-part path remains unsupported.
};
struct UnitSurfaceRequest {
    PixelRect destination{},source{},sourceBounds{},clip{};
    std::uint32_t blitter=0;
    int depth=0,gradient=0,brightness=0,extra=0;
};
struct UnitSurfaceServices {
    std::function<int()> layer,layerFourExtra,gradient,depth;
    std::function<std::uint8_t()> flag204,flag205,disguised;
    std::function<bool()> ownerVisible;
    std::function<std::uint32_t(std::uint32_t)> disguiseFlags,houseBlitter;
    std::function<PixelRect()> sourceBounds;
    std::function<void(const UnitSurfaceRequest&)> draw;
};
// Ordinary complete Unit final wrapper with type +0xBAE zero. Read-only services
// and immutable inputs; actor construction, alternate split, ownership and full
// frame scheduling are not implied. The final child owns clipping/span behavior.
void drawOrdinaryUnitSurface(const UnitSurfaceInputs&,const UnitSurfaceServices&);
}
