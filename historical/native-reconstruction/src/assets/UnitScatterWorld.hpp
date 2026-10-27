// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCoordinateCell.hpp"
#include "assets/ScatterProjection.hpp"
#include "sim/FootCoordinates.hpp"
#include "sim/FootLayer.hpp"
#include "sim/MovingUnitAdmission.hpp"
#include "sim/UnitCellDestination.hpp"
#include "sim/UnitScatter.hpp"
#include <map>
namespace ra2 {
struct UnitScatterExtra {
    std::int8_t registry574=-1;
    std::uint8_t field5b9=0,field599=0;
    bool target228=false;
};
struct ScatterWorldCellBinding {MapCellInput* cell=nullptr;int id=-1;std::uint8_t abstractFlags=0;};
using ScatterWorldTrace=std::function<void(char,char,std::int64_t,std::int64_t,std::int64_t)>;
template<class Admission,class Motion> struct BasicUnitScatterWorldView {
    UnitDestinationView unit;
    const UnitDestinationProfile& profile;
    UnitScatterExtra& extra;
    Admission& admission;
    int mover=0;
    std::span<MapCellInput* const> slots;
    MapCellInput& fallback;
    std::span<const ScatterWorldCellBinding> bindings;
    MapFloorHeightState& floor;
    int& floorHeight;
    int& layerHeight;
    const MapPermissionShape& permission;
    std::span<const TerrainCellPoint> registry;
    // Optional actual motion projection, refreshed only at the admission query.
    std::function<const Motion*()> admissionMotion={};
};
using UnitScatterWorldView=BasicUnitScatterWorldView<UnitAdmissionWorld,UnitAdmissionMotionWorld>;
struct UnsupportedUnitScatter : std::invalid_argument {
    explicit UnsupportedUnitScatter(const char* why):std::invalid_argument(why){}
};
// Internal shared Scatter composition; the explicit search binding distinguishes
// the legacy nonzero-point entry from the nearby-search caller join.
// Unwired complete Scatter join. All reads/commands borrow the
// same movement, mission, lifetime and Cell identities. Initial records and
// world associations remain supplied; this neither finds routes nor advances.
template<class Admission,class Motion>
inline void scatterOrdinaryUnitOnMapWithSearch(BasicUnitScatterWorldView<Admission,Motion> v,const Coord& away,
    std::uint8_t ignoreMission,std::uint8_t ignoreDestination,const DirectionData& directions,
    OriginalRandomState& random,std::array<ScatterCellPoint,8> neighbors,int height,int tick,
    int destinationPadding,int destinationDelay,double stopScale,
    const std::function<std::uint8_t(int,int)>& missionControl,const ScatterWorldTrace& trace,
    const int& type5a4,const auto& nearbySearch){
    const auto event=[&](char group,char k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0){if(trace)trace(group,k,a,b,c);};
    if(v.slots.size()!=262144||v.admission.gates.slots.size()!=262144||
       &v.unit.mission!=&v.admission.gates.objects.at(v.mover).mission)
        throw std::invalid_argument("Scatter requires canonical shared mission/map records");
    const auto binding=[&](const MapCellInput& cell)->const ScatterWorldCellBinding&{
        for(const auto& b:v.bindings)if(b.cell==&cell)return b;
        throw std::invalid_argument("Scatter Cell identity missing");
    };
    const auto fallback=[&](MapInputPosition p){
        if constexpr(requires {v.admission.gates.forwardAssignedFallback;}){
            if(!v.admission.gates.forwardAssignedFallback)
                throw std::invalid_argument("Missing assigned Scatter fallback forwarding");
            v.admission.gates.forwardAssignedFallback({p.x,p.y});
        }else{
            v.fallback.position=p;
            v.admission.gates.cells.at(v.admission.gates.fallbackCell).point={p.x,p.y};
        }
        event('w','W',std::uint32_t(std::uint16_t(p.x))|(std::uint32_t(std::uint16_t(p.y))<<16));
    };
    MapAttributeLookup words{v.slots,&v.fallback,[&](auto p){event('w','L',p.x,p.y);},fallback};
    MapFloorHeightWorld floors{v.slots,&v.fallback,fallback};
    const auto coordinateCell=[&](Coord p)->MapCellInput&{event('w','K',p.x,p.y,p.z);return mapCoordinateCell(p,floors,262144);};
    const auto floor=[&](Coord p){event('w','F',p.x,p.y,p.z);int h=mapFloorHeight(v.floor,v.floorHeight,p,floors);event('w','f',h);return h;};
    const auto coordinates=[&](int flag){
        event('w','Q',flag);
        FootCoordinateServices s;
        s.locomotor=[&]{return driveSecondaryCoordinates(v.unit.drive.movement.actor.position,v.unit.drive.movement.head);};
        s.coordinates=[&]{return v.unit.drive.movement.actor.position;};
        const auto p=footSecondaryCoordinates(v.extra.registry574,v.registry,s);event('w','q',p.x,p.y,p.z);return p;
    };
    struct CellView {
        MapCellInput& input;std::int8_t& level;std::uint32_t& flags;
        explicit CellView(MapCellInput& c):input(c),level(c.level),flags(c.flags){}
    };
    std::map<MapCellInput*,CellView> views;
    struct Services {
        decltype(UnitScatterServices::missionControl) missionControl;
        decltype(UnitScatterServices::coordinates) coordinates;
        std::function<CellView&(ScatterCellPoint)> lookup;
        decltype(UnitScatterServices::layer) layer;
        decltype(UnitScatterServices::inBounds) inBounds;
        decltype(UnitScatterServices::admissionLevel) admissionLevel;
        std::function<int(CellView&,int,int)> admission;
        decltype(UnitScatterServices::project) project;
        decltype(UnitScatterServices::pathfinder) pathfinder;
        std::function<void(CellView&,std::uint8_t)> destination;
        decltype(UnitScatterServices::trace) trace;
    } s;
    struct ActorView {
        UnitDiscoveryActor& mission;Facing& body;Coord& position;
        const std::uint8_t& isTrain;const std::uint8_t& field5c8;
        std::uint8_t& field5b9;std::uint8_t& field599;std::uint8_t& bridge79;
        const void*& destination494;bool& target228;const int& type5a4;
    } actor{v.admission.gates.objects.at(v.mover).mission,v.unit.drive.movement.body,
        v.unit.drive.movement.actor.position,v.profile.isTrain,v.profile.field5c8,
        v.extra.field5b9,v.extra.field599,v.unit.drive.movement.actor.bridge79,
        v.unit.actor.target494,v.extra.target228,type5a4};
    struct Lifetime {std::uint32_t& globalReferences;std::uint32_t& references;};
    struct Inputs {
        const DirectionData& directions;OriginalRandomState& random;Lifetime lifetime;
        std::array<ScatterCellPoint,8> neighbors;Coord emptyCoordinate{};ScatterCellPoint emptyCell{};int height,tick;
    } inputs{directions,random,{v.unit.globalReferences,v.unit.references},neighbors,{},{},height,tick};
    s.coordinates=[&]{return coordinates(0);};
    s.lookup=[&](ScatterCellPoint p)->CellView&{
        auto& cell=mapAttributeCell({p.x,p.y},words);
        return views.try_emplace(&cell,cell).first->second;
    };
    s.layer=[&]{
        event('w','Y');FootLayerServices layer;
        layer.bridge=[&]{return actor.bridge79;};layer.secondaryCoordinates=coordinates;
        layer.actorCoordinates=[&]{return actor.position;};layer.floorHeight=floor;
        layer.levelHeight=[&]{return v.layerHeight;};layer.cellFlags=[&](Coord p){return coordinateCell(p).flags;};
        const auto value=footCoordinateLayer(v.extra.registry574,0,layer);event('w','y',value);return value;
    };
    s.inBounds=[&](ScatterCellPoint p){
        event('w','N',p.x,p.y);auto inlineMap=words;inlineMap.query={};
        const bool result=mapCellPermitted({p.x,p.y},true,v.permission,inlineMap);event('w','n',result);return result;
    };
    s.admissionLevel=[&]{
        event('w','V');(void)coordinateCell(actor.position);
        const auto& cell=coordinateCell(actor.position);
        const int level=int(cell.level)+(actor.bridge79?4:0);event('w','v',level);return level;
    };
    struct TraceScope {
        Admission& world;decltype(world.trace) saved;decltype(world.gates.trace) gate;
        explicit TraceScope(Admission& w):world(w),saved(w.trace),gate(w.gates.trace){}
        ~TraceScope(){world.trace=saved;world.gates.trace=gate;}
    } scope(v.admission);
    v.admission.trace=[&](char k,int a,int b,int c){
        if(k=='L')event('w','L',a,b);
        else if(k=='F'){
            if constexpr(requires {v.admission.gates.forwardAssignedFallback;})
                event('w','W',std::uint32_t(std::uint16_t(a))|(std::uint32_t(std::uint16_t(b))<<16));
            else fallback({std::int16_t(a),std::int16_t(b)});
        }
        else event('a',k,a,b,c);
    };
    v.admission.gates.trace=[&](char k,int a){event('a',k,a);};
    s.admission=[&](CellView& cell,int direction,int level){
        const auto id=binding(cell.input).id;event('w','A',id,direction,level);
        const auto* motion=v.admissionMotion?v.admissionMotion():nullptr;
        const int result=unit_admission_policy::unitAdmission(v.mover,id,direction,level,-1,1,v.admission,motion);
        event('w','a',result);return result;
    };
    s.project=[&](Coord p){event('w','P',p.x,p.y,p.z);const auto q=scatterProjectedCell(p,words);event('w','p',q.x,q.y);return ScatterCellPoint{q.x,q.y};};
    s.pathfinder=[&](auto source,auto close,int speed,std::uint32_t alternate){
        return nearbySearch(source,close,speed,alternate,words);
    };
    s.destination=[&](CellView& cell,std::uint8_t flag){
        event('w','S',binding(cell.input).id,flag);
        UnitDestinationServices destination;
        destination.trace=[&](char k,int a,int b,std::int64_t c){event('d',k,a,b,c);};
        destination.targetId=[&](const void* p){return binding(*static_cast<const MapCellInput*>(p)).id+1;};
        destination.coordinates=[&](const void* p){const auto q=mapCellCenterHeight(v.floor,v.floorHeight,*static_cast<const MapCellInput*>(p));event('d','Q',q.x,q.y,q.z);return q;};
        destination.cellFlags=[&](Coord p){return coordinateCell(p).flags;};
        destination.dispose=[](const void*){throw UnsupportedUnitScatter("Scatter owned-vector heap disposal unjoined");};
        const UnitDestinationInputs w{tick,destinationPadding,destinationDelay,{},stopScale};
        setOrdinaryUnitCellDestination(v.unit,&cell.input,flag,v.profile,w,destination,[&](const void* p){return binding(*static_cast<const MapCellInput*>(p)).abstractFlags;});
    };
    s.trace=[&](char k,std::int64_t a,std::int64_t b,std::int64_t c){event('s',k,a,b,c);};
    s.missionControl=[&](int raw,int offset){
        if(!missionControl)throw std::invalid_argument("Scatter requires supplied mission-control bytes");
        const auto value=missionControl(raw,offset);event('s','H',raw,offset,value);return value;
    };
    scatterUnit(actor,away,ignoreMission,ignoreDestination,inputs,s);
}
// Retained nonzero-point facade. Its supplied type value is never consumed by a
// supported call: the zero-point search stays explicitly refused.
template<class Admission,class Motion>
inline void scatterOrdinaryUnitOnMap(BasicUnitScatterWorldView<Admission,Motion> v,const Coord& away,
    std::uint8_t ignoreMission,std::uint8_t ignoreDestination,const DirectionData& directions,
    OriginalRandomState& random,std::array<ScatterCellPoint,8> neighbors,int height,int tick,
    int destinationPadding,int destinationDelay,double stopScale,
    const std::function<std::uint8_t(int,int)>& missionControl,const ScatterWorldTrace& trace={}){
    const int unusedType=1;
    scatterOrdinaryUnitOnMapWithSearch(v,away,ignoreMission,ignoreDestination,directions,
        random,neighbors,height,tick,destinationPadding,destinationDelay,stopScale,
        missionControl,trace,unusedType,[](auto,auto,int,std::uint32_t,const auto&)->ScatterCellPoint{
            throw UnsupportedUnitScatter("Zero-point original nearby search unjoined");
        });
}

}
