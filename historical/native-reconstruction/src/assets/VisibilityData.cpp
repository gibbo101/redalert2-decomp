// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/VisibilityData.hpp"
#include "assets/PreparedData.hpp"
#include <bit>
#include <stdexcept>

namespace ra2 {
VisibilityData readVisibilityData(const Data& data,std::string_view expectedSource){
    validatePreparedData(data,296,"","13b168f8b583febb048b4144aaff207398503bb9470cf89a17693b389abdabb8",expectedSource);
    constexpr std::array<std::uint8_t,8> header{'R','A','2','V','I','S','1',0};
    for(std::size_t i=0;i<header.size();++i)if(data.u8(i)!=header[i])throw std::runtime_error("Invalid visibility data header");
    VisibilityData out;
    for(std::size_t i=0;i<out.maskResults.size();++i)out.maskResults[i]=std::bit_cast<std::int8_t>(data.u8(40+i));
    return out;
}
}
