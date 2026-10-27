// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <stdexcept>
namespace ra2 {
struct BuildingImageSelectionType {
    std::function<const void*()> primary9c,secondaryC0;
};
struct BuildingImageSelectionServices {
    std::function<std::int32_t()> stage42c;
    std::function<std::uint8_t()> flag5b4;
    std::function<BuildingImageSelectionType()> type418;
};
// Complete44C5A0: short-circuit raw fields, late Type, tail child result.
inline const void* buildingImageSelection(const BuildingImageSelectionServices& s){
    if(!s.stage42c||!s.type418)throw std::invalid_argument("Building image selection owner unbound");
    bool primary=false;
    if(s.stage42c()!=0){
        if(!s.flag5b4)throw std::invalid_argument("Building image selection flag unbound");
        primary=s.flag5b4()!=0;
    }
    const auto type=s.type418();const auto& child=primary?type.primary9c:type.secondaryC0;
    if(!child)throw std::invalid_argument("Building image selection child unbound");
    return child();
}
}
