// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"
#include "sim/OriginalRandomRange.hpp"
#include "sim/UnitDiscovery.hpp"
#include <functional>
#include <stdexcept>

namespace ra2 {
struct ScatterCellPoint {
    std::int16_t x=0,y=0;
    bool operator==(const ScatterCellPoint&) const = default;
};
struct UnitScatterCell {
    ScatterCellPoint point;
    std::int8_t level=0;
    std::uint32_t flags=0;
};
struct UnitScatterActor {
    UnitDiscoveryActor mission;
    Facing body;
    Coord position;
    std::uint8_t isTrain=0,field5c8=0,field5b9=0,field599=0,bridge79=0;
    bool destination494=false,target228=false;
    std::int32_t type5a4=0;
};
// Only the verified ordinary Drive identity, successful acquisition and retained
// references are supported. This is not a general COM implementation.
struct UnitScatterDriveLifetime {
    std::uint32_t globalReferences=0,references=1;
};
struct UnitScatterServices {
    std::function<std::uint8_t(int,int)> missionControl; // raw mission, byte offset
    std::function<Coord()> coordinates;
    std::function<UnitScatterCell&(ScatterCellPoint)> lookup;
    std::function<std::uint8_t()> layer;
    std::function<bool(ScatterCellPoint)> inBounds;
    std::function<std::int32_t()> admissionLevel;
    std::function<int(UnitScatterCell&,int,std::int32_t)> admission;
    std::function<ScatterCellPoint(Coord)> project;
    // Policy constants and two distinct input Cell buffers are supplied to the
    // original pathfinder. This service does NOT recover route search.
    std::function<ScatterCellPoint(ScatterCellPoint,ScatterCellPoint,int,std::uint32_t)> pathfinder;
    std::function<void(UnitScatterCell&,std::uint8_t)> destination;
    // Logical read-only observation; values do not stand in for query results.
    std::function<void(char,std::int64_t,std::int64_t,std::int64_t)> trace;
};
struct UnitScatterInputs {
    const DirectionData& directions;
    OriginalRandomState& random;
    UnitScatterDriveLifetime& lifetime;
    std::array<ScatterCellPoint,8> neighbors;
    Coord emptyCoordinate{};
    ScatterCellPoint emptyCell{};
    std::int32_t height=104,tick=0;
};

// Unit Scatter control policy, with explicit unjoined map/coordinate/layer/
// admission/projection/pathfinder/destination services. Unwired; see recovery
// note. Ordinary Drive's class id differs from the parent's excluded class.
// Structural views may borrow these same fields; no actor/Drive copy is needed.
inline void scatterUnit(auto& a,const Coord& away,std::uint8_t ignoreMission,
    std::uint8_t ignoreDestination,auto& w,auto& s) {
    const auto event=[&](char c,std::int64_t x=0,std::int64_t y=0,std::int64_t z=0){if(s.trace)s.trace(c,x,y,z);};
    const auto mission=[&](){const int m=unitDiscoveryMission(a.mission);event('M',m);return m;};
    if(mission()==0||mission()==6||mission()==16)return;
    event('T');if(a.isTrain)return;
    if(w.lifetime.references==0||w.lifetime.references>=0x7fffffffu)
        throw std::invalid_argument("Unit Scatter needs retained ordinary Drive references");
    ++w.lifetime.globalReferences;event('C',w.lifetime.globalReferences);
    ++w.lifetime.references;event('I',w.lifetime.references);
    struct Release {
        decltype(w.lifetime)& state;
        decltype(event)& observe;
        ~Release(){--state.globalReferences;observe('C',state.globalReferences);--state.references;observe('I',state.references);}
    } release{w.lifetime,event};
    event('G'); // actual ordinary Drive GetClassID association; no GUID bytes
    if(!s.missionControl)throw std::invalid_argument("Missing Scatter mission control");
    if(!(s.missionControl(a.mission.mission98,9)||ignoreMission))return;
    const bool rotating=a.body.rotating(w.tick);event('F',rotating);if(rotating)return;
    if(a.destination494&&!ignoreDestination)return;
    if(a.field5c8)return;
    const auto cellOf=[](Coord p){return ScatterCellPoint{std::int16_t(p.x/256),std::int16_t(p.y/256)};};
    const auto lookup=[&](ScatterCellPoint p)->auto&{
        if(!s.lookup)throw std::invalid_argument("Missing Scatter map lookup");return s.lookup(p);};
    const auto destination=[&](ScatterCellPoint p){
        auto& c=lookup(p);if(!s.destination)throw std::invalid_argument("Missing Scatter destination effects");s.destination(c,1);};
    if(away==w.emptyCoordinate){
        if(!s.coordinates||!s.pathfinder)throw std::invalid_argument("Missing Scatter pathfinder/coordinates");
        const auto p=s.coordinates();
        // MOV AL preserves the upper bytes of the signed Y/256 result at the
        // original call site. They are padding, not a new bridge arithmetic rule.
        const auto bridge=(std::uint32_t(p.y/256)&0xffffff00u)|a.bridge79;
        const auto chosen=s.pathfinder(cellOf(p),{},a.type5a4,bridge);
        if(chosen!=w.emptyCell)destination(chosen);
        return; // zero-point path does not queue mission2
    }
    if(s.missionControl(a.mission.mission98,7))return;
    event('K',1);if(a.field5b9)return;
    if(a.destination494&&(!ignoreDestination||a.field599))return;
    const auto random=[&](int low,int high){
        const auto result=rangedOriginalRandom(w.random,low,high,[&](auto raw,const auto& after){event('D',raw,after.next1,after.next2);});
        event('R',low,high,result);return result;};
    if(a.target228&&!ignoreMission&&random(1,4)!=1)return;
    std::uint16_t heading;
    if(away==w.emptyCoordinate){heading=a.body.current(w.tick);event('J',heading);}
    else {heading=destinationDirection(w.directions,away,a.position);event('B',heading);}
    const int start=((((int(heading)>>12)+1)>>1)+random(0,2)-1)&7;
    if(!s.coordinates||!s.layer)throw std::invalid_argument("Missing Scatter coordinate/layer queries");
    const auto center=cellOf(s.coordinates());auto& current=lookup(center);
    const auto layer=s.layer();
    const bool raised=int(current.level)+layer!=0;
    (void)s.coordinates(); // repeated original query remains observable
    const auto z=signed32(std::uint32_t(w.height)*(raised?4u:0u));
    ScatterCellPoint first{},preferred{}; // not initialized from global sentinel
    for(int i=0;i<8;++i){
        const int dir=(start+i)&7;const auto delta=w.neighbors[std::size_t(dir)];
        const ScatterCellPoint p{std::int16_t(std::uint16_t(center.x)+std::uint16_t(delta.x)),
            std::int16_t(std::uint16_t(center.y)+std::uint16_t(delta.y))};
        auto& c=lookup(p); // lookup precedes bounds
        if(!s.inBounds)throw std::invalid_argument("Missing Scatter bounds");
        if(!s.inBounds(p))continue;
        if(!s.admissionLevel||!s.admission)throw std::invalid_argument("Missing Scatter admission");
        const auto level=s.admissionLevel();
        if(s.admission(c,dir,level)!=0)continue;
        if(first==w.emptyCell)first=p;
        if(w.emptyCell!=ScatterCellPoint{})continue;
        if(!s.project)throw std::invalid_argument("Missing Scatter projection");
        const Coord point{int(p.x)*256+128,int(p.y)*256+128,z};
        if(s.project(point)!=p)continue;
        if(lookup(p).flags&0x100u)continue;
        preferred=p;break;
    }
    const auto chosen=preferred==w.emptyCell?first:preferred;
    if(chosen==w.emptyCell)return;
    event('q',2);
    queueUnitDiscoveryMission(a.mission,2,[&](int,int off,std::uint32_t value){event('W',off,value);});
    destination(chosen);
}
}
