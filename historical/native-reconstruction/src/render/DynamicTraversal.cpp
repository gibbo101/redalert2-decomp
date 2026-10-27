// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/DynamicTraversal.hpp"
#include "sim/OriginalMath.hpp"
#include <bit>
#include <cmath>
#include <stdexcept>
namespace ra2 {
namespace {
int add(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
int sub(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
int twice(int a){return add(a,a);}
int truncate(float v){
    if(!std::isfinite(v)||double(v)<-2147483648.0||double(v)>=2147483648.0)
        throw std::invalid_argument("Inverse camera result outside bounded conversion domain");
    return int(v);
}
}
void drawDynamicLayers(std::span<TraversalActor> actors,const std::array<std::span<const int>,5>& layers,
                       PixelRect& viewport,const DynamicTraversalContext& c,
                       const DynamicTraversalServices& s,const DynamicTraversalTrace& trace){
    if(c.auxiliaryCount)throw std::invalid_argument("Auxiliary drawing collection is unrecovered");
    for(const auto layer:layers)for(const auto id:layer){
        if(id<0||std::size_t(id)>=actors.size())throw std::invalid_argument("Invalid dynamic layer member");
        const auto& a=actors[std::size_t(id)];
        if((a.kind!=TraversalKind::Unit&&a.kind!=TraversalKind::Terrain)||
           (a.kind==TraversalKind::Unit&&!(a.flags&4))||
           (a.kind==TraversalKind::Terrain&&(a.flags&5)))
            throw std::invalid_argument("Unsupported dynamic actor profile");
    }
    OriginalRounding rounding;
    // The caller saves the second input's Y over its earlier height local,
    // then reuses that Y for the third inverse-camera call.
    // Explicit float stores are required before invoking the inverse service.
    const auto first=s.inverse({float(add(c.origin.x,viewport.width/2)),float(sub(c.origin.y,viewport.height)),0});
    const int lowerX=truncate(first.x),lowerY=truncate(first.y);
    const auto second=s.inverse({float(add(c.origin.x,twice(viewport.width))),float(add(c.origin.y,viewport.height/2)),0});
    const int secondX=truncate(second.x);
    const auto third=s.inverse({float(sub(c.origin.x,viewport.width)),float(add(c.origin.y,viewport.height/2)),0});
    const int upperX=add(lowerX,twice(sub(secondX,lowerX)));
    const int upperY=add(lowerY,twice(sub(truncate(third.y),lowerY)));
    const auto insideWorld=[&](Coord p){return p.x>=lowerX&&p.x<upperX&&p.y>=lowerY&&p.y<upperY;};
    const auto screen=[&](Coord p){
        auto q=worldPixels(c.heightScale,p);q.x=sub(q.x,c.origin.x);q.y=sub(q.y,c.origin.y);return q;
    };
    const auto insideScreen=[&](PixelPoint p){return p.x>=-360&&p.x<=add(c.surfaceWidth,360)&&
                                                  p.y>=-180&&p.y<=add(c.surfaceHeight,180);};
    const auto visible=[&](int id,std::uint8_t v){actors[std::size_t(id)].visible=v;if(trace)trace(id,v);};
    for(const auto layer:layers)for(const auto id:layer){
        auto& a=actors[std::size_t(id)];visible(id,0);
        if(a.flags&4){
            if(!insideWorld(a.location))continue;
            s.footCoordinates(id);
            if((c.scenarioFlags&0x1000)&&s.mapRejects(id,a.location))continue;
            const auto p=screen(s.coordinates(id));
            if(!insideScreen(p))continue;
            visible(id,1);s.drawBehind(id,p,viewport);
            s.drawIfVisible(id,viewport,c.force,0);
        }else{
            if(s.type(id)!=TraversalKind::Terrain)throw std::invalid_argument("Unsupported object type");
            if(!a.animated&&!a.crumbling)continue;
            if(!insideWorld(a.location)||s.mapRejects(id,a.location))continue;
            visible(id,1);s.drawIfVisible(id,viewport,c.force,0);
        }
    }
    for(const auto layer:layers)for(const auto id:layer){
        const auto& a=actors[std::size_t(id)];
        if(!a.visible||!(a.flags&1))continue;
        if(a.flags&4){
            s.footCoordinates(id);
            if(c.contextPresent&&!c.bypass&&(c.scenarioFlags&0x1000)&&s.mapRejects(id,a.location))continue;
        }
        const auto p=screen(s.coordinates(id));
        if(insideScreen(p))s.drawExtras(id,p,viewport);
    }
}
}
