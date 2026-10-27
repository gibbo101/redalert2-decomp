// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/UnitDiscovery.hpp"
#include "sim/TerrainOccupation.hpp"
#include <span>
#include <stdexcept>
namespace ra2 {
struct MovementGateHouse {int index=-1;std::uint32_t allies=0;};
struct MovementGateObject {
    // Actual Abstract kind values: Unit=1, Building=6, Terrain=36 (0x24).
    int kind=1,next=-1,owner=-1;
    std::uint8_t gate=0,animation18=0,animation19=0;
    UnitDiscoveryActor mission;
    int statusA8=0,lastAC=0,timerStart=0,timerPadding=0,timerRemaining=0;
};
struct MovementGateCell {TerrainCellPoint point;int head=-1;};
// Logical ids retain pointer identity; -1 denotes null. Observers are read-only.
// Initial map/type/House/mission/animation records and both opaque temporary
// timer padding values are supplied, not original construction/startup results.
struct MovementGateWorld {
    std::map<int,MovementGateHouse> houses;
    std::map<int,MovementGateObject> objects;
    std::map<int,MovementGateCell> cells;
    std::span<const int> slots;
    int fallbackCell=-1,tick=0,setPadding=0,commencePadding=0;
    std::function<void(char,int)> trace;
    std::function<void(int,int)> kindResult;
    std::function<void(int,int,int,std::uint32_t)> store;
    std::function<void(TerrainCellPoint)> fallbackStore;
    void storeFallbackPoint(TerrainCellPoint p){cells.at(fallbackCell).point=p;}
};
// Complete House/object alliance and allied/nonallied Building gate helpers.
bool movementGateAllied(int house,int object,MovementGateWorld&);
bool makeMovementGateTraversable(int object,MovementGateWorld&);
bool movementGateTraversable(int object,MovementGateWorld&);
// Complete map gate interaction, not a generic Cell reservation. Only primary
// residents are traversed; nonallied closed gates do not themselves return false.
// Other admission/occupancy decisions and gate animation progression are separate.
bool checkMovementGates(int mover,TerrainCellPoint,MovementGateWorld&);
namespace movement_gate_policy {
template<class World>
void event(World& w,char k,int id){if(w.trace)w.trace(k,id);}
template<class World>
void store(World& w,int id,int off,int bytes,std::uint32_t value){if(w.store)w.store(id,off,bytes,value);}
template<class World>
int mission(int id,World& w){event(w,'M',id);return unitDiscoveryMission(w.objects.at(id).mission);}
template<class World>
bool animation(int id,char k,World& w){
    event(w,k,id);const auto& a=w.objects.at(id);
    if(k=='B')return a.animation18!=0&&a.animation19==0;
    if(k=='C')return a.animation18==0&&a.animation19==0;
    return a.animation18==0&&a.animation19==1;
}
template<class World>
void setMission(int id,int requested,World& w){
    event(w,'S',id);auto& a=w.objects.at(id);auto& m=a.mission;
    if(m.mission98==28&&requested==5)return;
    m.mission98=requested;store(w,id,0x98,4,std::uint32_t(requested));
    m.queuedA0=-1;store(w,id,0xa0,4,0xffffffff);
    m.queuedA4=0;store(w,id,0xa4,1,0);
    a.statusA8=0;store(w,id,0xa8,4,0);
    a.lastAC=w.tick;store(w,id,0xac,4,std::uint32_t(w.tick));
    a.timerStart=w.tick;store(w,id,0xb0,4,std::uint32_t(w.tick));
    a.timerPadding=w.setPadding;store(w,id,0xb4,4,std::uint32_t(w.setPadding));
    a.timerRemaining=0;store(w,id,0xb8,4,0);
}
template<class World>
bool commence(int id,World& w){
    event(w,'E',id);auto& a=w.objects.at(id);auto& m=a.mission;
    if(m.queuedA0==-1)return false;
    m.mission98=m.queuedA0;store(w,id,0x98,4,std::uint32_t(m.mission98));
    m.queuedA0=-1;store(w,id,0xa0,4,0xffffffff);
    a.statusA8=0;store(w,id,0xa8,4,0);
    a.timerStart=w.tick;store(w,id,0xb0,4,std::uint32_t(w.tick));
    a.timerPadding=w.commencePadding;store(w,id,0xb4,4,std::uint32_t(w.commencePadding));
    a.timerRemaining=0;store(w,id,0xb8,4,0);
    a.lastAC=w.tick;store(w,id,0xac,4,std::uint32_t(w.tick));
    m.queuedA4=0;store(w,id,0xa4,1,0);
    return true;
}
template<class World>
decltype(auto) building(int id,World& w){
    auto& a=w.objects.at(id);
    if(a.kind!=6)throw std::invalid_argument("Movement gate helper requires Building kind");
    return a;
}
template<class World>
bool movementGateAllied(int house,int object,World& w){
    event(w,'A',house);if(object==-1)return false;
    event(w,'O',object);const auto& a=w.objects.at(object);
    // Terrain's actual owner virtual is the null-return leaf.
    const int owner=a.kind==36?-1:a.owner;
    if(owner==-1)return false;
    if(owner==house)return true;
    const int index=w.houses.at(owner).index;const auto& h=w.houses.at(house);
    if(index==h.index)return true;
    if(index==-1)return false;
    return (h.allies&(std::uint32_t(1)<<(std::uint32_t(index)&31u)))!=0;
}
template<class World>
bool movementGateTraversable(int id,World& w){
    event(w,'I',id);auto& a=building(id,w);
    if(!a.gate)return true;
    return mission(id,w)==24&&animation(id,'D',w);
}
template<class World>
bool makeMovementGateTraversable(int id,World& w){
    event(w,'G',id);auto& a=building(id,w);
    if(!a.gate)return true;
    if(mission(id,w)==24&&!animation(id,'B',w)&&!animation(id,'C',w)){
        if(!a.gate)return true;
        return mission(id,w)==24&&animation(id,'D',w);
    }
    setMission(id,-1,w);
    event(w,'Q',id);
    queueUnitDiscoveryMission(a.mission,24,[&](int,int off,std::uint32_t value){store(w,id,off,off==0xa4?1:4,value);});
    commence(id,w);return false;
}
template<class World>
bool checkMovementGates(int mover,TerrainCellPoint p,World& w){
    if(w.slots.size()!=262144||!w.cells.contains(w.fallbackCell)||
       (mover!=-1&&!w.objects.contains(mover)))throw std::invalid_argument("Invalid movement gate map");
    const int index=int(p.y)*512+int(p.x);
    int id=index>=0&&index<262144?w.slots[std::size_t(index)]:-1;
    if(id==-1){
        id=w.fallbackCell;w.storeFallbackPoint(p);if(w.fallbackStore)w.fallbackStore(p);
    }
    int current=w.cells.at(id).head;std::size_t visits=0;
    while(current!=-1){
        // A finite, stable list is the verified domain. Cycles are refused for
        // native safety rather than reproducing an original unbounded traversal.
        if(++visits>w.objects.size())throw std::invalid_argument("Cyclic movement gate list");
        auto& a=w.objects.at(current);
        if(current!=mover){
            event(w,'K',current);
            if(w.kindResult)w.kindResult(current,a.kind);
            if(a.kind==6&&a.gate){
                if(movementGateAllied(a.owner,mover,w))return makeMovementGateTraversable(current,w);
                if(movementGateTraversable(current,w))return true;
            }
        }
        current=a.next;
    }
    return true;
}
}
}
