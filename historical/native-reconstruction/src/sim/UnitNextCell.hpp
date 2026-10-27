// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/UnitAdmission.hpp"
namespace ra2 {
// Supplied actor fields, in addition to UnitAdmissionWorld's canonical records.
struct UnitNextCellActor {Coord location{};std::uint8_t bridge79=0;};
// Unit +4B8 early paths: unpromoted noncrusher, or warning mode with no
// low-five occupation bits in the selected layer. Target lookup and bridge
// classification still execute before the type/ability test. Initial records
// and unpromoted state are supplied, not recovered construction. Warning
// delivery, crushing/list traversal and runtime integration remain excluded.
void ordinaryUnitNextCell(int mover,const UnitNextCellActor&,TerrainCellPoint target,
    std::uint8_t warning,UnitAdmissionWorld&);
namespace unit_next_cell_policy {
template<class World>
void event(World& w,char k,int id=0,int a=0,int b=0){if(w.trace)w.trace(k,id,a,b);}
template<class World>
int lookup(TerrainCellPoint p,World& w){
    event(w,'L',p.x,p.y);
    const int index=int(p.y)*512+int(p.x);
    const int id=index>=0&&index<262144?w.gates.slots[std::size_t(index)]:-1;
    if(id!=-1){
        if(!w.cells.contains(id)||!w.gates.cells.contains(id))
            throw std::invalid_argument("Noncanonical next-Cell slot");
        return id;
    }
    w.gates.storeFallbackPoint(p);event(w,'F',p.x,p.y);
    return w.gates.fallbackCell;
}
inline std::int16_t cell(int n){return std::bit_cast<std::int16_t>(std::uint16_t(n/256));}
template<class World>
void ordinaryUnitNextCell(int mover,const UnitNextCellActor& actor,TerrainCellPoint point,
    std::uint8_t warning,World& w){
    if(w.gates.slots.size()!=262144||!w.objects.contains(mover)||!w.gates.objects.contains(mover)||
       w.gates.objects.at(mover).kind!=1||!w.cells.contains(w.gates.fallbackCell)||
       !w.gates.cells.contains(w.gates.fallbackCell))
        throw std::invalid_argument("Unit next-Cell map/actor outside domain");
    const int target=lookup(point,w);
    bool elevated=false;
    if(w.cells.at(target).flags&0x100){
        if(actor.bridge79)elevated=true;
        else{
            event(w,'C',mover);
            const int current=lookup({cell(actor.location.x),cell(actor.location.y)},w);
            elevated=int(w.cells.at(current).level)==int(w.cells.at(target).level)+4;
        }
    }
    if(!w.objects.at(mover).crusher){
        // Actual ability17 with the supplied unpromoted 0.0 state. Both original
        // promotion predicates execute; no type ability table is consulted.
        event(w,'b',mover,17);event(w,'v',mover,1);event(w,'v',mover,2);
        return;
    }
    if(!warning)throw std::invalid_argument("Next-Cell crushing/list branch unsupported");
    const auto& c=w.cells.at(target);
    const auto occupation=elevated?c.elevatedOccupation:c.occupation;
    event(w,'S',target,elevated?1:0,int(occupation&0x1f));
    if(occupation&0x1f)throw std::invalid_argument("Next-Cell warning delivery unsupported");
}
}
}
