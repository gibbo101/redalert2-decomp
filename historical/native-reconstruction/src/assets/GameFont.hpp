// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Bytes.hpp"
#include "sim/MessageFontMetrics.hpp"
#include <array>
namespace ra2 {
// Owned stock fonT records. File/heap APIs and native allocation fill are host
// adapters; original header/index/glyph/fallback semantics are recovered.
class GameFont {
    std::array<std::uint32_t,6> fields_{};
    std::vector<std::uint16_t> indices_;
    Data glyphData_;
    std::uint32_t indexed_=0;
    Bytes fallback_;
    MessageFontGlyphs glyphs_;
    MessageFontMetrics metrics_;
public:
    explicit GameFont(const Data&,std::uint8_t suppliedHeapFill=0xa5);
    GameFont(const GameFont&)=delete;
    GameFont& operator=(const GameFont&)=delete;
    const auto& fields()const{return fields_;}
    std::uint32_t indexed()const{return indexed_;}
    std::span<const std::uint16_t> indices()const{return indices_;}
    const Data& glyphData()const{return glyphData_;}
    const Bytes& fallback()const{return fallback_;}
    const MessageFontMetrics& metrics()const{return metrics_;}
};
}
