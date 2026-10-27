// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/BuildingCoordinates.hpp"
#include <stdexcept>
#include <bit>
namespace ra2 {
Coord buildingRenderCoordinates(Coord p){
    p.x=std::bit_cast<std::int32_t>(std::uint32_t(p.x)-128u);
    p.y=std::bit_cast<std::int32_t>(std::uint32_t(p.y)-128u);
    return p;
}
std::int32_t buildingFoundationWidth(std::int32_t index,std::span<const std::int32_t> table){
    if(index<0||std::size_t(index)>=table.size())throw std::invalid_argument("Building foundation index outside supplied table");
    return table[std::size_t(index)];
}
std::int32_t buildingFoundationHeight(std::int32_t index,std::uint8_t extra,std::uint8_t include,std::span<const std::int32_t> table){
    const auto height=buildingFoundationWidth(index,table);
    return signed32(std::uint32_t(height)+std::uint32_t(include&&extra));
}
Coord buildingCoordinates(const BuildingCoordinateServices& s){
    if(!s.height||!s.width||!s.position88)throw std::invalid_argument("Building coordinates need actual type and position owners");
    const auto height=s.height(0);
    const auto y=(std::uint32_t(height)<<7)-128u;
    const auto width=s.width();
    const auto x=(std::uint32_t(width)<<7)-128u;
    const auto p=s.position88();
    return {signed32(std::uint32_t(p.x)+x),signed32(std::uint32_t(p.y)+y),p.z};
}
}
