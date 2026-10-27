// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
namespace ra2 {
// Logical House identity plus the recovered signed index30/alliance5674 fields.
// Legacy reveal names are retained at this boundary; countryIndex is the House
// index consumed by4E5540, not HouseType countryB8 or a country registry ordinal.
struct HouseIndexAlliance {
    int identity=0,countryIndex=0;
    std::uint32_t allianceMask=0;
};
}
