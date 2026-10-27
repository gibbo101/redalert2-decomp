// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/FontGlyph.hpp"
namespace ra2 {
// Supplied live pixel-format/global color records, not compiled original data.
struct FontTextColors {
    std::array<std::uint32_t,6> shifts{}; // R left/right, B left/right, G left/right.
    std::array<std::uint8_t,3> target{}; // R/G/B, the actual63CF20 source order.
};
inline std::uint8_t fontShiftByte(std::uint32_t n,std::uint32_t right,std::uint32_t left){
    return std::uint8_t((n>>(right&31))<<(left&31));
}
// Complete63CF20 for its nonoverlapping text-caller records. Signed /256 truncates.
inline void adjustFontRgb(std::array<std::uint8_t,3>& color,std::uint32_t factor,
        const std::array<std::uint8_t,3>& target){
    for(unsigned i=0;i<3;++i)color[i]=std::uint8_t(color[i]+(int(target[i])-int(color[i]))*int(factor&255)/256);
}
inline std::uint16_t fadedFontColor(std::uint16_t saved,std::uint32_t factor,const FontTextColors& colors){
    const auto& s=colors.shifts;
    std::array<std::uint8_t,3> rgb={fontShiftByte(saved,s[0],s[1]),fontShiftByte(saved,s[4],s[5]),fontShiftByte(saved,s[2],s[3])};
    adjustFontRgb(rgb,factor,colors.target);
    const auto channel=[](std::uint8_t c,std::uint32_t right,std::uint32_t left){return (std::uint32_t(c)>>(right&31))<<(left&31);};
    return std::uint16_t(channel(rgb[0],s[1],s[0])|channel(rgb[1],s[5],s[4])|channel(rgb[2],s[3],s[2]));
}
// Complete431CC0. The shortened-reveal tail measures from the saved NEXT text
// pointer, excluding the already fetched current unit. Its width output aliases
// that pointer's scratch slot before pen X is added; no host address is returned.
// Glyph/metric algorithms are shared; no replacement width or drawing callback.
inline std::int32_t drawFontText(FontGlyphState& font,std::u16string_view text,
        std::int32_t x,std::int32_t y,std::uint32_t count,
        std::int32_t reveal,const FontTextColors& colors,const FontGlyphTrace& trace={}){
    const auto saved=font.color;std::int32_t ordinal=0,countdown=messageFontSub(reveal,1);
    auto factor=(9u-std::uint32_t(reveal))*31u;
    for(std::size_t cursor=0;cursor<text.size()&&text[cursor];++cursor){
        if(cursor>=1048576)throw std::invalid_argument("Font text traversal bound");
        const auto code=text[cursor];
        if(reveal){
            if(ordinal>=reveal){
                font.color=saved;
                const auto suffix=text.substr(cursor+1);
                const MessageFontMetrics metrics={font.primary,font.fallback.empty()?nullptr:font.fallback.data(),font.lineHeight,font.tab,font.spacing};
                std::int32_t width=0;measureMessageFont(metrics,&suffix,&width,nullptr,0);
                return messageFontAdd(x,width);
            }
            if(countdown<8)font.color=fadedFontColor(saved,factor,colors);
            factor+=31;ordinal=messageFontAdd(ordinal,1);countdown=messageFontSub(countdown,1);
        }
        if(code!=13&&code!=10)x=drawFontGlyph(font,code,x,y,-1,trace);
        if(count&&!--count)break;
    }
    font.color=saved;return x;
}
// Named surface virtual services stay supplied until the production surface join.
struct FontSurfaceServices {
    std::function<std::span<std::uint16_t>(std::int32_t,std::int32_t)> lock;
    std::function<std::uint32_t()> pitchBytes;
    std::function<std::int32_t()> width,height;
    std::function<void()> unlock;
};
inline void bindFontSurface(FontGlyphState& font,const FontSurfaceServices& surface){
    if(!surface.lock||!surface.pitchBytes||!surface.width||!surface.height)throw std::invalid_argument("Font surface binding services required");
    font.surface=surface.lock(0,0);
    font.pitch=std::int32_t(surface.pitchBytes()>>1);
    FontRect bounds={0,0,messageFontSub(surface.width(),1),0};
    const auto bottom=messageFontSub(surface.height(),1);bounds[3]=bottom;
    if(!(std::uint32_t(font.clip[0])|std::uint32_t(font.clip[1])|std::uint32_t(font.clip[2])|std::uint32_t(font.clip[3]))){
        font.clip[3]=bottom;font.clip[0]=bounds[0];font.clip[1]=bounds[1];font.clip[2]=bounds[2];
    }else intersectFontRect(font.clip,font.clip,bounds);
}
inline void unbindFontSurface(FontGlyphState& font,const FontSurfaceServices& surface){
    if(!surface.unlock)throw std::invalid_argument("Font surface unlock service required");
    surface.unlock();font.surface={};font.pitch=0;
}
// Complete432350; original unused binding returns are deliberately unprojected.
inline std::int32_t drawFontOnSurface(FontGlyphState* font,const FontSurfaceServices& surface,
        std::u16string_view text,std::int32_t x,std::int32_t y,
        std::uint32_t count,std::int32_t reveal,const FontTextColors& colors,const FontGlyphTrace& trace={}){
    if(!font)return x;
    bindFontSurface(*font,surface);font->origin=x;
    const auto result=drawFontText(*font,text,x,y,count,reveal,colors,trace);
    unbindFontSurface(*font,surface);return result;
}
}
