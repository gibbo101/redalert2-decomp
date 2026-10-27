// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceRefreshPixels.hpp"
#include "render/RadarSurfacePixels.hpp"
#include "render/RadarActors.hpp"
#include <memory>
#include <optional>
namespace ra2 {
struct RadarRefreshProbes {
    decltype(RadarSurfacePixelWorld::before) pixel;
    decltype(RadarSurfacePixelWorld::readResult) read;
    decltype(SurfaceMarkPixelServices::enter) mark;
};
struct RadarRefreshSurfacePolicy {
    // Pure table metadata; retain an already installed recovered device copy8.
    std::function<bool(const RefreshSurfaceVirtuals*)> retainCopy;
};
// Both634030 branches borrow one set of surfaces and stock actor/
// scheme services. Initial associations and geometry remain supplied. Callers
// install RadarActorsBinding on radar with this same actor world before entry.
class RadarRefreshBinding {
    SurfaceRefreshServices& refresh_;
    RadarPixelServices& radar_;
    SurfaceMarkServices& marks_;
    decltype(SurfaceRefreshServices::pixel632000) pixel_;
    decltype(SurfaceMarkServices::owner1B4) owner_;
    decltype(SurfaceMarkServices::actorC0) flag_;
    decltype(SurfaceMarkServices::actorCC) house_;
    decltype(SurfaceMarkServices::resolve663D30) resolve_;
    RadarSurfacePixelWorld world_;
    std::optional<RadarSurfacePixelsBinding> pixels_;
    std::optional<SurfaceRefreshPixelsBinding> zero_;
    std::vector<std::unique_ptr<SurfaceCopyBinding>> copies_;
    static CopySurface& surfaceOwner(const SurfaceCopyServices& services,RefreshSurface& surface){
        if(!services.surface)throw std::invalid_argument("Missing shared radar surface owner");
        auto& record=services.surface(surface);
        if(&record.geometry!=&surface)throw std::invalid_argument("Foreign shared radar geometry");
        validateCopySurface(record);return record;
    }
public:
    RadarRefreshBinding(SurfaceRefreshServices& refresh,SurfaceMarkServices& marks,
            RadarPixelServices& radar,const RadarPixelActorWorld& actors,
            std::span<RefreshSurfaceVirtuals* const> tables,const SurfaceCopyServices& surfaces,
            const RadarRefreshProbes& probes={},const RadarRefreshSurfacePolicy& policy={}):refresh_(refresh),radar_(radar),marks_(marks){
        if(&refresh.first1218!=&radar.first1218||&refresh.second121C!=&radar.second121C||
           &refresh.modeB263D8!=&radar.modeB263D8||&marks.first1218!=&radar.first1218||
           &marks.buckets1254!=&radar.buckets1254||
           &marks.schemesAB6EFC!=&actors.schemes.registryAB6EFC||
           &radar.currentHouseA35DB4!=&actors.colors.currentA35DB4||tables.empty()||!surfaces.surface)
            throw std::invalid_argument("Radar refresh needs shared surface/bucket/scheme/House owners");
        for(unsigned i=0;i<tables.size();++i){
            if(!tables[i])throw std::invalid_argument("Null shared radar table");
            for(unsigned j=0;j<i;++j)if(tables[i]==tables[j])throw std::invalid_argument("Duplicate shared radar table");
        }
        std::vector<bool> retain;
        for(const auto* table:tables){
            const bool keep=policy.retainCopy&&policy.retainCopy(table);
            if(keep&&!table->copy8)throw std::invalid_argument("Missing retained radar copy8");
            retain.push_back(keep);
        }
        // Prepare all replacements before installation. Forward to the live
        // stock actor bindings; never retain a copied actor/color service state.
        decltype(pixel_) pixel=[&radar](auto& point){refreshRadarPixel(point,radar);};
        decltype(owner_) owner=[&radar](auto p){if(!radar.owner1B4)throw std::invalid_argument("Missing radar Owner");return radar.owner1B4(p);};
        decltype(flag_) flag=[&radar](auto p){if(!radar.actorC0)throw std::invalid_argument("Missing radar C0");return radar.actorC0(p);};
        decltype(house_) house=[&radar](auto p,auto argument){if(!radar.actorCC)throw std::invalid_argument("Missing radar CC");return radar.actorCC(p,argument);};
        decltype(resolve_) resolve=[&radar](auto category){if(!radar.resolve663D30)throw std::invalid_argument("Missing radar resolver");return radar.resolve663D30(category);};
        world_.stockTables={tables.data(),tables.size()};
        world_.view=[&surfaces](auto& surface){return surfaceOwner(surfaces,surface).pixels;};
        world_.access=[&surfaces](auto& surface){return copySurfacePixelAccess(surfaceOwner(surfaces,surface));};
        world_.before=probes.pixel;world_.readResult=probes.read;
        world_.store=[&surfaces](auto& surface,auto at,auto n,auto value){auto& s=surfaceOwner(surfaces,surface);if(s.stores)s.stores(at,n,value);};
        world_.locks=[&surfaces](auto& surface,auto depth){auto& s=surfaceOwner(surfaces,surface);if(s.locks)s.locks(depth);};
        pixels_.emplace(radar,world_);
        zero_.emplace(*tables[0],refresh,marks,surfaces,probes.mark,retain[0]);
        for(unsigned i=1;i<tables.size();++i)if(!retain[i])copies_.push_back(std::make_unique<SurfaceCopyBinding>(*tables[i],surfaces));
        pixel_=std::move(refresh_.pixel632000);owner_=std::move(marks_.owner1B4);flag_=std::move(marks_.actorC0);
        house_=std::move(marks_.actorCC);resolve_=std::move(marks_.resolve663D30);
        refresh_.pixel632000=std::move(pixel);marks_.owner1B4=std::move(owner);marks_.actorC0=std::move(flag);
        marks_.actorCC=std::move(house);marks_.resolve663D30=std::move(resolve);
    }
    bool binds(const SurfaceRefreshServices& refresh,const RadarPixelServices& radar)const noexcept{
        return &refresh_==&refresh&&&radar_==&radar;
    }
    ~RadarRefreshBinding(){refresh_.pixel632000=std::move(pixel_);marks_.owner1B4=std::move(owner_);marks_.actorC0=std::move(flag_);marks_.actorCC=std::move(house_);marks_.resolve663D30=std::move(resolve_);}
    RadarRefreshBinding(const RadarRefreshBinding&)=delete;
    RadarRefreshBinding& operator=(const RadarRefreshBinding&)=delete;
    RadarRefreshBinding(RadarRefreshBinding&&)=delete;
    RadarRefreshBinding& operator=(RadarRefreshBinding&&)=delete;
};
}
