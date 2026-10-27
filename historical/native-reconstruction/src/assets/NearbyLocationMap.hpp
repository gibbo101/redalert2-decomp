// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/NearbyCellAdmission.hpp"
#include "assets/ScatterProjection.hpp"
#include "sim/NearbyLocationPolicy.hpp"
#include <map>
namespace ra2 {
struct NearbyLocationMapView {
    const MapAttributeLookup& map;
    const MapPermissionShape& permission;
    const int& dimension1;
    const int& frame;
    const NearbyLocationPoint& emptyCell;
    const std::function<NearbyAdmissionCell(const MapCellInput&)>& bind;
    const NearbyAdmissionServices& admission;
};
// Observational parent/permission/rectangle/projection boundaries. Cell pointers
// retain identity; nullptr means the event has no Cell. No extra world query.
using NearbyLocationMapTrace=std::function<void(char,NearbyLocationPoint,const MapCellInput*,int)>;
// Complete nearby policy with actual permission, rectangle/Cell admission and
// center projection over one borrowed map/fallback. Burrowability stays refused
// when entered; non-default zone resolution stays an explicit admission service.
// Initial records/geometry/frame/type associations remain supplied. Unwired.
inline NearbyLocationPoint nearbyLocationOnMap(const NearbyLocationPoint& source,
    const NearbyLocationPoint& closeTo,const NearbyLocationOptions& options,
    NearbyLocationMapView v,const std::function<double(double)>& squareRoot,
    const NearbyLocationMapTrace& trace={}){
    const auto event=[&](char k,NearbyLocationPoint p={},const MapCellInput* cell=nullptr,int n=0){if(trace)trace(k,p,cell,n);};
    struct CellView {
        MapCellInput& input;const std::int8_t& level;const std::uint32_t& flags;
        explicit CellView(MapCellInput& c):input(c),level(c.level),flags(c.flags){}
    };
    std::map<MapCellInput*,CellView> cells;
    struct Services {
        std::function<CellView&(NearbyLocationPoint)> lookup;
        std::function<bool(CellView&,int)> permission;
        decltype(NearbyLocationServices::rectangle) rectangle;
        std::function<bool(CellView&)> burrowable;
        decltype(NearbyLocationServices::projectCenter) projectCenter;
        decltype(NearbyLocationServices::squareRoot) squareRoot;
    } services;
    services.lookup=[&](auto p)->CellView&{
        auto& cell=mapAttributeCell({p.x,p.y},v.map);event('L',p,&cell);
        return cells.try_emplace(&cell,cell).first->second;
    };
    services.permission=[&](CellView& c,int flag){
        event('B',{c.input.position.x,c.input.position.y},&c.input,flag);
        const bool result=nearbyCellPermitted(c.input,std::uint8_t(flag),v.permission);
        event('b',{},&c.input,result);return result;
    };
    services.rectangle=[&](auto p,int w,int h,int speed,int zone,int movement,int level,std::uint32_t alternate,std::uint8_t overlay){
        event('T',p);
        const bool result=nearbyRectangleAdmits({p.x,p.y},w,h,speed,zone,movement,level,alternate,overlay,v.map,v.bind,v.admission);
        event('t',{},nullptr,result);return result;
    };
    services.burrowable=[](auto&)->bool{throw std::invalid_argument("Nearby burrowability unjoined");};
    services.projectCenter=[&](auto p){
        event('P',p);
        const auto result=scatterProjectedCell({int(p.x)*256+128,int(p.y)*256+128,0},v.map);
        const NearbyLocationPoint q{result.x,result.y};event('p',q);return q;
    };
    services.squareRoot=squareRoot;
    struct World {const int& dimension0;const int& dimension1;const int& frame;const NearbyLocationPoint& emptyCell;};
    const World world{v.permission.dimension0,v.dimension1,v.frame,v.emptyCell};
    return nearbyLocationPolicy(source,closeTo,options,world,services);
}
}
