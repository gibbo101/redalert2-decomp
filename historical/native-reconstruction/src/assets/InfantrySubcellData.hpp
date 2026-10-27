// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Bytes.hpp"
#include "sim/InfantrySubcell.hpp"
#include <string_view>
namespace ra2 {
InfantrySubcellData readInfantrySubcellData(const Data&,std::string_view expectedSource={});
}
