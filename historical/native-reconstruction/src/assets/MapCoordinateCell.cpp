// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapCoordinateCell.hpp"
#include "sim/OriginalMath.hpp"
#include <stdexcept>
namespace ra2 {
MapCellInput& mapCoordinateCell(Coord p,const MapFloorHeightWorld& w,int count){
    if(count<0||std::size_t(count)>w.cells.size()||!w.fallback)
        throw std::invalid_argument("Coordinate Cell lookup requires bounded storage and fallback");
    const int x=p.x/256,y=p.y/256;
    const int index=signed32((std::uint32_t(y)<<9)+std::uint32_t(x));
    if(index>=0&&index<count&&w.cells[std::size_t(index)])return *w.cells[std::size_t(index)];
    w.fallback->position={std::bit_cast<std::int16_t>(std::uint16_t(x)),std::bit_cast<std::int16_t>(std::uint16_t(y))};
    if(w.fallbackStore)w.fallbackStore(w.fallback->position);
    return *w.fallback;
}
}
