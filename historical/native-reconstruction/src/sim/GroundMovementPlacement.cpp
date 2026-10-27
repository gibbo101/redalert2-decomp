// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/GroundMovementPlacement.hpp"
#include <stdexcept>
namespace ra2 {
namespace {
void write(const GroundStateStore& s,int off,int v){if(s)s(off,v);}
void marked(ActorGroundState& a,std::uint8_t v,const GroundStateStore& w){a.marked74=v;write(w,0x74,v);}
bool sameCell(const Coord& a,const Coord& b){
    return std::uint16_t(a.x/256)==std::uint16_t(b.x/256)&&
        std::uint16_t(a.y/256)==std::uint16_t(b.y/256);
}
}
void setFootLocation(ActorGroundState& a,const Coord& next,const ActorGroundServices& s,const GroundStateStore& w){
    const bool wasMarked=a.marked74!=0;
    if(wasMarked&&!s.mark)throw std::invalid_argument("Foot location requires Mark service");
    if(wasMarked)s.mark(0);
    a.position.x=next.x;write(w,0x88,a.position.x);
    a.position.y=next.y;write(w,0x8c,a.position.y);
    a.position.z=next.z;write(w,0x90,a.position.z);
    if(wasMarked)s.mark(1);
}
void placeDriveResidualGround(ActorGroundState& a,const Coord& next,int bridgeHeight,
    const ActorGroundServices& s,const GroundStateStore& w){
    if(!s.floor||!s.mark)throw std::invalid_argument("Drive placement requires floor/Mark services");
    if(sameCell(a.position,next)){
        const auto saved=a.marked74;marked(a,0,w);
        setFootLocation(a,next,s,w);setActorRelativeHeight(a,0,bridgeHeight,s,w);
        marked(a,saved,w);
    }else{
        s.mark(0);setFootLocation(a,next,s,w);setActorRelativeHeight(a,0,bridgeHeight,s,w);s.mark(1);
    }
}
void placeDriveCommittedSameCell(ActorGroundState& a,const Coord& next,const std::uint8_t& onMap,
    int bridgeHeight,const ActorGroundServices& s,const GroundStateStore& w){
    if(!s.floor)throw std::invalid_argument("Committed placement requires floor service");
    auto saved=a.marked74;marked(a,0,w);setFootLocation(a,next,s,w);marked(a,saved,w);
    if(!onMap)return;
    saved=a.marked74;marked(a,0,w);setActorRelativeHeight(a,0,bridgeHeight,s,w);marked(a,saved,w);
}
}
