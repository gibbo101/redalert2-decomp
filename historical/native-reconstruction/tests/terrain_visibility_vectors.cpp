// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/TerrainVisibility.hpp"
#include <iostream>
using namespace ra2;
static PixelRect rect(){PixelRect r;std::cin>>r.x>>r.y>>r.width>>r.height;return r;}
static PixelPoint point(){PixelPoint p;std::cin>>p.x>>p.y;return p;}
static void print(PixelRect r){std::cout<<r.x<<' '<<r.y<<' '<<r.width<<' '<<r.height;}
static const ShpImage* image(ShpImage& out){
    int count;std::cin>>count;if(count==-1)return nullptr;
    if(count<0||count>32767)throw std::invalid_argument("Invalid frame count");
    std::cin>>out.width>>out.height;out.frames.resize(std::size_t(count));
    for(auto& f:out.frames)std::cin>>f.x>>f.y>>f.width>>f.height;
    return &out;
}
int main(){
 try{
    char op;
    while(std::cin>>op){
        if(op=='I'){
            auto a=rect(),b=rect();int mask,x,y;std::cin>>mask>>x>>y;
            print(intersectDrawBounds(a,b,mask&1?&x:nullptr,mask&2?&y:nullptr));std::cout<<' '<<x<<' '<<y;
        }else if(op=='B'){
            auto screen=point(),origin=point();ShpImage shp;const auto* src=image(shp);
            print(terrainRenderBounds(src,screen,origin));
        }else if(op=='D'||op=='E'){
            unsigned onMap,redraw,limbo,bypass,force,projectSuccess;bool context;int unused;
            std::cin>>onMap>>redraw>>limbo>>bypass>>context>>force>>unused>>projectSuccess;
            TerrainMarkState state{std::uint8_t(onMap),std::uint8_t(redraw),std::uint8_t(limbo)};
            auto bounds=rect(),viewport=rect(),shape=rect();auto projected=point();Coord coords;
            std::cin>>coords.x>>coords.y>>coords.z;
            ShpImage shp;const ShpImage* src=nullptr;PixelPoint screen{},origin{};
            if(op=='E'){screen=point();origin=point();src=image(shp);}
            std::vector<TerrainVisibilityEvent> events;auto emit=[&](char k,int v){events.push_back({k,v});};
            TerrainVisibilityServices services;
            services.renderBounds=[&]{emit('B',0);return op=='E'?terrainRenderBounds(src,screen,origin):shape;};
            services.coordinates=[&]{emit('C',coords.x);emit('C',coords.y);emit('C',coords.z);return coords;};
            services.project=[&](Coord p){emit('P',p.x);emit('P',p.y);emit('P',p.z);return projected;};
            services.draw=[&](PixelPoint p,PixelRect r){emit('D',p.x);emit('D',p.y);for(int v:{r.x,r.y,r.width,r.height})emit('D',v);};
            auto result=drawTerrainIfVisible(state,bounds,viewport,{std::uint8_t(bypass),context,std::uint8_t(force)},services,
                                            [&](auto e){events.push_back(e);});
            std::cout<<result<<' '<<unsigned(state.needsRedraw)<<' ';print(bounds);
            for(const auto& e:events)std::cout<<' '<<e.kind<<' '<<e.value;
        }else throw std::invalid_argument("Unknown visibility vector");
        if(!std::cin)throw std::invalid_argument("Incomplete visibility vector");
        std::cout<<'\n';
    }
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
