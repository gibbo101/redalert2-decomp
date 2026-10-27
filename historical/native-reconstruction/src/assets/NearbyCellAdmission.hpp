// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellChildren.hpp"
#include "assets/OverlayTypeInputs.hpp"
#include <bit>
#include <cmath>
#include <stdexcept>

namespace ra2 {
// Borrow actual Cell fields and occupation/overlay owners. Binding performs no
// lookup and owns no copied map, type registry or occupation projection.
struct NearbyAdmissionCell {
    const MapCellInput& input;
    const std::uint32_t& occupation;
    const std::uint32_t& elevatedOccupation;
    const int& overlay;
};
struct NearbyAdmissionServices {
    // 54F8F0 is an explicit supplied service, consulted only for zone != -1.
    std::function<int(const MapInputPosition&,int,std::uint32_t)> zone;
    std::span<const OverlayTypeInputs* const> overlays;
    // Original 9-dword land rows, including the retained ninth entry.
    std::span<const std::uint32_t> speedBits;
    std::function<void(char,const MapCellInput&,int,int,int,int,int,int,std::uint32_t)> trace;
};
// Complete direct-Cell permission 55A740. Unlike 55A660 it never looks up a Cell.
inline bool nearbyCellPermitted(const MapCellInput& cell,std::uint8_t elevation,
    const MapPermissionShape& shape){
    const auto add=[](int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));};
    const auto sub=[](int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));};
    const auto twice=[](int n){return std::bit_cast<std::int32_t>(std::uint32_t(n)*2u);};
    const int x=cell.position.x,y=cell.position.y,sum=x+y;
    int level=0;
    if(elevation){
        level=cell.level;
        if(cell.slope&&sum<add(add(add(shape.dimension0,twice(shape.originY)),4),level))++level;
    }
    if(sum<=add(add(shape.dimension0,twice(shape.originY)),level))return false;
    if(sum>add(add(add(shape.dimension0,twice(add(shape.originY,shape.height))),2),level))return false;
    if(x-y>=sub(twice(add(shape.originX,shape.width)),shape.dimension0))return false;
    if(y-x>=sub(shape.dimension0,twice(shape.originX)))return false;
    return true;
}
// Complete 478760 policy; zone resolution and initial associations stay supplied.
inline bool nearbyCellAdmits(NearbyAdmissionCell v,int speedType,
    std::uint8_t ignoreLow,std::uint8_t ignoreMiddle,int zone,int movementZone,
    int level,std::uint32_t alternate,const NearbyAdmissionServices& services){
    if(services.trace)services.trace('C',v.input,speedType,ignoreLow,ignoreMiddle,zone,movementZone,level,alternate);
    const auto finish=[&](bool result){if(services.trace)services.trace('c',v.input,result,0,0,0,0,0,0);return result;};
    if(speedType==4)return finish(true);
    if(zone!=-1){
        if(!services.zone)throw std::invalid_argument("Nearby admission zone resolver unjoined");
        if(services.zone(v.input.position,movementZone,alternate)!=zone)return finish(false);
    }
    if(level!=-1){
        if(level!=int(v.input.level)){
            if(!(v.input.flags&0x100u)||level!=int(v.input.level)+4)return finish(false);
        }else if((v.input.flags&0x100u)&&!(alternate&255u))return finish(false);
    }
    const bool elevated=(level==-1||level==int(v.input.level)+4)&&(v.input.flags&0x100u);
    auto occupation=(elevated?v.elevatedOccupation:v.occupation)&255u;
    if(ignoreLow)occupation&=0xe0u;
    if(ignoreMiddle)occupation&=0x5fu;
    if(occupation)return finish(false);
    int land=v.input.land;
    if(v.overlay!=-1){
        if(v.overlay<0||std::size_t(v.overlay)>=services.overlays.size())
            throw std::invalid_argument("Nearby admission overlay registry index");
        const auto* type=services.overlays[std::size_t(v.overlay)];
        if(type&&type->wall){
            if(movementZone!=2&&movementZone!=3&&movementZone!=8&&
               !((movementZone==1||movementZone==4)&&type->crushable))return finish(false);
            land=0;
        }
    }
    const int index=std::bit_cast<std::int32_t>(std::uint32_t(land)*9u+std::uint32_t(speedType));
    if(index<0||std::size_t(index)>=services.speedBits.size())
        throw std::invalid_argument("Nearby admission land speed index");
    const float speed=std::bit_cast<float>(services.speedBits[std::size_t(index)]);
    // Original C3 comparison bit: equality OR unordered, not positivity.
    return finish(elevated||(!std::isnan(speed)&&speed!=0.f));
}
// Complete 550CF0 rectangle. X outer/Y inner, signed-word offsets, immediate
// fallback forwarding and first-failure return. No native route search.
inline bool nearbyRectangleAdmits(const MapInputPosition& origin,int width,int height,
    int speedType,int zone,int movementZone,int level,std::uint32_t alternate,
    std::uint8_t disallowOverlay,const MapAttributeLookup& map,
    const std::function<NearbyAdmissionCell(const MapCellInput&)>& bind,
    const NearbyAdmissionServices& services){
    const auto word=[](unsigned n){return std::bit_cast<std::int16_t>(std::uint16_t(n));};
    for(int x=0;x<width;++x)for(int y=0;y<height;++y){
        const MapInputPosition point{word(unsigned(origin.x)+unsigned(x)),word(unsigned(origin.y)+unsigned(y))};
        const auto& input=mapAttributeCell(point,map);
        if(!bind)throw std::invalid_argument("Nearby admission requires borrowed Cell binding");
        const auto cell=bind(input);
        if(&cell.input!=&input)throw std::invalid_argument("Nearby admission split Cell binding");
        if(disallowOverlay&&cell.overlay!=-1)return false;
        if(!nearbyCellAdmits(cell,speedType,0,0,zone,movementZone,level,alternate,services))return false;
    }
    return true;
}
}
