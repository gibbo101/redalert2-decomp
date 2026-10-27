// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/CellUnitScatterWorld.hpp"
#include "assets/UnitNearbyScatterWorld.hpp"
namespace ra2 {
struct CellNearbySearchInputs {
    // Same type indexes as CellUnitScatterView, including shared-type aliases.
    const std::map<int,int>& speedTypes5a4;
    const int& dimension1;
    const int& frame;
    const NearbyLocationPoint& emptyCell;
    const std::function<NearbyAdmissionCell(const MapCellInput&)>& bind;
    const NearbyAdmissionServices& admission;
};
// Separate unwired Cell -> Unit -> nearby search/destination composition.
// Snapshot/eligibility and admission-refresh policy remain in the shared Cell
// kernel. Every dispatched Unit borrows its own records and actual shared type
// field. No actor, map, floor cache, RNG or renderer owner is copied here.
template<class Admission,class Motion>
inline void scatterCellUnitsWithNearbyOnMap(int cell,const Coord& at,std::uint8_t ignoreMission,
    std::uint8_t ignoreDestination,std::uint8_t elevated,BasicCellUnitScatterView<Admission,Motion> v,
    const CellUnitScatterInputs& input,CellNearbySearchInputs nearby,
    const ScatterWorldTrace& trace={},const NearbyLocationMapTrace& nearbyTrace={}){
    for(const int type:v.typeIds)if(!nearby.speedTypes5a4.contains(type))
        throw std::invalid_argument("Cell nearby requires each shared type speed field");
    scatterCellUnitsOnMapWithUnitCall(cell,at,ignoreMission,ignoreDestination,elevated,v,input,trace,
        [&](auto unit,int id,const Coord& point,std::uint8_t im,std::uint8_t dest,const auto& checkedTrace){
            const UnitNearbySearchInputs search{nearby.speedTypes5a4.at(v.typeIds[std::size_t(id)]),
                nearby.dimension1,nearby.frame,nearby.emptyCell,nearby.bind,nearby.admission,input.squareRoot};
            scatterUnitWithNearbyOnMap(unit,point,im,dest,input.driveData.directionsToTargets,
                input.random,input.neighbors,input.height,input.tick,input.destinationPadding[std::size_t(id)],
                input.delay,input.stopScale,input.missionControl,search,checkedTrace,nearbyTrace);
        });
}
}
