// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/CellVisibilityDraw.hpp"
namespace ra2 {
// Storage belongs to the presentation owner. Drawing never silently initializes
// this table: original startup/cleanup scheduling is a separate dependency.
struct AlphaCombinationTable {
    std::uint8_t initialized=0;
    std::array<std::uint8_t,65536> values{};
};
// Complete41F950. Index is (source<<8)+old destination. Inputs are nonnegative,
// so the original signed magic division is exactly integer division by127.
inline void initializeAlphaCombination(AlphaCombinationTable& table,
        const std::function<void(std::uint32_t,std::uint8_t)>& store={}){
    table.initialized=1;if(store)store(65536,1);
    for(std::uint32_t i=0;i<65536;++i){
        table.values[i]=std::uint8_t(std::min(255u,((i&255)*(i>>8))/127));
        if(store)store(i,table.values[i]);
    }
}
struct AlphaAnimationRecord {
    const void* associated24=nullptr;
    PixelRect bounds28{};
    std::span<const std::uint8_t> image38;
    std::uint8_t expired3c=0;
    // Abstract base fields consumed by complete40FF10 construction. These are
    // not an emulated object layout or host vtable addresses.
    std::int32_t index10=-1;
    std::uint8_t flags14=0;
    std::uint32_t value18=0,value1c=0;
    std::uint8_t byte20=0;
    bool derivedInterfaces=true; // Typed virtual20 dispatch after interface projection.
};
// Borrow live physical slots, including their lifetime across the Type query.
// A Type child may replace the registry backing. Its saved old slot must remain
// alive until the cache store; this is deliberately not a copied record list.
struct AlphaAnimationServices {
    std::function<std::int32_t()> count;
    std::function<std::span<AlphaAnimationRecord*>()> backing;
    std::function<std::span<const std::uint8_t>(const void*)> typeImage84;
    std::function<void(AlphaAnimationRecord&)> cacheStore;
    std::function<PixelPoint()> origin,viewport;
    std::function<FrameDepthView()> alpha;
    std::function<std::uint32_t(PixelPoint)> address411230;
    PixelRect invalidFrame{};
    std::span<const std::uint8_t> tileMask; // Original60x30 mask, caller owned.
};
// Complete41F1C0(point) /41F5E0(rectangle), bounded nonfaulting raw SHP profile.
// Point pass requires a populated cache and skips expired records; rectangle
// pass resolves a missing cache and draws expired records too.
inline void drawAlphaAnimations(bool pointPass,const PixelPoint& screen,const PixelRect& requested,
        const AlphaCombinationTable& table,const AlphaAnimationServices& s,const FillStoreTrace& stores={}){
    const auto need=[](const auto& f)->const auto&{if(!f)throw std::invalid_argument("Alpha animation child unbound");return f;};
    const auto record=[&](std::span<AlphaAnimationRecord*> slots,int i)->AlphaAnimationRecord&{
        if(i<0||std::size_t(i)>=slots.size()||!slots[i])throw std::invalid_argument("Alpha animation registry slot invalid");
        return *slots[i];};
    const auto intersect=[](PixelRect a,PixelRect b){const auto r=intersectFillRect({a.x,a.y,a.width,a.height},{b.x,b.y,b.width,b.height});return PixelRect{r[0],r[1],r[2],r[3]};};
    for(int index=0;index<need(s.count)();++index){
        if(index>=1048576)throw std::invalid_argument("Alpha animation traversal exceeds execution bound");
        auto& initial=record(need(s.backing)(),index);
        if(pointPass&&initial.expired3c)continue;
        auto bounds=initial.bounds28;const auto origin=need(s.origin)(),viewport=need(s.viewport)();
        bounds.x=fillAdd(fillSub(bounds.x,origin.x),viewport.x);
        bounds.y=fillAdd(fillSub(bounds.y,origin.y),viewport.y);
        const auto request=requested;
        auto clip=intersect(bounds,request);
        if(pointPass)clip=intersect(clip,{screen.x,screen.y,60,30});
        if(clip.width<=0||clip.height<=0)continue;
        auto slots=need(s.backing)();auto image=record(slots,index).image38;
        if(!pointPass&&image.empty()){
            const auto resolved=need(s.typeImage84)(record(slots,index).associated24);
            auto& saved=record(slots,index);saved.image38=resolved;
            if(s.cacheStore)s.cacheStore(saved);
            image=record(need(s.backing)(),index).image38;
        }
        const auto word=[&](std::size_t at){if(at+2>image.size())throw std::invalid_argument("Alpha SHP header exceeds backing");return std::uint16_t(image[at]|(unsigned(image[at+1])<<8));};
        const auto signedWord=[&](std::size_t at){return std::int32_t(std::bit_cast<std::int16_t>(word(at)));};
        const bool valid=word(6)!=0; // Negative signed count passes unsigned JBE.
        PixelRect frame=s.invalidFrame;
        if(valid)frame={signedWord(8),signedWord(10),signedWord(12),signedWord(14)};
        for(int n:{bounds.x,bounds.y,clip.x,clip.y,clip.width,clip.height,frame.x,frame.y,frame.width,frame.height})
            if(std::abs(std::int64_t(n))>1048576)throw std::invalid_argument("Alpha geometry outside bounded profile");
        // Rectangle pass uses the copied REQUEST right/bottom after the
        // intersection gate, while the point pass uses the final tile clip.
        const auto bottomClip=pointPass?fillAdd(clip.y,clip.height):fillAdd(request.y,request.height);
        const auto rightClip=pointPass?fillAdd(clip.x,clip.width):fillAdd(request.x,request.width);
        const auto top=std::max(clip.y,bounds.y+frame.y),bottom=std::min(bottomClip,bounds.y+frame.y+frame.height);
        const auto left=std::max(clip.x,bounds.x+frame.x),right=std::min(rightClip,bounds.x+frame.x+frame.width);
        const auto sourceGap=frame.width-right+left,destinationGap=fillAdd(fillSub(need(s.alpha)().rowWords28,right),left);
        std::uint32_t payload=0;if(valid)payload=word(28)|(std::uint32_t(word(30))<<16);
        const auto liveViewport=need(s.viewport)();
        auto at=need(s.address411230)({pointPass?left:fillSub(left,liveViewport.x),fillSub(top,liveViewport.y)});
        std::optional<FrameDepthView> plane;plane.emplace(need(s.alpha)());
        const auto probe=at+(std::uint32_t(right)+std::uint32_t(plane->rowWords28)*std::uint32_t(bottom-top)-std::uint32_t(left))*2+4;
        const bool wrapped=probe>=plane->end1c;
        if(bottom<=top)continue;
        if(std::uint64_t(bottom-top)*std::uint32_t(std::max(0,right-left))>67108864)throw std::invalid_argument("Alpha raster exceeds execution bound");
        std::int64_t source=std::int64_t(payload)+std::int64_t(frame.width)*(top-bounds.y-frame.y)+left-bounds.x-frame.x;
        // Point mask starts at the intersection origin, BEFORE frame cropping.
        // Its row gap also uses intersection width, not the cropped span.
        std::int64_t mask=std::int64_t(clip.y-screen.y)*60+clip.x-screen.x;
        const auto maskGap=60-clip.width;
        const auto backing=plane->plane;
        if(!backing.storage.empty()&&!backing.words.empty())throw std::invalid_argument("Ambiguous alpha backing");
        const auto size=backing.words.empty()?std::uint64_t(backing.storage.size()):std::uint64_t(backing.words.size())*2;
        const auto read=[&](std::uint32_t p){
            if(std::uint64_t(p)+2>size)throw std::invalid_argument("Alpha access exceeds backing");
            if(backing.words.empty())return unsigned(backing.storage[p])|(unsigned(backing.storage[p+1])<<8);
            return (unsigned(backing.words[p/2])>>(8*(p&1)))|((p&1)?(unsigned(backing.words[(p+1)/2]&255)<<8):0);};
        const auto store=[&](std::uint32_t p,std::uint16_t value){
            (void)read(p);for(unsigned i=0;i<2;++i){const auto k=p+i,shift=8*(k&1);const auto v=std::uint8_t(value>>(8*i));
                if(backing.words.empty())backing.storage[k]=v;
                else backing.words[k/2]=std::uint16_t((backing.words[k/2]&~(255u<<shift))|(unsigned(v)<<shift));}
            if(stores)stores(p,2,value);};
        for(int y=top;y<bottom;++y){
            for(int x=left;x<right;++x){
                if(source<0||std::uint64_t(source)>=image.size()||!payload)throw std::invalid_argument("Alpha raw payload exceeds backing");
                const auto v=image[std::size_t(source++)];bool skip=false;
                if(pointPass){if(mask<0||std::uint64_t(mask)>=s.tileMask.size())throw std::invalid_argument("Alpha tile mask exceeds backing");skip=s.tileMask[std::size_t(mask++)]==0x20;}
                if(!skip){const auto old=read(at);const auto lookup=(unsigned(v)<<8)+old;
                    if(lookup>=table.values.size())throw std::invalid_argument("Alpha combination lookup exceeds table");
                    store(at,table.values[lookup]);if(wrapped)plane.emplace(need(s.alpha)());}
                at+=2;if(wrapped&&at>=plane->end1c)at-=plane->bytes20;
            }
            source+=sourceGap;mask+=maskGap;at+=std::uint32_t(destinationGap)*2;
            if(wrapped&&at>=plane->end1c)at-=plane->bytes20;
        }
    }
}
}
