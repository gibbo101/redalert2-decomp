// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/StaticRedraw.hpp"
#include "render/StaticTerrainTraversal.hpp"
#include <iostream>
#include <numeric>
using namespace ra2;
static PixelRect rect(){PixelRect r;std::cin>>r.x>>r.y>>r.width>>r.height;return r;}
struct Actor {unsigned alive,animated,crumbling;TerrainMarkState state;PixelRect shape;Coord coords;PixelPoint projected;};
int main(){try{
    int visible,regions,full;
    while(std::cin>>visible>>regions>>full){
        PixelPoint origin;double scale;std::cin>>origin.x>>origin.y>>scale;
        const auto viewport=rect(),first=rect(),second=rect();
        std::vector<TerrainCellPoint> cells;std::vector<DirtyRegion> dirty;
        for(int i=0;i<visible;++i){int x,y;std::cin>>x>>y;cells.push_back({std::int16_t(x),std::int16_t(y)});}
        for(int i=0;i<regions;++i){auto bounds=rect();unsigned flag;std::cin>>flag;dirty.push_back({bounds,std::uint8_t(flag)});}
        int count;std::cin>>count;std::vector<Actor> actors;
        for(int i=0;i<count;++i){
            Actor a;unsigned onMap,redraw,limbo;
            std::cin>>a.alive>>a.animated>>a.crumbling>>onMap>>redraw>>limbo;
            a.state={std::uint8_t(onMap),std::uint8_t(redraw),std::uint8_t(limbo)};a.shape=rect();
            std::cin>>a.coords.x>>a.coords.y>>a.coords.z>>a.projected.x>>a.projected.y;actors.push_back(a);
        }
        if(!std::cin)throw std::invalid_argument("Incomplete static redraw vector");
        std::vector<int> layer(actors.size());std::iota(layer.begin(),layer.end(),0);
        std::string events;
        auto event=[&](char k,int id,std::initializer_list<int> values={}){
            events+=' ';events+=k;events+=' ';events+=std::to_string(id);
            for(auto v:values){events+=' ';events+=std::to_string(v);}
        };
        StaticTerrainTraversalServices services;
        services.isTerrain=[&](int id){event('T',id);return true;};
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
            drawTerrainIfVisible(a.state,r,viewport,{0,true,f},draw,[&](auto e){event(e.kind,id,{e.value});});
        };
        auto scan=[&](std::uint8_t force,const PixelRect& bounds,const PixelRect& clip){
            event('S',force,{&bounds==&clip,bounds.x,bounds.y,bounds.width,bounds.height,clip.x,clip.y,clip.width,clip.height});
            drawStaticTerrainRegion(layer,force,bounds,clip,viewport,services);
        };
        auto trace=[&](Coord p){event('G',p.x,{p.y,p.z});};
        requestStaticTerrainRedraw(cells,dirty,origin,viewport,first,second,std::uint8_t(full),scale,scan,trace);
        for(const auto& a:actors)std::cout<<unsigned(a.state.needsRedraw)<<' ';
        std::cout<<events<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
