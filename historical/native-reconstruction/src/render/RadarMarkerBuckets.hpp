// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/RadarMarkerPlacement.hpp"
#include "render/SurfaceCopy.hpp"
namespace ra2 {
struct RadarMarkerVectorServices {
    std::function<std::span<SurfaceMarkEntry>(std::uint32_t)> allocate;
    std::function<void(std::span<SurfaceMarkEntry>)> release;
    std::function<void(unsigned,unsigned,std::uint32_t)> fieldStore;
    std::function<void(std::span<SurfaceMarkEntry>,unsigned,std::uintptr_t)> entryStore;
};
inline void markerVectorField(const RadarMarkerVectorServices& s,unsigned off,unsigned n,std::uint32_t value){
    if(s.fieldStore)s.fieldStore(off,n,value);
}
inline std::uintptr_t markerEntryWord(std::span<SurfaceMarkEntry> entries,unsigned at){
    if(at%4||at/16>=entries.size())throw std::invalid_argument("Radar marker entry read extent");
    const auto& e=entries[at/16];
    switch(at%16){case 0:return e.actor?reinterpret_cast<std::uintptr_t>(e.actor):0;
        case 4:return std::uint32_t(e.x);case 8:return std::uint32_t(e.y);default:return e.trailer;}
}
inline void markerEntryStore(std::span<SurfaceMarkEntry> entries,unsigned at,std::uintptr_t value,
        const RadarMarkerVectorServices& s){
    if(at%4||at/16>=entries.size())throw std::invalid_argument("Radar marker entry store extent");
    auto& e=entries[at/16];
    switch(at%16){case 0:e.actor=value?reinterpret_cast<const void*>(value):nullptr;break;
        case 4:e.x=std::bit_cast<std::int32_t>(std::uint32_t(value));break;
        case 8:e.y=std::bit_cast<std::int32_t>(std::uint32_t(value));break;default:e.trailer=value;}
    if(s.entryStore)s.entryStore(entries,at,value);
}
// Complete634BC0; external backing stays referenced after capacity/count clear.
inline void clearRadarMarkerBucket(SurfaceMarkBucket& b,const RadarMarkerVectorServices& s){
    b.count=0;markerVectorField(s,16,4,0);
    if(b.entries.data()&&b.owns){
        if(!s.release)throw std::invalid_argument("Radar marker release unbound");
        s.release(b.entries);b.entries={};markerVectorField(s,4,4,0);
    }
    b.owns=0;markerVectorField(s,13,1,0);b.capacity=0;markerVectorField(s,8,4,0);
}
// Complete634E40, stock dynamic vector, null external argument. Unlike point
// vectors, new entries initialize only their first three words before copying
// ALL FOUR words of every old capacity slot, including inactive tails.
inline bool resizeRadarMarkerBucket(SurfaceMarkBucket& b,std::int32_t capacity,
        const RadarMarkerVectorServices& s){
    if(capacity){
        b.valid=0;markerVectorField(s,12,1,0);
        if(!s.allocate)throw std::invalid_argument("Radar marker allocation unbound");
        auto next=s.allocate(std::uint32_t(capacity)*16u);
        if(next.data()){
            if(capacity>4096||capacity<0||std::size_t(capacity)>next.size())
                throw std::invalid_argument("Radar marker initialization extent");
            for(std::int32_t i=0;i<capacity;++i)for(unsigned word=0;word<3;++word)
                markerEntryStore(next,unsigned(i)*16+word*4,0,s);
        }
        b.valid=1;markerVectorField(s,12,1,1);
        if(!next.data())return false;
        if(b.entries.data()){
            const auto copy=std::min(capacity,b.capacity);
            if(copy>4096)throw std::invalid_argument("Radar marker copy execution bound");
            for(std::int32_t i=0;i<copy;++i)for(unsigned word=0;word<4;++word)
                markerEntryStore(next,unsigned(i)*16+word*4,markerEntryWord(b.entries,unsigned(i)*16+word*4),s);
            if(b.owns){
                if(!s.release)throw std::invalid_argument("Radar marker release unbound");
                s.release(b.entries);b.entries={};markerVectorField(s,4,4,0);
            }
        }
        b.entries=next;markerVectorField(s,4,4,1);b.capacity=capacity;markerVectorField(s,8,4,std::uint32_t(capacity));
        b.owns=1;markerVectorField(s,13,1,1);
    }else clearRadarMarkerBucket(b,s);
    if(b.capacity<b.count){b.count=b.capacity;markerVectorField(s,16,4,std::uint32_t(b.count));}
    return true;
}
// Complete634F50 ignores valid and compares actor/x/y only, never the trailer.
inline std::int32_t findRadarMarker(const SurfaceMarkBucket& b,const void* actor,std::int32_t x,std::int32_t y){
    if(b.count<=0)return -1;
    if(b.count>4096||std::size_t(b.count)>b.entries.size())throw std::invalid_argument("Radar marker find extent");
    for(std::int32_t i=0;i<b.count;++i){const auto& e=b.entries[std::size_t(i)];
        if(e.actor==actor&&e.x==x&&e.y==y)return i;
    }return -1;
}
struct RadarMarkerPosition {std::int32_t& x1A0;std::int32_t& y1A4;};
struct RadarMarkerBucketFields {
    RefreshSurface* const& first1218;
    SurfaceMarkBuckets* const& buckets1254;
    const void* const& currentHouseA35DB4;
    std::uint8_t& dirty14D5;
};
struct RadarMarkerBucketServices {
    std::function<std::int32_t(const void*)> kind2C;
    std::function<const void*(const void*)> owner1B4;
    std::function<RadarMarkerPosition(const void*)> position;
    std::function<RadarMarkerVectorServices(unsigned)> vector;
    std::function<void(const RadarShapePoint&)> queue632620;
    std::function<void(const void*,unsigned,std::int32_t)> actorStore;
    std::function<void(std::uint8_t)> dirtyStore;
};
inline unsigned radarMarkerBucket(std::int32_t x,std::int32_t y){return (std::uint32_t(x)-std::uint32_t(y)*5u)&255u;}
inline SurfaceMarkBucket& radarMarkerBucket(RadarMarkerBucketFields f,unsigned index){
    if(!f.buckets1254)throw std::invalid_argument("Radar marker bucket owner");return (*f.buckets1254)[index];
}
inline void finishRadarMarker(RadarShapePoint point,RadarMarkerBucketFields f,const RadarMarkerBucketServices& s){
    if(!s.queue632620)throw std::invalid_argument("Radar marker dirty producer unbound");
    s.queue632620(point);f.dirty14D5=1;if(s.dirtyStore)s.dirtyStore(1);
}
// Complete631910; actual stock rectangle virtual and actor kind association are
// explicit. Services lend the same actor/House/vector/dirty owners as drawing.
inline void insertRadarMarker(const void* actor,std::int32_t x,std::int32_t y,
        RadarMarkerBucketFields f,const RadarMarkerBucketServices& s){
    auto* surface=f.first1218;
    if(!surface||!surface->table||!surface->table->rect78)throw std::invalid_argument("Radar marker rectangle owner");
    RefreshRect scratch{};auto* rect=surface->table->rect78(*surface,scratch);
    if(!rect)throw std::invalid_argument("Radar marker rectangle result");
    const auto left=(*rect)[0],top=(*rect)[1],width=(*rect)[2],height=(*rect)[3];
    if(x<left||x>=fillAdd(left,width)||y<top||y>=fillAdd(top,height)){
        if(!s.kind2C)throw std::invalid_argument("Radar marker kind unbound");
        if(s.kind2C(actor)==6)return;
        if(x<left)x=left;if(x>=fillAdd(left,width))x=fillSub(fillAdd(left,width),1);
        if(y<top)y=top;if(y>=fillAdd(top,height))y=fillSub(fillAdd(top,height),1);
        if(!s.position)throw std::invalid_argument("Radar marker position owner");
        auto p=s.position(actor);p.x1A0=x;if(s.actorStore)s.actorStore(actor,0x1a0,x);
        p.y1A4=y;if(s.actorStore)s.actorStore(actor,0x1a4,y);
    }
    const auto index=radarMarkerBucket(x,y);auto& b=radarMarkerBucket(f,index);
    if(findRadarMarker(b,actor,x,y)!=-1)return;
    if(!s.owner1B4||!s.vector)throw std::invalid_argument("Radar marker owner/vector unbound");
    const auto* savedCurrent=f.currentHouseA35DB4;
    const bool prepend=s.owner1B4(actor)==savedCurrent;
    const auto services=s.vector(index);
    bool append=b.count<b.capacity;
    if(!append&&(b.owns||b.capacity==0)&&b.growth>0)
        append=resizeRadarMarkerBucket(b,fillAdd(b.capacity,b.growth),services);
    if(append){
        if(b.count<0||b.count>=4096||std::size_t(b.count)>=b.entries.size())throw std::invalid_argument("Radar marker insertion extent");
        const auto at=prepend?0u:unsigned(b.count)*16;
        if(prepend&&b.count){
            const auto entries=b.entries;
            transferSurfaceOverlapBytes(true,16,0,unsigned(b.count)*16,[&](auto to,auto from,unsigned n){
                if(n!=4)throw std::invalid_argument("Radar marker transfer alignment");
                markerEntryStore(entries,to,markerEntryWord(entries,from),services);
            });
        }
        if(!prepend){b.count=fillAdd(b.count,1);markerVectorField(services,16,4,std::uint32_t(b.count));}
        markerEntryStore(b.entries,at,reinterpret_cast<std::uintptr_t>(actor),services);
        markerEntryStore(b.entries,at+4,std::uint32_t(x),services);markerEntryStore(b.entries,at+8,std::uint32_t(y),services);
        markerEntryStore(b.entries,at+12,reinterpret_cast<std::uintptr_t>(actor),services);
        if(prepend){b.count=fillAdd(b.count,1);markerVectorField(services,16,4,std::uint32_t(b.count));}
    }
    finishRadarMarker({x,y},f,s);
}
// Complete631AF0 with actual634F50: decrement before four-word forward shifts,
// retaining the inactive tail and no refresh at all for a missing match.
inline void removeRadarMarker(const void* actor,std::int32_t x,std::int32_t y,
        RadarMarkerBucketFields f,const RadarMarkerBucketServices& s){
    const auto bucket=radarMarkerBucket(x,y);auto& b=radarMarkerBucket(f,bucket);
    const auto index=findRadarMarker(b,actor,x,y);if(index==-1||index>=b.count)return;
    if(!s.vector)throw std::invalid_argument("Radar marker vector services unbound");const auto services=s.vector(bucket);
    b.count=fillSub(b.count,1);markerVectorField(services,16,4,std::uint32_t(b.count));
    for(auto i=index;i<b.count;i=fillAdd(i,1)){
        if(i<0||i>=4096)throw std::invalid_argument("Radar marker removal extent");const auto entries=b.entries;
        for(unsigned word=0;word<4;++word)markerEntryStore(entries,unsigned(i)*16+word*4,
            markerEntryWord(entries,unsigned(i+1)*16+word*4),services);
    }
    finishRadarMarker({x,y},f,s);
}
}
