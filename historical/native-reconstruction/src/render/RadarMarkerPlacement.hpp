// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/RadarShapeBuckets.hpp"
#include "render/SurfaceRefreshMarks.hpp"
namespace ra2 {
struct RadarMarkerProjectionFields {
    const float& scale1484;
    const std::int32_t &origin148C,&origin1494,&width14A0,&height14A4;
};
// Complete631BA0. This is the coordinate helper, not actor/type footprint
// production. Output may alias input; read both input words before either store.
inline RadarShapePoint& projectRadarMarker(RadarShapePoint& out,const RadarShapePoint& world,
        std::uint8_t clamp,RadarMarkerProjectionFields s){
    OriginalRounding rounding;
    const auto x=world.x,y=world.y;
    const auto first=fillAdd(fillSub(std::bit_cast<std::int32_t>(std::uint32_t(s.origin148C)<<8),y),x);
    volatile double a=double(first)*double(s.scale1484);
    volatile double b=a*0x1p-8;
    auto px=radarProjectionInteger(b);
    const auto second=fillAdd(fillSub(y,std::bit_cast<std::int32_t>(std::uint32_t(s.origin1494)<<8)),x);
    volatile double c=double(second)*double(s.scale1484);
    volatile double d=c*0x1p-8;
    auto py=radarProjectionInteger(d);
    if(clamp){
        if(px<0)px=0;
        if(px>=s.width14A0)px=fillSub(s.width14A0,1);
        if(py<0)py=0;
        if(py>=s.height14A4)py=fillSub(s.height14A4,1);
    }
    out.x=px;out.y=py;return out;
}
struct RadarDirtyFields {
    RefreshSurface* const& first1218;
    SurfaceMarkBitmap* const& bitmap1270;
    RadarShapeVector& points1258;
    std::uint8_t& dirty14D5;
};
struct RadarDirtyServices {
    RadarShapeServices vector;
    // Diagnostic write observations, not extra game queries.
    std::function<void(std::size_t,std::uint8_t)> bitmapStore;
    std::function<void(std::uint8_t)> dirtyStore;
};
// Complete632620 with the stock5B1B00 resize child. First set the bitmap bit;
// failed/disabled growth still sets dirty, and a later retry sees that bit.
template<class Point=RadarShapePoint>
inline void queueRadarDirtyPoint(const Point& point,RadarDirtyFields s,
        const RadarDirtyServices& services){
    const auto width=[&]{auto* p=s.first1218;
        if(!p||!p->table||!p->table->width7C)throw std::invalid_argument("Radar dirty width owner");
        return p->table->width7C(*p);};
    const auto height=[&]{auto* p=s.first1218;
        if(!p||!p->table||!p->table->height80)throw std::invalid_argument("Radar dirty height owner");
        return p->table->height80(*p);};
    if(point.x<0)return;
    const auto w=width();if(point.x>=w)return;
    if(point.y<0)return;
    const auto h=height();if(point.y>=h)return;
    const auto stride=width();
    const auto index=fillAdd(std::bit_cast<std::int32_t>(std::uint32_t(stride)*std::uint32_t(point.y)),point.x);
    const auto mask=std::uint8_t(1u<<(std::uint32_t(index)&7u));
    const auto byte=index/8-(index<0&&index%8!=0?1:0);
    auto* bitmap=s.bitmap1270;
    if(!bitmap||bitmap->origin>bitmap->bytes.size())throw std::invalid_argument("Radar dirty bitmap owner");
    const auto at=std::int64_t(bitmap->origin)+byte;
    if(at<0||std::uint64_t(at)>=bitmap->bytes.size())throw std::invalid_argument("Radar dirty bitmap extent");
    auto& bit=bitmap->bytes[std::size_t(at)];
    if(bit&mask)return;
    bit|=mask;if(services.bitmapStore)services.bitmapStore(std::size_t(at),bit);
    auto& v=s.points1258;
    bool append=v.count<v.capacity;
    if(!append&&(v.owns||v.capacity==0)&&v.growth>0)
        append=resizeRadarShapeVector(v,fillAdd(v.capacity,v.growth),services.vector);
    if(append){
        const auto old=v.count;v.count=fillAdd(old,1);radarShapeField(services.vector,16,4,std::uint32_t(v.count));
        if(old<0||std::size_t(old)>=v.items.size())throw std::invalid_argument("Radar dirty vector extent");
        v.items[std::size_t(old)].x=point.x;
        if(services.vector.pointStore)services.vector.pointStore(v.items,unsigned(old)*8,4,std::uint32_t(point.x));
        v.items[std::size_t(old)].y=point.y;
        if(services.vector.pointStore)services.vector.pointStore(v.items,unsigned(old)*8+4,4,std::uint32_t(point.y));
    }
    s.dirty14D5=1;if(services.dirtyStore)services.dirtyStore(1);
}
}
