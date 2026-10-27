// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapPreparation.hpp"
#include "assets/ResidentCellPreparation.hpp"
#include "assets/MapWallOwner.hpp"
namespace ra2 {
struct MapFinalizationCell {
    MapCellAttributes attributes;
    std::uint32_t field30=0;
    int wallOwner=-1;
    bool attachedTag=false;
};
struct MapFinalizationInputs {
    int width=0,height=0;
    std::span<const int> slots;
    ResidentCellInputs cell;
    std::span<const std::uint8_t> frames;
    std::span<const WallOwnerBuilding> buildings;
};
struct MapFinalizationServices {
    // Observers and supplied services must not mutate Cell/slot/type/registry
    // inputs. Lighting owns separate converter/light storage outside this record.
    std::function<void(int)> visit,initializeLighting,beforeResource,beforeRecalculation,beforeOwner;
    std::function<void(int,int)> afterResource,passabilityStore,ownerStore;
    std::function<void(int,MapPreparationField,std::uint32_t)> parentStore;
    std::function<void(int,MapAttributeField,std::uint32_t)> attributeStore;
    std::function<void(int,const MapCellAttributes&)> beforeLAT,beforePassability;
    std::function<void(int)> classifyQuery,missingResource;
    // Read-only candidate services; the differential fixture binds the actual
    // native Cell-target coordinate/distance helper. Height and construction
    // remain explicit supplied boundaries, not replacement parent algorithms.
    std::function<int(int,std::size_t)> buildingDistance,buildingOwner;
};
struct MapFinalizationResult {TileSweepCursor cursor;std::uint32_t resourceTotal=0;};
// Complete later two-pass parent on empty transient list/no tags/no occupants,
// with actual resource/Cell/LAT/passability/permission/TMP/wall-owner children.
// Canonical Cell input records must already be bound to world/slots. Lighting,
// candidate services, type/initial state/geometry/table construction are supplied.
// This does not execute original actor loading or the earlier overlay reader.
MapFinalizationResult finalizeResidentMap(const MapFinalizationInputs&,
    std::span<MapFinalizationCell>,MapCellAttributes& fallback,
    std::span<std::uint8_t> buffer4,std::span<std::uint8_t> buffer10,
    const MapFinalizationServices&);
}
