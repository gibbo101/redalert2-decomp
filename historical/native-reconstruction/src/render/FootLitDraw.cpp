// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/FootLitDraw.hpp"
#include "sim/OriginalMath.hpp"
#include <cstring>
namespace ra2 {
void drawFootLit(const FootLitRequest& input,bool hasLocomotor,
                 const std::function<PixelPoint()>& drawOffset,
                 const std::function<void(const FootLitRequest&)>& draw) {
    auto call=input;
    // The original copies 12 dwords, including NaN payloads and signed zero.
    std::memcpy(call.pose.data(),input.pose.data(),sizeof(call.pose));
    if(hasLocomotor) {
        const auto offset=drawOffset();
        call.point={signed32(std::uint32_t(input.point.x)+std::uint32_t(offset.x)),
                    signed32(std::uint32_t(input.point.y)+std::uint32_t(offset.y))};
    }
    draw(call);
}
PixelPoint driveLitDrawOffset(){return {0,0};}
}
