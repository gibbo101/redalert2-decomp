// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TechnoCoverage.hpp"
#include "render/RadarMap.hpp"
namespace ra2 {
struct CoverageRadarWorld {
    const RadarMapWorld& map;
    // Pure borrowed fields from the exact terrain Cell returned by548070.
    std::function<TechnoCoverageCell(MapCellInput&)> coverage;
    std::function<void(TerrainCellPoint)> query;
};
// Explicit unwired coverage -> complete nonzero634030 ->632000 composition.
// Shares one canonical map/fallback and actual12C/13C storage with discovery.
// This owns callbacks only. Stock actor/House/height services remain caller-bound.
class CoverageRadarBinding {
    TechnoCoverageServices& target_;
    SurfaceRefreshServices& refresh_;
    decltype(TechnoCoverageServices::cell) cell_;
    decltype(TechnoCoverageServices::refresh634030) refreshSaved_;
    decltype(SurfaceRefreshServices::pixel632000) pixel_;
public:
    CoverageRadarBinding(TechnoCoverageServices& target,SurfaceRefreshServices& refresh,
            RadarPixelServices& radar,const CoverageRadarWorld& world,
            SurfaceRefreshScratch& scratch):target_(target),refresh_(refresh){
        if(&target.currentHouse!=&radar.currentHouseA35DB4||
           &refresh.modeB263D8!=&radar.modeB263D8||
           &refresh.first1218!=&radar.first1218||&refresh.second121C!=&radar.second121C||
           world.map.floor.cells.size()!=262144||!world.map.floor.fallback||
           !world.map.discoveryFields||!world.coverage)
            throw std::invalid_argument("Coverage radar needs shared map/House/surface owners");
        decltype(cell_) cell=[&world](std::int16_t x,std::int16_t y){
            const TerrainCellPoint point{x,y};if(world.query)world.query(point);
            const int index=int(y)*512+int(x);
            auto* c=index>=0&&index<262144?world.map.floor.cells[std::size_t(index)]:nullptr;
            if(!c){c=world.map.floor.fallback;c->position={x,y};
                if(world.map.floor.fallbackStore)world.map.floor.fallbackStore(c->position);}
            auto fields=world.coverage(*c);const auto discovery=world.map.discoveryFields(*c);
            if(&fields.flags12C!=&discovery.flags12C||&fields.count13C!=&discovery.count13C)
                throw std::invalid_argument("Coverage radar Cell fields have distinct owners");
            return fields;
        };
        decltype(pixel_) pixel=[&radar](RefreshRect& p){refreshRadarPixel(p,radar);};
        decltype(refreshSaved_) draw=[&refresh,&scratch]{
            // This association does not silently enter the separate zero-mode
            // copy/marks implementation or claim rollback of preceding stores.
            if(!refresh.modeB263D8)throw std::invalid_argument("Coverage zero-mode refresh not joined");
            refreshSurfaces(refresh,scratch);
        };
        cell_=std::move(target_.cell);refreshSaved_=std::move(target_.refresh634030);pixel_=std::move(refresh_.pixel632000);
        target_.cell=std::move(cell);target_.refresh634030=std::move(draw);refresh_.pixel632000=std::move(pixel);
    }
    ~CoverageRadarBinding(){target_.cell=std::move(cell_);target_.refresh634030=std::move(refreshSaved_);refresh_.pixel632000=std::move(pixel_);}
    CoverageRadarBinding(const CoverageRadarBinding&)=delete;
    CoverageRadarBinding& operator=(const CoverageRadarBinding&)=delete;
    CoverageRadarBinding(CoverageRadarBinding&&)=delete;
    CoverageRadarBinding& operator=(CoverageRadarBinding&&)=delete;
};
}
