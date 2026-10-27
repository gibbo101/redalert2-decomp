// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/StaticRedraw.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {
int add(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
int sub(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
Coord cellCoordinates(TerrainCellPoint p){
    // Keep the original signed divide toward zero after adding half a cell.
    return {((int(p.x)*256+128)/256)*256,((int(p.y)*256+128)/256)*256,0};
}
}
void requestStaticTerrainRedraw(std::span<const TerrainCellPoint> visible,
    std::span<const DirtyRegion> dirty,PixelPoint origin,const PixelRect& viewport,
    const PixelRect& first,const PixelRect& second,std::uint8_t full,double scale,
    const StaticRedrawScan& scan,const StaticRedrawProjectionTrace& trace){
    if(visible.size()>800||dirty.size()>128)throw std::invalid_argument("Static redraw collection outside bounded profile");
    for(const auto cell:visible){
        const auto p=cellCoordinates(cell);
        if(p.x<-1048576||p.x>1048576||p.y<-1048576||p.y>1048576)
            throw std::invalid_argument("Static redraw coordinates outside native world projection profile");
    }
    for(const auto cell:visible){
        const auto p=cellCoordinates(cell);if(trace)trace(p);
        const auto screen=worldPixels(scale,p);
        const PixelRect bounds{sub(sub(screen.x,origin.x),30),add(sub(screen.y,origin.y),viewport.y),60,30};
        const auto clip=bounds;
        scan(1,bounds,clip);
    }
    for(auto it=dirty.rbegin();it!=dirty.rend();++it){
        auto bounds=it->bounds;bounds.y=add(bounds.y,viewport.y);
        const auto clipped=intersectDrawBounds(viewport,bounds);
        if(clipped.width<=0||clipped.height<=0)continue;
        const auto clip=clipped;
        scan(1,clipped,clip);
    }
    if(full)scan(1,viewport,viewport);
    else{
        if(first.width>0&&first.height>0)scan(1,first,first);
        if(second.width>0&&second.height>0)scan(1,second,second);
    }
}
}
