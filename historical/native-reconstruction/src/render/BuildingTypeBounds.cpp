// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingTypeBounds.hpp"
#include "render/Redraw.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {
int sub(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
bool same(PixelRect a,PixelRect b){return a.x==b.x&&a.y==b.y&&a.width==b.width&&a.height==b.height;}
std::int16_t word(int v){return std::bit_cast<std::int16_t>(std::uint16_t(v));}
}
ShpBoundsView shpBoundsView(const ShpImage& image){
    return {&image,[&image]{return word(int(image.frames.size()));},
        [&image]{return PixelPoint{word(image.width),word(image.height)};},
        [&image](std::uint32_t index,int field){
            if(index>=image.frames.size())throw std::invalid_argument("SHP bounds backing shorter than signed frame count");
            const auto& f=image.frames[index];
            return word(field==0?f.x:field==1?f.y:field==2?f.width:f.height);
        }};
}
PixelRect shpFrameBounds(const ShpBoundsView& image,std::int32_t index,const PixelRect& empty){
    if(!image.identity||!image.count)throw std::invalid_argument("SHP bounds image/count unbound");
    if(std::uint32_t(index)>=std::uint32_t(std::int32_t(image.count())))return empty;
    if(!image.field)throw std::invalid_argument("SHP bounds frame backing unbound");
    // Preserve the guest's32-bit header address arithmetic before resolving a
    // native backing entry: INT_MIN*24 wraps to frame0. Offsets into unmodeled
    // header words/pixels are outside this borrowed metadata view and refuse.
    const auto offset=std::uint32_t(index)*24u;
    if(offset%24u)throw std::invalid_argument("SHP frame address outside metadata view");
    const auto slot=offset/24u;
    return {image.field(slot,0),image.field(slot,1),image.field(slot,2),image.field(slot,3)};
}
void releaseBuildingSecondary(BuildingTypeBoundsState& a,const BuildingTypeBoundsServices& s){
    if(!a.release13e2||!a.secondaryB98)return;
    if(!s.freeImage)throw std::invalid_argument("Building secondary image heap child unbound");
    s.freeImage(a.secondaryB98);
    a.secondaryB98=nullptr;if(s.store)s.store(0xb98,0);
    a.flagB9c=0;if(s.store)s.store(0xb9c,0);
}
PixelRect buildingTypeBounds(BuildingTypeBoundsState& a,const PixelRect& empty,const BuildingTypeBoundsServices& s){
    if(!same(a.bounds11ec,empty))return a.bounds11ec;
    if(!s.primary9c)throw std::invalid_argument("Building primary image getter unbound");
    const auto primary=s.primary9c();if(!primary.identity)return empty;
    if(!primary.count||!primary.dimensions)throw std::invalid_argument("Building primary SHP metadata unbound");
    auto bounds=empty;const int primaryCount=primary.count();const auto dimensions=primary.dimensions();
    for(int i=0;i<primaryCount;++i){
        PixelRect f=empty;
        if(std::uint32_t(i)<std::uint32_t(std::int32_t(primary.count()))){
            if(!primary.field)throw std::invalid_argument("Building primary frame backing unbound");
            const int h=primary.field(i,3),w=primary.field(i,2),y=primary.field(i,1),x=primary.field(i,0);f={x,y,w,h};
        }
        bounds=unionDirtyBounds(bounds,f);
    }
    const bool release=!a.secondaryB98;
    if(!s.secondaryC0)throw std::invalid_argument("Building secondary image getter unbound");
    const auto secondary=s.secondaryC0();
    if(secondary.identity){
        if(!secondary.count)throw std::invalid_argument("Building secondary SHP count unbound");
        const int secondaryCount=secondary.count();
        for(int i=0;i<secondaryCount;++i){
            PixelRect f=empty;
            if(std::uint32_t(i)<std::uint32_t(std::int32_t(secondary.count()))){
                if(!secondary.field)throw std::invalid_argument("Building secondary frame backing unbound");
                const int h=secondary.field(i,3),w=secondary.field(i,2),y=secondary.field(i,1),x=secondary.field(i,0);f={x,y,w,h};
            }
            bounds=unionDirtyBounds(bounds,f);
        }
        if(release)releaseBuildingSecondary(a,s);
    }
    if(a.auxiliary11cc){
        if(!s.auxiliary)throw std::invalid_argument("Building auxiliary image unbound");
        bounds=unionDirtyBounds(bounds,shpFrameBounds(s.auxiliary(a.auxiliary11cc),0,empty));
    }
    bounds.x=sub(bounds.x,dimensions.x/2);bounds.y=sub(bounds.y,dimensions.y/2);
    const auto store=[&](int off,int& field,int value){field=value;if(s.store)s.store(off,value);};
    store(0x11ec,a.bounds11ec.x,bounds.x);store(0x11f0,a.bounds11ec.y,bounds.y);
    store(0x11f4,a.bounds11ec.width,bounds.width);store(0x11f8,a.bounds11ec.height,bounds.height);
    return bounds;
}
}
