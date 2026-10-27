// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TileImagePreparation.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <bit>
namespace ra2 {
namespace {
using RGB=std::array<std::uint8_t,3>;
std::uint8_t channel(double n){return std::uint8_t(int(std::clamp(n,0.0,255.0)));}
RGB brighten(RGB color){
    // Original binary32 1.4, followed by per-channel truncation/clamping.
    constexpr auto scale=std::bit_cast<float>(0x3fb33333u);
    for(auto& c:color)c=channel(double(c)*double(scale));return color;
}
std::uint16_t pack(RGB c,TileColorPacking p){
    const auto shifted=[](std::uint8_t c,unsigned right,unsigned left){return (std::uint32_t(c)>>(right&31))<<(left&31);};
    return std::uint16_t(shifted(c[0],p.redRight,p.redLeft)|shifted(c[1],p.greenRight,p.greenLeft)|shifted(c[2],p.blueRight,p.blueLeft));
}
TileColorRamp ramp(RGB first,RGB second,TileColorPacking packing){
    const auto brightFirst=brighten(first),brightSecond=brighten(second);TileColorRamp result{};
    for(int i=0;i<=12;++i){
        // Original binary64 1/12 product has a required binary32 store.
        const volatile float stored=float(double(i)*0.08333333333333333);
        const double t=stored;
        const auto interpolate=[&](RGB a,RGB b){
            RGB out{};for(unsigned c=0;c<3;++c)out[c]=channel(double(b[c])*t+double(a[c])*(1.0-t));return out;
        };
        result[std::size_t(i)*2]=pack(interpolate(first,brightFirst),packing);
        result[std::size_t(i)*2+1]=pack(interpolate(second,brightSecond),packing);
    }
    return result;
}
}
PreparedTileImage prepareTileImage(const Data& data,TileColorPacking packing){
    data.check(0,16);const int columns=data.i32(0),rows=data.i32(4);
    if(columns<0||rows<0||columns>255||rows>255||std::int64_t(columns)*rows>16384)
        throw std::invalid_argument("Unsupported prepared TMP dimensions");
    const auto count=std::size_t(columns)*std::size_t(rows);data.check(16,count*4);
    PreparedTileImage result;result.typeColumns=data.u8(0);result.typeRows=data.u8(4);
    result.image.columns=columns;result.image.rows=rows;result.image.width=data.i32(8);result.image.height=data.i32(12);
    result.subTileOffsets.reserve(count);result.image.subTiles.reserve(count);result.colorRamps.reserve(count);
    OriginalRounding rounding;
    for(std::size_t i=0;i<count;++i){
        const auto offset=data.u32(16+i*4);result.subTileOffsets.push_back(offset);
        if(!offset){result.image.subTiles.emplace_back();result.colorRamps.emplace_back();continue;}
        if(offset<16+count*4)throw std::invalid_argument("TMP sub-tile overlaps reference table");
        data.check(offset,52);
        MapSubTileInput sub;sub.land=data.u8(offset+0x29);sub.ramp=data.u8(offset+0x2a);
        sub.extra=(data.u32(offset+0x24)&1)!=0;sub.y=data.i32(offset+4);sub.extraY=data.i32(offset+0x18);
        result.image.subTiles.emplace_back(sub);
        result.colorRamps.emplace_back(ramp({data.u8(offset+0x2b),data.u8(offset+0x2c),data.u8(offset+0x2d)},
            {data.u8(offset+0x2e),data.u8(offset+0x2f),data.u8(offset+0x30)},packing));
    }
    return result;
}
}
