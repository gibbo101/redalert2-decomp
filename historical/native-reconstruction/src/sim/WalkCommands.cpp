// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/WalkCommands.hpp"
#include "sim/OriginalMath.hpp"
#include <cmath>
#include <stdexcept>
namespace ra2 {
namespace {
void event(const WalkCommandServices& s,char k,std::int64_t x=0,std::int64_t y=0,std::int64_t z=0){if(s.trace)s.trace(k,x,y,z);}
void pointStore(Coord& to,Coord from,int offset,const WalkCommandServices& s){
    to.x=from.x;event(s,'L',offset,std::uint32_t(to.x));
    to.y=from.y;event(s,'L',offset+4,std::uint32_t(to.y));
    to.z=from.z;event(s,'L',offset+8,std::uint32_t(to.z));
}
void byteStore(std::uint8_t& to,std::uint8_t value,int offset,const WalkCommandServices& s){to=value;event(s,'L',offset,value);}
void reset(const WalkCommandServices& s){
    if(!s.resetMovement)throw std::invalid_argument("Walk command requires movement reset");
    s.resetMovement();
}
}
void moveWalkTo(WalkMovementState& w,WalkCommandActor a,Coord request,const WalkCommandServices& s,Coord empty){
    event(s,'g',0x324);if(a.immobilized3fc>0)return;
    event(s,'g',0x1bc);if(a.disabled204)return;
    event(s,'g',0x1c0);if(a.disabled205)return;
    pointStore(w.destination,request,0x1c,s);
    if(request!=empty){
        if(!s.cellFlags)throw std::invalid_argument("Walk command requires coordinate Cell lookup");
        if(s.cellFlags(request)&0x100u){
            if(!s.projectionScale)throw std::invalid_argument("Walk bridge command requires projection scale");
            event(s,'h',60);
            OriginalRounding rounding;
            // Actual6A29B0 ->77F110: signed64 conversion, consumed as low32.
            const double value=(60.-.5)*s.projectionScale();
            const auto low=!std::isfinite(value)||value<-0x1p63||value>=0x1p63?
                std::uint32_t(0):std::uint32_t(std::int64_t(value));
            w.destination.z=signed32(std::uint32_t(w.destination.z)+low);
            event(s,'L',0x24,std::uint32_t(w.destination.z));
        }
        byteStore(w.moving34,1,0x34,s);
    }else if(w.head==empty){
        const auto saved=w.moving34;byteStore(w.moving34,0,0x34,s);
        if(saved)reset(s);
    }
}
void setWalkHeadImmediate(WalkMovementState& w,Coord request,const WalkCommandServices& s,Coord empty){
    const auto saved=w.moving34;pointStore(w.head,request,0x28,s);
    if(w.head==empty&&w.destination==empty){
        byteStore(w.moving34,0,0x34,s);if(saved)reset(s);
    }
}
void resetInfantryWalkMovement(std::uint8_t& flag,const std::function<void(int,int,int)>& animation,
    const std::function<void(char,std::int64_t,std::int64_t,std::int64_t)>& trace){
    if(!flag)return;
    flag=0;if(trace)trace('A',0x5cc,0,0);
    if(!animation)throw std::invalid_argument("Infantry reset requires animation4DC");
    animation(27,0,0);
}
}
