// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/AlphaAnimationLifecycle.hpp"
namespace ra2 {
struct ObjectAlphaPlacementServices {
    const std::int32_t& loading;
    std::function<Coord(const void*)> coordinates48;
    std::function<PixelPoint(Coord)> project6a29d0;
    std::function<PixelPoint()> tacticalOrigin;
    std::function<std::span<const std::uint8_t>(const void*)> image84;
    std::function<AlphaAnimationRecord*(std::uint32_t)> allocate;
    std::function<void(AlphaAnimationRecord&,const void*,std::int32_t,std::int32_t)> construct;
    std::function<void(PixelRect,std::uint32_t)> register6a3020;
};
inline std::int32_t alphaCanvasDimension(std::span<const std::uint8_t> image,std::size_t at){
    if(image.size()<at+2)throw std::invalid_argument("Object AlphaImage canvas header missing");
    return std::bit_cast<std::int16_t>(std::uint16_t(image[at]|unsigned(image[at+1])<<8));
}
// Entire inline5D39EF..5D3AE7 effect, entered only after the parent saved-Type
// AlphaImage gate. Independent live Type/image query and constructor child.
inline void placeObjectAlpha(const void* associated,const ObjectAlphaPlacementServices& s){
    if(!associated||!s.coordinates48||!s.project6a29d0||!s.tacticalOrigin||!s.image84||!s.allocate)
        throw std::invalid_argument("Object AlphaImage producer children unbound");
    const auto coordinates=s.coordinates48(associated);
    const auto projected=s.project6a29d0(coordinates);
    const auto origin=s.tacticalOrigin();
    const auto screenX=fillAdd(projected.x,origin.x),screenY=fillAdd(projected.y,origin.y);
    const auto image=s.image84(associated);
    const auto x=fillSub(screenX,alphaCanvasDimension(image,2)/2);
    const auto y=fillSub(screenY,alphaCanvasDimension(image,4)/2);
    auto* record=s.allocate(64);
    if(record){if(!s.construct)throw std::invalid_argument("Object AlphaImage construction unbound");s.construct(*record,associated,x,y);}
    if(!s.loading){
        if(!s.register6a3020)throw std::invalid_argument("Object AlphaImage redraw unbound");
        const auto lateOrigin=s.tacticalOrigin();
        s.register6a3020({fillSub(x,lateOrigin.x),fillSub(y,lateOrigin.y),
            alphaCanvasDimension(image,2),alphaCanvasDimension(image,4)},1);
    }
}
}
