// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <span>
#include <stdexcept>
namespace ra2 {
struct IniBufferedInput {
    const void*& source4;
    std::span<std::uint8_t>& bufferC;
    std::int32_t& size10;
    std::int32_t& cursor18;
    std::int32_t& available1C;
};
struct IniInputServices {
    // Actual upstream byte source remains a supplied platform/file boundary.
    std::function<std::int32_t(const void*,std::span<std::uint8_t>,std::int32_t)> sourceRead;
    std::function<void(std::span<std::uint8_t>,std::span<const std::uint8_t>)> copy;
    std::function<void(std::int64_t,std::int32_t)> store;
};
// Complete69B0A0 and494760 over one shared pipe/buffer owner.
std::int32_t readIniSource(const void*,std::span<std::uint8_t>,std::int32_t,const IniInputServices&);
std::int32_t readBufferedIniInput(IniBufferedInput&,std::span<std::uint8_t>,std::int32_t,const IniInputServices&);
struct IniLineServices {
    std::function<std::int32_t(std::uint8_t&)> readByte;
    // false=destination byte, true=EOF byte; writes have already occurred.
    std::function<void(bool,std::size_t,std::uint8_t)> store;
};
// Complete639670. Consumes a whole line even when storage fills, drops CR,
// preserves embedded NUL bytes and EOF's existing raw byte until a failed read.
std::int32_t readIniInputLine(std::span<std::uint8_t>,std::int32_t,std::uint8_t*,const IniLineServices&);
}
