// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/TerrainDepthPass.hpp"
#include "sim/CellVisibilityState.hpp"
#include <string_view>
namespace ra2 {
struct CellVisibilityDrawServices {
    // Mask resolves the live Tactical owner on each call; point is borrowed.
    std::function<std::int32_t(const TerrainCellPoint&,bool)> mask6a8d40;
    std::function<std::uint32_t()> scenarioFlags;
    std::function<std::uint8_t()> house13d;
    std::function<void(const PixelPoint&,const PixelRect&,std::int32_t)> shroud474260,fog474510;
};
inline std::int32_t visibilityFrame(std::uint8_t v){
    const auto n=v<128?std::int32_t(v):std::int32_t(v)-256;
    return n==-2?15:n==-1?0:n;
}
// Complete475520. The second mask store precedes both fog gates. Children may
// mutate the point or globals; never snapshot those across child calls.
inline void drawCellVisibility(CellVisibilityState& cell,const PixelPoint& screen,
        const PixelRect& clip,const CellVisibilityDrawServices& s){
    const auto need=[](const auto& f)->const auto&{if(!f)throw std::invalid_argument("Cell visibility draw child unbound");return f;};
    cell.primary120=std::uint8_t(need(s.mask6a8d40)(cell.point,false));
    need(s.shroud474260)(screen,clip,visibilityFrame(cell.primary120));
    const auto secondary=std::uint8_t(need(s.mask6a8d40)(cell.point,true));
    cell.secondary121=secondary;
    if((need(s.scenarioFlags)()&0x1000)&&!need(s.house13d)())
        need(s.fog474510)(screen,clip,visibilityFrame(secondary));
}
// Borrowed cached raw SHP bytes. Loading/heap lifetime and initial associations
// are adapters. Lazy flag publication and cache selection follow the originals.
struct VisibilityRasterCache {
    std::uint8_t shroudInitialized=0,fogInitialized=0;
    std::span<const std::uint8_t> shroud,shroudFog,fog;
    PixelRect invalidFrame{};
};
struct VisibilityRasterServices {
    std::function<std::span<const std::uint8_t>(std::string_view)> load5956c0;
    std::function<std::uint32_t()> scenarioFlags;
    std::function<FrameDepthView()> alpha;
    std::function<std::uint32_t(PixelPoint)> address411230;
    std::function<std::int32_t()> viewportY;
    std::int32_t transparent79dad0=254;
};
// Complete474260/474510 control for bounded nonfaulting raw frames. Original
// pixels are byte payloads even when a header claims compression. No decoding.
// Traces are observational; they cannot mutate globals during a pixel store.
inline void drawVisibilityRaster(bool fog,VisibilityRasterCache& cache,
        const PixelPoint& screen,const PixelRect& clip,std::int32_t frame,
        const VisibilityRasterServices& s,const FillStoreTrace& stores={}){
    const auto need=[](const auto& f)->const auto&{if(!f)throw std::invalid_argument("Visibility raster child unbound");return f;};
    std::span<const std::uint8_t> image;
    if(fog){
        if(!cache.fogInitialized){cache.fogInitialized=1;cache.fog=need(s.load5956c0)("FOG.SHP");}
        image=cache.fog;
    }else{
        if(!cache.shroudInitialized){
            cache.shroudInitialized=1;
            cache.shroud=need(s.load5956c0)("SHROUD.SHP");
            cache.shroudFog=need(s.load5956c0)("FOG.SHP");
        }
        image=(need(s.scenarioFlags)()&0x1000)?cache.shroudFog:cache.shroud;
    }
    const auto word=[&](std::size_t at)->std::uint16_t{
        if(at+2>image.size())throw std::invalid_argument("Visibility SHP header exceeds backing");
        return std::uint16_t(image[at]|(unsigned(image[at+1])<<8));};
    const auto signedWord=[&](std::size_t at){const auto v=word(at);return v<32768?int(v):int(v)-65536;};
    const auto frames=signedWord(6);
    const bool valid=std::uint32_t(frame)<std::uint32_t(frames);
    auto bounds=cache.invalidFrame;std::size_t header=0;
    if(valid){header=8+std::size_t(std::uint32_t(frame))*24;
        bounds={signedWord(header),signedWord(header+2),signedWord(header+4),signedWord(header+6)};}
    // Safe geometry domain; original malformed-input faults are not emulated.
    for(auto n:{screen.x,screen.y,clip.x,clip.y,clip.width,clip.height,bounds.x,bounds.y,bounds.width,bounds.height})
        if(std::abs(std::int64_t(n))>1048576)throw std::invalid_argument("Visibility geometry outside bounded profile");
    const auto bottomSprite=screen.y+bounds.y+bounds.height,rightSprite=screen.x+bounds.x+bounds.width;
    if(bottomSprite<clip.y+1||screen.y>=clip.y+clip.height||rightSprite<clip.x+1||screen.x>=clip.x+clip.width)return;
    const int top=std::max(clip.y,screen.y+bounds.y),bottom=std::min(clip.y+clip.height,bottomSprite);
    const int left=std::max(clip.x,screen.x+bounds.x),right=std::min(clip.x+clip.width,rightSprite);
    const auto initial=need(s.alpha)();
    const int destinationGap=fillAdd(fillSub(initial.rowWords28,right),left);
    std::uint32_t payload=0;
    if(valid){payload=std::uint32_t(word(header+20))|(std::uint32_t(word(header+22))<<16);}
    auto at=need(s.address411230)({left,fillSub(top,need(s.viewportY)())});
    const auto plane=need(s.alpha)();
    // neg(left)<<31 disappears after the following scale by two, modulo32.
    const auto probe=at+(std::uint32_t(right)+std::uint32_t(plane.rowWords28)*std::uint32_t(bottom-top)-std::uint32_t(left))*2+4;
    const bool wrapped=probe>=plane.end1c;
    // Shroud's fast branch is do/while in both dimensions; an entered empty
    // clip can therefore write one pixel. Fog and wrapped shroud test height.
    const int rows=(!fog&&!wrapped)?std::max(1,bottom-top):std::max(0,bottom-top);
    const int columns=(!fog&&!wrapped)?std::max(1,right-left):std::max(0,right-left);
    if(!rows)return;
    if(bounds.width<=0||!payload)throw std::invalid_argument("Visibility entered invalid frame/payload outside profile");
    if(std::uint64_t(columns)*std::uint32_t(rows)>67108864)throw std::invalid_argument("Visibility raster exceeds execution bound");
    std::uint64_t source=std::uint64_t(payload)+std::uint64_t(bounds.width)*std::uint32_t(top-screen.y-bounds.y)+std::uint32_t(left-screen.x-bounds.x);
    const auto sourceGap=bounds.width-(right-left);
    const auto backing=plane.plane;
    if(!backing.storage.empty()&&!backing.words.empty())throw std::invalid_argument("Ambiguous visibility alpha backing");
    const auto size=backing.words.empty()?std::uint64_t(backing.storage.size()):std::uint64_t(backing.words.size())*2;
    const auto read=[&](std::uint32_t p){
        if(std::uint64_t(p)+2>size)throw std::invalid_argument("Visibility alpha access exceeds backing");
        if(backing.words.empty())return unsigned(backing.storage[p])|(unsigned(backing.storage[p+1])<<8);
        return (unsigned(backing.words[p/2])>>(8*(p&1)))|((p&1)?(unsigned(backing.words[(p+1)/2]&255)<<8):0);};
    const auto store=[&](std::uint32_t p,std::uint16_t value){
        (void)read(p);
        for(unsigned i=0;i<2;++i){const auto k=p+i,shift=8*(k&1);const auto v=std::uint8_t(value>>(8*i));
            if(backing.words.empty())backing.storage[k]=v;
            else backing.words[k/2]=std::uint16_t((backing.words[k/2]&~(255u<<shift))|(unsigned(v)<<shift));}
        if(stores)stores(p,2,value);
    };
    for(int y=0;y<rows;++y){
        for(int x=0;x<columns;++x){
            if(source>=image.size())throw std::invalid_argument("Visibility raw payload exceeds backing");
            const auto v=image[source++];bool wrote=false;
            if(fog){if(v<=127){const auto old=read(at);store(at,std::uint16_t(old==127?v:std::max(0,int(old)+int(v)-127)));wrote=true;}}
            else if(wrapped?v!=254:int(v)!=s.transparent79dad0){store(at,v);wrote=true;}
            at+=2;
            // Wrapped code reloads the alpha global after every store. It
            // retains the preceding owner on transparent pixels and row gaps.
            if(wrapped&&wrote){const auto live=need(s.alpha)();if(at>=live.end1c)at-=live.bytes20;}
            else if(wrapped&&at>=plane.end1c)at-=plane.bytes20;
        }
        source+=sourceGap;at+=std::uint32_t(destinationGap)*2;
        if(wrapped&&at>=plane.end1c)at-=plane.bytes20;
    }
}
}
