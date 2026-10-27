// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Formats.hpp"
#include <functional>
#include <string_view>

namespace ra2 {
// Selected base-engine fields, not a complete UnitType constructor or INI parser.
struct UnitDrawMetadata {
    int zFudgeCliff=10,zFudgeColumn=5,zFudgeTunnel=10,zFudgeBridge=0;
    std::uint8_t tooBigToFitUnderBridge=0;
};
struct UnitDrawMetadataServices {
    std::function<int(std::string_view,int)> integer;
    std::function<std::uint8_t(std::string_view,std::uint8_t)> boolean;
};
UnitDrawMetadata updateUnitDrawMetadata(UnitDrawMetadata,const UnitDrawMetadataServices&);
// Uses the existing native text/integer parser. Original GetInt parsing is open.
UnitDrawMetadata readUnitDrawMetadata(const Ini& rules,const std::string& type,
                                     UnitDrawMetadata defaults={});
}
