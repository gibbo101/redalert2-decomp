// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/PreparedUnitMembership.hpp"
#include "assets/ResidentMapFinalization.hpp"
#include <memory>
namespace ra2 {
// Host snapshot of prepared inputs. Image bytes remain borrowed from keepAlive;
// all mutable Cells, buffers, fallback and lazy state are private to this owner.
struct UnitMapSeed {
    std::span<const MapFinalizationCell> cells;
    std::span<const int> slots;
    const MapCellAttributes& fallback;
    const MapFloorHeightState& floor;
    ResidentCellInputs resident;
    std::span<const std::uint8_t> buffer4,buffer10;
    int width=0,height=0,levelHeight=104;
};
class MutableUnitMap {
    std::shared_ptr<const void> keepAlive_;
    std::array<int,16> landMap_;
    std::array<float,11> wheelSpeeds_;
    std::vector<MapTileAttributes> tiles_;
    std::vector<MapOverlayType> overlays_;
    std::vector<MapResourceType> resources_;
public:
    std::vector<MapFinalizationCell> cells;
    std::vector<MapCellAttributes*> attributes;
    std::vector<MapCellInput*> table;
    std::vector<int> slots;
    MapCellAttributes fallback;
    MapFloorHeightState floor;
    ResidentCellInputs resident;
    Bytes buffer4,buffer10;
    int width,height,levelHeight;
    explicit MutableUnitMap(UnitMapSeed,std::shared_ptr<const void> keepAlive={});
    MutableUnitMap(const MutableUnitMap&)=delete;
    MutableUnitMap& operator=(const MutableUnitMap&)=delete;
    std::unique_ptr<MutableUnitMap> clone() const;
    PreparedMembershipMap input();
    // Read-only validation; missing/fallback identities are not promoted.
    const MapCellAttributes* find(const MapCellInput&) const;
};
}
