// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/ActorGroundState.hpp"
#include <bit>
#include <optional>
#include <stdexcept>
namespace ra2 {
// Explicit field views. Initial type/Cell associations remain supplied; these
// services neither destroy overlays nor substitute admission/ability answers.
struct GroundDrivePreparationOverlayServices {
    const std::uint8_t& crusher;
    std::function<const int&(const void*)> index;
    std::function<const std::uint8_t&(int)> crushable;
};
struct GroundDriveCrossingOverlay {const int& index264;};
struct GroundDriveCrusherType {
    const std::uint8_t& crusherAf3;
    const std::uint8_t& flagAf4;
};
struct GroundDriveCrushingServices {
    const std::uint8_t& onMap7d;
    const std::uint8_t& curve64;
    std::uint8_t& crushing59f;
    float& velocity28c;
    std::function<std::optional<GroundDriveCrossingOverlay>(const void*)> cell;
    std::function<GroundDriveCrusherType()> type;
    std::function<bool()> ability17;
};
// 4A1A39..4A1AAE, after the crossing's actual second word lookup and Mark(1).
// Keep the retained Cell identity; do not make an extra coordinate/map query.
inline void markGroundDriveCrushing(const void* cell,const GroundDriveCrushingServices& s,
    const GroundStateStore& store){
    if(!s.onMap7d)throw std::invalid_argument("Off-map overlay crossing continuation unjoined");
    if(!cell||!s.cell)throw std::invalid_argument("Overlay crossing requires an actual retained Cell");
    const auto overlay=s.cell(cell);
    if(!overlay||!s.curve64)return;
    if(!s.type)throw std::invalid_argument("Overlay crossing requires actual type fields");
    const auto type=s.type();
    if(!type.crusherAf3){
        if(!s.ability17)throw std::invalid_argument("Overlay crossing requires actual ability17");
        if(!s.ability17())return;
    }
    if(overlay->index264)return;
    s.crushing59f=1;if(store)store(0x59f,1);
    const auto again=s.type();
    if(again.flagAf4){
        s.velocity28c=std::bit_cast<float>(std::uint32_t(0xbca3d70a));
        if(store)store(0x28c,std::bit_cast<std::int32_t>(s.velocity28c));
    }
}
}
