// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceRefresh.hpp"
#include "render/SurfaceFill.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <bit>
#include <cmath>
#include <span>
namespace ra2 {
struct RadarProjectionFields {
    RefreshSurface*& second121C;
    std::span<std::uint8_t>& colors1238;
    std::int32_t& width123C;std::int32_t& height1240;
    std::span<std::uint8_t>& bitmap1270;
    float& scale1484;
    const std::array<std::int32_t,6>& shifts;
};
struct RadarProjectionServices {
    std::function<std::span<std::uint8_t>(std::uint32_t)> allocate;
    std::function<void(RefreshRect&,RefreshRect&)> colors631250;
    // Platform storage factory; ordinary BSurface initialization remains explicit.
    std::function<RefreshSurface*(std::int32_t,std::int32_t)> createSecond;
    std::function<void(RefreshSurface&,std::uint32_t)> clear;
    std::function<std::span<std::uint8_t>(RefreshSurface&,std::int32_t,std::int32_t)> lock;
    std::function<void(RefreshSurface&)> unlock;
    std::function<void(unsigned,std::uint32_t)> mapStore;
    std::function<void(char,std::uint32_t,unsigned,std::uint32_t)> bufferStore;
};
// Explicit53-bit/toward-zero profile, retaining each float32 spill. FTOL returns
// the low dword of its signed-qword result, including the indefinite zero low word.
inline std::int32_t radarProjectionInteger(double v){
    if(!std::isfinite(v)||v<-0x1p63||v>=0x1p63)return 0;
    return std::bit_cast<std::int32_t>(std::uint32_t(std::int64_t(v)));
}
inline std::uint32_t radarProjectionFloatBits(float v){return std::bit_cast<std::uint32_t>(v);}
inline RefreshRect* buildRadarProjection(RefreshRect& out,RefreshRect& source,
        RefreshRect& region,std::uint8_t update,RadarProjectionFields s,
        const RadarProjectionServices& services){
    OriginalRounding rounding;
    const auto need=[](bool v){if(!v)throw std::invalid_argument("Radar projection owner/service/domain");};
    const auto map=[&](unsigned off,std::uint32_t v){if(services.mapStore)services.mapStore(off,v);};
    const auto write=[&](std::span<std::uint8_t> bytes,char kind,std::uint32_t at,unsigned n,std::uint32_t value){
        need(std::uint64_t(at)+n<=bytes.size());for(unsigned i=0;i<n;++i)bytes[at+i]=std::uint8_t(value>>(8*i));
        if(services.bufferStore)services.bufferStore(kind,at,n,value);
    };
    const auto zero=[&](std::span<std::uint8_t> bytes,char kind,std::uint32_t n){
        std::uint32_t p=0;for(;n-p>=4;p+=4)write(bytes,kind,p,4,0);for(;p<n;++p)write(bytes,kind,p,1,0);
    };
    if(update&&(region[2]<=0||region[3]<=0))for(unsigned i=0;i<4;++i)region[i]=source[i];
    if(s.colors1238.empty()){
        const auto pixels=std::uint32_t(source[2])*std::uint32_t(source[3]);const auto n=pixels*3;
        need(n<=16*1024*1024&&bool(services.allocate));s.colors1238=services.allocate(n);
        need(s.colors1238.size()>=n);
        // Constructor's byte stores precede the independent bulk clear.
        if(std::bit_cast<std::int32_t>(pixels-1)>=0)for(std::uint32_t i=0;i<pixels;++i)for(unsigned k=0;k<3;++k)write(s.colors1238,'C',i*3+k,1,0);
        map(0x1238,1);zero(s.colors1238,'C',n);
        s.width123C=source[2];map(0x123c,std::uint32_t(s.width123C));s.height1240=source[3];map(0x1240,std::uint32_t(s.height1240));
    }
    if(update){need(bool(services.colors631250));services.colors631250(source,region);}
    //630C47 saves this stride before the surface service/getter calls.
    const auto sourceStride=source[2];
    auto scale=s.scale1484;std::int32_t width,height;
    if(!s.second121C){
        need(source[2]>0&&source[3]>0);
        volatile double ratio=140.0/double(source[2]);volatile float narrowed=float(ratio);scale=narrowed;
        volatile double scaledHeight=double(source[3])*double(scale);volatile float storedHeight=float(scaledHeight);
        if(scaledHeight<108.0){width=140;height=radarProjectionInteger(double(storedHeight));}
        else{volatile double other=108.0/double(source[3]);narrowed=float(other);scale=narrowed;volatile double scaledWidth=double(source[2])*double(scale);width=radarProjectionInteger(scaledWidth);height=108;}
        s.scale1484=scale;map(0x1484,radarProjectionFloatBits(scale));
        need(bool(services.createSecond));s.second121C=services.createSecond(width,height);map(0x121c,1);
        need(s.second121C&&bool(services.clear));services.clear(*s.second121C,0);
    }else{
        need(s.second121C->table&&bool(s.second121C->table->width7C));width=s.second121C->table->width7C(*s.second121C);
        need(s.second121C&&s.second121C->table&&bool(s.second121C->table->height80));height=s.second121C->table->height80(*s.second121C);
    }
    need(width>0&&height>0&&std::isfinite(scale)&&scale>0&&s.width123C>0&&s.height1240>0);
    volatile double rx=double(source[2])/double(width);volatile float stepX=float(rx);
    volatile double ry=double(source[3])/double(height);volatile float stepY=float(ry);
    volatile double area=ry*double(stepX);volatile double inverse=1.0/area;volatile float invArea=float(inverse);
    need(bool(services.lock));auto pixels=services.lock(*s.second121C,0,0);
    const auto mulScale=[&](std::int32_t v){volatile double q=double(v)*double(scale);return radarProjectionInteger(q);};
    const auto x0=mulScale(region[0]);const auto x1=std::min(fillAdd(mulScale(fillAdd(region[0],region[2])),1),width);
    const auto y0=mulScale(region[1]);const auto y1=std::min(fillAdd(mulScale(fillAdd(region[1],region[3])),1),height);
    volatile double initialX=double(x0)/double(scale);volatile float storedX=float(initialX);
    volatile double initialY=double(y0)/double(scale);volatile float storedY=float(initialY);
    need(std::uint64_t(width)*std::uint64_t(height)<=1048576);
    for(auto y=y0;y<y1;++y){
        auto sy=std::min(s.height1240,radarProjectionInteger(double(storedY)));
        volatile double endY=double(storedY)+double(stepY);const auto ey=std::min(s.height1240,fillAdd(radarProjectionInteger(endY),1));
        auto xf=storedX;
        for(auto x=x0;x<x1;++x){
            volatile double red=0,green=0,blue=0;
            const auto sx=std::min(s.width123C,radarProjectionInteger(double(xf)));
            volatile double endX=double(xf)+double(stepX);volatile float storedEndX=float(endX);
            const auto ex=std::min(s.width123C,fillAdd(radarProjectionInteger(endX),1));
            // The supplied inputs must not require invalid original pointer access.
            need(sy>=0&&sx>=0&&ey>=sy&&ex>=sx&&std::uint64_t(ey-sy)*std::uint64_t(ex-sx)<=1048576);
            for(auto yy=sy;yy<ey;++yy){
                volatile double wy;
                if(ey-sy<=1)wy=double(stepY);else if(yy==sy)wy=double(yy+1)-double(storedY);else if(yy==ey-1)wy=endY-double(yy);else wy=1.0;
                for(auto xx=sx;xx<ex;++xx){
                    volatile double wx;
                    if(ex-sx<=1)wx=double(stepX);else if(xx==sx)wx=double(xx+1)-double(xf);else if(xx==ex-1)wx=double(storedEndX)-double(xx);else wx=1.0;
                    volatile double weight=wx*wy;weight=weight*double(invArea);
                    const auto index=std::uint32_t(yy)*std::uint32_t(sourceStride)+std::uint32_t(xx);
                    const auto total=std::uint32_t(s.width123C)*std::uint32_t(s.height1240);
                    if(std::bit_cast<std::int32_t>(index)<std::bit_cast<std::int32_t>(total)){
                        need(std::uint64_t(index)*3+3<=s.colors1238.size());
                        volatile double r=double(s.colors1238[index*3])*weight;red=red+r;
                        volatile double g=double(s.colors1238[index*3+1])*weight;green=green+g;
                        volatile double b=double(s.colors1238[index*3+2])*weight;blue=blue+b;
                    }
                }
            }
            const auto rounded=[](double v){volatile double q=v+.5;return std::min(radarProjectionInteger(q),255);};
            const auto r=rounded(red),g=rounded(green),b=rounded(blue);
            const auto channel=[](std::int32_t v,std::int32_t right,std::int32_t left){
                return std::uint32_t(v>>(std::uint32_t(right)&31))<<(std::uint32_t(left)&31);
            };
            const auto packed=channel(r,s.shifts[1],s.shifts[0])|channel(g,s.shifts[5],s.shifts[4])|channel(b,s.shifts[3],s.shifts[2]);
            write(pixels,'P',(std::uint32_t(y)*std::uint32_t(width)+std::uint32_t(x))*2,2,packed&65535);
            xf=storedEndX;
        }
        storedY=float(endY);
    }
    need(bool(services.unlock));services.unlock(*s.second121C);
    const auto count=std::bit_cast<std::int32_t>(std::uint32_t(width)*std::uint32_t(height));
    const auto bitmapBytes=std::uint32_t(count/8)+1;
    if(s.bitmap1270.empty()){need(bitmapBytes<=16*1024*1024&&bool(services.allocate));s.bitmap1270=services.allocate(bitmapBytes);need(s.bitmap1270.size()>=bitmapBytes);map(0x1270,1);zero(s.bitmap1270,'B',bitmapBytes);}
    out[0]=x0;out[1]=y0;out[2]=fillSub(x1,x0);out[3]=fillSub(y1,y0);return &out;
}
}
