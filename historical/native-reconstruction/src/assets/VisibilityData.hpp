// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Bytes.hpp"
#include <array>
#include <cstdint>
#include <string_view>

namespace ra2 {
struct VisibilityData {std::array<std::int8_t,256> maskResults{};};
VisibilityData readVisibilityData(const Data&,std::string_view expectedSource={});
}
