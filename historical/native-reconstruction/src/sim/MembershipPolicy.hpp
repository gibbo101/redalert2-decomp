// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/UnitMembership.hpp"
#include <bit>
#include <stdexcept>
namespace ra2::membership_policy {
template<class F>const F& require(const F& f){
    if(!f)throw std::invalid_argument("Reached missing Unit membership service");return f;
}
inline std::uint32_t pointBits(TerrainCellPoint p){return std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16);}
inline TerrainCellPoint add(TerrainCellPoint a,TerrainCellPoint b){
    return {std::bit_cast<std::int16_t>(std::uint16_t(int(a.x)+b.x)),
            std::bit_cast<std::int16_t>(std::uint16_t(int(a.y)+b.y))};
}
template<class World>void event(World& w,char k,int a=0,int b=0){if(w.trace)w.trace(k,a,b);}
template<class World>void write(World& w,int id,int off,std::uint32_t v){if(w.store)w.store(id,off,v);}
template<class World>int slotCell(World& w,int index){
    if constexpr(requires{w.slotCell(index);})return w.slotCell(index);
    else {const auto slot=w.slots.find(index);return slot==w.slots.end()?-1:slot->second;}
}
template<class World>void occupation(int id,bool mark,World& w){
    auto& a=w.actors.at(id);
    // Both actual Cell parents skip Infantry before querying eligibility.
    // Walk's head transfer, rather than map membership, owns its subcell claim.
    if(a.kind==15)return;
    if(!a.eligible)return;
    // The original makes a local copy, after visibility notification/eligibility.
    const Coord position=a.position;
    require(w.services.occupation)(id,position,mark);
}
template<class World>void cellInsert(int id,int cellId,World& w){
    event(w,'C',1,cellId);
    auto& cell=w.cells.at(cellId);
    if(id==-1)return;
    auto& a=w.actors.at(id);const bool alternate=a.alternate!=0;
    if(a.kind!=1&&a.kind!=15)throw std::invalid_argument("Unrecovered membership actor kind");
    auto& head=alternate?cell.alternateHead:cell.head;
    if(head==-1||w.actors.at(head).next!=id){
        a.next=head;write(w,id,0x30,std::uint32_t(head));
        head=id;write(w,100+cellId,alternate?0xe8:0xe4,std::uint32_t(id));
    }
    const auto center=[&]{
        // Coordinates are saved before floor; a second query recomputes them.
        const TerrainCellPoint p{cell.point.x,cell.point.y};
        const int z=require(w.services.centerFloor)(cellId);
        return Coord{int(p.x)*256+128,int(p.y)*256+128,z};
    };
    const bool first=(require(w.services.visible)(center())&255)!=0;
    const bool second=first?false:(require(w.services.visibleSecondary)(center())&255)!=0;
    if((!first&&!second)||(w.services.liveVisibilityGate?w.services.liveVisibilityGate():w.services.visibilityGate)!=0)
        require(w.services.notify)(id,w.services.liveNotificationArgument?w.services.liveNotificationArgument():w.services.notificationArgument);
    occupation(id,true,w);
}
template<class World>void cellRemove(int id,int cellId,World& w){
    event(w,'C',0,cellId);
    auto& cell=w.cells.at(cellId);
    if(id==-1)return;
    auto& a=w.actors.at(id);const bool alternate=a.alternate!=0;
    if(a.kind!=1&&a.kind!=15)throw std::invalid_argument("Unrecovered membership actor kind");
    auto& head=alternate?cell.alternateHead:cell.head;
    bool found=false;
    if(head==id){head=a.next;write(w,100+cellId,alternate?0xe8:0xe4,std::uint32_t(head));found=true;}
    else {
        int before=head;std::size_t visits=0;
        while(before!=-1){
            if(++visits>w.actors.size())throw std::invalid_argument("Cyclic Unit membership outside valid profile");
            auto& previous=w.actors.at(before);
            if(previous.next==id){previous.next=a.next;write(w,before,0x30,std::uint32_t(previous.next));found=true;break;}
            before=previous.next;
        }
    }
    if(found){a.next=-1;write(w,id,0x30,0xffffffffu);}
    // Unmark even on a membership miss. No reference counts or deduplication.
    occupation(id,false,w);
}
template<class World>void mapChange(int id,TerrainCellPoint origin,bool insert,World& w){
    event(w,'M',int(insert),id);
    if(id==-1)return;
    auto& a=w.actors.at(id);
    if(!a.typeMapFlag)return;
    // Caller has established the ordinary nonnull layer2 profile. The
    // supplied foundation owner remains distinct for each type family.
    event(w,'F');
    if(!(w.foundation.objectFlag&1)){
        w.foundation.objectFlag|=1;write(w,200,0,w.foundation.objectFlag);
        w.foundation.fallback={32767,32767};write(w,200,4,pointBits(w.foundation.fallback));event(w,'A',0);
    }
    event(w,'U');
    if(!(w.foundation.unitFlag&1)){
        w.foundation.unitFlag|=1;write(w,200,8,w.foundation.unitFlag);
        w.foundation.unit[0]={0,0};write(w,200,12,0);
        w.foundation.unit[1]={32767,32767};write(w,200,16,pointBits(w.foundation.unit[1]));event(w,'A',1);
    }
    event(w,'B',32);
    // The actual bounded copy uses 32 slots. Only the initialized stock two-word
    // list is admitted here; its sentinel terminates before the truncation path.
    if(w.foundation.unit!=std::array<TerrainCellPoint,2>{{{0,0},{32767,32767}}})
        throw std::invalid_argument("Nonstock Foot foundation outside verified profile");
    const auto p=add(origin,w.foundation.unit[0]);const int index=int(p.y)*512+int(p.x);
    if(index<0||index>=262144)throw std::invalid_argument("Unit membership speculative slot outside native domain");
    const int cellId=slotCell(w,index);
    if(cellId==-1)return;
    if(insert)cellInsert(id,cellId,w);else cellRemove(id,cellId,w);
    // Reload the slot after Cell/visibility/occupation effects, preserving a
    // changed identity or the shared fallback, rather than reusing cellId.
    const int reloaded=slotCell(w,index),current=reloaded==-1?w.fallbackCell:reloaded;
    if(reloaded==-1){
        w.cells.at(w.fallbackCell).point=p;write(w,100+w.fallbackCell,0x24,pointBits(p));
    }
    require(w.services.recalculate)(current,-1);
}
}
