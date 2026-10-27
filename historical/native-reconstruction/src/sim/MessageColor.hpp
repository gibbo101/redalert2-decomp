// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <array>
#include <cstdint>
namespace ra2 {
using MessageColorTable=std::array<std::int8_t,9>;
// Complete base6715D0. The unsigned test keeps all negative selectors except
// -2 unchanged; selected bytes are sign-extended, never clamped to a color enum.
inline std::int32_t messageColor(std::int32_t selector,const MessageColorTable& table){
    if(selector==-2)selector=8;
    return std::uint32_t(selector)<table.size()?std::int32_t(table[std::uint32_t(selector)]):selector;
}
}
