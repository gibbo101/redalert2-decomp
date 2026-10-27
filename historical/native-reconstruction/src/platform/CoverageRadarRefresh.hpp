// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "platform/CoverageRadar.hpp"
#include "render/RadarRefresh.hpp"
namespace ra2 {
// Separate complete coverage -> both refresh branches association. The legacy
// nonzero facade retains its refusal. The shared refresh binding must outlive
// this entry; it proves which exact refresh/radar service owners are installed.
class CoverageRadarRefreshBinding {
    CoverageRadarBinding map_;
    TechnoCoverageServices& target_;
    decltype(TechnoCoverageServices::refresh634030) saved_;
    static TechnoCoverageServices& checked(TechnoCoverageServices& target,
            SurfaceRefreshServices& refresh,RadarPixelServices& radar,
            const RadarRefreshBinding& association){
        if(!association.binds(refresh,radar))
            throw std::invalid_argument("Coverage refresh association has different service owners");
        return target;
    }
public:
    CoverageRadarRefreshBinding(TechnoCoverageServices& target,SurfaceRefreshServices& refresh,
            RadarPixelServices& radar,const CoverageRadarWorld& world,
            SurfaceRefreshScratch& scratch,const RadarRefreshBinding& association):
        map_(checked(target,refresh,radar,association),refresh,radar,world,scratch),target_(target){
        decltype(saved_) draw=[&refresh,&scratch]{refreshSurfaces(refresh,scratch);};
        saved_=std::move(target_.refresh634030);target_.refresh634030=std::move(draw);
    }
    ~CoverageRadarRefreshBinding(){target_.refresh634030=std::move(saved_);}
    CoverageRadarRefreshBinding(const CoverageRadarRefreshBinding&)=delete;
    CoverageRadarRefreshBinding& operator=(const CoverageRadarRefreshBinding&)=delete;
    CoverageRadarRefreshBinding(CoverageRadarRefreshBinding&&)=delete;
    CoverageRadarRefreshBinding& operator=(CoverageRadarRefreshBinding&&)=delete;
};
}
