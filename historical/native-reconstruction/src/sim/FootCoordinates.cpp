// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/FootCoordinates.hpp"
#include <stdexcept>
namespace ra2 {
UnitDrawingInputs initialUnitDrawingInputs(std::uint8_t flags){return {std::uint8_t((flags&0xf8)|7),0,-1};}
Coord driveSecondaryCoordinates(Coord current,Coord destination){return destination==Coord{}?current:destination;}
Coord footSecondaryCoordinates(std::int8_t index,std::span<const TerrainCellPoint> pool,
                               const FootCoordinateServices& s){
    if(index>=0){
        if(std::size_t(index)>=pool.size())throw std::invalid_argument("Missing indexed Foot coordinate entry");
        const auto p=pool[std::size_t(index)];
        return {int(p.x)*256+128,int(p.y)*256+128,0};
    }
    if(!s.locomotor)throw std::invalid_argument("Foot coordinate query requires a locomotor");
    const auto p=s.locomotor();return p==Coord{}?s.coordinates():p;
}
}
