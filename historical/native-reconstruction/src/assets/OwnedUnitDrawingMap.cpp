// SPDX-License-Identifier: GPL-3.0-or-later
#include "OwnedUnitDrawingMap.hpp"
#include "assets/MapCoordinateCell.hpp"
#include "assets/MapCellChildren.hpp"
#include <stdexcept>
namespace ra2 {
OwnedUnitDrawingMap::OwnedUnitDrawingMap(MutableUnitMap& map,PreparedUnitMembership& unit)
    :map_(map),unit_(unit),world_(unit.world()) {
    if(world_.cells.data()!=map_.table.data()||world_.cells.size()!=map_.table.size()||
       world_.fallback!=&map_.fallback.input||!world_.fallbackStore)
        throw std::invalid_argument("Drawing requires this map's actual membership world");
}
const GroundDriveProcessState& OwnedUnitDrawingMap::actorState(int id)const{return unit_.actorState(id);}
const MapCellInput& OwnedUnitDrawingMap::coordinate(Coord p){return mapCoordinateCell(p,world_,262144);}
const MapCellAttributes& OwnedUnitDrawingMap::cell(MapInputPosition p){
    const auto& found=mapAttributeCell(p,{world_.cells,world_.fallback,{},world_.fallbackStore});
    if(&found==&map_.fallback.input)return map_.fallback;
    const auto* attributes=map_.find(found);
    if(!attributes)throw std::invalid_argument("Drawing encountered an unbound canonical Cell");
    return *attributes;
}
int OwnedUnitDrawingMap::floor(Coord p){return mapFloorHeight(map_.floor,map_.levelHeight,p,world_);}
int OwnedUnitDrawingMap::relative(Coord p){return relativeMapHeight(map_.floor,map_.levelHeight,p,0,0,world_);}
}
