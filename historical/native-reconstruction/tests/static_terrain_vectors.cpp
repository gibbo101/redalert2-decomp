// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/StaticTerrainTraversal.hpp"
#include <iostream>
using namespace ra2;
static PixelRect rect(){PixelRect r;std::cin>>r.x>>r.y>>r.width>>r.height;return r;}
struct Actor {unsigned type,alive,animated,crumbling;TerrainMarkState state;PixelRect shape;Coord coords;PixelPoint projected;};
int main(){
 try{
    int count,slots;
    while(std::cin>>count>>slots){
        if(count<0||count>1024||slots<0||slots>2048)throw std::invalid_argument("Invalid static traversal fixture");
        unsigned force,bypass;bool context;std::cin>>force>>bypass>>context;
        const auto dirty=rect(),clip=rect(),viewport=rect();
        std::vector<Actor> actors;std::vector<int> layer(std::size_t(slots),0);
        for(int i=0;i<count;++i){
            Actor a{};unsigned onMap,redraw,limbo;
            std::cin>>a.type>>a.alive>>a.animated>>a.crumbling>>onMap>>redraw>>limbo;
            a.state={std::uint8_t(onMap),std::uint8_t(redraw),std::uint8_t(limbo)};a.shape=rect();
            std::cin>>a.coords.x>>a.coords.y>>a.coords.z>>a.projected.x>>a.projected.y;actors.push_back(a);
        }
        for(auto& id:layer){std::cin>>id;if(id<0||id>=count)throw std::invalid_argument("Invalid layer actor");}
        std::string events;auto event=[&](char kind,int id,std::initializer_list<int> values={}){
            events+=' ';events+=kind;events+=' ';events+=std::to_string(id);
            for(auto v:values){events+=' ';events+=std::to_string(v);}
        };
        StaticTerrainTraversalServices services;
        services.isTerrain=[&](int id){event('T',id);return actors.at(id).type==0x24;};
        services.isDead=[&](int id){event('A',id);return !actors.at(id).alive;};
        services.isAnimated=[&](int id){return actors.at(id).animated!=0;};
        services.isCrumbling=[&](int id){return actors.at(id).crumbling!=0;};
        services.renderBounds=[&](int id){event('B',id);return actors.at(id).shape;};
        services.clearRedraw=[&](int id){actors.at(id).state.needsRedraw=0;event('r',id,{0});};
        services.drawIfVisible=[&](int id,PixelRect& r,std::uint8_t f){
            auto& a=actors.at(id);event('V',id,{int(f),0,r.x,r.y,r.width,r.height});
            TerrainVisibilityServices draw;
            draw.renderBounds=[&]{return services.renderBounds(id);};
            draw.coordinates=[&]{event('C',id,{a.coords.x,a.coords.y,a.coords.z});return a.coords;};
            draw.project=[&](Coord p){event('P',id,{p.x,p.y,p.z});return a.projected;};
            draw.draw=[&](PixelPoint p,PixelRect b){event('D',id,{p.x,p.y,b.x,b.y,b.width,b.height});};
            drawTerrainIfVisible(a.state,r,viewport,{std::uint8_t(bypass),context,f},draw,
                                 [&](auto e){event(e.kind,id,{e.value});});
        };
        drawStaticTerrainRegion(layer,std::uint8_t(force),dirty,clip,viewport,services);
        if(!std::cin)throw std::invalid_argument("Incomplete static traversal fixture");
        for(std::size_t i=0;i<actors.size();++i){if(i)std::cout<<' ';std::cout<<unsigned(actors[i].state.needsRedraw);}
        std::cout<<events<<'\n';
    }
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
