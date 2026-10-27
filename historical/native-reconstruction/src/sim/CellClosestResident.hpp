// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"
#include <functional>
#include <cmath>
#include <stdexcept>

namespace ra2 {
struct CellClosestResidentServices {
    std::function<int(bool)> head;
    std::function<std::uint8_t(int)> flags;
    std::function<int(int)> next;
    std::function<Coord(int)> coordinates;
    std::function<double(double)> squareRoot;
    std::size_t memberLimit=0;
};
// 471660: primary/elevated list, flag14 bit0, optional ignored identity,
// low-byte XY versus seven times the supplied point; first wins equal distance.
// A cycle/oversized list is a native domain refusal, not original behavior.
inline int closestCellResident(int x,int y,bool elevated,int ignore,const CellClosestResidentServices& s){
    const int px=signed32(std::uint32_t(x)*7u),py=signed32(std::uint32_t(y)*7u);
    int best=-1,distance=0;std::size_t visits=0;
    for(int id=s.head(elevated);id!=-1;id=s.next(id)){
        if(++visits>s.memberLimit)throw std::invalid_argument("Closest resident requires a finite actual list");
        if(!(s.flags(id)&1u)||id==ignore)continue;
        const auto p=s.coordinates(id);
        const double dx=signed32((std::uint32_t(p.x)&255u)-std::uint32_t(px)),
            dy=signed32((std::uint32_t(p.y)&255u)-std::uint32_t(py));
        const double value=s.squareRoot(dx*dx+dy*dy);
        if(!std::isfinite(value)||value<0||value>2147483647.)
            throw std::invalid_argument("Closest resident distance outside finite int32 profile");
        const int n=int(value);
        if(best==-1||n<distance){best=id;distance=n;}
    }
    return best;
}
}
