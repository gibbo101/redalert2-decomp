// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/ActorGroundState.hpp"
#include <stdexcept>
namespace ra2 {
namespace {
int add(int a,int b){return signed32(std::uint32_t(a)+std::uint32_t(b));}
void write(const GroundStateStore& s,int offset,int value){if(s)s(offset,value);}
void timer(DriveRampState& s,int tick,int padding,int duration,const GroundStateStore& w){
    s.start=tick;write(w,0x20,tick);
    s.padding=padding;write(w,0x24,padding);
    s.remaining=duration;write(w,0x28,duration);
    s.duration=duration;write(w,0x2c,duration);
}
}
void setActorRelativeHeight(ActorGroundState& a,int height,int bridgeHeight,
    const ActorGroundServices& s,const GroundStateStore& w){
    if(!s.floor||(!s.mark&&a.marked74))throw std::invalid_argument("Ground height requires floor/Mark services");
    if(a.bridge79)height=add(height,bridgeHeight);
    const bool marked=a.marked74!=0;
    if(marked)s.mark(0);
    const int floor=s.floor(a.position);
    a.position.z=add(floor,height);write(w,0x90,a.position.z);
    if(marked)s.mark(1);
}
void initializeDriveRamp(DriveRampState& s,int ramp,int tick,int padding,const GroundStateStore& w){
    s.previous=ramp;write(w,0x1c,ramp);
    s.current=ramp;write(w,0x18,ramp);
    timer(s,tick,padding,0,w);
}
void unlimboDriveRamp(DriveRampState& s,const std::function<std::uint8_t()>& ramp,
    int tick,int padding,const GroundStateStore& w){
    if(!ramp)throw std::invalid_argument("Drive Unlimbo requires current Cell");
    initializeDriveRamp(s,ramp(),tick,padding,w);
}
void observeDriveRamp(DriveRampState& s,const std::function<std::uint8_t()>& ramp,
    int tick,int padding,const GroundStateStore& w){
    if(!ramp)throw std::invalid_argument("Drive ramp observation requires current Cell");
    const int next=ramp();
    if(next==s.current)return;
    s.previous=s.current;write(w,0x1c,s.previous);
    s.current=next;write(w,0x18,next);
    timer(s,tick,padding,3,w);
}
}
