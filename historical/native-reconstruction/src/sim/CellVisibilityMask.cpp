// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/CellVisibilityMask.hpp"
#include "sim/Facing.hpp"
#include <array>
#include <stdexcept>

namespace ra2 {
namespace {
std::int16_t word(std::uint32_t value){return signed16(std::uint16_t(value));}
CellVisibilityMaskCell& lookup(TerrainCellPoint point,
        const CellVisibilityMaskWorld& world) {
    if(world.cells.size()!=262144||!world.fallback)
        throw std::invalid_argument("Cell visibility mask requires complete map");
    const auto index=signed32(std::uint32_t(std::int32_t(point.y))*512u+
        std::uint32_t(std::int32_t(point.x)));
    CellVisibilityMaskCell* cell=nullptr;
    if(index>=0&&index<262144)cell=world.cells[std::size_t(index)];
    if(!cell){world.fallback->point=point;if(world.fallbackStore)world.fallbackStore(point);cell=world.fallback;}
    if(world.query)world.query(point,cell->identity);
    return *cell;
}
TerrainCellPoint offset(TerrainCellPoint point,std::int16_t x,std::int16_t y){
    return {word(std::uint32_t(std::uint16_t(point.x))+std::uint32_t(std::uint16_t(x))),
            word(std::uint32_t(std::uint16_t(point.y))+std::uint32_t(std::uint16_t(y)))};
}
}
std::int32_t cellVisibilityMask(TerrainCellPoint point,bool mode,
        std::span<const std::int8_t> results,const CellVisibilityMaskWorld& world) {
    if(results.size()!=256)
        throw std::invalid_argument("Cell visibility mask requires 256 result entries");
    const auto& center=lookup(point,world);
    const auto flags=mode?center.flags140:center.flags12c;
    const std::uint8_t admitted=mode?2u:8u;
    const std::uint8_t initial=mode?3u:0x18u;
    std::int32_t unavailable=-1;
    if(!(std::uint8_t(flags)&initial))unavailable=-2;
    if(!(std::uint8_t(flags)&admitted))return unavailable;
    constexpr std::array<std::array<std::int16_t,2>,8> offsets{{
        {{-1,-1}},{{0,-1}},{{1,-1}},{{-1,0}},{{1,0}},{{-1,1}},{{0,1}},{{1,1}}
    }};
    constexpr std::array<std::uint8_t,8> bits{{0x40,0x80,0x01,0x20,0x02,0x10,0x08,0x04}};
    std::uint8_t mask=0;
    for(std::size_t i=0;i<offsets.size();++i){
        const auto& cell=lookup(offset(point,offsets[i][0],offsets[i][1]),world);
        const auto neighborFlags=mode?cell.flags140:cell.flags12c;
        if(!(std::uint8_t(neighborFlags)&admitted))mask|=bits[i];
    }
    return results[mask];
}
}
