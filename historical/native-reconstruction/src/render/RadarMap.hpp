// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapFloorHeight.hpp"
#include "render/RadarDiscovery.hpp"
#include <optional>
namespace ra2 {
struct RadarMapDiscoveryFields {
    const std::uint32_t& flags12C;
    const std::int32_t& count13C;
};
struct RadarMapWorld {
    // The canonical Cell table, terrain fields and fallback used by55A280.
    const MapFloorHeightWorld& floor;
    // Pure borrowed field access, including the canonical fallback. No query.
    std::function<RadarMapDiscoveryFields(const MapCellInput&)> discoveryFields;
    std::function<void(char,TerrainCellPoint)> query;
    std::function<void(const MapVisibilityCell&,int)> neighbor;
    std::function<void(const MapVisibilityCell&)> countRead;
    TerrainCellPoint direction3{1,1}; // Verified491620 initial offset; supplied association.
};
// Complete floor and discovery share actual terrain owners, table and fallback.
// Discovery retains its word-based lookup; floor retains its full signed index.
// Owns only service bindings, with no second Cell table, cached Cell mirrors or
// private floor state. All borrowed owners must outlive this immovable binding.
class RadarMapBinding {
    RadarPixelServices& target_;
    decltype(RadarPixelServices::floor55A280) savedFloor_;
    MapVisibilityWorld visibility_;
    std::optional<RadarDiscoveryBinding> discovery_;
public:
    RadarMapBinding(RadarPixelServices& target,MapFloorHeightState& floorState,
        const std::int32_t& currentHeight,const MapVisibilityState& discoveryState,
        const RadarMapWorld& world,
        std::function<void(RadarMapPoint&)> beforeFloor={},
        std::function<void(std::int32_t)> floorResult={},
        std::function<void(RadarMapPoint&,bool,std::uint8_t)> discoveryResult={}):target_(target){
        if(world.floor.cells.size()!=262144||!world.floor.fallback||!world.discoveryFields)
            throw std::invalid_argument("Radar map needs canonical complete table/fallback/fields");
        visibility_.direction3=world.direction3;
        visibility_.query=world.query;visibility_.neighbor=world.neighbor;visibility_.countRead=world.countRead;
        visibility_.borrowedCell=[&world](TerrainCellPoint point){
            const int index=int(point.y)*512+int(point.x);
            auto* cell=index>=0&&index<262144?world.floor.cells[std::size_t(index)]:nullptr;
            if(!cell){
                cell=world.floor.fallback;cell->position={point.x,point.y};
                if(world.floor.fallbackStore)world.floor.fallbackStore(cell->position);
            }
            const auto fields=world.discoveryFields(*cell);
            return MapVisibilityCell{{cell->position.x,cell->position.y},fields.flags12C,cell->flags,fields.count13C};
        };
        decltype(savedFloor_) floor=[&floorState,&currentHeight,&world,beforeFloor,floorResult](RadarMapPoint& p){
            if(beforeFloor)beforeFloor(p);
            const auto value=mapFloorHeight(floorState,currentHeight,{p.x,p.y,p.z},world.floor);
            if(floorResult)floorResult(value);return value;
        };
        discovery_.emplace(target,discoveryState,visibility_,std::move(discoveryResult));
        savedFloor_=std::move(target_.floor55A280);target_.floor55A280=std::move(floor);
    }
    ~RadarMapBinding(){target_.floor55A280=std::move(savedFloor_);}
    RadarMapBinding(const RadarMapBinding&)=delete;
    RadarMapBinding& operator=(const RadarMapBinding&)=delete;
    RadarMapBinding(RadarMapBinding&&)=delete;
    RadarMapBinding& operator=(RadarMapBinding&&)=delete;
};
}
