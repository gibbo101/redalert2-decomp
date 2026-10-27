// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/OverlayMapPreparation.hpp"
#include "assets/OverlayMapResources.hpp"
#include "assets/ResidentCellPreparation.hpp"

namespace ra2 {
struct ResidentOverlayServices {
    // Reader, lifetime, wall bounds/queues and selected-store observers retain
    // their earlier boundaries. Resource/recalculation effects are bound here.
    OverlayMapPreparationServices overlay;
    // Stable association with canonical terrain input records. Initial selected
    // overlay/data/slope/passability/position values must already agree.
    std::function<MapCellAttributes&(OverlayPlacementCell&)> attributes;
    std::function<void(OverlayPlacementCell&,int)> beforeResource,afterResource,beforeRecalculation;
    std::function<void(int)> classifyQuery,missingResource;
    std::function<void(OverlayPlacementCell&,MapAttributeField,std::uint32_t)> attributeStore;
    std::function<void(OverlayPlacementCell&,int)> passabilityStore;
};
// Join the decoded reader/placement/wall/lifetime path to actual resource and
// resident Cell children. Forward each shared store before observers or later
// lookups; never reconcile stale copies only after a child returns. Canonical
// world records, type/resource initialization, geometry, buffers and services
// remain supplied. This is not the later two-pass map-preparation parent.
void prepareResidentMapOverlays(int version,int width,int height,bool filterCrates,
    std::span<const OverlayTypeInputs>,OverlayMapPreparationState&,
    const OverlayMapPreparationInputs&,OverlayPlacementCell& fallback,
    const ResidentCellInputs&,std::span<const std::uint8_t> frames,
    std::span<std::uint8_t> buffer4,std::span<std::uint8_t> buffer10,
    const ResidentOverlayServices&);
}
