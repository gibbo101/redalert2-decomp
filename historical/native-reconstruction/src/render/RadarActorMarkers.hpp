// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/RadarMarkerBuckets.hpp"
namespace ra2 {
struct RadarActorMarkerFields {
    std::int32_t &x1A0,&y1A4;
    std::uint8_t& registered37B;
};
struct RadarBorrowedPoint {const std::int32_t &x,&y;};
enum class RadarActorMarkerOperation {insert,remove,dirty};
struct RadarActorMarkerServices {
    std::function<void(const void*,std::int32_t,std::int32_t)> insert631910,remove631AF0;
    std::function<void(RadarBorrowedPoint)> dirty632620;
    std::function<const RadarShapeVector&(const void*)> shape6328D0;
    std::function<void(std::uint8_t)> registrationStore;
};
// Complete6328D0. Original type construction/index selection remains separate.
inline const RadarShapeVector& radarActorFootprint(std::span<const RadarShapeVector,22> shapes,
        std::int32_t indexC78){
    if(indexC78<0||indexC78>=22)throw std::invalid_argument("Radar Building footprint index");
    return shapes[std::size_t(indexC78)];
}
inline void finishActorMarkerRegistration(RadarActorMarkerOperation op,RadarActorMarkerFields f,
        const RadarActorMarkerServices& s){
    if(op==RadarActorMarkerOperation::dirty)return;
    f.registered37B=op==RadarActorMarkerOperation::insert?1:0;
    if(s.registrationStore)s.registrationStore(f.registered37B);
}
inline void dispatchActorMarker(RadarActorMarkerOperation op,const void* actor,std::int32_t x,std::int32_t y,
        const RadarActorMarkerServices& s){
    const auto& child=op==RadarActorMarkerOperation::insert?s.insert631910:s.remove631AF0;
    if(!child)throw std::invalid_argument("Radar actor marker child unbound");child(actor,x,y);
}
// Complete6D74D0/6D7500/6D7530. The dirty child borrows actual fields rather
// than a stack snapshot; its width/height services may change them during entry.
inline void infantryRadarMarker(RadarActorMarkerOperation op,const void* actor,RadarActorMarkerFields f,
        const RadarActorMarkerServices& s){
    if(op==RadarActorMarkerOperation::dirty){
        if(!s.dirty632620)throw std::invalid_argument("Radar actor dirty child unbound");
        s.dirty632620({f.x1A0,f.y1A4});
    }else{const auto y=f.y1A4,x=f.x1A0;dispatchActorMarker(op,actor,x,y,s);}
    finishActorMarkerRegistration(op,f,s);
}
// Complete451800/451860/4518C0. Select once, but reload live vector backing,
// count and actor coordinates each iteration. Building dirty points are local.
inline void buildingRadarMarker(RadarActorMarkerOperation op,const void* actor,RadarActorMarkerFields f,
        const RadarActorMarkerServices& s){
    if(!s.shape6328D0)throw std::invalid_argument("Radar Building footprint unbound");
    const auto& shape=s.shape6328D0(actor);
    unsigned work=0;
    for(std::int32_t i=0;i<shape.count;i=fillAdd(i,1)){
        if(++work>4096||i<0||std::size_t(i)>=shape.items.size())
            throw std::invalid_argument("Radar Building footprint execution extent");
        const auto x=fillAdd(f.x1A0,shape.items[std::size_t(i)].x);
        const auto y=fillAdd(shape.items[std::size_t(i)].y,f.y1A4);
        if(op==RadarActorMarkerOperation::dirty){
            if(!s.dirty632620)throw std::invalid_argument("Radar actor dirty child unbound");
            s.dirty632620({x,y});
        }else dispatchActorMarker(op,actor,x,y,s);
    }
    finishActorMarkerRegistration(op,f,s);
}
}
