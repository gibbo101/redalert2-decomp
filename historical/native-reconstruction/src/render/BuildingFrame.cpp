// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingFrame.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {
int add(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
int sub(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
}
std::int32_t buildingAnimationFrame(BuildingAnimationFrameFields a,const BuildingFrameServices& s){
    const auto read=[&](int subject,int off,int value){if(s.read)s.read(subject,off,value);return value;};
    const auto actor=[&](int off,int value){return read(0,off,value);};
    const auto type=[&]{if(!s.type)throw std::invalid_argument("Building frame Type unbound");return s.type();};
    const auto tr=[&](int off,int value){return read(1,off,value);};
    const auto total=[&](BuildingFrameType t,std::uint32_t offset,bool startFirst=false){
        // x86 index*12 wraps before indexing. Retain valid aliases, refuse
        // accesses outside the actual borrowed sequence backing.
        if(offset%12||offset>60)throw std::invalid_argument("Building frame sequence outside borrowed Type");
        if(!offset){const auto count=tr(0xc90,t.images.countC90);return add(count,tr(0xc8c,t.images.startC8c));}
        const auto& seq=t.fields.sequences[offset/12-1];
        if(startFirst){const auto start=tr(0xc8c+offset,seq.start);return add(start,tr(0xc90+offset,seq.count));}
        const auto count=tr(0xc90+offset,seq.count);return add(count,tr(0xc8c+offset,seq.start));
    };
    const auto damaged=[&](bool alternate){
        if(!s.healthRatio5d4540)throw std::invalid_argument("Building frame health ratio unbound");
        const auto ratio=s.healthRatio5d4540();const auto& threshold=alternate?s.threshold1370:s.threshold1368;
        if(!threshold)throw std::invalid_argument("Building frame threshold unbound");
        return !(ratio>threshold()); // Original equal/unordered both enter.
    };
    const auto t=type();auto frame=actor(0xe0,a.frameE0);
    if(tr(0x1359,t.fields.flag1359))return actor(0x4ec,a.frame4ec);
    if(tr(0x135a,t.fields.flag135a))return actor(0x4f0,a.frame4f0);
    if(!actor(0x42c,a.stage42c)){
        if(tr(0x1351,t.images.flag1351))frame=sub(sub(total(t,0),frame),1);
        if(!s.mission16c)throw std::invalid_argument("Building frame mission unbound");
        if(s.mission16c()!=19)return frame;
        const auto stage=actor(0x42c,a.stage42c);const auto live=type();
        return sub(sub(total(live,std::uint32_t(stage)*12u),frame),1);
    }
    if(tr(0x121e,t.fields.flag121e)){
        if(damaged(true))return 1;
        return actor(0x564,a.field564)>0?2:0;
    }
    if(tr(0x1351,t.images.flag1351)){
        if(!damaged(false))return 0;
        const auto live=type();return add(tr(0x137c,live.images.count137c),1);
    }
    if(!damaged(false))return frame;
    if(actor(0x42c,a.stage42c)==1)return add(frame,1);
    const auto live=type();auto maximum=total(live,12);
    for(const auto offset:{24u,48u,60u}){const auto candidate=total(live,offset,offset==24);if(maximum<=candidate)maximum=candidate;}
    return add(frame,maximum);
}
}
