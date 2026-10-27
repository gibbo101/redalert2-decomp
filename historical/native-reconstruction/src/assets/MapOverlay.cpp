// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapOverlay.hpp"
#include "assets/OverlayTypeInputs.hpp"
#include <bit>
#include <cmath>
#include <stdexcept>

namespace ra2 {
namespace {
int plus(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
MapInputPosition offset(MapInputPosition p,MapInputPosition d){
    return {std::bit_cast<std::int16_t>(std::uint16_t(int(p.x)+d.x)),
            std::bit_cast<std::int16_t>(std::uint16_t(int(p.y)+d.y))};
}
}
int classifyMapOverlay(int overlay,const MapOverlayType* type,std::span<const MapResourceType> resources,
    const std::function<void(int)>& missing){
    if(overlay==-1)return -1;
    if(overlay<0||!type)throw std::invalid_argument("Missing overlay type binding");
    if(!type->tiberium)return -1;
    for(const auto& r:resources){
        const int split=plus(r.imageIndex,r.numImages),end=plus(split,r.numSlopes);
        if((overlay>=r.imageIndex&&overlay<split)||(overlay>=split&&overlay<end))return r.index;
    }
    if(missing)missing(overlay);
    return 0;
}
int classifyOverlayResource(int overlay,const OverlayTypeInputs* type,std::span<const MapResourceType> resources,
    const std::function<void(int)>& missing){
    MapOverlayType selected;if(overlay!=-1&&type)selected.tiberium=type->tiberium;
    return classifyMapOverlay(overlay,type?&selected:nullptr,resources,missing);
}
int overlayCellPassability(const MapCellInput& cell,bool permitted,const MapOverlayType* overlay,
    std::span<const float> speeds){
    if(!permitted)return 7;
    if(overlay){
        if(overlay->flag1FD)return 1;
        if(overlay->wall)return 2;
        if(overlay->land<0||std::size_t(overlay->land)>=speeds.size())
            throw std::invalid_argument("Overlay land outside supplied Wheel table");
        const float speed=speeds[std::size_t(overlay->land)];
        // x87 C3 alone is tested: unordered follows the equality path as well.
        if(speed==0.0f||std::isnan(speed))return 6;
        if(overlay->rock)return 6;
        if(overlay->rubble)return 0;
    }
    return emptyCellPassability(cell,true,speeds);
}
int updateMapResource(MapInputPosition p,int overlay,std::uint8_t& data,const MapResourceServices& s){
    if(overlay==-1)return 0;
    if(!s.classify)throw std::invalid_argument("Missing resource classifier");
    const int index=s.classify(overlay);
    if(index==-1)return 0;
    if(index<0||std::size_t(index)>=s.types.size())throw std::invalid_argument("Resource result outside supplied registry");
    const auto& r=s.types[std::size_t(index)];
    const int value=r.value; // The original saves value before neighbor queries.
    if(r.numFrames<=0||!s.neighborOverlay)throw std::invalid_argument("Unsupported resource frame divisor or lookup");
    int matches=0;
    for(const auto d:s.directions)if(s.classify(s.neighborOverlay(offset(p,d)))==index)++matches;
    const auto frame=std::size_t(matches%r.numFrames);
    if(frame>=s.frameTable.size())throw std::invalid_argument("Resource frame outside supplied table");
    data=s.frameTable[frame];if(s.store)s.store(data);
    return std::bit_cast<std::int32_t>((std::uint32_t(data)+1u)*std::uint32_t(value));
}
}
