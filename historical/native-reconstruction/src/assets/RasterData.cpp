// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/RasterData.hpp"
#include "assets/PreparedData.hpp"
namespace ra2 {
RasterData readRasterData(const Data& data,std::string_view expectedSource) {
    validatePreparedData(data,41312,"f357f3b4d7b048b7f65d7a43f4f96a41e6c21b5974bb1340d7fd98e92abcd8a3",
        "0feb5f4985519e5432ed5d464a8d1e3e5877e8e3cabe3d71bd7f9f3c7c9d435b",expectedSource);
    RasterData result;std::size_t p=40;
    for(auto& row:result.traversal)for(auto& v:row){v=data.i32(p);p+=4;}
    for(auto& v:result.sine){v=data.f32(p);p+=4;}
    result.sineScale=data.f32(p);result.cosineScale=data.f32(p+4);p+=8;
    auto number=[&](std::size_t at){return std::bit_cast<double>(std::uint64_t(data.u32(at))|(std::uint64_t(data.u32(at+4))<<32));};
    result.headingStep=number(p);result.degrees=number(p+8);return result;
}
}
