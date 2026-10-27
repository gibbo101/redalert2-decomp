// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MessageFontMetrics.hpp"
#include <array>
namespace ra2 {
using FontRect=std::array<std::int32_t,4>; // Inclusive left/top/right/bottom.
// Complete432000. Keep the sequential reads/stores: output may alias either input.
inline bool intersectFontRect(FontRect& out,const FontRect& a,const FontRect& b){
    if(a[1]>b[3]||b[1]>a[3]||a[0]>b[2]||b[0]>a[2]){out[0]=0;out[1]=0;out[2]=-1;out[3]=-1;return false;}
    out[0]=a[0];out[1]=a[1];out[2]=a[2];out[3]=a[3];
    if(out[1]<b[1])out[1]=b[1];if(out[0]<b[0])out[0]=b[0];
    if(out[3]>b[3])out[3]=b[3];if(out[2]>b[2])out[2]=b[2];return true;
}
struct FontGlyphState {
    const MessageFontGlyphs* primary=nullptr;
    std::span<const std::uint8_t> fallback;
    std::span<std::uint16_t> surface;
    std::int32_t rows=0,pitch=0,rowBytes=0,origin=0,tab=64,spacing=1,lineHeight=0;
    std::uint16_t color=0;
    FontRect clip{};
    bool clipping=false;
};
// Complete4318E0 over borrowed records. The trace observes index, glyph/fallback
// byte reads and ordered pixel stores. Bounds/work refusals are host safeguards,
// not original validation. A refusal can retain earlier writes; no rollback.
using FontGlyphTrace=std::function<void(char,std::uint32_t,std::uint32_t)>;
inline std::int32_t drawFontGlyph(const FontGlyphState& f,std::uint32_t code,
        std::int32_t x,std::int32_t y,std::int32_t overrideColor=-1,const FontGlyphTrace& trace={}){
    if(std::uint16_t(code)==9){
        const auto next=messageFontAdd(x,f.tab),relative=messageFontSub(next,f.origin);
        if(!f.tab||(relative==INT32_MIN&&f.tab==-1))throw std::invalid_argument("Font glyph original tab division faults");
        return messageFontSub(next,relative%f.tab);
    }
    auto color=overrideColor==-1?f.color:std::uint16_t(overrideColor);
    std::uint32_t address=0;
    if(f.primary){
        const auto c=std::uint16_t(code);if(c>=f.primary->indices.size())throw std::invalid_argument("Font glyph index outside owner");
        const auto index=f.primary->indices[c];if(trace)trace('I',c,index);
        if(index)address=f.primary->base+f.primary->stride*(std::uint32_t(index)-1);
    }
    const bool fallback=!address;
    if(fallback){color^=0x5555;if(f.fallback.empty())return x;}
    if(f.surface.empty())return x;
    // Original dereferences primary+8 even after fallback selection.
    if(!f.primary)throw std::invalid_argument("Font glyph missing primary row owner");
    auto read=[&](std::uint32_t offset){
        std::uint8_t value;
        if(fallback){if(offset>=f.fallback.size())throw std::invalid_argument("Font fallback byte outside owner");value=f.fallback[offset];}
        else {if(!f.primary->byte)throw std::invalid_argument("Font glyph bytes required");value=f.primary->byte(address+offset);}
        if(trace)trace(fallback?'F':'G',fallback?offset:address+offset,value);return value;
    };
    auto rows=f.rows;
    const auto width=read(0);
    const auto advance=[&]{return messageFontAdd(x,messageFontAdd(width,f.spacing));};
    std::int32_t firstRow=0;FontRect intersection{};bool partial=false;
    if(f.clipping){
        const FontRect glyph={x,y,messageFontAdd(x,std::int32_t(width)-1),messageFontAdd(y,messageFontSub(rows,1))};
        if(!intersectFontRect(intersection,glyph,f.clip))return advance();
        partial=glyph[0]<intersection[0]||glyph[2]>intersection[2]||glyph[1]<intersection[1]||glyph[3]>intersection[3];
        if(partial){firstRow=messageFontSub(intersection[1],glyph[1]);rows=messageFontAdd(messageFontSub(intersection[3],intersection[1]),1);}
    }
    if(std::uint32_t(rows)>65536)throw std::invalid_argument("Font glyph row work bound");
    std::uint32_t source=1+std::uint32_t(f.rowBytes)*std::uint32_t(firstRow);
    auto line=std::uint32_t(f.pitch)*std::uint32_t(messageFontAdd(y,firstRow))+std::uint32_t(x);
    for(std::uint32_t row=0;row<std::uint32_t(rows);++row){
        auto cursor=source,pixel=line;auto remaining=std::int32_t(width),column=x;
        do {
            const auto bits=read(cursor++);
            if(!bits){pixel+=8;remaining=messageFontSub(remaining,8);column=messageFontAdd(column,8);}
            else for(unsigned bit=0;bit<8;++bit){
                if((!partial||(column>=intersection[0]&&column<=intersection[2]))&&(bits&(0x80u>>bit))){
                    // x86 LEA scales modulo32 before addressing. Keep the pixel
                    // offset modulo31 bits, then require the borrowed backing.
                    const auto index=pixel&0x7fffffff;
                    if(index>=f.surface.size())throw std::invalid_argument("Font glyph pixel outside surface owner");
                    f.surface[index]=color;if(trace)trace('W',index,color);
                }
                ++pixel;column=messageFontAdd(column,1);remaining=messageFontSub(remaining,1);if(remaining<=0)break;
            }
        }while(remaining>0);
        source+=std::uint32_t(f.rowBytes);line+=std::uint32_t(f.pitch);
    }
    return advance();
}
}
