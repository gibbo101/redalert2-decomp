// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/RadarProjection.hpp"
#include <memory>
#include <vector>
namespace ra2 {
struct RadarShapePoint { std::int32_t x,y; };
struct RadarShapeVector {
    std::span<RadarShapePoint> items;
    std::int32_t capacity=0,count=0,growth=10;
    std::uint8_t valid=1,owns=0;
};
struct RadarShapeServices {
    std::function<std::span<RadarShapePoint>(std::uint32_t)> allocate;
    std::function<void(std::span<RadarShapePoint>)> release;
    std::function<void(unsigned,unsigned,std::uint32_t)> fieldStore;
    std::function<void(std::span<RadarShapePoint>,unsigned,unsigned,std::uint32_t)> pointStore;
};
inline void radarShapeField(const RadarShapeServices& s,unsigned off,unsigned n,std::uint32_t v){if(s.fieldStore)s.fieldStore(off,n,v);}
// Complete5B16E0. External backing remains referenced even after capacity becomes0.
inline void clearRadarShapeVector(RadarShapeVector& v,const RadarShapeServices& s){
    v.count=0;radarShapeField(s,16,4,0);
    if(v.items.data()&&v.owns){
        if(!s.release)throw std::invalid_argument("Radar shape release unbound");
        s.release(v.items);v.items={};radarShapeField(s,4,4,0);
    }
    v.owns=0;radarShapeField(s,13,1,0);v.capacity=0;radarShapeField(s,8,4,0);
}
// Complete5B1B00 with its second argument0 (the632700 caller's profile).
// Allocation/free are native platform services. Failed allocation still sets valid1.
inline bool resizeRadarShapeVector(RadarShapeVector& v,std::int32_t capacity,const RadarShapeServices& s){
    if(capacity){
        v.valid=0;radarShapeField(s,12,1,0);
        if(!s.allocate)throw std::invalid_argument("Radar shape allocation unbound");
        auto next=s.allocate(std::uint32_t(capacity)*8u);
        v.valid=1;radarShapeField(s,12,1,1);
        if(!next.data())return false;
        if(v.items.data()){
            const auto copy=std::min(v.capacity,capacity);
            if(copy>0){
                if(std::size_t(copy)>v.items.size()||std::size_t(copy)>next.size())throw std::invalid_argument("Radar shape resize backing");
                for(std::int32_t i=0;i<copy;++i){
                    next[std::size_t(i)].x=v.items[std::size_t(i)].x;
                    if(s.pointStore)s.pointStore(next,unsigned(i)*8,4,std::uint32_t(next[std::size_t(i)].x));
                    next[std::size_t(i)].y=v.items[std::size_t(i)].y;
                    if(s.pointStore)s.pointStore(next,unsigned(i)*8+4,4,std::uint32_t(next[std::size_t(i)].y));
                }
            }
            if(v.owns){
                if(!s.release)throw std::invalid_argument("Radar shape release unbound");
                s.release(v.items);v.items={};radarShapeField(s,4,4,0);
            }
        }
        v.items=next;radarShapeField(s,4,4,1);v.capacity=capacity;radarShapeField(s,8,4,std::uint32_t(capacity));
        v.owns=1;radarShapeField(s,13,1,1);
    }else clearRadarShapeVector(v,s);
    if(v.capacity<v.count){v.count=v.capacity;radarShapeField(s,16,4,std::uint32_t(v.count));}
    return true;
}
using RadarShapeDimensions=std::array<std::int32_t,22>;
// Complete632700 on stock point vectors. Dimension tables are borrowed private
// inputs, not embedded extracted game data. Preserve late scale reads after Clear.
inline void initializeRadarShapeBuckets(std::span<RadarShapeVector,22> buckets,
        const float& scale,const RadarShapeDimensions& widths,const RadarShapeDimensions& heights,
        const std::function<RadarShapeServices(unsigned)>& services){
    OriginalRounding rounding;
    const auto size=[&](std::int32_t dimension){
        volatile double product=dimension==1?double(scale):double(dimension)*double(scale);
        volatile double rounded=product+.5;
        const double minimum=dimension==1?1.0:2.0;
        return radarProjectionInteger(rounded<minimum?minimum:double(rounded));
    };
    for(unsigned i=0;i<22;++i){
        if(!services)throw std::invalid_argument("Radar shape services unbound");
        auto s=services(i);auto& v=buckets[i];clearRadarShapeVector(v,s);
        const auto width=widths[i],height=heights[i];
        const auto w=size(width),h=size(height),rows=fillSub(fillAdd(w,h),1);
        if(rows>4096)throw std::invalid_argument("Radar shape row execution bound");
        for(std::int32_t y=0;y<rows;y=fillAdd(y,1)){
            const auto left=y<h?fillSub(0,y):fillAdd(fillSub(y,fillAdd(h,h)),2);
            const auto right=y<w?y:fillSub(fillSub(fillAdd(w,w),y),2);
            if(left<=right&&std::uint32_t(right)-std::uint32_t(left)>4096)throw std::invalid_argument("Radar shape column execution bound");
            unsigned columns=0;
            for(auto x=left;x<=right;x=fillAdd(x,1)){
                if(++columns>4096)throw std::invalid_argument("Radar shape column execution bound");
                bool append=v.count<v.capacity;
                if(!append&&(v.owns||v.capacity==0)&&v.growth>0)
                    append=resizeRadarShapeVector(v,fillAdd(v.capacity,v.growth),s);
                if(append){
                    const auto index=v.count;v.count=fillAdd(v.count,1);radarShapeField(s,16,4,std::uint32_t(v.count));
                    if(index<0||std::size_t(index)>=v.items.size())throw std::invalid_argument("Radar shape point backing");
                    v.items[std::size_t(index)].x=x;if(s.pointStore)s.pointStore(v.items,unsigned(index)*8,4,std::uint32_t(x));
                    v.items[std::size_t(index)].y=y;if(s.pointStore)s.pointStore(v.items,unsigned(index)*8+4,4,std::uint32_t(y));
                }
            }
        }
    }
}
// Native allocations for exactly the existing22 shape vectors. Their spans are
// the records consumed by the recovered kernels, with no second point model.
class NativeRadarShapeBuckets {
    std::array<RadarShapeVector,22> buckets_{};
    struct Allocation { std::unique_ptr<RadarShapePoint[]> points;std::size_t count; };
    std::vector<Allocation> allocations_;
public:
    NativeRadarShapeBuckets()=default;
    NativeRadarShapeBuckets(const NativeRadarShapeBuckets&)=delete;
    NativeRadarShapeBuckets& operator=(const NativeRadarShapeBuckets&)=delete;
    std::span<const RadarShapeVector,22> buckets()const{return buckets_;}
    void initialize(const float& scale,const RadarShapeDimensions& widths,const RadarShapeDimensions& heights){
        initializeRadarShapeBuckets(buckets_,scale,widths,heights,[this](unsigned){
            RadarShapeServices s;
            s.allocate=[this](std::uint32_t bytes)->std::span<RadarShapePoint>{
                if(!bytes||bytes%8||bytes>32768)throw std::invalid_argument("Native radar shape allocation extent");
                auto points=std::make_unique<RadarShapePoint[]>(bytes/8);auto view=std::span<RadarShapePoint>(points.get(),bytes/8);
                allocations_.push_back({std::move(points),view.size()});return view;
            };
            s.release=[this](auto points){
                const auto it=std::find_if(allocations_.begin(),allocations_.end(),[&](const auto& a){return a.points.get()==points.data();});
                if(it==allocations_.end())throw std::invalid_argument("Native radar shape allocation identity");allocations_.erase(it);
            };return s;
        });
    }
};
}
