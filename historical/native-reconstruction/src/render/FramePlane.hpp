// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/FrameDepthRefresh.hpp"
namespace ra2 {
struct FramePlaneView {
    std::uint32_t& offset10;
    const std::uint32_t& begin18;
    const std::uint32_t& end1c;
    const std::uint32_t& bytes20;
    std::int32_t& base24;
    const std::int32_t& width28;
    const std::int32_t& height2c;
    SurfacePixelBacking plane;
};
using FramePlaneFill=std::function<void(FillRect,std::uint32_t)>;
using FramePlaneStore=std::function<void(int,std::uint32_t)>;
// Complete776160/411050: height precedes width; color is truncated before the
// live surface's ordinary rectangle fill. Surface construction remains supplied.
inline void clearFramePlane(FramePlaneView v,std::uint32_t color,const FramePlaneFill& fill){
    const auto height=v.height2c;const auto width=v.width28;
    if(!fill)throw std::invalid_argument("Frame plane fill unbound");fill({0,0,width,height},color&65535);
}
// Complete775D60/410C50. Common backing addresses are normalized to offsets;
// its nonwrapping allocation is below2GiB, and signed intermediate scrolls stay
// within one allocation. Raw32 offset/base stores and single wraps are retained.
inline void scrollFramePlane(FramePlaneView v,std::int32_t dx,std::int32_t dy,std::uint32_t color,
        const FramePlaneFill& fill,const FillStoreTrace& pixels={},const FramePlaneStore& fields={}){
    const auto width=v.width28;
    if(width<=0||width>1048576||v.height2c<=0||v.height2c>1048576||
        std::uint64_t(width)*std::uint32_t(v.height2c)>67108864||
        dx==INT32_MIN||dy==INT32_MIN||std::abs(std::int64_t(dx))>67108864||std::abs(std::int64_t(dy))>67108864||
        v.end1c>=0x80000000u||v.bytes20>=0x80000000u)
        throw std::invalid_argument("Frame plane scroll outside bounded profile");
    const auto offset=[&](std::uint32_t value){v.offset10=value;if(fields)fields(0x10,value);};
    const auto base=[&](std::int32_t value){v.base24=value;if(fields)fields(0x24,std::uint32_t(value));};
    const auto paint=[&](FillRect r){if(!fill)throw std::invalid_argument("Frame plane fill unbound");fill(r,color&65535);};
    const auto normalized=[&]{
        auto at=v.begin18+v.offset10;
        // In the accepted nonwrapping common allocation, a negative relative
        // offset is exactly the original unsigned address-below-begin branch.
        if(std::bit_cast<std::int32_t>(v.offset10)<0)at+=v.bytes20;
        if(at>=v.end1c)at-=v.bytes20;return at-v.begin18;
    };
    const auto signedOffset=std::bit_cast<std::int32_t>(v.offset10);
    const auto oldColumn=(signedOffset/2)%width;
    if(std::abs(dx)>width||std::abs(dy)>v.height2c){
        paint({0,0,width,v.height2c});base(32768);return; // Offset is retained.
    }
    auto column=fillAdd(oldColumn,dx);
    if(dx){
        offset(v.offset10+std::uint32_t(dx)*2);offset(normalized());
        if(dx<0){
            if(column<0){paint({0,0,oldColumn,v.height2c});const auto w=v.width28;column=fillAdd(column,w);paint({column,0,fillSub(w,column),v.height2c});}
            else paint({column,0,fillSub(0,dx),v.height2c});
        }else{
            if(column>=width){paint({oldColumn,0,fillSub(width,oldColumn),v.height2c});column=fillSub(column,v.width28);paint({0,0,column,v.height2c});}
            else paint({oldColumn,0,dx,v.height2c});
        }
    }
    if(!dy)return;
    const auto old=v.offset10;const auto w=v.width28;
    if(w<=0)throw std::invalid_argument("Frame plane live width invalid");
    const auto row=(std::bit_cast<std::int32_t>(old)/2)/w;
    base(fillSub(v.base24,dy));offset(old+std::uint32_t(w)*std::uint32_t(dy)*2);offset(normalized());
    const auto nextRow=fillAdd(row,dy);const auto now=v.offset10;
    const auto half=[](std::uint32_t value){return std::bit_cast<std::int32_t>(value)/2;};
    const auto span=[&](std::uint32_t at,std::int32_t count){
        if(count<0||count>67108864)throw std::invalid_argument("Frame plane vertical span invalid");
        fillFrameDepthSpan(v.plane,at,std::uint32_t(count),color,pixels);
    };
    if(dy<0){
        if(nextRow<0){span(v.begin18,half(old));span(v.begin18+v.offset10,half(std::uint32_t(v.height2c)*std::uint32_t(v.width28)*2-v.offset10));}
        else span(v.begin18+now,half(old-now));
    }else{
        if(nextRow>=v.height2c){span(v.begin18+old,half(std::uint32_t(v.height2c)*std::uint32_t(v.width28)*2-old));span(v.begin18,half(v.offset10));}
        else span(v.begin18+old,half(now-old));
    }
}
}
