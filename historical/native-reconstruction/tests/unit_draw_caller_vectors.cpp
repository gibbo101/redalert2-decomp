// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitDrawCaller.hpp"
#include "render/UnitVisibility.hpp"
#include "render/UnitTypeVisibility.hpp"
#include <iostream>
#include <string>
using namespace ra2;
int main(){try{
    std::string op;
    while(std::cin>>op){
        UnitScreenRegistry registry;int x,y,ox,oy,w,h;unsigned flags,shape,loaded;
        std::string events;auto event=[&](char k,std::initializer_list<int> values){
            events+=' ';events+=k;for(int value:values){events+=' ';events+=std::to_string(value);}
        };
        auto trace=[&](char k,int value){event(k,{value});};
        if(op=="registry"){
            std::cin>>registry.count>>x>>y>>ox>>oy>>w>>h;
            const int old=registry.count;
            const bool accepted=registerUnitScreen(registry,17,{x,y},{ox,oy},w,h,trace);
            const auto entry=accepted?registry.entries.at(std::size_t(old)):UnitScreenEntry{};
            std::cout<<accepted<<' '<<registry.count<<' '<<entry.actor<<' '<<entry.point.x<<' '<<entry.point.y<<events<<'\n';continue;
        }
        if(op!="draw"&&op!="nested"&&op!="timer"&&op!="state")throw std::invalid_argument("Unknown Unit caller vector");
        OrdinaryUnitDrawInputs a;PixelRect bounds;int offset,add14,index,layer,ground,ambient,predicate,visible,voxel,model,altVoxel,altModel;
        unsigned cellFlags;
        std::cin>>flags>>shape>>loaded>>x>>y>>bounds.x>>bounds.y>>bounds.width>>bounds.height
                >>a.coordinates.x>>a.coordinates.y>>a.coordinates.z>>offset>>add14>>index>>layer>>ground
                >>ambient>>a.extraLight>>cellFlags>>predicate>>visible>>voxel>>model>>altVoxel>>altModel
                >>registry.count>>ox>>oy>>w>>h;
        if(!std::cin)throw std::invalid_argument("Incomplete Unit caller vector");
        a.actor=17;a.screenOffset=std::int8_t(offset);a.addFourteen=std::uint8_t(add14);a.secondaryIndex=std::int8_t(index);
        a.type.voxel=std::uint8_t(voxel);a.type.voxelModel=model;a.alternate.voxel=std::uint8_t(altVoxel);a.alternate.voxelModel=altModel;
        UnitDrawResource resource{std::uint8_t(flags),shape};OrdinaryUnitDrawServices s;
        s.loadShape=[&]{event('L',{});return loaded;};s.layer=[&]{event('Y',{});return layer;};
        s.registerScreen=[&](int id,PixelPoint p){event('R',{p.x,p.y});registerUnitScreen(registry,id,p,{ox,oy},w,h,trace);};
        s.groundHeight=[&](Coord c){event('G',{c.x,c.y,c.z});return ground;};
        s.coordinateCell=[&](Coord c){event('A',{c.x,c.y,c.z});return UnitDrawCell{std::int16_t(ambient),cellFlags};};
        s.lightCell=[&](UnitLightCell c){event('c',{c.x,c.y});return UnitDrawCell{std::int16_t(ambient),cellFlags};};
        s.brightnessPredicate=[&]{event('p',{});return std::uint8_t(predicate);};
        s.originalTypeVisible=[&]{event('V',{});return std::uint8_t(visible);};
        s.alternateType=[&]{event('a',{1});};
        s.draw=[&](bool v,PixelPoint p,PixelRect b,int bright){event(v?'v':'s',{p.x,p.y,b.x,b.y,b.width,b.height,bright});};
        s.footDecoration=[&](PixelPoint p,PixelRect b){event('F',{p.x,p.y,b.x,b.y,b.width,b.height});};
        s.timerDecoration=[&]{event('Z',{});};
        if(op=="timer"||op=="state")std::cin>>a.currentFrame>>a.timerStart>>a.timerDuration;
        if(op=="state"){
            UnitDisguiseState state;int disguised,mode,flagA,flagB,current,sensors;
            int ownerIndex,currentIndex;unsigned alliances;
            std::cin>>state.timerStart>>state.timerDuration>>disguised>>state.creationFrame
                    >>mode>>flagA>>flagB>>current>>ownerIndex>>currentIndex>>alliances>>sensors;
            state.disguised=std::uint8_t(disguised);
            // Values captured by copy: callbacks run after this parse scope.
            s.originalTypeVisible=[&,state,mode,flagA,flagB,current,sensors]{
                event('V',{});
                return originalUnitTypeVisible(state,a.currentFrame,[&]{event('o',{});
                    return unitOwnerTypeVisible(mode,std::uint8_t(flagA),std::uint8_t(flagB),current!=0);},
                    [&]()->std::optional<std::int16_t>{event('B',{});for(int i=0;i<2;++i)event('A',{a.coordinates.x,a.coordinates.y,a.coordinates.z});
                        return std::int16_t(sensors);},[&](char k){event(k,{});});
            };
            s.alternateType=[&,ownerIndex,currentIndex,alliances,current]{event('a',{1});
                const int selected=selectUnitDisplayType(1,2,1,[&]{event('l',{});
                    return unitOwnerAlliedToCurrent(true,current!=0,ownerIndex,currentIndex,alliances);});
                if(selected!=2)throw std::logic_error("Unit caller selected unexpected type");};
        }
        if(!std::cin)throw std::invalid_argument("Incomplete Unit drawing state vector");
        if(op=="nested"){
            int onMap,redraw,limbo,bypass,context,force,success;
            std::cin>>onMap>>redraw>>limbo>>bypass>>context>>force>>success;
            if(!std::cin)throw std::invalid_argument("Incomplete nested Unit caller vector");
            TerrainMarkState state{std::uint8_t(onMap),std::uint8_t(redraw),std::uint8_t(limbo)};
            const PixelRect viewport{0,0,w,h};UnitVisibilityServices v;
            v.coordinates=[&]{event('Q',{a.coordinates.x,a.coordinates.y,a.coordinates.z});return a.coordinates;};
            v.project=[&](Coord c){event('P',{c.x,c.y,c.z});return std::pair{PixelPoint{x,y},std::uint8_t(success)!=0};};
            v.draw=[&](PixelPoint p,PixelRect b){drawOrdinaryUnitCaller(resource,a,p,b,s,trace);};
            const bool accepted=drawOrdinaryUnitIfVisible(state,bounds,viewport,
                {std::uint8_t(bypass),context!=0,std::uint8_t(force)},0,v,[&](auto e){trace(e.kind,e.value);});
            std::cout<<accepted<<' '<<unsigned(state.needsRedraw)<<' '<<bounds.x<<' '<<bounds.y<<' '<<bounds.width<<' '<<bounds.height<<' ';
        }else drawOrdinaryUnitCaller(resource,a,{x,y},bounds,s,trace);
        std::cout<<unsigned(resource.flags)<<' '<<resource.shape<<' '<<registry.count<<events<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
