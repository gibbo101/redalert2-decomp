// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TerrainOccupation.hpp"
#include <iostream>
int main() {
 try {
    std::string op;
    while(std::cin>>op) {
        if(op=="O") {
            ra2::Coord p;ra2::TerrainOccupationType type;int theater;std::uint32_t flags;bool mark;
            std::cin>>p.x>>p.y>>p.z>>theater>>type.temperate>>type.snow>>flags>>mark;
            const auto r=ra2::terrainOccupation(p,theater,type,flags,mark);
            std::cout<<r.cell.x<<' '<<r.cell.y<<' '<<r.flags;
            std::cout<<" L "<<r.cell.x<<' '<<r.cell.y;
            for(auto value:r.writes)std::cout<<" W 0 "<<unsigned(value);
        } else if(op=="S"||op=="M") {
            ra2::TerrainOccupationWorld w;int count,head,alt,target,cx,cy,mode;std::uint32_t flags;bool alternate;
            std::cin>>w.theater>>cx>>cy>>flags>>head>>alt>>count>>target>>mode>>alternate;
            const ra2::TerrainCellPoint point{std::int16_t(cx),std::int16_t(cy)};
            w.cells[point]={flags,head,alt};
            for(int id=0;id<count;++id) {
                ra2::TerrainMember m;unsigned onMap,redraw,limbo;
                std::cin>>m.position.x>>m.position.y>>m.position.z>>m.type.temperate>>m.type.snow>>m.next>>onMap>>redraw>>limbo;
                m.state={std::uint8_t(onMap),std::uint8_t(redraw),std::uint8_t(limbo)};w.members[id]=m;
                w.cells.try_emplace(ra2::terrainCellPoint(m.position));
            }
            std::vector<ra2::TerrainOccupationEvent> events;auto trace=[&](auto event){events.push_back(event);};bool result=true;
            if(op=="S"&&mode==4)w.cellInsert(target,point,alternate,trace);
            else if(op=="S"&&mode==5)w.cellRemove(target,point,alternate,trace);
            else result=w.mark(target,mode,trace);
            std::cout<<result<<' '<<w.cells.at(point).head<<' '<<w.cells.at(point).alternateHead<<' '<<w.cells.at(point).flags;
            for(int id=0;id<count;++id)std::cout<<' '<<w.members.at(id).next<<' '<<unsigned(w.members.at(id).state.onMap)<<' '<<unsigned(w.members.at(id).state.needsRedraw);
            for(const auto& e:events)std::cout<<' '<<e.kind<<' '<<e.id<<' '<<e.value;
        } else return 2;
        if(!std::cin)return 3;std::cout<<'\n';
    }
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
