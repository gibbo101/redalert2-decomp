// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Formats.hpp"
#include "render/Composition.hpp"
#include <functional>
namespace ra2 {
// Portable values/opaque model and cache identities at the complete Foot lit
// wrapper boundary. Callbacks are read-only services, not original ownership.
struct FootLitRequest {
    std::uint32_t model=0,cache=0;
    int frame=0,key=-1;
    PixelRect clip{};
    PixelPoint point{};
    Matrix pose{};
    int brightness=0;
    std::uint32_t flags=0;
};
void drawFootLit(const FootLitRequest&,bool hasLocomotor,
                 const std::function<PixelPoint()>& drawOffset,
                 const std::function<void(const FootLitRequest&)>& draw);
// Actual ordinary Drive interface +0x2C returns a zero point.
PixelPoint driveLitDrawOffset();
}
