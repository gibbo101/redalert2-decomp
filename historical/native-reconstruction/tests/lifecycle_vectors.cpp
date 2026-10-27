// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TerrainLifecycle.hpp"
#include "render/Composition.hpp"
#include <iostream>

static void readLayers(ra2::ObjectLayers& objects) {
    for(auto& layer:objects.layers) {
        int capacity;unsigned valid,owned;
        std::cin>>capacity>>layer.count>>layer.growBy>>valid>>owned>>layer.storageId;
        if(capacity<0||capacity>16384)throw std::invalid_argument("Invalid layer capacity");
        layer.valid=std::uint8_t(valid);layer.owned=std::uint8_t(owned);
        layer.slots.resize(std::size_t(capacity));
        for(auto& id:layer.slots)std::cin>>id;
    }
}
static void printLayers(const ra2::ObjectLayers& objects) {
    for(const auto& [id,actor]:objects.actors)std::cout<<' '<<actor.lastLayer;
    for(const auto& layer:objects.layers) {
        std::cout<<' '<<layer.slots.size()<<' '<<layer.count<<' '<<layer.growBy<<' '
                 <<unsigned(layer.valid)<<' '<<unsigned(layer.owned)<<' '<<layer.storageId;
        for(auto id:layer.slots)std::cout<<' '<<id;
    }
}
int main(int argc,char** argv) {
 try {
    double scale=0;
    if(argc==3)scale=ra2::worldHeightScale(ra2::readRasterData(ra2::readFile(argv[2])),ra2::readRenderData(ra2::readFile(argv[1])));
    std::string op;
    while(std::cin>>op) {
        std::vector<ra2::ObjectLayerEvent> events;
        auto trace=[&](auto e){events.push_back(e);};
        if(op=="L") {
            ra2::ObjectLayers objects;char action;int count,target,index;bool sorted;
            std::cin>>action>>count>>target>>index>>sorted>>objects.allocationSucceeds;
            for(int id=0;id<count;++id) {
                ra2::ObjectLayerActor actor;
                std::cin>>actor.position.x>>actor.position.y>>actor.position.z>>actor.lastLayer;
                objects.actors[id]=actor;
            }
            readLayers(objects);bool result=true;
            if(action=='I')result=objects.insert(index,target,sorted,trace);
            else if(action=='S')objects.submit(target,trace);
            else if(action=='R')objects.remove(target,trace);
            else throw std::invalid_argument("Invalid layer operation");
            std::cout<<result;printLayers(objects);
        } else if(op=="G") {
            ra2::Coord p;int first,second,calls=0;
            std::cin>>p.x>>p.y>>p.z>>first>>second;
            const auto out=ra2::terrainPlacementPosition(p,[&](auto){return calls++?second:first;},trace);
            std::cout<<out.x<<' '<<out.y<<' '<<out.z;
        } else if(op=="T") {
            if(scale==0)throw std::invalid_argument("Prepared render/raster data required");
            ra2::TerrainLifecycle world;int count,cellCount,steps;unsigned enabled;
            ra2::TerrainLifeServices services;
            std::cin>>count>>cellCount>>steps>>world.occupation.theater>>enabled>>world.loading
                    >>world.objects.allocationSucceeds>>services.screenOrigin[0]>>services.screenOrigin[1];
            world.enabled=std::uint8_t(enabled);
            for(int id=0;id<count;++id) {
                ra2::TerrainMember member;ra2::TerrainLifeState life;
                unsigned onMap,redraw,limbo,active,logic,vein;int last;
                std::cin>>member.position.x>>member.position.y>>member.position.z>>member.type.temperate
                        >>member.type.snow>>member.next>>onMap>>redraw>>limbo>>last>>active>>logic>>vein
                        >>life.resourceCountA>>life.resourceCountB>>life.screenX>>life.screenY;
                member.state={std::uint8_t(onMap),std::uint8_t(redraw),std::uint8_t(limbo)};
                life.active=std::uint8_t(active);life.typeLogic=std::uint8_t(logic);life.veinhole=std::uint8_t(vein);
                world.occupation.members[id]=member;world.actors[id]=life;
                world.objects.actors[id]={member.position,last};
            }
            std::map<ra2::TerrainCellPoint,int> ground;
            std::map<ra2::TerrainCellPoint,bool> allowed;
            for(int i=0;i<cellCount;++i) {
                int x,y,z;ra2::TerrainCellState cell;unsigned neighbors,frame;bool allow;
                std::cin>>x>>y>>z>>allow>>cell.flags>>cell.head>>cell.alternateHead>>neighbors>>cell.overlay>>frame;
                const ra2::TerrainCellPoint point{std::int16_t(x),std::int16_t(y)};
                cell.neighbors=std::uint8_t(neighbors);cell.overlayFrame=std::uint8_t(frame);
                world.occupation.cells[point]=cell;ground[point]=z;allowed[point]=allow;
            }
            readLayers(world.objects);
            services.groundHeight=[&](auto p){return ground.at(ra2::terrainCellPoint(p));};
            services.placementAllowed=[&](auto p){return allowed.at(p);};
            services.projectWorld=[&](auto p){const auto screen=ra2::worldPixels(scale,p);return std::array<std::int32_t,2>{screen.x,screen.y};};
            for(int i=0;i<steps;++i) {
                char action;int id;ra2::Coord target;std::cin>>action>>id>>target.x>>target.y>>target.z;
                if(i)std::cout<<' ';
                if(action=='U')std::cout<<world.unlimbo(id,target,services,trace);
                else if(action=='R')std::cout<<world.limbo(id,services,trace);
                else throw std::invalid_argument("Invalid lifecycle operation");
            }
            for(int id=0;id<count;++id) {
                const auto& m=world.occupation.members.at(id);const auto& a=world.actors.at(id);
                std::cout<<' '<<m.position.x<<' '<<m.position.y<<' '<<m.position.z<<' '<<m.next
                         <<' '<<unsigned(m.state.onMap)<<' '<<unsigned(m.state.needsRedraw)<<' '<<unsigned(m.state.limbo)
                         <<' '<<a.resourceCountA<<' '<<a.resourceCountB<<' '<<a.screenX<<' '<<a.screenY;
            }
            for(const auto& [point,cell]:world.occupation.cells)
                std::cout<<' '<<cell.flags<<' '<<cell.head<<' '<<cell.alternateHead<<' '<<unsigned(cell.neighbors)
                         <<' '<<cell.overlay<<' '<<unsigned(cell.overlayFrame);
            printLayers(world.objects);
        } else throw std::invalid_argument("Unknown vector operation");
        if(!std::cin)throw std::invalid_argument("Incomplete vector input");
        for(const auto& e:events)std::cout<<' '<<e.kind<<' '<<e.a<<' '<<e.b<<' '<<e.c;
        std::cout<<'\n';
    }
 } catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
