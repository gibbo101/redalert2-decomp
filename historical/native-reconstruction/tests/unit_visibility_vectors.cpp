// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitVisibility.hpp"
#include <iostream>
using namespace ra2;
static PixelRect rect(){PixelRect r;std::cin>>r.x>>r.y>>r.width>>r.height;return r;}
int main(){try{
    unsigned onMap,redraw,limbo,bypass,force;
    while(std::cin>>onMap>>redraw>>limbo>>bypass){
        bool context,alias;int unused,success;std::cin>>context>>force>>unused>>success>>alias;
        auto supplied=rect(),viewport=rect();PixelPoint projected;Coord coords;
        std::cin>>projected.x>>projected.y>>coords.x>>coords.y>>coords.z;
        if(!std::cin)throw std::invalid_argument("Incomplete unit visibility vector");
        auto& bounds=alias?viewport:supplied;
        TerrainMarkState state{std::uint8_t(onMap),std::uint8_t(redraw),std::uint8_t(limbo)};
        std::string events;auto event=[&](char k,std::initializer_list<int> values){
            events+=' ';events+=k;for(int v:values){events+=' ';events+=std::to_string(v);}
        };
        UnitVisibilityServices s;
        s.coordinates=[&]{event('C',{coords.x,coords.y,coords.z});return coords;};
        s.project=[&](Coord p){event('P',{p.x,p.y,p.z});return std::pair{projected,std::uint8_t(success)!=0};};
        s.draw=[&](PixelPoint p,PixelRect b){event('D',{p.x,p.y,b.x,b.y,b.width,b.height});};
        const bool result=drawOrdinaryUnitIfVisible(state,bounds,viewport,{std::uint8_t(bypass),context,std::uint8_t(force)},0,s,
                                                   [&](auto e){event(e.kind,{e.value});});
        std::cout<<result<<' '<<unsigned(state.needsRedraw)<<' '<<bounds.x<<' '<<bounds.y<<' '<<bounds.width<<' '<<bounds.height<<' '
                 <<viewport.x<<' '<<viewport.y<<' '<<viewport.width<<' '<<viewport.height<<events<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
