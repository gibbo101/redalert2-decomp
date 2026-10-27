// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceRadarPixel.hpp"
#include "sim/MapVisibility.hpp"
namespace ra2 {
// Both discovery calls borrow one map/fallback and the separate map-height
// divisor. Lifetime must enclose this binding; construction makes no queries.
class RadarDiscoveryBinding {
    RadarPixelServices& target_;
    decltype(RadarPixelServices::discovery568140) primary_,count_;
public:
    RadarDiscoveryBinding(RadarPixelServices& target,const MapVisibilityState& state,const MapVisibilityWorld& world,
        std::function<void(RadarMapPoint&,bool,std::uint8_t)> result={}):target_(target){
        decltype(primary_) primary=[&state,&world,result](RadarMapPoint& p){const auto value=std::uint8_t(mapPrimaryVisibility({p.x,p.y,p.z},state,world));if(result)result(p,false,value);return value;};
        decltype(count_) count=[&state,&world,result](RadarMapPoint& p){const auto value=std::uint8_t(mapCountVisibility({p.x,p.y,p.z},state,world));if(result)result(p,true,value);return value;};
        primary_=std::move(target_.discovery568140);count_=std::move(target_.discovery568280);
        target_.discovery568140=std::move(primary);target_.discovery568280=std::move(count);
    }
    ~RadarDiscoveryBinding(){target_.discovery568140=std::move(primary_);target_.discovery568280=std::move(count_);}
    RadarDiscoveryBinding(const RadarDiscoveryBinding&)=delete;
    RadarDiscoveryBinding& operator=(const RadarDiscoveryBinding&)=delete;
    RadarDiscoveryBinding(RadarDiscoveryBinding&&)=delete;
    RadarDiscoveryBinding& operator=(RadarDiscoveryBinding&&)=delete;
};
}
