// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/MapLighting.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <bit>
#include <cmath>
namespace ra2 {
namespace {
void bounded(int v,int limit) {
    if(std::abs(std::int64_t(v))>limit)throw std::invalid_argument("Map lighting outside recovered domain");
}
int quantize(double v,int factor) {
    if(!std::isfinite(v)||std::abs(v)>10)throw std::invalid_argument("Nonfinite or unsupported map light setting");
    return int(v*factor);
}
// Explicit low-32-bit multiply and arithmetic shift preserve the executable's
// integer behavior without invoking signed overflow or relying on signed shifts.
int multiply(int a,int b) {return std::bit_cast<std::int32_t>(std::uint32_t(a)*std::uint32_t(b));}
int fixedProduct(int a,int b) {
    const int p=multiply(a,b);return p>=0?p/65536:-int((-std::int64_t(p)+65535)/65536);
}
}
MapLightSettings mapLightSettings(double ambient,std::array<double,3> tint,double ground,double level) {
    OriginalRounding rounding;
    MapLightSettings r;r.ambient=quantize(ambient,100);
    for(int i=0;i<3;++i)r.tint[i]=quantize(tint[i],100);
    r.ground=quantize(ground,1000);r.level=quantize(level,1000);return r;
}
void normalizeLight(int& scale,int& brightness,std::array<int,3>& tint) {
    bounded(brightness,100000);
    for(auto& c:tint){bounded(c,100000);c=std::clamp(c,0,2000);}
    OriginalRounding rounding;scale=65536;
    if(tint!=std::array<int,3>{1000,1000,1000}) {
        // Red wins equal maxima, then green. Red retains its untruncated FP
        // denominator; the other two use the truncated 16.16 scale.
        const int dominant=tint[0]>=tint[1]&&tint[0]>=tint[2]?0:tint[1]>=tint[2]?1:2;
        const double denominator=(double(tint[dominant])*65536.0)*0.001;
        scale=int(denominator);
        if(scale<66){scale=65536;tint={1000,1000,1000};brightness=0;}
        else {
            for(int i=0;i<3;++i)if(i!=dominant)tint[i]=int(double(tint[i])*65536.0/(dominant==0?denominator:double(scale)));
            tint[dominant]=1000;brightness=fixedProduct(scale,brightness);
        }
    }
    brightness=std::min(brightness,2000);
}
CellLight cellLight(const RenderData& data,const MapLightSettings& settings,int x,int y,int elevation,std::span<const LightSource> sources,int detail) {
    bounded(x,1023);bounded(y,1023);if(elevation<0||elevation>31||sources.size()>256)throw std::invalid_argument("Unsupported map light cell");
    bounded(settings.ambient,1000);bounded(settings.ground,10000);bounded(settings.level,10000);
    CellLight r;
    // Original sentinels bypass scenario/source inputs completely.
    if((x==0&&y==0)||(x==-1&&y==-1))return r;
    r.ambient=settings.ambient*10;
    for(int i=0;i<3;++i){bounded(settings.tint[i],1000);r.tint[i]=settings.tint[i]*10;}
    OriginalRounding rounding;
    const int cx=x*256+128,cy=y*256+128;
    for(const auto& s:sources) {
        bounded(s.x,1<<20);bounded(s.y,1<<20);bounded(s.intensity,10000);
        for(int c:s.tint)bounded(c,10000);
        if(s.radius<=0||s.radius>32767)throw std::invalid_argument("Unsupported light source radius");
        if(!s.active||detail<s.minimumDetail)continue;
        const std::int64_t dx=std::int64_t(cx)-s.x,dy=std::int64_t(cy)-s.y;
        const auto distanceSquared=dx*dx+dy*dy;
        // Restrict to non-overflowing original squared-distance inputs.
        if(distanceSquared>2147483647)throw std::invalid_argument("Light distance outside recovered domain");
        if(distanceSquared>std::int64_t(s.radius)*s.radius)continue;
        const int distance=int(tableSqrt(data,double(distanceSquared)));
        if(distance>s.radius)continue;
        const int falloff=(s.radius-distance)*1000/s.radius;
        r.sourceIntensity+=multiply(s.intensity,falloff)/1000;
        for(int i=0;i<3;++i)r.tint[i]+=multiply(s.tint[i],falloff)/1000;
    }
    r.ambient+=r.sourceIntensity;
    r.terrain=std::min(2000,r.ambient+elevation*settings.level-settings.ground);
    r.bridge=r.ambient+(elevation+4)*settings.level-settings.ground;
    r.ambient=r.terrain;
    normalizeLight(r.scale,r.terrain,r.tint);
    r.bridge=std::clamp(fixedProduct(r.bridge,r.scale),0,2000);
    r.ambient=std::clamp(r.ambient,0,2000);r.terrain=std::max(0,r.terrain);
    return r;
}
}
