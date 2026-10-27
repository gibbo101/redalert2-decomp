// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/FootCoordinates.hpp"
#include "render/DynamicTraversal.hpp"
#include "render/UnitVisibility.hpp"
#include <bit>
#include <iostream>
using namespace ra2;
static Coord coord(){Coord p;std::cin>>p.x>>p.y>>p.z;return p;}
static PixelRect rect(){PixelRect p;std::cin>>p.x>>p.y>>p.width>>p.height;return p;}
static std::int8_t indexByte(int v){return std::bit_cast<std::int8_t>(std::uint8_t(v));}
static std::int16_t word(int v){return std::bit_cast<std::int16_t>(std::uint16_t(v));}
int main(){try{
    char command;
    while(std::cin>>command){
        std::string events;
        auto event=[&](char k,int id,std::initializer_list<int> values={}){
            events+=' ';events+=k;events+=' ';events+=std::to_string(id);
            for(int v:values){events+=' ';events+=std::to_string(v);}
        };
        if(command=='G'){
            unsigned byte;std::cin>>byte;const auto p=initialUnitDrawingInputs(std::uint8_t(byte));
            std::cout<<unsigned(p.flags)<<' '<<unsigned(p.specialState)<<' '<<int(p.secondaryIndex)<<'\n';
        }else if(command=='F'){
            int index,x,y,unused;std::cin>>index;const auto current=coord(),destination=coord();std::cin>>x>>y>>unused;
            std::array<TerrainCellPoint,128> pool{};const auto signedIndex=indexByte(index);
            if(signedIndex>=0)pool[std::size_t(signedIndex)]={word(x),word(y)};
            FootCoordinateServices s;
            s.locomotor=[&]{event('L',0);return driveSecondaryCoordinates(current,destination);};
            s.coordinates=[&]{event('C',0,{current.x,current.y,current.z});return current;};
            const auto p=footSecondaryCoordinates(signedIndex,pool,s);
            std::cout<<p.x<<' '<<p.y<<' '<<p.z<<events<<'\n';
        }else if(command=='D'){
            int count;std::cin>>count;if(count<0||count>600)throw std::invalid_argument("Invalid actor count");
            DynamicTraversalContext c;unsigned bypass;std::cin>>c.force>>c.scenarioFlags>>c.contextPresent>>bypass
                >>c.origin.x>>c.origin.y>>c.surfaceWidth>>c.surfaceHeight>>c.heightScale;c.bypass=std::uint8_t(bypass);
            auto viewport=rect();std::array<TraversalVector,3> inverse;
            for(auto& p:inverse){int x,y,z;std::cin>>x>>y>>z;p={std::bit_cast<float>(x),std::bit_cast<float>(y),std::bit_cast<float>(z)};}
            std::vector<TraversalActor> actors;std::vector<TerrainMarkState> states;
            std::vector<int> rejected,indices,successes;std::vector<Coord> destinations;std::vector<PixelPoint> projected;
            for(int i=0;i<count;++i){
                TraversalActor a;int kind,flags,visible,onMap,redraw,limbo,index,reject,success;PixelPoint point;
                std::cin>>kind>>flags>>visible;a.location=coord();std::cin>>onMap>>redraw>>limbo>>index>>reject;
                const auto destination=coord();std::cin>>success>>point.x>>point.y;
                if(kind<0||kind>1)throw std::invalid_argument("Invalid actor kind");
                a.kind=kind?TraversalKind::Terrain:TraversalKind::Unit;a.flags=std::uint8_t(flags);a.visible=std::uint8_t(visible);
                actors.push_back(a);states.push_back({std::uint8_t(onMap),std::uint8_t(redraw),std::uint8_t(limbo)});
                indices.push_back(index);rejected.push_back(reject);destinations.push_back(destination);successes.push_back(success);projected.push_back(point);
            }
            std::array<std::vector<int>,5> storage;std::array<std::span<const int>,5> layers;
            for(std::size_t i=0;i<5;++i){
                int size;std::cin>>size;if(size<0||size>1200)throw std::invalid_argument("Invalid layer size");
                storage[i].resize(std::size_t(size));for(auto& id:storage[i])std::cin>>id;layers[i]=storage[i];
            }
            std::array<TerrainCellPoint,128> pool;for(int i=0;i<128;++i)pool[std::size_t(i)]={word(i*13-800),word(i*11+1400)};
            auto coordinates=[&](int id){const auto p=actors.at(id).location;event('C',id,{p.x,p.y,p.z});return p;};
            auto type=[&](int id){event('T',id);return actors.at(id).kind;};
            DynamicTraversalServices s;s.type=type;int inv=0;
            s.inverse=[&](TraversalVector p){event('I',inv,{std::bit_cast<int>(p.x),std::bit_cast<int>(p.y),std::bit_cast<int>(p.z)});return inverse.at(std::size_t(inv++));};
            s.coordinates=coordinates;
            s.footCoordinates=[&](int id){
                event('F',id,{0});FootCoordinateServices f;
                f.locomotor=[&]{event('L',id);return driveSecondaryCoordinates(actors.at(id).location,destinations.at(id));};
                f.coordinates=[&]{return coordinates(id);};
                (void)footSecondaryCoordinates(indexByte(indices.at(id)),pool,f);
            };
            s.mapRejects=[&](int id,Coord p){event('M',id,{p.x,p.y,p.z});return std::uint8_t(rejected.at(id))!=0;};
            s.drawBehind=[&](int id,PixelPoint p,PixelRect& b){event('B',id,{p.x,p.y,b.x,b.y,b.width,b.height});type(id);};
            s.drawIfVisible=[&](int id,PixelRect& b,int force,int third){
                event('D',id,{force,third,b.x,b.y,b.width,b.height});
                if(actors.at(id).kind!=TraversalKind::Unit)throw std::invalid_argument("Dynamic Terrain is outside combined profile");
                UnitVisibilityServices u;u.coordinates=[&]{return coordinates(id);};
                u.project=[&](Coord p){event('P',id,{p.x,p.y,p.z});return std::pair{projected.at(id),std::uint8_t(successes.at(id))!=0};};
                u.draw=[&](PixelPoint p,PixelRect bounds){event('W',id,{p.x,p.y,bounds.x,bounds.y,bounds.width,bounds.height});};
                drawOrdinaryUnitIfVisible(states.at(id),b,viewport,{c.bypass,c.contextPresent,std::uint8_t(force)},0,u,[&](auto e){
                    if(e.kind=='t')type(id);else event(e.kind,id,{e.value});
                });
            };
            s.drawExtras=[&](int id,PixelPoint p,PixelRect& b){event('E',id,{p.x,p.y,b.x,b.y,b.width,b.height});};
            drawDynamicLayers(actors,layers,viewport,c,s,[&](int id,std::uint8_t v){event('v',id,{v});});
            for(std::size_t i=0;i<actors.size();++i)std::cout<<unsigned(actors[i].visible)<<' '<<unsigned(states[i].needsRedraw)<<' ';
            std::cout<<viewport.x<<' '<<viewport.y<<' '<<viewport.width<<' '<<viewport.height<<events<<'\n';
        }else throw std::invalid_argument("Unknown actor fixture command");
        if(!std::cin)throw std::invalid_argument("Incomplete actor fixture");
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
