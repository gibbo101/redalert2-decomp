// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/BuildingDepthImage.hpp"
#include <algorithm>
#include <bit>
namespace ra2 {
void initializeBuildingDepthImage(BuildingDepthImageState& state,const BuildingDepthImageServices& s){
    const auto need=[]<class F>(const F& f)->const F&{if(!f)throw std::invalid_argument("Building depth initializer child missing");return f;};
    const auto publish=[&]{if(s.globalStore)s.globalStore(state.raw);};
    if(state.raw){need(s.release781d3b)(state.raw);state.raw.reset();publish();}
    need(s.construct468f50)("BUILDNGZ.SHP");
    const auto size=need(s.size2c)();
    need(s.destroy438410)();need(s.destroy42f350)();
    if(size>64u*1024u*1024u)throw std::invalid_argument("Building depth allocation outside bounded profile");
    auto allocated=need(s.allocate782017)(size);
    if(!allocated||allocated->size()!=size)throw std::invalid_argument("Building depth allocation failed/size differs");
    state.raw=std::move(allocated);publish();
    const auto source=need(s.source5956c0)("BUILDNGZ.SHP");
    // The original reloads the global after the cache child; do not save the
    // allocation result across that child and copy into a stale receiver.
    const auto destination=state.raw;
    if(!destination||destination->size()<size||source.size()<size)throw std::invalid_argument("Building depth copy outside backing");
    const auto store=[&](std::uint32_t at,std::uint32_t n,std::uint32_t value){
        if(s.memoryStore)s.memoryStore(*destination,at,n,value);
    };
    std::uint32_t at=0;
    for(;size-at>=4;at+=4){
        std::uint32_t word=0;for(unsigned k=0;k<4;++k)word|=std::uint32_t(source[at+k])<<(k*8);
        for(unsigned k=0;k<4;++k)(*destination)[at+k]=std::uint8_t(word>>(k*8));
        store(at,4,word);
    }
    for(;at<size;++at){(*destination)[at]=source[at];store(at,1,source[at]);}
    const auto& b=*destination;
    const auto u16=[&](std::size_t p){if(p+2>b.size())throw std::invalid_argument("Truncated Building depth header");return std::uint16_t(b[p]|std::uint16_t(b[p+1])<<8);};
    const auto count=u16(6);
    std::uint32_t pixels=0;
    if(count){
        if(b.size()<32)throw std::invalid_argument("Truncated first Building depth frame");
        for(unsigned k=0;k<4;++k)pixels|=std::uint32_t(b[28+k])<<(k*8);
    }
    const auto width=std::bit_cast<std::int16_t>(u16(2)),height=std::bit_cast<std::int16_t>(u16(4));
    if(width<=0||height<=0)return;
    const auto length=std::uint32_t(width)*std::uint32_t(height);
    if(!pixels||pixels>b.size()||length>b.size()-pixels)throw std::invalid_argument("Building depth first canvas outside backing");
    for(std::uint32_t i=0;i<length;++i){
        auto& value=(*destination)[pixels+i];
        if(value){value=std::uint8_t(unsigned(value)-0x41u);store(pixels+i,1,value);}
    }
}
ShpImage loadBuildingDepthImage(const AssetStore& assets,BuildingDepthImageState& state){
    Data source;
    BuildingDepthImageServices s;
    s.release781d3b=[](const auto&){};
    s.construct468f50=[&](std::string_view name){source=assets.require(std::string(name));};
    s.size2c=[&]{if(source.size>64u*1024u*1024u)throw std::invalid_argument("Building depth asset too large");return std::uint32_t(source.size);};
    s.destroy438410=[]{};s.destroy42f350=[]{};
    s.allocate782017=[](std::uint32_t size){return std::make_shared<Bytes>(size);};
    s.source5956c0=[&](std::string_view name){if(name!="BUILDNGZ.SHP")throw std::invalid_argument("Building depth asset association");return std::span(source.ptr(),source.size);};
    initializeBuildingDepthImage(state,s);
    Data transformed;transformed.storage=state.raw;transformed.size=state.raw->size();
    return readShp(transformed);
}
}
