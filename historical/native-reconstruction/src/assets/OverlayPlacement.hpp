// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapOverlayLoading.hpp"
#include "assets/MapWallUpdate.hpp"
#include "sim/Drive.hpp"
#include <array>

namespace ra2 {
// Selected temporary Object/Overlay fields. Base construction, identity-provider
// initialization, storage and eventual destruction remain explicit boundaries.
struct TransientMapOverlay {
    const OverlayTypeInputs* type=nullptr;
    Coord position{};
    std::uint8_t onMap=0,redraw=0,limbo=1,active=1;
    std::uint32_t identityToken=0;
};
struct OverlayPlacementCell : OverlayLoadCell {
    // Placement and wall update share the same selected Cell fields/storage.
    std::uint8_t slope=0;
};
struct OverlayTransientRegistry {
    std::vector<std::uint32_t> slots;
    int count=0,growth=1;
    std::uint8_t owns=1;
};
struct OverlayPlacementServices {
    std::function<void(TransientMapOverlay&)> base;
    // Optional provider counter; initialization/association/lifetime supplied.
    // The actual identity child increments this uint32 before storing its token.
    std::uint32_t* identityCounter=nullptr;
    std::function<bool(int)> grow;
    std::function<void()> noAttachedAnimation,redraw;
    std::function<OverlayPlacementCell&(MapInputPosition)> cell;
    std::function<void(OverlayPlacementCell&)> resource;
    std::function<void(OverlayPlacementCell&,int)> recalculate;
    // Supplied retirement effects must clear active. Queue/cleanup/destruction
    // and ownership remain unrecovered at this boundary.
    std::function<void(TransientMapOverlay&)> retire;
    // role: 0 actor offset/size/value, 1 Cell, 2 registry count/slot,
    // 3 placement-global flag, 4 identity counter. Diagnostic only.
    std::function<void(unsigned,unsigned,unsigned,std::uint32_t)> store;
};
// Loading !=0, ordinary nonwall/nonbridge/no-animation type only. Unsupported
// special placement is refused before mutation. Resource/recalculation services
// may bind the separately recovered Cell kernels; their effects remain explicit.
bool markLoadedMapOverlay(TransientMapOverlay&,int mode,const OverlayPlacementServices&);
bool unlimboLoadedMapOverlay(TransientMapOverlay&,Coord,std::uint8_t enabled,
                            const OverlayPlacementServices&);
void constructLoadedMapOverlay(TransientMapOverlay&,const OverlayTypeInputs&,
    MapInputPosition,MapInputPosition invalid,int flag,int& placementFlag,
    std::uint32_t identity,OverlayTransientRegistry&,std::uint8_t enabled,
    const OverlayPlacementServices&);
struct LoadedWallPlacementServices {
    OverlayPlacementServices object;
    // Directions and current owner/placement globals are supplied inputs.
    std::array<MapInputPosition,8> directions{};
    int loading=1,placementFlag=-1,currentOwner=-1;
    const int* livePlacementFlag=nullptr;
    // May bind updateMapWall directly on this shared Cell projection. Image/
    // camera/queue/recalculation providers remain explicit services there.
    std::function<void(OverlayPlacementCell&,std::uint8_t)> updateWall;
    // Observer for the loaded Cell permission call (1, null, null), whose
    // actual complete original root returns true immediately while loading.
    std::function<void()> permissionQuery;
};
// Complete Overlay Mark, loaded wall/no-CellAnim domain. Long bridges/veins
// and land 9 remain refused. Object Mark is shared with ordinary placement.
bool markLoadedMapWall(TransientMapOverlay&,int mode,const LoadedWallPlacementServices&);
bool unlimboLoadedMapWall(TransientMapOverlay&,Coord,std::uint8_t enabled,
                         const LoadedWallPlacementServices&);
// The placement flag is a live reference: Mark reads the constructor's new
// value, then the constructor resets it to -1 even after rejected placement.
void constructLoadedMapWall(TransientMapOverlay&,const OverlayTypeInputs&,
    MapInputPosition,MapInputPosition invalid,int flag,int& placementFlag,
    std::uint32_t identity,OverlayTransientRegistry&,std::uint8_t enabled,
    const LoadedWallPlacementServices&);
}
