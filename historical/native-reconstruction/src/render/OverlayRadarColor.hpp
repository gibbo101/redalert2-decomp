// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/OverlayTypeInputs.hpp"
#include "render/RadarTerrain.hpp"

namespace ra2 {
struct OverlayRadarColorServices {
    std::function<const Data*()> primaryImage;
    std::function<const Data*(std::uint32_t)> animationImage;
    std::function<void(unsigned,unsigned,std::uint32_t)> store;
};
// Complete5DD000, borrowing the existing type/index/CellAnim owner. Image
// virtuals remain explicit services, including any loading or late type changes.
inline void overlayRadarColor(const OverlayTypeInputs& type,std::uint32_t frame,
        RadarRGB& output,const OverlayRadarColorServices& services){
    if(!services.primaryImage)throw std::invalid_argument("Overlay primary image query unbound");
    const Data* image=services.primaryImage();
    if(!image&&type.cellAnim){
        if(!services.animationImage)throw std::invalid_argument("Overlay animation image query unbound");
        image=services.animationImage(type.cellAnim);
    }
    RadarRGB color{};
    if(image){
        const auto count=std::int32_t(std::bit_cast<std::int16_t>(image->u16(6)));
        // The signed16 count is compared with the full unsigned32 argument.
        if(frame<std::uint32_t(count)){
            const auto at=std::uint32_t(frame*24u+20u);
            if(std::uint64_t(at)+3>image->size)throw std::invalid_argument("Overlay frame outside image");
            color={image->u8(std::size_t(at)),image->u8(std::size_t(at+1)),image->u8(std::size_t(at+2))};
            const auto index=type.index; // Read after both possible virtual calls.
            if((index>=127&&index<=138)||(index>=147&&index<=158))std::swap(color[1],color[2]);
        }
    }
    output[0]=color[0];output[1]=color[1];
    if(services.store)services.store(0,2,std::uint32_t(color[0])|(std::uint32_t(color[1])<<8));
    output[2]=color[2];if(services.store)services.store(2,1,color[2]);
}
}
