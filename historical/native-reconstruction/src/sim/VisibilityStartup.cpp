// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/VisibilityStartup.hpp"
#include <bit>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace ra2 {
namespace {
void append(std::array<TerrainCellPoint,369>& points,std::size_t& size,int x,int y){
    if(size>=points.size())throw std::logic_error("Visibility spread generator overflow");
    points[size++]={std::int16_t(x),std::int16_t(y)};
}
void quartet(std::array<TerrainCellPoint,369>& points,std::size_t& size,int x,int y){
    append(points,size,-x,y);append(points,size,x,y);
    append(points,size,-x,-y);append(points,size,x,-y);
}
}

VisibilityStartup initializeVisibilityStartup(){
    VisibilityStartup result{};
    std::size_t size=0;
    append(result.offsets,size,0,0);
    result.radiusCounts[0]=1;
    for(int radius=1;radius<=10;++radius){
        int x=-1,y=-radius;
        bool hasTwo=true,hadTwo=true;
        for(;;){
            append(result.offsets,size,x,y);
            if(x==1&&y==radius)break;
            if(hasTwo){++x;hasTwo=(x==0);continue;}
            if(x<0){x=-x;hasTwo=hadTwo;continue;}
            ++y;
            const bool reflected=y>0;
            if(reflected)y=-y;
            x=-2*(radius+y)-1;
            const int difference=x-y;
            hasTwo=difference>=0;
            hadTwo=hasTwo;
            if(difference==-1)++x;
            else if(difference<0)x=(-y)/2-radius;
            if(reflected)y=-y;
        }
        result.radiusCounts[std::size_t(radius)]=std::int32_t(size);
    }

    // The stock radius-one constructor writes the two top corners in this
    // order. Later rings already have the constructor's exact order.
    std::swap(result.offsets[1],result.offsets[3]);

    for(std::size_t i=0;i<result.heightOffsets.size();++i){
        const auto point=result.offsets[i];
        const int ax=point.x<0?-int(point.x):int(point.x);
        const int ay=point.y<0?-int(point.y):int(point.y);
        const auto opposite=[](std::int16_t value)->std::int16_t{
            return value<0?1:value>0?-1:0;
        };
        result.heightOffsets[i]={ax*2<ay?std::int16_t(0):opposite(point.x),
            ay*2<ax?std::int16_t(0):opposite(point.y)};
    }
    // Preserve the stock constructor's isolated asymmetric entry.
    result.heightOffsets[101]={1,0};

    // Radius 11 is initialized for other stock callers, although reveal-area
    // clamps to 10. Preserve its separate order and the original fourth x=3
    // duplicate; do not normalize the table.
    append(result.offsets,size,0,11);append(result.offsets,size,0,-11);
    for(int x=1;x<=3;++x){
        quartet(result.offsets,size,x,11);
        if(x==3)result.offsets[size-1]={-3,11};
    }
    for(int x=4;x<=5;++x)quartet(result.offsets,size,x,9);
    for(int x=6;x<=7;++x)quartet(result.offsets,size,x,8);
    for(int y=7;y>=6;--y)quartet(result.offsets,size,8,y);
    for(int y=5;y>=4;--y)quartet(result.offsets,size,9,y);
    for(int y=3;y>=2;--y)quartet(result.offsets,size,10,y);
    quartet(result.offsets,size,11,1);
    append(result.offsets,size,11,0);append(result.offsets,size,-11,0);
    if(size!=result.offsets.size())throw std::logic_error("Visibility spread generator size differs");

    // 6A20E0 -> 6A2170 -> 6A2440 reaches this exact binary64 result for
    // the fixed stock constants and private lookup tables. Keeping the proven
    // result by bits avoids substituting host libm for the original tables.
    result.heightProjectionScale=std::bit_cast<double>(std::uint64_t(0x3fc25e5374344960));
    return result;
}
}
