// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/RenderData.hpp"
#include "assets/PreparedData.hpp"
#include <algorithm>
#include <bit>
namespace ra2 {
RenderData readRenderData(const Data& data,std::string_view expectedSource) {
    validatePreparedData(data,69944,"50d2876e6bf8a3b9d535a1843ef93f41109b7021a15e1dbacb47aaa881389c6d",
        "afccee17250dcb5fe08c7da2183d530d22c2380c8c98d253f5f5b1847ba1d032",expectedSource);
    RenderData result;std::size_t p=60;
    for(std::size_t i=0;i<5;++i) for(unsigned j=0;j<data.u32(40+4*i);++j,p+=12)
        result.normals[i].push_back({data.f32(p),data.f32(p+4),data.f32(p+8)});
    result.paletteCoefficient=std::bit_cast<double>(std::uint64_t(data.u32(p))|(std::uint64_t(data.u32(p+4))<<32));
    result.shadeScale=data.f32(p+8);result.lightAngle=data.f32(p+12);
    for(std::size_t i=0;i<result.sqrtMantissas.size();++i)result.sqrtMantissas[i]=data.u32(p+16+4*i);
    return result;
}
VoxelPalette readVpl(const Data& data) {
    const auto first=data.u32(0),last=data.u32(4),count=data.u32(8);
    if(first>last||last>255||count==0||count>256||data.size!=784+count*256)
        throw std::runtime_error("Invalid VPL extent or header");
    VoxelPalette result;result.remapStart=first;result.remapEnd=last;
    // The VPL embeds eight-bit RGB, unlike the game's six-bit .pal files.
    for(unsigned i=0;i<256;++i)result.palette[i]={data.u8(16+3*i),data.u8(17+3*i),data.u8(18+3*i),std::uint8_t(i?255:0)};
    result.sections.resize(count);
    for(unsigned s=0;s<count;++s)std::copy_n(data.ptr(784+256*s,256),256,result.sections[s].begin());
    return result;
}
std::uint8_t VoxelPalette::lookup(std::uint8_t color,std::uint8_t shade) const {
    if(shade>=sections.size())throw std::runtime_error("Voxel shade outside supplied VPL");
    return sections[shade][color];
}
}
