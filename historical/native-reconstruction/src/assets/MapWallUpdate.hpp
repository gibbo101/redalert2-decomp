// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellInputs.hpp"
#include <array>
#include <functional>
#include <span>

namespace ra2 {
struct MapWallOccupant {
    int kind=0,health=0;
    std::uint32_t type=0;
};
struct MapWallCell {
    MapInputPosition position{};
    int overlay=-1,passability=0,owner=-1;
    std::uint8_t data=0,neighbors=0;
    // Ordered native projection; original linked storage/lifetime is supplied.
    std::span<const MapWallOccupant> occupants;
};
struct WallConnectionInputs {
    // Supplied native identities corresponding to base Rules fields
    // +0x77C, +0x780, +0x78C, +0x784, +0x788, in that order.
    std::array<std::uint32_t,5> gates{};
    std::function<void(const MapWallCell&,unsigned)> occupantQuery;
    std::function<void(const MapWallCell&,int,int)> connectionQuery;
};
bool connectsToMapOverlay(const MapWallCell&,int overlay,int facing,
                          const WallConnectionInputs&);
struct MapWallBounds {int x=0,y=0,width=0,height=0;};
struct MapWallUpdateServices {
    std::array<MapInputPosition,8> directions{};
    std::array<int,5> visits{}; // Supplied cardinal/self visit table.
    std::span<const std::uint8_t> wallTypes;
    WallConnectionInputs connections;
    int screenX=0,screenY=0;
    std::function<MapWallCell&(MapInputPosition)> cell;
    // Overlay=0, shadow=1, terrain=2. Image/camera inputs and bound providers
    // remain supplied. The union service may bind the recovered render kernel.
    std::function<MapWallBounds(const MapWallCell&,unsigned)> bounds;
    std::function<MapWallBounds(MapWallBounds,MapWallBounds)> unite;
    std::function<void(MapWallBounds)> dirty;
    std::function<void(MapInputPosition)> notify;
    std::function<void(MapWallCell&,int)> recalculate;
    std::function<void(MapWallCell&)> expired;
    // Zone change: remove=0, add=1, second notification=2.
    std::function<void(unsigned,MapInputPosition)> zone;
    std::function<void(MapWallCell&,unsigned,unsigned,std::uint32_t)> store;
};
// Complete wall-update parent around explicit bounds, storage, map/zone,
// pointer-expiration and Cell recalculation services. Shared evolving Cells;
// no original image/camera/queue storage, startup or runtime integration claim.
void updateMapWall(MapWallCell&,std::uint8_t skipCenterOldBounds,
                   const MapWallUpdateServices&);
struct MapWallDamageType {
    const std::uint8_t& wall;
    const int& levels270;
    const int& strength274;
};
struct MapWallDamageServices {
    const MapWallUpdateServices& update;
    const int& forceDamage;
    std::function<MapWallDamageType(int)> type;
    // Bind the recovered inclusive generator on the actual scenario state.
    // Equal/disabled/rejection behavior belongs to that shared RNG kernel.
    std::function<int(int,int)> randomRange;
};
// Complete Cell475FE0 parent. Bounds/map/zone/expiration/recalculation remain
// named services; actual damage, recursion, ordered clears and neighbors execute.
// This does not join its Unit notification caller or enable runtime traversal.
bool damageMapWall(MapWallCell&,int damage,const MapWallDamageServices&);
}
