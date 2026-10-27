// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/OverlayObjectLifetime.hpp"

namespace ra2 {
struct PreparedOverlayObject {
    TransientMapOverlay actor;
    OverlayObjectBase base;
};
struct OverlayMapPreparationState {
    // Native diagnostic storage/handles. A released record remains inspectable;
    // original heap ownership and destruction of base registrations are supplied.
    std::vector<PreparedOverlayObject> objects;
    std::array<OverlayTransientRegistry,6> registries;
    int placementFlag=-1;
    std::uint32_t identityCounter=0;
};
struct OverlayMapPreparationInputs {
    MapInputPosition invalidCell{};
    Coord invalidWorld{};
    std::uint32_t resourceTag=0,initialFlags=0;
    bool identityProvider=true;
    std::uint8_t enabled=1;
    int currentOwner=-1;
};
struct OverlayMapPreparationServices {
    // section/read/allocate/store/imageQuery/permissionQuery are consumed.
    // cleanup is an optional read-only observer before actual transient cleanup.
    OverlayMapLoadServices reader;
    // cell/animation absence/redraw/resource/recalculate/store are consumed;
    // base/identity/grow/retire are bound to the recovered lifetime below.
    OverlayPlacementServices placement;
    MapWallUpdateServices wall;
    OverlayLifetimeServices lifetime;
    // Read-only observer for selected actor stores/services; handles start at 1.
    std::function<void(unsigned)> currentObject;
};
// Empty native object/registry counts at entry; capacity/growth are supplied.
// Joins decoded reader, temporary construction, ordinary/wall placement, wall
// updates, retirement and cleanup on shared Cells. Cell resource/recalculation,
// heap/broadcast/RTTI/base destruction/queues and original decoding remain services.
void prepareDecodedMapOverlays(int version,int width,int height,bool filterCrates,
    std::span<const OverlayTypeInputs>,OverlayMapPreparationState&,
    const OverlayMapPreparationInputs&,const OverlayMapPreparationServices&);
}
