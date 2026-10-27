// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/TerrainVisibility.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {
int add(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
int sub(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
int word(int a){return std::bit_cast<std::int16_t>(std::uint16_t(a));}
PixelRect crop(const ShpFrame& f){return {word(f.x),word(f.y),word(f.width),word(f.height)};}
}
PixelRect intersectDrawBounds(PixelRect a,PixelRect b,int* adjustX,int* adjustY){
    const auto original=b;
    if(a.width<=0||a.height<=0||b.width<=0||b.height<=0)return {};
    if(b.x<a.x){b.width=add(b.width,sub(b.x,a.x));b.x=a.x;}
    if(b.width<1)return {};
    if(b.y<a.y){b.height=add(b.height,sub(b.y,a.y));b.y=a.y;}
    if(b.height<1)return {};
    if(add(b.x,b.width)>add(a.x,a.width))b.width=add(sub(a.x,b.x),a.width);
    if(b.width<1)return {};
    if(add(b.y,b.height)>add(a.y,a.height))b.height=sub(add(a.y,a.height),b.y);
    if(b.height<1)return {};
    if(adjustX)*adjustX=add(*adjustX,sub(original.x,b.x));
    if(adjustY)*adjustY=add(*adjustY,sub(original.y,b.y));
    return b;
}
PixelRect terrainRenderBounds(const ShpImage* image,PixelPoint screen,PixelPoint origin){
    if(!image)return {};
    if(image->frames.size()>32767)throw std::invalid_argument("Terrain bounds require nonnegative signed SHP frame count");
    PixelRect first{},second{};
    if(!image->frames.empty()){
        first=crop(image->frames.front());second=crop(image->frames[image->frames.size()/2]);
    }
    if(first.width<=0||first.height<=0)first=second;
    else if(second.width>0&&second.height>0){
        if(first.x>second.x){first.width=add(first.width,sub(first.x,second.x));first.x=second.x;}
        if(first.y>second.y){first.height=add(first.height,sub(first.y,second.y));first.y=second.y;}
        if(add(first.x,first.width)<add(second.x,second.width))first.width=add(add(sub(second.x,first.x),second.width),1);
        if(add(first.y,first.height)<add(second.y,second.height))first.height=add(add(sub(second.y,first.y),second.height),1);
    }
    first.x=add(sub(first.x,word(image->width)/2),sub(screen.x,origin.x));
    first.y=add(sub(first.y,word(image->height)/2),sub(screen.y,origin.y));
    return first;
}
bool drawTerrainIfVisible(TerrainMarkState& state,PixelRect& bounds,PixelRect viewport,
                         TerrainDrawGate gate,const TerrainVisibilityServices& services,
                         const TerrainVisibilityTrace& trace){
    if(!gate.bypass&&gate.contextPresent){
        if(!gate.force&&!state.needsRedraw)return false;
        if(!state.onMap||state.limbo)return false;
    }
    state.needsRedraw=0;if(trace)trace({'r',0});
    bounds=intersectDrawBounds(bounds,viewport);
    if(trace){trace({'x',bounds.x});trace({'y',bounds.y});trace({'w',bounds.width});trace({'h',bounds.height});}
    const auto shape=services.renderBounds();
    const auto x=add(shape.x,viewport.x),y=add(shape.y,viewport.y);
    if(bounds.x>=add(x,shape.width)||bounds.y>=add(y,shape.height)||
       add(bounds.x,bounds.width)<=x||add(bounds.y,bounds.height)<=y)return false;
    auto point=services.project(services.coordinates());
    if(bounds.x>viewport.x)point.x=add(point.x,sub(viewport.x,bounds.x));
    if(bounds.y>viewport.y)point.y=add(point.y,sub(viewport.y,bounds.y));
    services.draw(point,bounds);return true;
}
}
