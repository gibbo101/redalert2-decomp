// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Formats.hpp"
#include <array>
#include <functional>
#include <optional>
#include <span>
#include <string_view>
namespace ra2 {
// Decoded-entry ReadString boundary, not INI text/index construction.
// Source/destination aliasing is outside this immutable-input interface.
std::size_t readIniStringBuffer(std::span<std::uint8_t> output,int capacity,
    std::optional<std::string_view> value,std::optional<std::string_view> fallback,
    bool validNames=true);
using ModelImageName=std::array<std::uint8_t,25>;
struct UnitModelInputs {ModelImageName image{};int turretCount=0,turretOffset=0;};
UnitModelInputs initializeUnitModelInputs(const ModelImageName& typeId);
struct UnitModelInputServices {
    std::function<void(std::string_view,const ModelImageName&,ModelImageName&)> image;
    std::function<int(std::string_view,std::string_view,int)> rulesInteger,artInteger;
};
UnitModelInputs updateUnitModelInputs(UnitModelInputs,const std::string& typeId,
                                     const UnitModelInputServices&);
// Existing native INI text/integer parsing remains a host boundary.
UnitModelInputs readUnitModelInputs(const Ini& rules,const Ini& art,const std::string& typeId);
std::string modelImageString(const ModelImageName&);
void requireOrdinaryRhinoModelInputs(const UnitModelInputs&);
}
