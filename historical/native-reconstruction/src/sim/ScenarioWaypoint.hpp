// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
#include <array>
#include <span>
#include <stdexcept>
namespace ra2 {
// Complete base663180: unaligned packed dword at scenario+632+index*4,
// wrapping32-bit indexing, read before the output store, return output identity.
// Host spans bound supplied records; unsupported/faulting addresses refuse.
inline std::uint8_t* copyScenarioWaypoint(std::span<const std::uint8_t> scenario,
        std::int32_t index,std::span<std::uint8_t> output){
    const auto offset=std::uint32_t(0x632u+std::uint32_t(index)*4u);
    if(output.size()<4||std::uint64_t(offset)+4>scenario.size())
        throw std::invalid_argument("Scenario waypoint address outside supplied records");
    const auto value=std::uint32_t(scenario[offset])|(std::uint32_t(scenario[offset+1])<<8)|
        (std::uint32_t(scenario[offset+2])<<16)|(std::uint32_t(scenario[offset+3])<<24);
    for(unsigned i=0;i<4;++i)output[i]=std::uint8_t(value>>(8*i));
    return output.data();
}
inline TerrainCellPoint scenarioWaypoint(std::span<const std::uint8_t> scenario,std::int32_t index){
    std::array<std::uint8_t,4> out{};copyScenarioWaypoint(scenario,index,out);
    return {std::int16_t(signed16(std::uint16_t(out[0]|(unsigned(out[1])<<8)))),
        std::int16_t(signed16(std::uint16_t(out[2]|(unsigned(out[3])<<8))))};
}
}
