// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <bit>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace ra2 {
using Bytes = std::vector<std::uint8_t>;
struct Data {
    std::shared_ptr<const Bytes> storage;
    std::size_t offset = 0, size = 0;
    Data() = default;
    explicit Data(Bytes b) : storage(std::make_shared<Bytes>(std::move(b))), size(storage->size()) {}
    void check(std::size_t p, std::size_t n) const {
        if (!storage || p > size || n > size - p) throw std::runtime_error("Truncated or invalid asset range");
    }
    const std::uint8_t* ptr(std::size_t p=0, std::size_t n=0) const { check(p,n); return storage->data()+offset+p; }
    Data slice(std::size_t p, std::size_t n) const { check(p,n); Data d=*this; d.offset+=p;d.size=n;return d; }
    std::uint8_t u8(std::size_t p) const { return *ptr(p,1); }
    std::uint16_t u16(std::size_t p) const { const auto* b=ptr(p,2);return std::uint16_t(b[0] | b[1]<<8); }
    std::uint32_t u32(std::size_t p) const { const auto* b=ptr(p,4);return std::uint32_t(b[0]) | std::uint32_t(b[1])<<8 | std::uint32_t(b[2])<<16 | std::uint32_t(b[3])<<24; }
    std::int32_t i32(std::size_t p) const { return std::bit_cast<std::int32_t>(u32(p)); }
    float f32(std::size_t p) const { return std::bit_cast<float>(u32(p)); }
    std::string text() const { return std::string(reinterpret_cast<const char*>(ptr()),size); }
    std::string name(std::size_t p,std::size_t n) const {
        check(p,n);std::size_t l=0;while(l<n && u8(p+l)) ++l;
        return std::string(reinterpret_cast<const char*>(ptr(p,n)),l);
    }
};
Data readFile(const std::filesystem::path& path);
std::string lower(std::string s);
}
