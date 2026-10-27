// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"
#include "sim/OriginalMath.hpp"
#include <functional>
#include <stdexcept>
namespace ra2 {
struct FootLayerServices {
    std::function<std::uint8_t()> bridge;
    std::function<Coord(int)> secondaryCoordinates;
    std::function<Coord()> actorCoordinates;
    std::function<int(Coord)> floorHeight;
    std::function<int()> levelHeight;
    std::function<std::uint32_t(Coord)> cellFlags;
};
// Complete Object coordinate-layer decision (5D52F0). Borrow the actual actor
// and map through live queries: the saved bridge byte is not a boolean, the two
// floor queries are independent, and the later lookup uses the saved point.
// Construction, map ownership and initial globals remain supplied. Unwired.
inline std::uint8_t objectCoordinateLayer(int flag,const FootLayerServices& s) {
    if(!s.bridge||!s.secondaryCoordinates||!s.actorCoordinates||!s.floorHeight||
       !s.levelHeight||!s.cellFlags)
        throw std::invalid_argument("Coordinate layer requires live actor/map queries");
    const auto saved=s.bridge();
    const auto point=s.secondaryCoordinates(flag);
    const int pointFloor=s.floorHeight(point);
    const int actorFloor=s.floorHeight(s.actorCoordinates());
    const auto triple=[](int n){return signed32(std::uint32_t(n)*3u);};
    const auto difference=[](int a,int b){return signed32(std::uint32_t(a)-std::uint32_t(b));};
    int height;
    if(!s.bridge()) {
        height=s.levelHeight();
        if(difference(actorFloor,pointFloor)>triple(height)) {
            if(s.cellFlags(point)&0x100u)return 1;
            height=s.levelHeight();
        }
    } else height=s.levelHeight();
    if(s.bridge()&&difference(pointFloor,actorFloor)>triple(height))return 0;
    return saved;
}
// Complete Foot wrapper (4CC4B0). Nonnegative signed registry indices return
// zero without coordinate, floor, bridge or global queries. Flag is forwarded.
inline std::uint8_t footCoordinateLayer(std::int8_t index,int flag,const FootLayerServices& s) {
    if(index>=0)return 0;
    return objectCoordinateLayer(flag,s);
}
}
