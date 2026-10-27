// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/DynamicTraversal.hpp"
#include <bit>
#include <iostream>
#include <vector>
using namespace ra2;
static int bits(float f){return std::bit_cast<std::int32_t>(f);}
static PixelRect rect(){PixelRect r;std::cin>>r.x>>r.y>>r.width>>r.height;return r;}
int main(){try{
    int count;
    while(std::cin>>count){
        if(count<0||count>600)throw std::invalid_argument("Invalid dynamic actor count");
        DynamicTraversalContext c;unsigned bypass;
        std::cin>>c.force>>c.scenarioFlags>>c.contextPresent>>bypass>>c.origin.x>>c.origin.y>>c.surfaceWidth>>c.surfaceHeight>>c.heightScale;
        c.bypass=std::uint8_t(bypass);auto viewport=rect();
        std::array<TraversalVector,3> inverse;
        for(auto& p:inverse){int x,y,z;std::cin>>x>>y>>z;p={std::bit_cast<float>(x),std::bit_cast<float>(y),std::bit_cast<float>(z)};}
        std::vector<TraversalActor> actors;std::vector<int> rejected,mutations;
        std::vector<PixelRect> supplied;
        for(int i=0;i<count;++i){
            TraversalActor a;int kind,flags,visible,animated,crumbling,reject,mutate;
            std::cin>>kind>>flags>>visible>>animated>>crumbling>>a.location.x>>a.location.y>>a.location.z>>reject>>mutate;
            if(kind<0||kind>1)throw std::invalid_argument("Invalid dynamic actor type");
            a.kind=kind?TraversalKind::Terrain:TraversalKind::Unit;
            a.flags=std::uint8_t(flags);a.visible=std::uint8_t(visible);a.animated=std::uint8_t(animated);a.crumbling=std::uint8_t(crumbling);
            actors.push_back(a);rejected.push_back(reject);mutations.push_back(mutate);supplied.push_back(rect());
        }
        std::array<std::vector<int>,5> storage;std::array<std::span<const int>,5> layers;
        for(std::size_t i=0;i<5;++i){
            int size;std::cin>>size;if(size<0||size>1200)throw std::invalid_argument("Invalid dynamic layer count");
            storage[i].resize(std::size_t(size));for(auto& id:storage[i])std::cin>>id;layers[i]=storage[i];
        }
        if(!std::cin)throw std::invalid_argument("Incomplete dynamic vector");
        std::string events;
        auto event=[&](char k,int id,std::initializer_list<int> values={}){
            events+=' ';events+=k;events+=' ';events+=std::to_string(id);
            for(auto v:values){events+=' ';events+=std::to_string(v);}
        };
        auto type=[&](int id){event('T',id);return actors.at(id).kind;};
        int inv=0;DynamicTraversalServices s;
        s.type=type;
        s.inverse=[&](TraversalVector p){event('I',inv,{bits(p.x),bits(p.y),bits(p.z)});return inverse.at(std::size_t(inv++));};
        s.footCoordinates=[&](int id){event('F',id,{0});};
        s.coordinates=[&](int id){auto p=actors.at(id).location;event('C',id,{p.x,p.y,p.z});return p;};
        s.mapRejects=[&](int id,Coord p){event('M',id,{p.x,p.y,p.z});return std::uint8_t(rejected.at(id))!=0;};
        s.drawBehind=[&](int id,PixelPoint p,PixelRect& b){
            event('B',id,{p.x,p.y,b.x,b.y,b.width,b.height});type(id); // Actual Unit path tests its type then exits.
        };
        s.drawIfVisible=[&](int id,PixelRect& b,int f,int third){
            event('D',id,{f,third,b.x,b.y,b.width,b.height});
            if(mutations.at(id)){b=supplied.at(id);event('S',id,{b.x,b.y,b.width,b.height});}
        };
        s.drawExtras=[&](int id,PixelPoint p,PixelRect& b){event('E',id,{p.x,p.y,b.x,b.y,b.width,b.height});};
        drawDynamicLayers(actors,layers,viewport,c,s,[&](int id,std::uint8_t v){event('v',id,{v});});
        for(const auto& a:actors)std::cout<<unsigned(a.visible)<<' ';
        std::cout<<viewport.x<<' '<<viewport.y<<' '<<viewport.width<<' '<<viewport.height<<events<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
