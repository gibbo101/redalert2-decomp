// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/PostSightRefresh.hpp"
#include "sim/Facing.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <bit>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace ra2 {
namespace {
std::int32_t integer(double value){
    constexpr double limit=9223372036854775808.0;
    if(!std::isfinite(value)||value<-limit||value>=limit)return 0;
    return signed32(std::uint32_t(std::uint64_t(std::int64_t(value))));
}
std::int32_t projected(std::int32_t z,double scale){
    volatile double a=double(z)*scale;
    volatile double b=a+double(z>=728);
    volatile double c=b+.5;
    return integer(c);
}
std::int32_t add(std::int32_t a,std::int32_t b){return signed32(std::uint32_t(a)+std::uint32_t(b));}
std::int16_t word(std::uint32_t value){return std::bit_cast<std::int16_t>(std::uint16_t(value));}
}
void refreshPostSightVisibility(Coord coordinates,std::int32_t innerRadius,
        std::int32_t outerRadius,std::uint32_t disabled,
        const PostSightRefreshWorld& world,const VisibilityStartup& startup,
        const PostSightRefreshServices& services){
    if(world.cells.size()!=262144||!world.fallback)
        throw std::invalid_argument("Post-sight refresh requires complete Cell ownership");
    if(!services.visibilityMask||!services.redraw)
        throw std::invalid_argument("Post-sight refresh services are incomplete");
    outerRadius=std::clamp(outerRadius,std::int32_t(3),std::int32_t(11));
    if(disabled)return;
    if(innerRadius<0)innerRadius=0;else if(innerRadius>8)innerRadius=8;
    const auto skip=innerRadius?startup.radiusCounts[std::size_t(innerRadius-1)]:0;
    const auto outerCount=outerRadius==11?std::int32_t(startup.offsets.size()):startup.radiusCounts[std::size_t(outerRadius)];
    const auto count=signed32(std::uint32_t(outerCount)-std::uint32_t(skip));
    if(count<0)throw std::invalid_argument("Post-sight refresh nonterminating spread is outside bounded profile");
    if(std::size_t(skip)+std::size_t(count)>startup.offsets.size())
        throw std::invalid_argument("Post-sight refresh spread is outside supplied table");
    OriginalRounding rounding;
    const auto event=[&](char k,int a=0,int b=0,int c=0){if(services.trace)services.trace(k,a,b,c);};
    const auto height=[&]{const auto value=projected(coordinates.z,startup.heightProjectionScale);event('H',value);return value;};
    const auto shiftX=signed32(0u-std::uint32_t(height()/30));
    const auto shiftY=signed32(0u-std::uint32_t(height()/30));
    const auto adjustedX=add(coordinates.x,signed32(std::uint32_t(shiftX)*256u));
    const auto adjustedY=add(coordinates.y,signed32(std::uint32_t(shiftY)*256u));
    const auto centerX=word(std::uint32_t(adjustedX/256)),centerY=word(std::uint32_t(adjustedY/256));
    for(std::int32_t i=0;i<count;++i){
        const auto offset=startup.offsets[std::size_t(skip+i)];
        const TerrainCellPoint point{word(std::uint32_t(std::uint16_t(centerX))+std::uint32_t(std::uint16_t(offset.x))),
            word(std::uint32_t(std::uint16_t(centerY))+std::uint32_t(std::uint16_t(offset.y)))};
        const auto index=signed32(std::uint32_t(std::int32_t(point.y))*512u+std::uint32_t(std::int32_t(point.x)));
        CellVisibilityState* cell=nullptr;
        if(index>=0&&index<262144)cell=world.cells[std::size_t(index)];
        if(!cell){world.fallback->point=point;if(world.fallbackStore)world.fallbackStore(point);cell=world.fallback;}
        if(world.query)world.query(point,cell->identity);
        const auto mask=services.visibilityMask(point);event('M',point.x,point.y,mask);
        if(mask==cell->primary120)continue;
        cell->primary120=mask;event('P',cell->identity,mask);
        cell->redraw138=1;event('B',cell->identity,1);
        services.redraw(cell->identity);
    }
}
}
