// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/ActorRadarColor.hpp"
#include "render/SchemeResolver.hpp"
#include "render/SurfaceRadarPixel.hpp"
namespace ra2 {
struct RadarPixelHouseFields {
    const std::uint8_t& flag134;const std::uint8_t& flag135;
    const std::array<std::uint8_t,3>& color55E9;
};
struct RadarPixelActorWorld {
    const RadarColorWorld& colors;
    const std::int32_t& houseModeA3D298;
    const SchemeResolverWorld& schemes;
    // Pure borrowed fields; stock80->84 and3C resolve these same owners.
    std::function<const void*(const void*)> type;
    std::function<const std::uint8_t&(const void*)> typeByte1FF;
    std::function<RadarPixelHouseFields(const void*)> house;
    std::function<RadarPixelTimer(const void*)> timer;
};
struct RadarPixelActorProbes {
    std::function<void(const void*,std::uint8_t)> local;
    std::function<void(const void*,const void*)> type;
    std::function<void(const void*,const void*,std::uint8_t)> alliedObject;
    ActorRadarColorProbes color;
    std::function<void(const SurfaceMarkScheme*)> resolved;
};
// Complete stock radar actor/House/resolver children below632000. Reuses the
// recovered predicates and color/resolver kernels. Kind/type/global/registry
// associations and all initial records remain supplied. Binding makes no queries.
class RadarActorsBinding {
    RadarPixelServices& target_;
    decltype(RadarPixelServices::owner1B4) owner_;
    decltype(RadarPixelServices::local4F52B0) local_,type_,flag_;
    decltype(RadarPixelServices::alliedObject4E5580) allied_;
    decltype(RadarPixelServices::actorCC) house_;
    decltype(RadarPixelServices::houseColor55E9) color_;
    decltype(RadarPixelServices::resolve663D30) resolve_;
    decltype(RadarPixelServices::timer) timer_;
public:
    RadarActorsBinding(RadarPixelServices& target,const RadarPixelActorWorld& world,
            const RadarPixelActorProbes& probes):target_(target){
        if(&target.currentHouseA35DB4!=&world.colors.currentA35DB4||!world.type||!world.typeByte1FF||!world.house||!world.timer)
            throw std::invalid_argument("Radar actors need shared current House and borrowed field views");
        decltype(owner_) owner=[&world](const void* p){const auto a=radarColorActor(world.colors,p);if(!a.owner1B4)throw std::invalid_argument("Missing radar Owner field");return a.owner1B4();};
        decltype(local_) local=[&world,&probes](const void* h){
            std::uint8_t result=0;
            if(world.houseModeA3D298)result=unitOwnerTypeVisible(world.houseModeA3D298,0,0,h==world.colors.currentA35DB4);
            else{if(!h)throw std::invalid_argument("Missing local radar House");const auto fields=world.house(h);result=unitOwnerTypeVisible(0,fields.flag134,fields.flag135,false);}
            if(probes.local)probes.local(h,result);return result;
        };
        decltype(type_) type=[&world,&probes](const void* p){const auto t=world.type(p);if(probes.type)probes.type(p,t);if(!t)throw std::invalid_argument("Missing stock radar type");return world.typeByte1FF(t);};
        decltype(allied_) allied=[&world,&probes,owner](const void* h,const void* p){
            const auto result=std::uint8_t(p?radarColorAllied(h,owner(p),world.colors):false);
            if(probes.alliedObject)probes.alliedObject(h,p,result);return result;
        };
        decltype(flag_) flag=[&world,&probes](const void* p){const auto result=actorRadarColorFlag(p,world.colors);if(probes.color.flag)probes.color.flag(p,result);return result;};
        decltype(house_) house=[&world,&probes](const void* p,std::uint32_t arg){const auto result=actorRadarColorHouse(p,arg,world.colors);if(probes.color.house)probes.color.house(p,arg,result);return result;};
        decltype(color_) color=[&world](const void* h){if(!h)throw std::invalid_argument("Missing radar RGB House");return world.house(h).color55E9;};
        decltype(resolve_) resolve=[&world,&probes](std::uint32_t category){const auto result=resolveSurfaceScheme("LightGrey",std::bit_cast<std::int32_t>(category),world.schemes);if(probes.resolved)probes.resolved(result);return result;};
        decltype(timer_) timer=world.timer;
        owner_=std::move(target_.owner1B4);local_=std::move(target_.local4F52B0);type_=std::move(target_.typeFlag1FF);allied_=std::move(target_.alliedObject4E5580);flag_=std::move(target_.actorC0);house_=std::move(target_.actorCC);color_=std::move(target_.houseColor55E9);resolve_=std::move(target_.resolve663D30);timer_=std::move(target_.timer);
        target_.owner1B4=std::move(owner);target_.local4F52B0=std::move(local);target_.typeFlag1FF=std::move(type);target_.alliedObject4E5580=std::move(allied);target_.actorC0=std::move(flag);target_.actorCC=std::move(house);target_.houseColor55E9=std::move(color);target_.resolve663D30=std::move(resolve);target_.timer=std::move(timer);
    }
    ~RadarActorsBinding(){target_.owner1B4=std::move(owner_);target_.local4F52B0=std::move(local_);target_.typeFlag1FF=std::move(type_);target_.alliedObject4E5580=std::move(allied_);target_.actorC0=std::move(flag_);target_.actorCC=std::move(house_);target_.houseColor55E9=std::move(color_);target_.resolve663D30=std::move(resolve_);target_.timer=std::move(timer_);}
    RadarActorsBinding(const RadarActorsBinding&)=delete;
    RadarActorsBinding& operator=(const RadarActorsBinding&)=delete;
    RadarActorsBinding(RadarActorsBinding&&)=delete;
    RadarActorsBinding& operator=(RadarActorsBinding&&)=delete;
};
}
