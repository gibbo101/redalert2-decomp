// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "platform/OwnedUnitWorld.hpp"
#include <bit>
#include <sstream>
namespace owned_check {
using namespace ra2;
inline std::string snapshot(const TerrainUnitContext& c){
    std::ostringstream out;const auto put=[&](auto... v){((out<<+v<<' '),...);};
    const auto point=[&](Coord p){put(p.x,p.y,p.z);};
    const auto state=[&](const GroundDriveProcessState& s,const UnitMarkState& mark,const UnitDiscoveryActor& d){
        const auto& m=s.movement;point(m.actor.position);point(m.head);put(m.actor.marked74,m.actor.bridge79,m.reached5a0,m.reached5a1,
            m.track,m.index,m.accumulator,m.driving,m.body.desired,m.body.start,m.body.timerStart,m.body.duration,m.body.rate);
        const auto& r=s.ramps;put(r.current,r.previous,r.start,r.padding,r.remaining,r.duration);point(s.destination);
        for(int n:s.route)put(n);put(std::bit_cast<std::uint64_t>(s.percentage),std::bit_cast<std::uint64_t>(s.instancePercentage),
            s.wasRotating,s.crossing57b,s.preparation57a,s.nextX,s.nextY,s.retryStart,s.retryPadding,s.retryRemaining);
        put(mark.onMap,mark.needsRedraw,mark.limbo,mark.special,d.field372,d.current373,d.other374,d.queuedA4,d.owner,d.mission98,d.queuedA0,d.hasTag);
    };
    const auto cell=[&](const MapCellAttributes& a){const auto& v=a.input;
        put(v.position.x,v.position.y,v.tile,v.land,v.tube,v.subTile,v.ice,v.slope,v.level,v.flags,a.overlay,a.passability,a.overlayData,a.extraHeight);};
    const auto& map=*c.map;for(const auto& v:map.cells){cell(v.attributes);put(v.field30,v.wallOwner,v.attachedTag);}cell(map.fallback);
    put(map.width,map.height,map.levelHeight);
    for(int n:map.slots)put(n);
    std::map<const MapCellInput*,int> tableIds;std::map<const MapCellAttributes*,int> attributeIds;
    for(std::size_t i=0;i<map.cells.size();++i){tableIds[&map.cells[i].attributes.input]=int(i);attributeIds[&map.cells[i].attributes]=int(i);}
    tableIds[&map.fallback.input]=-2;attributeIds[&map.fallback]=-2;
    for(const auto* p:map.table)put(p?tableIds.at(p):-1);
    for(const auto* p:map.attributes)put(p?attributeIds.at(p):-1);
    put(map.floor.flags,std::bit_cast<std::uint64_t>(map.floor.height),std::bit_cast<std::uint64_t>(map.floor.scale));
    for(const auto& p:map.floor.planes)for(double n:{p.x,p.y,p.offset,p.limit,p.add})put(std::bit_cast<std::uint64_t>(n));
    for(auto n:map.buffer4)put(n);for(auto n:map.buffer10)put(n);
    const auto& u=*c.unit;const auto& f=u.membership.foundation;
    put(u.membership.fallbackCell);for(const auto& [slot,id]:u.membership.slots)put(slot,id);
    put(f.objectFlag,f.unitFlag,f.fallback.x,f.fallback.y);for(auto p:f.unit)put(p.x,p.y);
    for(const auto& [id,a]:u.membership.actors){put(id);point(a.position);put(a.next,a.alternate,a.eligible,a.typeMapFlag);}
    for(const auto& [id,v]:u.membership.cells)put(id,v.point.x,v.point.y,v.head,v.alternateHead);
    for(const auto& o:u.occupation)put(o.flags,o.ground,o.elevated);
    for(const auto& v:u.visibilityCells)put(v.point.x,v.point.y,v.flags12c,v.flags140);
    put(u.visibility.heightDivisor,u.visibility.mode,u.visibility.overrideValue,u.visibility.currentHouse13d,u.occupationThreshold,
        u.houses.currentHouse,u.houses.mode,u.houses.loading,u.houses.tagContext,u.membership.services.visibilityGate,u.membership.services.notificationArgument);
    for(const auto& [id,h]:u.houses.houses)put(id,h.human134,h.control135,h.discovered13c,h.field13d,h.field5668,h.field5669);
    put(c.redraw.mapMode,c.redraw.counter,c.redraw.tactical,c.redraw.tacticalPresent);
    const auto supplied=[&](const GroundDriveProcessServices& s){for(float n:s.trackSpeed)put(std::bit_cast<std::uint32_t>(n));
        put(std::bit_cast<std::uint64_t>(s.uphill),std::bit_cast<std::uint64_t>(s.downhill));};
    supplied(c.services);if(c.parked)supplied(c.parked->services);
    state(c.state,u.marking,u.discovery);
    if(c.parked){state(c.parked->state,c.parked->marking,c.parked->discovery);
        put(c.parked->turret.has_value());if(c.parked->turret){const auto& t=*c.parked->turret;
            put(t.desired,t.start,t.timerStart,t.duration,t.rate);}}
    return out.str();
}

inline std::string snapshot(OwnedUnitWorld& world){
    std::ostringstream s;s<<snapshot(world.context())<<world.selected()<<' ';
    for(int id:{0,1}){auto a=world.actor(id);const auto& t=a.turret;const auto& c=a.commands;
        s<<world.preparationCounter(id)<<' '<<t.desired<<' '<<t.start<<' '<<t.timerStart<<' '<<t.duration<<' '<<t.rate<<' '
         <<a.wait.start<<' '<<a.wait.padding<<' '<<a.wait.remaining<<' '
         <<c.manualTurret<<c.turretTurning<<c.stopRequested<<' ';
        if(c.navigationTarget)s<<c.navigationTarget->x<<' '<<c.navigationTarget->y<<' '<<c.navigationTarget->z;
        s<<'/'<<c.pendingBodyTurn.value_or(0)<<' '<<c.pendingBodyTurn.has_value()<<';';
        // Logical target identities, never process-local addresses.
        for(const auto* target:{world.movementTarget(id),world.pendingScatterRoute(id)}){
            s<<bool(target)<<' ';
            if(target)s<<target->position.x<<' '<<target->position.y<<' ';
        }
    }return s.str();
}
}
