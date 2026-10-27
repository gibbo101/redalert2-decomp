// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/NearbyLocationMap.hpp"
#include "assets/UnitScatterWorld.hpp"
namespace ra2 {
struct UnitNearbySearchInputs {
    const int& type5a4;
    const int& dimension1;
    const int& frame;
    const NearbyLocationPoint& emptyCell;
    const std::function<NearbyAdmissionCell(const MapCellInput&)>& bind;
    const NearbyAdmissionServices& admission;
    const std::function<double(double)>& squareRoot;
};
// Separate unwired Unit caller join. The search borrows the caller's actual map,
// fallback, permission shape and type input, then returns to actual destination
// effects. It supplies neither routes nor movement. Initial associations remain
// supplied; unsupported calls are not transactional and previews must discard
// their entire owner. The legacy nonzero-point facade keeps its refusal.
template<class Admission,class Motion>
inline void scatterUnitWithNearbyOnMap(BasicUnitScatterWorldView<Admission,Motion> v,const Coord& away,
    std::uint8_t ignoreMission,std::uint8_t ignoreDestination,const DirectionData& directions,
    OriginalRandomState& random,std::array<ScatterCellPoint,8> neighbors,int height,int tick,
    int destinationPadding,int destinationDelay,double stopScale,
    const std::function<std::uint8_t(int,int)>& missionControl,
    UnitNearbySearchInputs nearby,const ScatterWorldTrace& trace={},
    const NearbyLocationMapTrace& nearbyTrace={}){
    // Nonzero-point admission still has the earlier Track-only association.
    // The nearby Cell child accepts all supplied speed types, but must never
    // silently widen that distinct Unit-admission profile.
    const ScatterWorldTrace checkedTrace=[&](char g,char k,std::int64_t a,std::int64_t b,std::int64_t c){
        if(g=='w'&&k=='A'&&nearby.type5a4!=1)
            throw UnsupportedUnitScatter("Non-Track Unit admission speed remains unjoined");
        if(trace)trace(g,k,a,b,c);
    };
    scatterOrdinaryUnitOnMapWithSearch(v,away,ignoreMission,ignoreDestination,directions,
        random,neighbors,height,tick,destinationPadding,destinationDelay,stopScale,
        missionControl,checkedTrace,nearby.type5a4,[&](auto source,auto close,int speed,std::uint32_t alternate,const auto& map){
            const NearbyLocationPoint p{source.x,source.y},target{close.x,close.y};
            if(nearbyTrace){nearbyTrace('S',p,nullptr,speed);nearbyTrace('A',target,nullptr,std::bit_cast<std::int32_t>(alternate));}
            NearbyLocationOptions options;options.speedType=speed;options.alternate=alternate;
            const NearbyLocationMapView world{map,v.permission,nearby.dimension1,
                nearby.frame,nearby.emptyCell,nearby.bind,nearby.admission};
            const auto result=nearbyLocationOnMap(p,target,options,world,nearby.squareRoot,nearbyTrace);
            if(nearbyTrace)nearbyTrace('R',result,nullptr,0);
            return ScatterCellPoint{result.x,result.y};
        });
}
}
