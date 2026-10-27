// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceRefresh.hpp"
#include <bit>
#include <span>
#include <utility>
namespace ra2 {
struct SurfaceMarkEntry {
    const void* actor;
    std::int32_t x,y;
    // Logical original fourth word. Marker producers repeat the actor identity;
    // older drawing fixtures may retain an uninterpreted numeric sentinel here.
    std::uintptr_t trailer;
};
struct SurfaceMarkBucket {
    std::span<SurfaceMarkEntry> entries;
    std::int32_t count=0,capacity=0,growth=10;
    std::uint8_t valid=1,owns=0;
};
using SurfaceMarkBuckets=std::array<SurfaceMarkBucket,256>;
struct SurfaceMarkBitmap { std::span<std::uint8_t> bytes;std::size_t origin; };
struct SurfaceMarkPalette { std::int32_t format4;std::span<const std::uint8_t> data174; };
struct SurfaceMarkScheme { const SurfaceMarkPalette* palette30C;std::uint32_t index330; };
struct SurfaceMarkServices {
    RefreshSurface* const& first1218;
    SurfaceMarkBuckets* const& buckets1254;
    SurfaceMarkBitmap* const& bitmap1270;
    const std::span<const SurfaceMarkScheme*>& schemesAB6EFC;
    // Pure borrowed field views; not additional game queries.
    std::function<const void*(const void*)> owner1B4;
    std::function<std::int32_t(const void*)> houseIndex15F40;
    std::function<std::uint8_t(const void*)> actorC0;
    std::function<const void*(const void*,std::uint32_t)> actorCC;
    std::function<const SurfaceMarkScheme*(std::uint32_t)> resolve663D30;
    std::function<void(RefreshSurface&,SurfaceMarkEntry&,std::uint32_t)> pixel24;
    // Diagnostic stores only; binding/telemetry must not introduce game queries.
    std::function<void(const SurfaceMarkBitmap&,std::size_t,unsigned,std::uint32_t)> store;
};
inline void refreshSurfaceMarks(const SurfaceMarkServices& s){
    const auto surface=[](RefreshSurface* p)->RefreshSurface&{
        if(!p||!p->table)throw std::invalid_argument("Missing mark surface/table");return *p;
    };
    auto& saved=surface(s.first1218);
    if(!saved.table->height80)throw std::invalid_argument("Missing mark height80");
    const auto height=saved.table->height80(saved);
    if(!saved.table->width7C)throw std::invalid_argument("Missing mark width7C");
    const auto width=saved.table->width7C(saved);
    const auto product=std::bit_cast<std::int32_t>(std::uint32_t(width)*std::uint32_t(height));
    const auto length=std::uint32_t(product/8)+1u;
    auto* bitmap=s.bitmap1270;
    if(!bitmap||bitmap->origin>bitmap->bytes.size()||length>bitmap->bytes.size()-bitmap->origin)
        throw std::invalid_argument("Mark bitmap clear outside backing");
    const auto write=[&](SurfaceMarkBitmap& b,std::size_t p,unsigned n,std::uint32_t value){
        if(p>b.bytes.size()||n>b.bytes.size()-p)throw std::invalid_argument("Mark bitmap store outside backing");
        for(unsigned i=0;i<n;++i)b.bytes[p+i]=std::uint8_t(value>>(8*i));
        if(s.store)s.store(b,p,n,value);
    };
    std::uint32_t cleared=0;
    for(;length-cleared>=4;cleared+=4)write(*bitmap,bitmap->origin+cleared,4,0);
    for(;cleared<length;++cleared)write(*bitmap,bitmap->origin+cleared,1,0);
    const auto scheme=[&](const void* house)->const SurfaceMarkScheme*{
        if(!s.houseIndex15F40)throw std::invalid_argument("Missing mark House index view");
        const auto index=s.houseIndex15F40(house);
        if(index<0||std::size_t(index)>=s.schemesAB6EFC.size())throw std::invalid_argument("Mark House scheme index");
        return s.schemesAB6EFC[std::size_t(index)];
    };
    for(std::size_t bucket=0;bucket<256;++bucket){
        if(!s.buckets1254)throw std::invalid_argument("Missing mark bucket table");
        const auto count=(*s.buckets1254)[bucket].count;
        const auto entries=(*s.buckets1254)[bucket].entries;
        if(count<=0)continue;
        if(std::size_t(count)>entries.size()||count>4096)throw std::invalid_argument("Mark bucket count/backing bound");
        for(std::int32_t i=0;i<count;++i){
            auto& current=surface(s.first1218);
            auto& entry=entries[std::size_t(i)];
            const auto actor=entry.actor; // Before width callback; x/y remain late.
            if(!current.table->width7C)throw std::invalid_argument("Missing mark width7C");
            const auto w=current.table->width7C(current);
            const auto index=std::bit_cast<std::int32_t>(std::uint32_t(w)*std::uint32_t(entry.y)+std::uint32_t(entry.x));
            const auto mask=std::uint32_t(1)<<(std::uint32_t(index)&7);
            // Arithmetic signed shift, without relying on a host shift model.
            const auto byte=index/8-(index<0&&index%8!=0?1:0);
            bitmap=s.bitmap1270;
            if(!bitmap||bitmap->origin>bitmap->bytes.size())throw std::invalid_argument("Missing mark bitmap");
            const auto at=std::int64_t(bitmap->origin)+byte;
            if(at<0||std::uint64_t(at)>=bitmap->bytes.size())throw std::invalid_argument("Mark bitmap bit outside backing");
            const auto old=bitmap->bytes[std::size_t(at)];
            if(old&mask)continue;
            write(*bitmap,std::size_t(at),1,old|mask);
            if(!s.owner1B4||!s.actorC0)throw std::invalid_argument("Missing mark actor view/virtual");
            auto* color=scheme(s.owner1B4(actor));
            if(s.actorC0(actor)){
                if(!s.actorCC)throw std::invalid_argument("Missing mark actorCC");
                if(s.actorCC(actor,0))color=scheme(s.actorCC(actor,0));
                else {
                    if(!s.resolve663D30)throw std::invalid_argument("Missing mark scheme resolver");
                    color=s.resolve663D30(1);
                }
            }
            if(!color||!color->palette30C)throw std::invalid_argument("Missing mark color scheme/palette");
            const auto& palette=*color->palette30C;
            const auto bytes=palette.format4==1?1u:2u;
            const auto offset=std::uint64_t(color->index330)*bytes;
            if(offset>palette.data174.size()||bytes>palette.data174.size()-offset)throw std::invalid_argument("Mark palette index outside backing");
            auto pixel=std::uint32_t(palette.data174[std::size_t(offset)]);
            if(bytes==2)pixel|=std::uint32_t(palette.data174[std::size_t(offset)+1])<<8;
            auto& target=surface(s.first1218);
            if(!s.pixel24)throw std::invalid_argument("Missing mark pixel24");
            s.pixel24(target,entry,pixel);
        }
    }
}
// Separate explicit parent composition; no query or runtime adoption on binding.
class SurfaceRefreshMarksBinding {
    SurfaceRefreshServices& target_;
    decltype(SurfaceRefreshServices::finish6324A0) saved_;
public:
    SurfaceRefreshMarksBinding(SurfaceRefreshServices& target,const SurfaceMarkServices& marks):target_(target){
        decltype(saved_) replacement=[&marks]{refreshSurfaceMarks(marks);};
        saved_=std::move(target_.finish6324A0);target_.finish6324A0=std::move(replacement);
    }
    ~SurfaceRefreshMarksBinding(){target_.finish6324A0=std::move(saved_);}
    SurfaceRefreshMarksBinding(const SurfaceRefreshMarksBinding&)=delete;
    SurfaceRefreshMarksBinding& operator=(const SurfaceRefreshMarksBinding&)=delete;
    SurfaceRefreshMarksBinding(SurfaceRefreshMarksBinding&&)=delete;
    SurfaceRefreshMarksBinding& operator=(SurfaceRefreshMarksBinding&&)=delete;
};
}
