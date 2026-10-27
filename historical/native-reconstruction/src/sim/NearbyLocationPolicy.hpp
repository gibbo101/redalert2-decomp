// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/NearbyLocation.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <cstdlib>
#include <stdexcept>

namespace ra2 {
namespace nearby_detail {
inline std::int32_t signedWord(std::uint32_t n){return std::bit_cast<std::int32_t>(n);}
inline std::int16_t word(int n){return std::bit_cast<std::int16_t>(std::uint16_t(n));}
}
// Borrowed Cell/world views preserve live fields across nested child calls.
template<class World,class Services>
NearbyLocationPoint nearbyLocationPolicy(const NearbyLocationPoint& source,
    const NearbyLocationPoint& closeTo,const NearbyLocationOptions& options,
    const World& world,const Services& services) {
    using nearby_detail::signedWord;using nearby_detail::word;
    if(!services.lookup)throw std::invalid_argument("Nearby location requires Cell lookup");
    const int x=source.x,y=source.y;
    const int zone=options.zone==65535?-1:options.zone;
    int level=services.lookup(source).level;
    if((options.alternate&255u)&&(services.lookup(source).flags&0x100u))level+=4;
    const auto limit=std::min(32,signedWord(std::uint32_t(world.dimension0)+std::uint32_t(world.dimension1)));
    std::array<NearbyLocationPoint,24> candidates{},preferred{},other{};
    int count=0;bool acceptableProjection=false;
    const auto append=[&](int cx,int cy){
        const NearbyLocationPoint point{word(cx),word(cy)};
        auto& cell=services.lookup(point);
        if(!services.permission)throw std::invalid_argument("Nearby location requires permission");
        if(!services.permission(cell,1))return;
        if(!services.rectangle)throw std::invalid_argument("Nearby location requires rectangle admission");
        if(!services.rectangle(point,options.width,options.height,options.speedType,
            zone,options.movementZone,-1,options.alternate,options.disallowOverlay))return;
        if(options.matchLevel){
            const int difference=level-int((cell.flags>>8)&1u)*4-int(cell.level);
            if(std::abs(difference)>=2)return;
        }
        if(options.requireBurrowable){
            if(!services.burrowable)throw std::invalid_argument("Nearby location requires burrowable query");
            if(!services.burrowable(cell))return;
        }
        if(!options.allowBridge&&(cell.flags&0x100u))return;
        candidates[std::size_t(count++)]=point;
        // Append before checking the projection. Nonmatching candidates remain
        // in the list and count toward the 24-entry bound.
        if(options.alternate&255u)acceptableProjection=true;
        else {
            if(!services.projectCenter)throw std::invalid_argument("Nearby location requires projection");
            if(services.projectCenter(point)==point)acceptableProjection=true;
        }
    };
    for(int radius=0;radius<limit&&count<24;++radius){
        for(int dx=-radius;dx<=radius&&count<24;++dx){
            if(!options.skipNorthWest)append(x+dx,y-radius);
            if(count==24)break;
            if(!options.skipNorthWest||dx>-radius)append(x+dx,y+radius);
        }
        for(int dy=1-radius;dy<radius&&count<24;++dy){
            if(!options.skipNorthWest)append(x-radius,y+dy);
            if(count==24)break;
            append(x+radius,y+dy);
        }
        if(acceptableProjection)break;
    }
    if(!count)return world.emptyCell;
    int good=0,bad=0;
    for(int i=0;i<count;++i){
        if(!services.projectCenter)throw std::invalid_argument("Nearby location requires final projection");
        const auto point=candidates[std::size_t(i)];
        if(services.projectCenter(point)==point)preferred[std::size_t(good++)]=point;
        else other[std::size_t(bad++)]=point;
    }
    const auto& selected=good?preferred:other;const int size=good?good:bad;
    if(closeTo==world.emptyCell){
        // Original signed frame remainder is not an RNG draw. A negative
        // remainder indexes before its local array; refuse, never normalize it.
        const int index=world.frame%size;
        if(index<0)throw std::invalid_argument("Nearby location negative frame remainder");
        return selected[std::size_t(index)];
    }
    if(!services.squareRoot)throw std::invalid_argument("Nearby location requires table square root");
    OriginalRounding rounding;
    auto result=world.emptyCell;double best=100000.;
    for(int i=0;i<size;++i){
        const auto point=selected[std::size_t(i)];
        const auto dx=std::uint32_t(int(point.x)-int(closeTo.x));
        const auto dy=std::uint32_t(int(point.y)-int(closeTo.y));
        const auto squared=signedWord(dx*dx+dy*dy);
        const double distance=services.squareRoot(double(squared));
        if(distance<best){best=distance;result=point;}
    }
    return result;
}
}
