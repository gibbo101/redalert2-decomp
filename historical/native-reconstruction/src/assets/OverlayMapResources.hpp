// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapOverlay.hpp"
#include "assets/OverlayPlacement.hpp"

namespace ra2 {
struct OverlayMapResourceInputs {
    std::span<const OverlayTypeInputs> overlays;
    std::span<const MapResourceType> resources;
    std::span<const std::uint8_t> frames;
    std::array<MapInputPosition,8> directions{};
};
struct OverlayMapResourceServices {
    std::function<OverlayPlacementCell&(MapInputPosition)> cell;
    std::function<void(int)> classifyQuery,missing;
    std::function<void(OverlayPlacementCell&,std::uint8_t)> store;
};
// Bind the argument-zero resource child to the same evolving Cells used by
// decoded overlay placement. Registries, image/index association, directions,
// frame table and initial state remain supplied; no growth or random replacement.
int updateLoadedMapResource(OverlayPlacementCell&,const OverlayMapResourceInputs&,
    const OverlayMapResourceServices&);
}
