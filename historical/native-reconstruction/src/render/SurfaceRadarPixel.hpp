// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceRefreshMarks.hpp"
#include "render/SurfaceFill.hpp"
#include "sim/OriginalMath.hpp"
#include <cmath>
namespace ra2 {
struct RadarMapPoint {std::int32_t x,y,z;};
struct RadarPixelVirtuals {
    std::function<std::uint32_t(RefreshSurface&,RefreshRect&)> get28;
    std::function<void(RefreshSurface&,RefreshRect&,std::uint32_t)> set24;
};
struct RadarPixelTimer {const std::int32_t& start13C;const std::int32_t& remaining144;};
struct RadarPixelServices {
    const void* const& currentHouseA35DB4;
    const std::int32_t& modeB263D8;
    RefreshSurface* const& first1218;RefreshSurface* const& second121C;
    const float& scale1484;
    const std::int32_t& offset148C;const std::int32_t& offset1494;
    const std::int32_t& screen1498;const std::int32_t& screen149C;
    RefreshRect& dirty1208;
    SurfaceMarkBuckets* const& buckets1254;
    // red bit/right shift, blue bit/right shift, green bit/right shift.
    // These are actual852FB8/BC/C0/C4/C8/CC, despite the channel order.
    const std::array<std::int32_t,6>& shifts;
    const std::int32_t& frameA40D2C;
    std::function<const RadarPixelVirtuals&(const RefreshSurfaceVirtuals*)> pixels;
    std::function<std::int32_t(RadarMapPoint&)> floor55A280;
    std::function<std::uint8_t(RadarMapPoint&)> discovery568140,discovery568280;
    std::function<const void*(const void*)> owner1B4;
    std::function<std::uint8_t(const void*)> local4F52B0,typeFlag1FF;
    std::function<std::uint8_t(const void*,const void*)> alliedObject4E5580;
    std::function<std::uint8_t(const void*)> actorC0;
    std::function<const void*(const void*,std::uint32_t)> actorCC;
    std::function<std::array<std::uint8_t,3>(const void*)> houseColor55E9;
    std::function<const SurfaceMarkScheme*(std::uint32_t)> resolve663D30;
    std::function<RadarPixelTimer(const void*)> timer;
    std::function<std::int32_t()> flashDivisor90;
    std::function<void(unsigned,std::int32_t)> dirtyStore;
};
// Original53-bit/toward-zero x87 projection including actual FTOL's qword
// indefinite/low-word behavior. Finite nonzero float scale is the explicit
// numeric domain; no original runtime executable/table reads are required.
inline RadarMapPoint projectRadarPoint(std::int32_t x,std::int32_t y,float scale,
        std::int32_t ox,std::int32_t oy){
    if(!std::isfinite(scale)||scale==0)throw std::invalid_argument("Radar projection scale outside finite nonzero profile");
    OriginalRounding rounding;
    volatile double a=double(x)/double(scale);a=a-double(ox);
    volatile double b=double(y)/double(scale);b=b+double(oy);
    const auto word=[](double v){const auto bits=!std::isfinite(v)||v<-0x1p63||v>=0x1p63?std::uint16_t(0):std::uint16_t(std::int64_t(v));return std::bit_cast<std::int16_t>(bits);};
    volatile double sum=b+a;sum=sum*.5;sum=sum+.5;
    const auto cx=word(sum);
    volatile double difference=b-a;difference=difference*.5;difference=difference+.5;
    const auto cy=word(difference);
    return {std::int32_t(cx)*256+128,std::int32_t(cy)*256+128,0};
}
inline std::uint32_t radarShiftRight(std::uint32_t v,std::int32_t count){return v>>(std::uint32_t(count)&31);}
inline std::uint32_t radarShiftLeft(std::uint32_t v,std::int32_t count){return v<<(std::uint32_t(count)&31);}
inline std::uint32_t packRadarHouseColor(std::array<std::uint8_t,3> rgb,const std::array<std::int32_t,6>& s){
    return radarShiftLeft(radarShiftRight(rgb[2],s[3]),s[2])|
        radarShiftLeft(radarShiftRight(rgb[1],s[5]),s[4])|
        radarShiftLeft(radarShiftRight(rgb[0],s[1]),s[0]);
}
inline std::uint32_t darkenRadarPixel(std::uint32_t color,const std::array<std::int32_t,6>& s){
    const auto channel=[&](int bit,int shift){return std::uint8_t(radarShiftLeft(radarShiftRight(std::uint16_t(color),s[bit]),s[shift]));};
    const auto red=channel(0,1),green=channel(4,5),blue=channel(2,3);
    return radarShiftLeft(radarShiftRight(std::uint32_t(blue)>>1,s[3]),s[2])|
        radarShiftLeft(radarShiftRight(std::uint32_t(green)>>1,s[5]),s[4])|
        radarShiftLeft(radarShiftRight(std::uint32_t(red)>>1,s[1]),s[0]);
}
// Complete632000 parent. Map/discovery/House/actor/pixel children are explicit
// named services until their separate composition proofs; initial state supplied.
inline void refreshRadarPixel(RefreshRect& point,const RadarPixelServices& s){
    const auto need=[](bool ok){if(!ok)throw std::invalid_argument("Missing radar pixel service/owner");};
    if(!s.currentHouseA35DB4)return;
    const auto table=[&](RefreshSurface* p){need(p&&p->table);return p->table;};
    auto* first=s.first1218;auto* firstTable=table(first);need(bool(firstTable->rect78));
    RefreshRect scratch{};auto* rect=firstTable->rect78(*first,scratch);need(rect!=nullptr);
    const auto x=point[0];if(x<(*rect)[0]||x>=fillAdd((*rect)[0],(*rect)[2]))return;
    const auto y=point[1];if(y<(*rect)[1]||y>=fillAdd((*rect)[1],(*rect)[3]))return;
    auto map=projectRadarPoint(x,y,s.scale1484,s.offset148C,s.offset1494);
    need(bool(s.floor55A280));map.z=s.floor55A280(map);
    bool hidden=false,dim=false;
    if(s.modeB263D8){need(bool(s.discovery568140));hidden=s.discovery568140(map)!=0;}
    if(s.modeB263D8){need(bool(s.discovery568280));dim=s.discovery568280(map)!=0;}
    const auto bucket=(std::uint32_t(point[0])-std::uint32_t(point[1])*5u)&255u;
    need(s.buckets1254!=nullptr);const auto list=(*s.buckets1254)[bucket];
    if(list.count>0)need(std::size_t(list.count)<=list.entries.size()&&list.count<=4096);
    const void* chosen=nullptr;
    for(std::int32_t i=0;i<list.count;++i){
        const auto& e=list.entries[std::size_t(i)];const auto actor=e.actor;
        if(e.x!=point[0]||e.y!=point[1])continue;
        if(hidden){need(bool(s.owner1B4)&&bool(s.local4F52B0));if(!s.local4F52B0(s.owner1B4(actor)))continue;}
        need(bool(s.typeFlag1FF));
        if(s.typeFlag1FF(actor)){need(bool(s.alliedObject4E5580));if(!s.alliedObject4E5580(s.currentHouseA35DB4,actor))continue;}
        chosen=actor;break;
    }
    need(bool(s.pixels));
    const auto read=[&]{auto* receiver=s.second121C;const auto& v=s.pixels(table(receiver));need(bool(v.get28));return v.get28(*receiver,point);};
    const auto write=[&](std::uint32_t color){auto* receiver=s.first1218;const auto& v=s.pixels(table(receiver));need(bool(v.set24));v.set24(*receiver,point,color);};
    if(chosen){
        need(bool(s.owner1B4)&&bool(s.actorC0));auto* house=s.owner1B4(chosen);
        if(s.actorC0(chosen)){need(bool(s.actorCC));house=s.actorCC(chosen,0);}
        std::uint32_t color;
        if(house){need(bool(s.houseColor55E9));color=packRadarHouseColor(s.houseColor55E9(house),s.shifts);}
        else{need(bool(s.resolve663D30));const auto* scheme=s.resolve663D30(1);need(scheme!=nullptr);color=scheme->index330;}
        need(bool(s.timer));const auto timer=s.timer(chosen);auto remaining=timer.remaining144;
        if(timer.start13C!=-1){const auto elapsed=fillSub(s.frameA40D2C,timer.start13C);remaining=elapsed>=remaining?0:fillSub(remaining,elapsed);}
        bool flash=false;
        if(remaining>0){need(bool(s.flashDivisor90));const auto divisor=s.flashDivisor90();need(divisor!=0);flash=((remaining-1)/divisor)%2==1;}
        if(flash&&s.owner1B4(chosen)==s.currentHouseA35DB4)color=~color;
        write(color);
    }else if(dim){const auto color=read();write(darkenRadarPixel(color,s.shifts));}
    else if(hidden)write(0);
    else{
        // Original saves the first table before entering second.get28, then
        // reloads the receiver. A callback can replace first/table independently.
        const auto* saved=table(s.first1218);const auto color=read();const auto& v=s.pixels(saved);need(bool(v.set24)&&s.first1218);v.set24(*s.first1218,point,color);
    }
    const auto px=fillAdd(point[0],s.screen1498),py=fillAdd(point[1],s.screen149C);
    RefreshRect out{px,py,1,1};
    if(s.dirty1208[2]>0&&s.dirty1208[3]>0){
        out=s.dirty1208;
        if(out[0]>px){out[2]=fillAdd(out[2],fillSub(out[0],px));out[0]=px;}
        if(out[1]>py){out[3]=fillAdd(out[3],fillSub(out[1],py));out[1]=py;}
        if(fillAdd(out[2],out[0])<fillAdd(px,1))out[2]=fillAdd(fillSub(px,out[0]),2);
        if(fillAdd(out[3],out[1])<fillAdd(py,1))out[3]=fillAdd(fillSub(py,out[1]),2);
    }
    for(unsigned i=0;i<4;++i){s.dirty1208[i]=out[i];if(s.dirtyStore)s.dirtyStore(i,out[i]);}
}
}
