// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TerrainLifecycle.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
static void emit(const ObjectLayerTrace& t,char k,std::int64_t a,std::int64_t b=0,std::int64_t c=0){if(t)t({k,a,b,c});}
static std::int32_t add(std::int32_t a,std::int32_t b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
static std::int32_t sub(std::int32_t a,std::int32_t b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
static TerrainCellPoint neighbor(TerrainCellPoint p,int d){const auto [x,y]=directionOffset(d);return {std::bit_cast<std::int16_t>(std::uint16_t(int(p.x)+x)),std::bit_cast<std::int16_t>(std::uint16_t(int(p.y)+y))};}
Coord terrainPlacementPosition(Coord p,const std::function<std::int32_t(Coord)>& ground,const ObjectLayerTrace& t) {
    emit(t,'g',p.x,p.y,p.z);const auto height=ground(p);
    if(p.z<height){emit(t,'g',p.x,p.y,p.z);p.z=ground(p);}return p;
}
void TerrainLifecycle::emitMark(int id,int mode,const ObjectLayerTrace& t){
    occupation.mark(id,mode,[&](auto e){
        emit(t,e.kind,e.id,e.value);
        if(e.kind=='C'&&(mode==0||mode==1))emit(t,'I',id,2); // Map insert/remove asks the ground layer.
    });
}
bool TerrainLifecycle::unlimbo(int id,Coord target,const TerrainLifeServices& service,const ObjectLayerTrace& t) {
    auto& member=occupation.members.at(id);auto& life=actors.at(id);
    if(!enabled||!member.state.limbo||member.state.onMap)return false;
    // Engineering profile guard, before any recovered writes. Elevated actors
    // need alternate membership/layers; this milestone accepts ground only.
    if(target.z>service.groundHeight(target))throw std::invalid_argument("Above-ground Terrain lifecycle is unrecovered");
    const auto input=target;
    const auto point=terrainCellPoint(target);
    if(!loading){emit(t,'O',target.x,target.y,target.z);emit(t,'L',point.x,point.y);emit(t,'Q',1,0,0);if(!service.placementAllowed(point))return false;}
    member.state.limbo=0;emit(t,'l',id,0);member.state.needsRedraw=0;emit(t,'B',id,0);
    target=terrainPlacementPosition(target,service.groundHeight,t);
    member.position=target;objects.actors.at(id).position=target;
    emit(t,'X',id,target.x);emit(t,'Y',id,target.y);emit(t,'Z',id,target.z);
    emitMark(id,1,t);
    if(!member.state.onMap){member.state.limbo=1;emit(t,'l',id,1);return false;}
    if(life.active){
        emit(t,'I',id,2);objects.submit(id,t);
        if(life.typeLogic&&life.veinhole)emit(t,'+',id,0); // Supplied logic registration.
    }
    // Terrain's neighbor loop uses the input coordinates, not adjusted Z.
    for(int d=0;d<8;++d){const auto p=neighbor(point,d);emit(t,'L',p.x,p.y);auto& cell=occupation.cells.at(p);cell.neighbors=std::uint8_t(cell.neighbors+1);emit(t,'n',p.x,p.y,cell.neighbors);}
    emit(t,'c',id);
    const auto screen=service.projectWorld(member.position);
    life.screenX=screen[0];emit(t,'x',id,life.screenX);life.screenY=screen[1];emit(t,'y',id,life.screenY);
    life.screenX=sub(life.screenX,service.screenOrigin[0]);emit(t,'x',id,life.screenX);
    life.screenY=sub(life.screenY,service.screenOrigin[1]);emit(t,'y',id,life.screenY);
    life.screenX=add(life.screenX,service.screenOrigin[0]);emit(t,'x',id,life.screenX);
    life.screenY=add(life.screenY,service.screenOrigin[1]);emit(t,'y',id,life.screenY);
    if(life.veinhole){emit(t,'O',input.x,input.y,input.z);auto& cell=occupation.cells.at(point);cell.overlay=-1;emit(t,'e',point.x,point.y,-1);emit(t,'O',input.x,input.y,input.z);cell.overlayFrame=0;emit(t,'f',point.x,point.y,0);}
    return true;
}
bool TerrainLifecycle::limbo(int id,const TerrainLifeServices& service,const ObjectLayerTrace& t) {
    auto& member=occupation.members.at(id);auto& life=actors.at(id);const auto point=terrainCellPoint(member.position);
    if(!member.state.limbo&&member.position.z!=service.groundHeight(member.position))
        throw std::invalid_argument("Nonground Terrain lifecycle is unrecovered");
    if(!member.state.limbo){
        emit(t,'C',id);
        for(int d=0;d<8;++d){const auto p=neighbor(point,d);emit(t,'L',p.x,p.y);auto& cell=occupation.cells.at(p);cell.neighbors=std::uint8_t(cell.neighbors-1);emit(t,'n',p.x,p.y,cell.neighbors);}
        emit(t,'O',member.position.x,member.position.y,member.position.z);
        auto& cell=occupation.cells.at(point);cell.flags&=~0x40u;emit(t,'b',point.x,point.y,cell.flags);
    }
    emit(t,'C',id);
    const bool accepted=enabled&&!member.state.limbo;
    if(accepted){
        emit(t,'!',id,1); // Original Disappear executes with external cleanup service.
        emitMark(id,0,t);objects.remove(id,t);
        life.resourceCountA=0;emit(t,'a',id,0);life.resourceCountB=0;emit(t,'r',id,0);
        if(life.typeLogic)emit(t,'-',id);
        member.state.limbo=1;emit(t,'l',id,1);member.state.needsRedraw=0;emit(t,'B',id,0);
    }
    emit(t,'L',point.x,point.y);emit(t,'D',point.x,point.y);
    if(!loading){emit(t,'u',point.x,point.y);emit(t,'t',point.x,point.y);emit(t,'h',point.x,point.y);}
    return accepted;
}
}
