// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/PreparedDriveTerrain.hpp"
#include "assets/MapCoordinateCell.hpp"
#include "assets/MapCellChildren.hpp"
#include <stdexcept>
namespace ra2 {
PreparedDriveTerrain::PreparedDriveTerrain(MapFloorHeightState& floor,int height,MapFloorHeightWorld world,
    const std::function<void(const MapCellInput&)>& check,const Query& query,
    const std::function<std::uint8_t(const MapCellInput&)>& ordinaryNeighborCheck)
    :floor_(floor),height_(height),world_(world),check_(check),ordinaryNeighborCheck_(ordinaryNeighborCheck),query_(query){
    if(!world_.fallback||world_.cells.size()!=262144)
        throw std::invalid_argument("Prepared Drive requires the complete shared Cell table and fallback");
}
GroundDriveCell PreparedDriveTerrain::record(const MapCellInput& c) const{
    if(check_)check_(c);
    return {c.position.x,c.position.y,c.level,c.slope,c.land,&c};
}
const MapCellInput& PreparedDriveTerrain::coordinate(Coord p) const{
    if(query_)query_('C',p);
    const auto& c=mapCoordinateCell(p,world_,262144);
    if(check_)check_(c);
    return c;
}
const MapCellInput& PreparedDriveTerrain::word(std::int16_t x,std::int16_t y,bool neighbor) const{
    if(query_)query_('W',{x,y,0});
    const auto& c=mapAttributeCell({x,y},{world_.cells,world_.fallback,{},world_.fallbackStore});
    if(!neighbor&&check_)check_(c);
    return c;
}
GroundDriveProcessServices PreparedDriveTerrain::bind(GroundDriveProcessServices s) const{
    if(ordinaryNeighborCheck_)s.ordinaryNeighbor=[this](std::int16_t x,std::int16_t y){
        return ordinaryNeighborCheck_(word(x,y,true));
    };
    s.cell=[this](Coord p){return record(coordinate(p));};
    s.wordCell=[this](std::int16_t x,std::int16_t y){return record(word(x,y));};
    s.liveCell=[this](const void* identity){
        // Only identities returned by the bound lookups are admitted. Retained
        // fallback coordinates must be reread after intervening floor queries.
        if(!identity)throw std::invalid_argument("Prepared Drive retained a null Cell");
        return record(*static_cast<const MapCellInput*>(identity));
    };
    s.center=[this](const GroundDriveCell& c){
        const auto& live=*static_cast<const MapCellInput*>(c.identity);
        if(query_)query_('T',{live.position.x,live.position.y,0});
        return mapCellCenterHeight(floor_,height_,live);
    };
    s.advance.coordinateCell=[this](Coord p)->const void*{return &coordinate(p);};
    s.advance.wordCell=[this](std::int16_t x,std::int16_t y){(void)word(x,y);};
    s.advance.ground.floor=[this](Coord p){
        if(query_)query_('F',p);
        return mapFloorHeight(floor_,height_,p,world_);
    };
    return s;
}
}
