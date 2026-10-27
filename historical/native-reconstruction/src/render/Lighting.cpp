// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/Lighting.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <bit>
#include <cmath>
#include <stdexcept>
namespace ra2 {
double tableSqrt(const RenderData& data,double value) {
    // Base helper 0x4B9F30: float32 store, exponent parity and a 14-bit table bin.
    if(value==0)return 0;
    const auto bits=std::bit_cast<std::uint32_t>(float(value));
    const int exponent=int(bits>>23)-127;
    const auto index=((bits&0x7fffff)|((exponent&1)?0x800000:0))>>10;
    const auto result=data.sqrtMantissas[index]+(std::uint32_t((exponent>>1)+127)<<23);
    return std::bit_cast<float>(result);
}
std::array<std::uint8_t,256> voxelShades(const RenderData& data,int type,Vec3 light,Vec3 view,float intensity,bool single) {
    if(type<1||type>4||data.normals[type].empty())throw std::invalid_argument("Unsupported VXL normal encoding");
    for(float v:{light.x,light.y,light.z,view.x,view.y,view.z})
        if(!std::isfinite(v)||std::abs(v)>2)throw std::invalid_argument("Lighting vector outside recovered domain");
    if(!std::isfinite(intensity)||intensity<1||intensity>8)throw std::invalid_argument("Lighting intensity outside recovered domain");
    OriginalRounding rounding;
    std::array<std::uint8_t,256> result;result.fill(16);
    Vec3 half{};
    if(!single) {
        half.x=float(double(light.x)+view.x);half.y=float(double(light.y)+view.y);
        const double z=double(light.z)+view.z;half.z=float(z);
        const double length=tableSqrt(data,(z*half.z+double(half.x)*half.x)+double(half.y)*half.y);
        if(length!=0)half={float(half.x/length),float(half.y/length),float(half.z/length)};
    }
    for(std::size_t i=0;i<data.normals[type].size();++i) {
        const auto n=data.normals[type][i];double value=0;
        if(single)value=(double(n.x)*light.x+double(n.z)*light.z)+double(n.y)*light.y;
        else {
            const double diffuse=(double(n.z)*light.z+double(n.y)*light.y)+double(n.x)*light.x;
            const double h=(double(half.x)*n.x+double(half.y)*n.y)+double(half.z)*n.z;
            const float specular=float(h/((double(intensity)-h*intensity)+h));
            value=std::max(0.0,diffuse)+std::max(0.0f,specular);
        }
        result[i]=value<0?0:std::uint8_t(int(value*data.shadeScale)&255);
    }
    // Original routines always override these three special normal slots.
    result[253]=result[254]=result[255]=16;return result;
}
std::vector<Palette16> lightPalette(const RenderData& data,const Palette& palette,std::array<int,3> tint,int shades,const std::array<std::uint8_t,256>& affected) {
    if(shades<1||shades>256)throw std::invalid_argument("Palette shade count outside bounded domain");
    OriginalRounding rounding;
    std::array<int,3> factor{};
    for(int i=0;i<3;++i)factor[i]=int(double(std::clamp(tint[i],0,2000)*1000)*data.paletteCoefficient);
    const int neutralSteps=std::min(std::max(0,shades*30/200-1),(shades-1)/2);
    if(shades>1&&neutralSteps==0)throw std::invalid_argument("Unsupported original palette shade count");
    std::vector<Palette16> result(shades);
    for(int shade=0;shade<shades;++shade) {
        std::array<int,3> scale=factor;
        if(shades>1)for(int i=0;i<3;++i)scale[i]=factor[i]*2*shade/(shades-1);
        const int neutral=shades==1||shade>neutralSteps?65536:shade*65536/neutralSteps;
        for(int index=1;index<256;++index) {
            const auto c=palette[index];const int rgb[3]={c.r,c.g,c.b};int channels[3];
            for(int i=0;i<3;++i)channels[i]=std::min(255,(rgb[i]*(affected[index]?scale[i]:neutral))>>16);
            result[shade][index]=std::uint16_t(((channels[0]>>3)<<11)|((channels[1]>>2)<<5)|(channels[2]>>3));
        }
    }
    return result;
}
std::uint32_t expand565(std::uint16_t c) {
    // Host display adapter: replicate bits to expand the original RGB565 channels.
    unsigned r=(c>>11)&31,g=(c>>5)&63,b=c&31;
    return 0xff000000u|(((r<<3)|(r>>2))<<16)|(((g<<2)|(g>>4))<<8)|((b<<3)|(b>>2));
}
void depthPixel(std::uint8_t index,int candidate,std::uint16_t color,std::uint16_t& destination,std::uint16_t& depth) {
    if(index&&candidate<int(depth)) {destination=color;depth=std::uint16_t(candidate);}
}
void depthSpan(std::span<const std::uint8_t> source,int candidate,const Palette16& palette,std::span<std::uint16_t> destination,std::span<std::uint16_t> depth,std::size_t start) {
    if(destination.size()<source.size()||depth.empty()||start>=depth.size())throw std::invalid_argument("Invalid depth span extent");
    for(std::size_t i=0;i<source.size();++i) {depthPixel(source[i],candidate,palette[source[i]],destination[i],depth[start]);if(++start==depth.size())start=0;}
}
}
