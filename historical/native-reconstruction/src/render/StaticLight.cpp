// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/StaticLight.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <cmath>
namespace ra2 {
namespace {
int typeValue(double v) {
    if(!std::isfinite(v)||std::abs(v)>10)throw std::invalid_argument("Unsupported light type setting");
    return int(v*1000.0+0.1);
}
void detailLevel(int d) {if(d<0||d>2)throw std::invalid_argument("Graphics detail must be 0..2");}
}
LightTypeInputs lightTypeInputs(int radius,double intensity,std::array<double,3> tint) {
    if(radius<1||radius>32767)throw std::invalid_argument("Unsupported static light radius");
    OriginalRounding rounding;LightTypeInputs r;r.radius=radius;r.intensity=typeValue(intensity);
    for(int i=0;i<3;++i)r.tint[i]=typeValue(tint[i]);return r;
}
LightSource makeStaticLight(const LightTypeInputs& type,int x,int y,int z) {
    if(type.radius<1||type.radius>32767||std::abs(std::int64_t(x))>(1<<20)||std::abs(std::int64_t(y))>(1<<20))throw std::invalid_argument("Unsupported static light placement");
    return {x,y,z,type.radius,type.intensity,type.tint,false,2};
}
bool changeLightActive(LightSource& s,bool active) {
    if(s.active==active)return false;s.active=active;return true;
}
std::vector<std::size_t> affectedLightCells(const RenderData& data,const LightSource& source,std::span<const MapCell> cells,int detail,bool enabled) {
    detailLevel(detail);std::vector<std::size_t> out;
    if(!enabled||detail<source.minimumDetail)return out;
    if(source.radius<1||source.radius>32767||std::abs(std::int64_t(source.x))>(1<<20)||std::abs(std::int64_t(source.y))>(1<<20))throw std::invalid_argument("Unsupported light update domain");
    std::map<std::pair<int,int>,std::size_t> index;
    for(std::size_t i=0;i<cells.size();++i)index.emplace(std::pair{cells[i].x,cells[i].y},i);
    const int radius=source.radius/256+1,cx=source.x/256,cy=source.y/256;
    OriginalRounding rounding;
    for(int y=std::max(0,cy-radius);y<=std::min(511,cy+radius);++y)
        for(int x=std::max(0,cx-radius);x<=std::min(511,cx+radius);++x) {
            const auto it=index.find({x,y});if(it==index.end())continue;
            const std::int64_t dx=x*256+128-source.x,dy=y*256+128-source.y;
            const auto squared=dx*dx+dy*dy;
            if(squared>2147483647)throw std::invalid_argument("Light update squared distance overflow");
            // No squared-radius shortcut: sqrt/truncation can include a cell
            // just beyond the true radius. It still receives an original update.
            if(int(tableSqrt(data,double(squared)))<=source.radius)out.push_back(it->second);
        }
    return out;
}
TerrainConverterInputs terrainConverterInputs(std::array<int,3> tint,int detail) {
    detailLevel(detail);
    // The factory's neutral fast path precedes tint quantization.
    if(tint==std::array<int,3>{1000,1000,1000})return {tint,53};
    const int quantum=detail==0?128:detail==1?64:32;
    for(auto& c:tint)c=std::clamp(c,0,1000)/quantum*quantum;
    const int shades=tint[0]+tint[1]+tint[2]<2000?27:53;return {tint,shades};
}
}
