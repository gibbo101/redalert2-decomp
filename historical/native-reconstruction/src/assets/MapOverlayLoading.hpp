// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellInputs.hpp"
#include "assets/MapWallUpdate.hpp"
#include "assets/OverlayTypeInputs.hpp"
#include <optional>

namespace ra2 {
enum class OverlayMapPack {Types,Data};
struct OverlayLoadCell : MapWallCell {};
// Full-map diamond permission, distinct from visible/elevation permission.
bool overlayMapPositionPermitted(MapInputPosition,int width,int height);
struct OverlayMapLoadServices {
    // Signed original section-read result and decoded byte stream. Parser,
    // buffer/filter construction and LCW decompression are separate boundaries.
    std::function<int(OverlayMapPack,unsigned)> section;
    std::function<std::optional<std::uint8_t>(OverlayMapPack)> read;
    std::function<OverlayLoadCell&(MapInputPosition)> cell;
    std::function<bool()> allocate;
    // Original temporary Overlay construction/Unlimbo effects stay supplied.
    std::function<void(unsigned,MapInputPosition,int)> construct;
    std::function<void(OverlayLoadCell&,std::uint8_t)> store;
    std::function<void()> cleanup;
    // Diagnostic observers; do not mutate supplied state.
    std::function<void(unsigned)> imageQuery;
    std::function<void(MapInputPosition,bool)> permissionQuery;
};
// Complete parent control flow, ordinary supplied resident/no-demand image
// getters and empty transient cleanup. Never equate the constructor service
// with recovered original placement. Runtime/map integration remains separate.
void loadDecodedMapOverlays(int version,int width,int height,bool filterCrates,
    std::span<const OverlayTypeInputs>,const OverlayMapLoadServices&);
}
