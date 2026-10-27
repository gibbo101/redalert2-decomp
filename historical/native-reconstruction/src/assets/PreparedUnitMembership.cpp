// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/PreparedUnitMembership.hpp"
#include "assets/MapCoordinateCell.hpp"
#include "assets/OccupiedCellPassability.hpp"
#include <bit>
#include <algorithm>
#include <stdexcept>
namespace ra2 {
namespace {
std::uint32_t packed(MapInputPosition p){return std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16);}
}
PreparedUnitMembership::PreparedUnitMembership(PreparedMembershipMap map,const PreparedMembershipStore& store,const Query& query)
    :map_(map),store_(store),query_(query){
    if(map_.cells.size()>16384||map_.slots.size()!=262144||map_.resident.world.cells.size()!=262144||
       map_.resident.world.fallback!=&map_.fallback.input||map_.levelHeight!=104||
       map_.buffer4.empty()||map_.buffer4.size()%4||map_.buffer4.size()/4!=map_.buffer10.size()/10||map_.buffer10.size()%10)
        throw std::invalid_argument("Prepared membership map outside bounded domain");
    occupation.resize(map_.cells.size()+1);visibilityCells.resize(occupation.size());visibilityTable_.resize(262144);
    membership.fallbackCell=CellBase+int(map_.cells.size());membership.actors[0]={};
    for(std::size_t i=0;i<occupation.size();++i){
        const auto& c=attributes(int(i));const auto p=c.input.position;
        occupation[i].flags=c.input.flags;visibilityCells[i]={{p.x,p.y},0,c.input.flags};
        membership.cells[CellBase+int(i)]={{p.x,p.y},-1,-1};
    }
    for(std::size_t slot=0;slot<map_.slots.size();++slot){
        const int i=map_.slots[slot];if(i<0)continue;
        if(std::size_t(i)>=map_.cells.size()||map_.resident.world.cells[slot]!=&map_.cells[std::size_t(i)]->input)
            throw std::invalid_argument("Noncanonical prepared membership slot");
        membership.slots[int(slot)]=CellBase+i;visibilityTable_[slot]=&visibilityCells[std::size_t(i)];
    }
    membership.store=[this](int id,int off,std::uint32_t value){
        if(id==200)write('g',0,off,value);
        else if(id>=100+CellBase){const int i=id-100-CellBase;if(off==0x24)fallback({std::bit_cast<std::int16_t>(std::uint16_t(value)),std::bit_cast<std::int16_t>(std::uint16_t(value>>16))});else write('c',i,off,value);}
        else write('a',id,off,value);
    };
    membership.services.centerFloor=[this](int id){const auto& c=attributes(id-CellBase).input;return cellFloorHeight(map_.floor,map_.levelHeight,c.level,c.slope,128,128);};
    const auto visible=[this](Coord p,bool secondary){
        MapVisibilityWorld w{visibilityTable_,&visibilityCells.back(),{1,1},{},{},{}};
        w.query=[this](char k,TerrainCellPoint p){if(k=='w'&&query_)query_('W',{p.x,p.y,0});};
        w.fallbackStore=[this](TerrainCellPoint p){fallback({p.x,p.y});};
        return secondary?mapSecondaryVisibility(p,visibility,w):mapPrimaryVisibility(p,visibility,w);
    };
    membership.services.visible=[visible](Coord p){return int(visible(p,false));};
    membership.services.visibleSecondary=[visible](Coord p){return int(visible(p,true));};
    membership.services.notify=[this](int actor,int discoverer){notify(actor,discoverer);};
    membership.services.occupation=[this](int,Coord p,bool mark){occupationChange(p,mark);};
    membership.services.recalculate=[this](int id,int level){recalculate(id-CellBase,level);};
    houses.store=[this](int subject,int off,std::uint32_t value){write(subject?'h':'a',subject?subject-1:0,off,value);};
}
void PreparedUnitMembership::write(char kind,int id,int off,std::uint32_t value)const{if(store_)store_(kind,id,off,value);}
void PreparedUnitMembership::copyStateFrom(const PreparedUnitMembership& other){
    if(occupation.size()!=other.occupation.size()||visibilityCells.size()!=other.visibilityCells.size()||membership.slots!=other.membership.slots||
       actors_.size()!=other.actors_.size()||other.discovery.hasTag||other.houses.tagEvent)
        throw std::invalid_argument("Incompatible Unit membership snapshot");
    for(const auto& [id,binding]:other.actors_)
        if(!actors_.contains(id)||binding.discovery->hasTag)
            throw std::invalid_argument("Incompatible parked Unit membership snapshot");
    membership.foundation=other.membership.foundation;membership.actors=other.membership.actors;membership.cells=other.membership.cells;
    membership.services.visibilityGate=other.membership.services.visibilityGate;
    membership.services.notificationArgument=other.membership.services.notificationArgument;
    std::copy(other.occupation.begin(),other.occupation.end(),occupation.begin());
    std::copy(other.visibilityCells.begin(),other.visibilityCells.end(),visibilityCells.begin());
    marking=other.marking;discovery=other.discovery;visibility=other.visibility;occupationThreshold=other.occupationThreshold;
    for(const auto& [id,binding]:other.actors_){
        *actors_.at(id).marking=*binding.marking;*actors_.at(id).discovery=*binding.discovery;
    }
    houses.houses=other.houses.houses;houses.currentHouse=other.houses.currentHouse;houses.mode=other.houses.mode;
    houses.loading=other.houses.loading;houses.tagContext=other.houses.tagContext;
}
const GroundDriveProcessState& PreparedUnitMembership::actorState(int id)const{return *actors_.at(id).state;}
const UnitDiscoveryActor& PreparedUnitMembership::actorDiscovery(int id)const{return *actors_.at(id).discovery;}
UnitDiscoveryActor& PreparedUnitMembership::actorDiscovery(int id){return *actors_.at(id).discovery;}
UnitMarkState& PreparedUnitMembership::actorMark(int id){return *actors_.at(id).marking;}
void PreparedUnitMembership::notify(int id,int discoverer){
    auto& actor=*actors_.at(id).discovery;
    // Discovery's observer uses subject zero for its actor. Keep the shared
    // House records live, remapping only this call's actor stores. The scoped
    // observer restores even when a diagnostic observer throws or reenters.
    struct Restore {
        UnitDiscoveryWorld& world;UnitDiscoveryStore previous;
        ~Restore(){world.store=std::move(previous);}
    } restore{houses,std::move(houses.store)};
    houses.store=[this,id,&restore](int subject,int off,std::uint32_t value){
        if(subject==0)write('a',id,off,value);
        else if(restore.previous)restore.previous(subject,off,value);
    };
    discoverUnit(actor,discoverer,houses);
}
MapCellAttributes& PreparedUnitMembership::attributes(int i){
    if(i==int(map_.cells.size()))return map_.fallback;
    if(i<0||std::size_t(i)>=map_.cells.size()||!map_.cells[std::size_t(i)])throw std::invalid_argument("Missing prepared membership Cell");
    return *map_.cells[std::size_t(i)];
}
int PreparedUnitMembership::index(const MapCellInput& c)const{
    if(&c==&map_.fallback.input)return int(map_.cells.size());
    const int slot=int(c.position.y)*512+int(c.position.x);
    if(slot<0||slot>=262144)throw std::invalid_argument("Prepared membership Cell coordinate outside table");
    const int i=map_.slots[std::size_t(slot)];
    if(i<0||std::size_t(i)>=map_.cells.size()||&map_.cells[std::size_t(i)]->input!=&c)
        throw std::invalid_argument("Unbound prepared membership identity");
    return i;
}
void PreparedUnitMembership::fallback(MapInputPosition p){
    map_.fallback.input.position=p;forwardAssignedFallback(p);
}
void PreparedUnitMembership::forwardAssignedFallback(MapInputPosition p){
    if(map_.fallback.input.position.x!=p.x||map_.fallback.input.position.y!=p.y)
        throw std::invalid_argument("Fallback associations require the actual assigned point");
    membership.cells.at(membership.fallbackCell).point={p.x,p.y};visibilityCells.back().point={p.x,p.y};
    write('c',int(map_.cells.size()),0x24,packed(p));
}
MapFloorHeightWorld PreparedUnitMembership::world(){return {map_.resident.world.cells,&map_.fallback.input,[this](MapInputPosition p){fallback(p);}};}
const UnitMembershipCell& PreparedUnitMembership::cellMembership(std::size_t i)const{
    if(i>map_.cells.size())throw std::invalid_argument("Prepared membership Cell index outside map");
    return membership.cells.at(CellBase+int(i));
}
void PreparedUnitMembership::occupationChange(Coord p,bool mark){
    UnitOccupationServices s;s.heightThreshold=occupationThreshold;
    s.cell=[this](const Coord& p)->UnitOccupationCell&{if(query_)query_('C',p);return occupation[std::size_t(index(mapCoordinateCell(p,world(),262144)))];};
    s.floor=[this](const Coord& p){if(query_)query_('F',p);return mapFloorHeight(map_.floor,map_.levelHeight,p,world());};
    const auto store=[this](const UnitOccupationCell& c,int off,std::uint32_t value){write('c',int(&c-occupation.data()),off,value);};
    if(mark)markUnitOccupation(p,s,store);else unmarkUnitOccupation(p,s,store);
}
void PreparedUnitMembership::recalculate(int i,int level){
    auto& c=attributes(i);if(c.overlay!=-1)throw std::invalid_argument("Occupied recalculation overlay profile is not joined");
    MapAttributeLookup lookup{map_.resident.world.cells,&map_.fallback.input,[this](MapInputPosition p){if(query_)query_('W',{p.x,p.y,0});},[this](MapInputPosition p){fallback(p);}};
    MapAttributeServices s;s.tiles=map_.resident.tiles;s.landMap=map_.resident.landMap;s.tubeCount=map_.resident.tubeCount;s.cliffMode=map_.resident.cliffMode;s.fallback=i==int(map_.cells.size());
    s.store=[this,i](MapAttributeField field,std::uint32_t value){
        constexpr int offsets[]={0x38,0x11a,0xec,0x11c,0x11b,0x11d,0,0,0x44,0x11e};
        if(field==MapAttributeField::Buffer4||field==MapAttributeField::Buffer10){const int index=mapAttributeBufferIndex(attributes(i).input.position,map_.width,map_.height,int(map_.buffer4.size()/4));write(field==MapAttributeField::Buffer4?'b':'d',0,index*(field==MapAttributeField::Buffer4?4:10)+int(value>>8),value&255);}
        else write('c',i,offsets[unsigned(field)],value);
    };
    s.neighborLevel=[&](MapInputPosition p){return mapAttributeCell(p,lookup).level;};
    s.setupLAT=[&](const MapCellAttributes&){setupMapLAT(c.input,map_.resident.lat,map_.resident.directions,lookup,int(s.tiles.size()),[&](int n){write('c',i,0x38,std::uint32_t(n));});return c.input.tile;};
    s.updatePassability=[&](const MapCellAttributes& state){
        OccupiedCellPassabilityWorld occupied;occupied.head=membership.cells.at(CellBase+i).head;
        for(const auto& [id,actor]:membership.actors)occupied.actors[id].next=actor.next;
        occupied.store=[&](int n){write('c',i,0x4c,std::uint32_t(n));};
        const bool permitted=mapCellPermitted(state.input.position,true,map_.resident.permission,{lookup.cells,lookup.fallback,{},lookup.fallbackStore});
        updateOccupiedCellPassability(c.passability,state.input,permitted,nullptr,map_.resident.wheelSpeeds,occupied);return c.passability;
    };
    const int slot=mapAttributeBufferIndex(c.input.position,map_.width,map_.height,int(map_.buffer4.size()/4));
    recalculateMapCellAttributes(c,level,std::span<std::uint8_t,4>{map_.buffer4.data()+slot*4,4},std::span<std::uint8_t,10>{map_.buffer10.data()+slot*10,10},s);
}
GroundDriveProcessServices PreparedUnitMembership::bind(GroundDriveProcessServices s,GroundDriveProcessState& state,const GroundStateStore& actorStore){
    return bindActor(0,std::move(s),state,marking,discovery,actorStore);
}
GroundDriveProcessServices PreparedUnitMembership::bindParked(GroundDriveProcessServices s,GroundDriveProcessState& state,
    UnitMarkState& mark,UnitDiscoveryActor& discover,const GroundStateStore& actorStore){
    return bindActor(1,std::move(s),state,mark,discover,actorStore);
}
GroundDriveProcessServices PreparedUnitMembership::bindActor(int id,GroundDriveProcessServices s,GroundDriveProcessState& state,
    UnitMarkState& mark,UnitDiscoveryActor& discover,const GroundStateStore& actorStore){
    if(actors_.contains(id))throw std::invalid_argument("Prepared Unit actor is already bound");
    actors_.emplace(id,ActorBinding{&state,&mark,&discover});membership.actors.try_emplace(id);
    s.advance.ground.mark=[this,id,&state,&mark,&discover,actorStore](int mode){
        auto& actor=state.movement.actor;if(actor.bridge79||mark.special||mark.limbo||discover.hasTag||houses.loading!=1)
            throw std::invalid_argument("Prepared Unit Mark outside ordinary loaded profile");
        mark.onMap=actor.marked74;auto& member=membership.actors.at(id);member.position=actor.position;member.alternate=actor.bridge79;member.eligible=state.movement.reached5a0;
        membership.services.visibilityGate=visibility.mode;membership.services.notificationArgument=houses.currentHouse;
        UnitMarkServices ms;ms.imageValue=[](){return 17;};ms.owner=[&discover](){return discover.owner;};ms.layer=[](){return 2;};
        ms.coordinates=[&](){return terrainCellPoint(actor.position);};ms.redrawMap=redrawMap;
        ms.insert=[this,id](TerrainCellPoint p){membership.mapInsert(id,p);};ms.remove=[this,id](TerrainCellPoint p){membership.mapRemove(id,p);};
        markUnitFoot(mark,mode,ms,[&](int off,std::uint8_t value){if(off==0x74){actor.marked74=value;if(actorStore)actorStore(off,value);}else write('a',id,off,value);});
    };
    s.advance.occupationEligible=[&state](){return state.movement.reached5a0;};
    s.advance.unmarkOccupation=[this](Coord p){occupationChange(p,false);};s.markOccupation=[this](Coord p){occupationChange(p,true);};return s;
}
}
