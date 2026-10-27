// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/OwnedMessagePresentation.hpp"
#include "render/Lighting.hpp"
namespace ra2 {
struct MessageFrameResult {bool expired=false;std::size_t glyphStores=0,fillStores=0,pixelStores=0;};
// Explicit host frame policy: sample a supplied uint32 millisecond clock, expire,
// then draw ordinary messages. Original full-frame scheduling is not recovered.
// Forward actual raster stores only; untouched ARGB terrain is never quantized.
// Cursor/IME and non-RGB565 display formats remain outside this presentation.
inline MessageFrameResult composeMessageFrame(OwnedMessagePresentation& owner,
        std::span<std::uint32_t> frame,std::int32_t width,std::int32_t height,
        std::uint32_t milliseconds){
    const auto& c=owner.config();
    if(width!=c.surfaceWidth||height!=c.surfaceHeight||width<=0||height<=0||
       std::uint64_t(width)*std::uint64_t(height)!=frame.size()||
       c.fillPolicy!=MessageFillPolicy::softwareDisplay||
       c.packing.shifts!=std::array<std::uint32_t,6>{11,3,0,3,5,2}||owner.globals().focused[2])
        throw std::invalid_argument("Message frame requires ordinary unfocused RGB565 software presentation");
    MessageFrameResult result;
    owner.setMilliseconds(milliseconds);result.expired=owner.expire();
    const auto store=[&](std::size_t index,std::uint16_t color){
        if(index>=frame.size())throw std::invalid_argument("Message frame raster store outside target");
        frame[index]=expand565(color);++result.pixelStores;
    };
    owner.draw([&](char kind,std::uint32_t index,std::uint32_t value){
        if(kind=='W'){store(index,std::uint16_t(value));++result.glyphStores;}
    },[&](std::uint32_t offset,unsigned bytes,std::uint32_t){
        if((offset&1)||(bytes!=2&&bytes!=4))throw std::invalid_argument("Unexpected message word store");
        for(unsigned i=0;i<bytes/2;++i){const auto index=std::size_t(offset/2)+i;
            if(index>=owner.pixels().size())throw std::invalid_argument("Message canvas store outside owner");
            store(index,owner.pixels()[index]);}
        ++result.fillStores;
    });
    return result;
}
}
