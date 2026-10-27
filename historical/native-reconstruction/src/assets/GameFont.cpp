// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/GameFont.hpp"
#include <bit>
namespace ra2 {
GameFont::GameFont(const Data& file,std::uint8_t suppliedHeapFill){
    // Base431150's ordinary fonT branch. FoNt range-table conversion is a
    // separate original branch and explicitly remains unsupported here.
    if(file.u32(0)!=0x546e6f66)throw std::invalid_argument("Only original fonT font records are recovered");
    file.check(0,28+131072);
    for(unsigned i=0;i<6;++i)fields_[i]=file.u32(4+i*4);
    indices_.reserve(65536);
    for(unsigned i=0;i<65536;++i){const auto index=file.u16(28+i*2);indices_.push_back(index);indexed_+=index!=0;}
    const auto bytes=fields_[4]*fields_[5]; // Original dword product before allocation/read.
    if(bytes>64*1024*1024)throw std::invalid_argument("Font glyph allocation outside bounded owner");
    glyphData_=file.slice(28+131072,bytes); // Original ignores trailing file content.
    for(const auto index:indices_)if(index&&std::uint64_t(fields_[5])*(index-1)>=glyphData_.size)
        throw std::invalid_argument("Font index outside bounded glyph owner");
    // Base431EC0: retain supplied allocator bytes wherever the routine does not
    // write, including the final byte even when X exists. No synthetic zeroing.
    const auto pixels=std::uint64_t(fields_[1])*fields_[2];
    const auto allocated=std::uint32_t(fields_[1]*fields_[2]+2);
    if(allocated>64*1024*1024||pixels+2!=allocated)throw std::invalid_argument("Font fallback allocation outside bounded owner");
    fallback_.assign(allocated,suppliedHeapFill);
    const auto x=indices_[0x58];
    if(x){
        const auto offset=fields_[5]*(std::uint32_t(x)-1);
        glyphData_.check(offset,std::size_t(pixels)+1);
        fallback_[0]=glyphData_.u8(offset);
        for(std::uint64_t i=0;i<pixels;++i)fallback_[std::size_t(i)+1]=std::uint8_t(~glyphData_.u8(std::size_t(offset)+1+std::size_t(i)));
    }
    // Logical nonzero data base; this is an immutable byte association, not a
    // guest pointer or executable mapping. Stable ownership binds callbacks.
    glyphs_={indices_,fields_[5],1,[this](std::uint32_t address){
        if(!address)throw std::invalid_argument("Font glyph null logical address");return glyphData_.u8(address-1);
    }};
    metrics_={&glyphs_,fallback_.data(),std::bit_cast<std::int32_t>(fields_[3]),64,1};
}
}
