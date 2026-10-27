// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "platform/BootCampWalkWorld.hpp"
#include "render/RadarActors.hpp"
#include "render/RadarActorMarkers.hpp"
#include "render/RadarActorPlacement.hpp"
#include "render/RadarActorPermission.hpp"
#include "sim/BuildingCoordinates.hpp"
#include "render/RadarStorage.hpp"
namespace ra2 {
// Scoped host association, not a second actor/House simulation. All consumed
// fields belong to the existing Walk/Structure/type/mission House owners.
// Marker placement, palettes and original startup remain caller boundaries.
class BootCampRadarActors {
    BootCampWalkWorld& owner_;
    RadarPixelServices& pixels_;
    SurfaceMarkServices& marks_;
    RadarPixelActorProbes probes_;
    RadarColorWorld colors_;
    RadarPixelActorWorld actors_;
    RadarActorsBinding binding_;
    decltype(SurfaceMarkServices::houseIndex15F40) savedIndex_;
    UnitDiscoveryHouse& house(const void* p)const{
        for(const auto& [id,h]:owner_.missionWorld_->houses())
            if(p==&h.indexAlliance)return owner_.missionWorld_->house(id);
        throw std::invalid_argument("Foreign Boot Camp radar House");
    }
    static const void* actorOwner(BootCampWalkWorld& owner,int id){
        const int key=owner.actors_.contains(id)?owner.actors_.at(id).object.mission.owner:
            owner.missionWorld_->structureSight(id).discovery.owner;
        return key==-1?nullptr:owner.visibilityWorld_->house(key);
    }
    const void* actorOwner(int id)const{return actorOwner(owner_,id);}
    RadarColorActor actor(const void* p)const{
        const int id=owner_.sightActorId(p);
        if(owner_.actors_.contains(id)){
            const auto& a=owner_.actors_.at(id);
            return {RadarColorActorKind::infantry,a.byte170,[this,id]{return actorOwner(id);},[this,id]()->const void*{
                const int key=owner_.actors_.at(id).alternateHouse410;
                return key==-1?nullptr:owner_.visibilityWorld_->house(key);
            }};
        }
        return {RadarColorActorKind::building,owner_.missionWorld_->structureExpirationState(id).byte170,
            [this,id]{return actorOwner(id);},{}};
    }
    const void* type(const void* p)const{
        const int id=owner_.sightActorId(p);
        return owner_.actors_.contains(id)?static_cast<const void*>(&owner_.type_):
            &owner_.missionWorld_->structureSightType(id);
    }
    const std::uint8_t& typeFlag(const void* p)const{
        if(p==&owner_.type_)return owner_.type_.radarFlag1ff;
        return owner_.missionWorld_->structureRadarTypeFlag(p);
    }
    RadarPixelTimer timer(const void* p)const{
        const int id=owner_.sightActorId(p);
        if(owner_.actors_.contains(id)){
            const auto& a=owner_.actors_.at(id);return {a.radarTimerStart13c,a.radarTimerRemaining144};
        }
        const auto& a=owner_.missionWorld_->structureSightState(id);
        return {a.radarTimerStart13c,a.radarTimerRemaining144};
    }
public:
    BootCampRadarActors(BootCampWalkWorld& owner,RadarPixelServices& pixels,
            SurfaceMarkServices& marks,const SchemeResolverWorld& schemes,
            const RadarPixelActorProbes& probes={}):owner_(owner),pixels_(pixels),marks_(marks),probes_(probes),
        colors_{pixels.currentHouseA35DB4,[this](auto p){return actor(p);},[this](auto p){
            const auto& h=house(p);return RadarColorHouse{h.indexAlliance.countryIndex,h.indexAlliance.allianceMask};
        },{}},
        actors_{colors_,owner.missionWorld_->discoveryMode(),schemes,
            [this](auto p){return type(p);},[this](auto p)->const std::uint8_t&{return typeFlag(p);},
            [this](auto p){const auto& h=house(p);return RadarPixelHouseFields{h.human134,h.control135,h.radarColor55e9};},
            [this](auto p){return timer(p);}},binding_(pixels,actors_,probes_){
        if(&marks.schemesAB6EFC!=&schemes.registryAB6EFC||
           &pixels.frameA40D2C!=&owner.globals_.tick||
           pixels.currentHouseA35DB4!=owner.visibilityWorld_->house(owner.missionWorld_->currentHouse()))
            throw std::invalid_argument("Boot Camp radar needs shared scheme/frame and actual player House");
        decltype(savedIndex_) index=[this](auto p){return house(p).radarScheme15f40;};
        savedIndex_=std::move(marks_.houseIndex15F40);marks_.houseIndex15F40=std::move(index);
    }
    const RadarPixelActorWorld& world()const{return actors_;}
    // Pure borrowed associations for explicit marker operations. Stock kind2C
    // is constant15/6; clamped1A0/1A4 remain on the actual actor owners.
    static RadarMarkerBucketServices markerServices(BootCampWalkWorld& owner){
        RadarMarkerBucketServices s;
        s.kind2C=[&owner](auto p){const auto id=owner.sightActorId(p);return owner.actors_.contains(id)?15:6;};
        s.owner1B4=[&owner](auto p){return actorOwner(owner,owner.sightActorId(p));};
        s.position=[&owner](auto p){const auto id=owner.sightActorId(p);
            if(owner.actors_.contains(id)){auto& a=owner.actors_.at(id);return RadarMarkerPosition{a.radarX1a0,a.radarY1a4};}
            auto& a=owner.missionWorld_->structureSight(id).fields;return RadarMarkerPosition{a.radarX1a0,a.radarY1a4};
        };return s;
    }
    // Explicit complete caller composition, with synchronous actual-owner lifetime.
    static void updateMarker(BootCampWalkWorld& owner,RadarStorage& storage,const void* p,RadarActorMarkerOperation op){
        const auto id=owner.sightActorId(p);
        auto fields=[&]()->RadarActorMarkerFields{
            if(owner.actors_.contains(id)){auto& a=owner.actors_.at(id);
                return {a.radarX1a0,a.radarY1a4,a.radarRegistered37b};}
            auto& a=owner.missionWorld_->structureSight(id).fields;
            return {a.radarX1a0,a.radarY1a4,a.radarRegistered37b};
        }();
        const auto markers=markerServices(owner);
        const void* current=owner.visibilityWorld_->house(owner.missionWorld_->currentHouse());
        RadarActorMarkerServices services;
        services.insert631910=[&](auto actor,auto x,auto y){storage.insertMarker(actor,x,y,current,markers);};
        services.remove631AF0=[&](auto actor,auto x,auto y){storage.removeMarker(actor,x,y,current,markers);};
        services.dirty632620=[&](auto point){storage.queueDirtyPoint(point);};
        services.shape6328D0=[&](auto actor)->const RadarShapeVector&{
            const auto key=owner.sightActorId(actor);
            return radarActorFootprint(storage.shapeBuckets(),owner.missionWorld_->structureSightType(key).radarFootprintC78);
        };
        if(owner.actors_.contains(id))infantryRadarMarker(op,p,fields,services);
        else buildingRadarMarker(op,p,fields,services);
    }
    RadarMarkerBucketServices markerServices(){return markerServices(owner_);}
    void updateMarker(RadarStorage& storage,const void* p,RadarActorMarkerOperation op){
        updateMarker(owner_,storage,p,op);
    }
    // Complete2F8 on actual fields. Height1B0 and2FC remain explicit entered
    // child boundaries; never substitute a host distance or primary visibility.
    bool markerPermission(const void* p,std::int32_t& status,const std::uint32_t& sessionFlags,
            RadarPermissionServices services={}){
        const auto id=owner_.sightActorId(p);const std::uint8_t unused=0;
        auto fields=[&]()->RadarPermissionActor{
            if(owner_.actors_.contains(id)){const auto& a=owner_.actors_.at(id);
                return {a.ground.position,a.radar325,a.object.mission.current373,a.veterancy118,
                    owner_.positions_.at(id).mode1b8,unused,unused};}
            const auto a=owner_.missionWorld_->structureSight(id);const auto& f=a.fields;
            return {a.position,unused,a.discovery.current373,f.veterancy118,f.radarMode1b8,f.radar5bd,f.radar5b7};
        }();
        services.type80=[&]()->RadarPermissionType{
            if(owner_.actors_.contains(id)){const auto& t=owner_.type_;
                return {t.radarAA6,t.radarAA7,t.radarVeteran277,t.radarElite289};}
            const auto& t=owner_.missionWorld_->structureSightType(id);
            return {t.radarAA6,t.radarAA7,t.radarVeteran277,t.radarElite289};
        };
        services.owner1B4=[&]{return actorOwner(id);};
        services.local4F52B0=pixels_.local4F52B0;
        services.allied4E5540=[&](auto self,auto other){return radarColorAllied(self,other,colors_);};
        services.primary568140=[&](auto point){return std::uint32_t(owner_.visibilityWorld_->visible(point,false));};
        services.secondary5683C0=[&](auto point){return std::uint32_t(owner_.visibilityWorld_->visible(point,true));};
        services.foundationHeight458940=[&](auto arg){if(arg)throw std::invalid_argument("Permission height argument must be zero");
            return owner_.missionWorld_->structureResident(id).height;};
        services.foundationWidth458930=[&]{return owner_.missionWorld_->structureResident(id).width;};
        const RadarPermissionWorld world{pixels_.modeB263D8,sessionFlags,colors_.currentA35DB4};
        return owner_.actors_.contains(id)?infantryRadarPermission(status,fields,world,services):
            buildingRadarPermission(status,fields,world,services);
    }
    void placeMarkerWithPermission(RadarStorage& storage,const void* p,std::uint32_t argument,
            const std::int32_t& loading,const std::uint32_t& sessionFlags,
            RadarPermissionServices permission,RadarActorPlacementServices placement){
        placement.permission2F8=[&](auto& status){return std::uint32_t(markerPermission(p,status,sessionFlags,permission));};
        placeMarker(storage,p,argument,loading,std::move(placement));
    }
    // Explicit complete parent seam, never called by Walk/arrival/SDL. The
    // permission/status, screen and remaining child boundaries must be supplied.
    void placeMarker(RadarStorage& storage,const void* p,std::uint32_t argument,
            const std::int32_t& loading,RadarActorPlacementServices services){
        const auto id=owner_.sightActorId(p);
        auto fields=[&]()->RadarActorPlacementFields{
            if(owner_.actors_.contains(id)){auto& a=owner_.actors_.at(id);
                return {a.ground.position,a.object.mission.current373,{a.radarX1a0,a.radarY1a4,a.radarRegistered37b},
                    a.object.flags14,a.secondary574,[this,id]{return actorOwner(id);},a.radarTimerStart13c,a.radarTimerRemaining144};}
            auto resident=owner_.missionWorld_->structureResident(id);
            auto sight=owner_.missionWorld_->structureSight(id);auto& a=sight.fields;
            return {resident.position88,sight.discovery.current373,{a.radarX1a0,a.radarY1a4,a.radarRegistered37b},
                resident.flags14,a.radarSecondary574,[this,id]{return actorOwner(id);},a.radarTimerStart13c,a.radarTimerRemaining144};
        }();
        // Stock Building48 uses the existing recovered foundation-center kernel;
        // dimension initialization/type-table association remains supplied.
        services.coordinates48=[&]{
            if(owner_.actors_.contains(id))return fields.coordinates88;
            const auto building=owner_.missionWorld_->structureResident(id);
            return buildingCoordinates({[building](auto arg){if(arg)throw std::invalid_argument("Building48 height argument");return building.height;},
                [building]{return building.width;},[building]{return building.position88;}});
        };
        services.discovery568140=[&](auto point){
            return std::uint32_t(owner_.visibilityWorld_->visible(point,false));
        };
        services.kind2C=[&]{return owner_.actors_.contains(id)?15:6;};
        services.remove424=[&]{updateMarker(storage,p,RadarActorMarkerOperation::remove);};
        services.insert420=[&]{updateMarker(storage,p,RadarActorMarkerOperation::insert);};
        services.dirty428=[&]{updateMarker(storage,p,RadarActorMarkerOperation::dirty);};
        services.flashDivisor90=pixels_.flashDivisor90;
        placeActorRadar(argument,fields,{loading,owner_.globals_.tick,colors_.currentA35DB4},services);
    }
    ~BootCampRadarActors(){marks_.houseIndex15F40=std::move(savedIndex_);}
    BootCampRadarActors(const BootCampRadarActors&)=delete;
    BootCampRadarActors& operator=(const BootCampRadarActors&)=delete;
    BootCampRadarActors(BootCampRadarActors&&)=delete;
    BootCampRadarActors& operator=(BootCampRadarActors&&)=delete;
};
}
