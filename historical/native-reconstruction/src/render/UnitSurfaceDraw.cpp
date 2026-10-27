// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitSurfaceDraw.hpp"
#include "sim/OriginalMath.hpp"
#include <stdexcept>
namespace ra2 {
std::uint32_t unitDisguiseDrawFlags(const UnitDisguiseState& a,int frame,
                                  std::uint32_t flags,const std::function<bool()>& ownerVisible) {
    if(unitDrawTimerHasRemainder(a.timerStart,a.timerDuration,frame)&&!ownerVisible())return flags;
    const int phase=signed32(std::uint32_t(frame)-std::uint32_t(a.creationFrame)+64u)%256;
    if((phase>=64&&phase<68)||(phase>=76&&phase<80)||
       (phase>=112&&phase<116)||(phase>=124&&phase<128))return flags|2u;
    if((phase>=68&&phase<76)||(phase>=116&&phase<124))return flags|4u;
    return flags;
}
unsigned unitSurfaceBlitterSlot(std::uint32_t flags) {
    if((flags&~14u)!=0x2800u)throw std::invalid_argument("Unsupported Unit surface flags");
    switch(flags&6u) {
    case 2:return flags&8u?0xb4:0xa8;
    case 4:return flags&8u?0xb0:0xa4;
    case 6:return flags&8u?0xac:0xa0;
    default:return 0x98;
    }
}
void drawOrdinaryUnitSurface(const UnitSurfaceInputs& in,const UnitSurfaceServices& s) {
    if(in.typeBAE)throw std::invalid_argument("Alternate Unit surface split is unrecovered");
    std::uint32_t flags=0x2800;int extra=0;
    switch(s.layer()) {
    case 1:flags=0x2802;break;
    case 2:case 3:flags=0x2804;break;
    case 4:flags=in.layerFourValue?0x280c:0x280a;extra=s.layerFourExtra();break;
    default:break;
    }
    if(s.flag204()!=0||s.flag205()!=0)flags|=4;
    if(s.ownerVisible()&&s.disguised()!=0)flags=s.disguiseFlags(flags);
    UnitSurfaceRequest r;
    r.blitter=s.houseBlitter(flags);
    r.destination={signed32(std::uint32_t(in.point.x)+std::uint32_t(in.dirty.x)-128u),
                   signed32(std::uint32_t(in.point.y)+std::uint32_t(in.dirty.y)-128u),
                   in.dirty.width,in.dirty.height};
    r.source=in.dirty;r.clip=in.clip;r.brightness=in.brightness;r.extra=extra;
    r.gradient=s.gradient();r.depth=s.depth();r.sourceBounds=s.sourceBounds();
    s.draw(r);
}
}
