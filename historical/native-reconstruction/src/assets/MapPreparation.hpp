// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellAttributes.hpp"
#include "assets/TileSweep.hpp"
#include "assets/MapCellChildren.hpp"
#include "assets/LandCharacteristics.hpp"

namespace ra2 {
struct MapPreparationCell {
    MapCellAttributes attributes;
    std::uint32_t field30 = 0;
    bool attachedTag = false;
};
enum class MapPreparationField {Field30, Flags};
struct MapPreparationServices {
    // Lighting remains in the presentation layer. Recalculation may nest the
    // recovered LAT/passability children using the evolving shared map state.
    std::function<void(int)> initializeLighting;
    std::function<void(int, int)> recalculate;
    std::function<void(int, MapPreparationField, std::uint32_t)> store;
    std::function<void(int)> visit; // Both passes, including each terminal -1.
};
// Complete ordinary cell-preparation parent: no preexisting transient actors,
// attached tags or overlays/resources/walls. Those branches are refused rather
// than supplying replacement behavior. Pointer-table/storage construction and
// child services remain explicit; the helper is independent of SDL/rendering.
TileSweepCursor prepareMapCells(int width, std::span<const int> slots,
    std::span<MapPreparationCell> cells, const MapPreparationServices&);

struct ResidentMapPreparationInputs {
    int width=0, height=0;
    MapPermissionShape permission;
    std::span<const int> slots;
    std::span<const MapTileAttributes> tiles;
    std::array<int,16> landMap{};
    MapLATSettings lat{};
    std::array<MapInputPosition,8> directions{};
    std::array<LandCharacteristic,12> land{};
    std::uint8_t cliffMode=0;
};
struct ResidentMapPreparationServices {
    std::function<void(int)> initializeLighting, visit;
    std::function<void(int,MapPreparationField,std::uint32_t)> parentStore;
    std::function<void(MapInputPosition)> query, fallbackStore;
    std::function<void(int)> beforeRecalculation, beforeLAT, beforePassability;
    std::function<void(int,int)> passabilityStore;
    std::function<void(int,MapAttributeField,std::uint32_t)> attributeStore;
};
// Bind the verified ordinary parent to actual native LAT/passability/permission/
// resident-TMP children over evolving shared Cells. Geometry, type/image records,
// land records and initial state are supplied. Use the Wheel column, not Foot.
// Lighting remains outside assets. This is not the complete scenario loader.
TileSweepCursor prepareResidentMapCells(const ResidentMapPreparationInputs&,
    std::span<MapPreparationCell>, MapCellInput& fallback,
    std::span<std::uint8_t> buffer4, std::span<std::uint8_t> buffer10,
    const ResidentMapPreparationServices&);
}
