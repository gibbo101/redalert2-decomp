// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Formats.hpp"
namespace ra2 {
inline constexpr int InitialUnitFireAngle=8;
// Exact field/default association; INI text and present integer parsing remain
// the existing native host reader. This is not a complete type constructor.
inline int readUnitFireAngle(const Ini& rules,const std::string& id,int fallback=InitialUnitFireAngle) {
    return rules.integer(id,"FireAngle",fallback);
}
}
