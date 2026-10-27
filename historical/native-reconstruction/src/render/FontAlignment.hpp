// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/FontText.hpp"
namespace ra2 {
struct FontTextBox {std::int32_t x=0,y=0,width=0,height=0;};
struct FontBlitContext {
    std::uint8_t enabled=0;
    FontGlyphState* defaultFont=nullptr;
    const FontSurfaceServices* defaultSurface=nullptr;
    FontTextColors colors;
};
// Complete5FE1B0. Box sizes and starting pen are saved before measurement, but
// clip X/Y are read again after alignment. The trace's M event observes the real
// measurement; it does not supply a layout answer. Pixel and surface events are
// forwarded from the single existing text/glyph kernel.
inline std::int32_t drawAlignedFontText(const FontBlitContext& context,std::uint32_t rgb,
        FontGlyphState* selectedFont,const FontTextBox& box,std::u16string_view text,
        std::uint32_t count,std::int32_t horizontal,std::int32_t vertical,
        const FontSurfaceServices* selectedSurface,std::int32_t reveal,const FontGlyphTrace& trace={}){
    if(!context.enabled)return 0;
    const auto* surface=selectedSurface?selectedSurface:context.defaultSurface;
    const auto& s=context.colors.shifts;
    const auto channel=[](std::uint32_t c,std::uint32_t right,std::uint32_t left){return ((c&255)>>(right&31))<<(left&31);};
    const auto color=std::uint16_t(channel(rgb>>16,s[3],s[2])|channel(rgb>>8,s[5],s[4])|channel(rgb,s[1],s[0]));
    auto x=box.x,y=box.y;const auto height=box.height,width=box.width;
    auto* font=selectedFont?selectedFont:context.defaultFont;
    if(!font)throw std::invalid_argument("Aligned text missing font owner");
    const MessageFontMetrics metrics={font->primary,font->fallback.empty()?nullptr:font->fallback.data(),font->lineHeight,font->tab,font->spacing};
    std::int32_t measuredWidth=0,measuredHeight=0;
    measureMessageFont(metrics,&text,&measuredWidth,&measuredHeight,width);
    if(trace)trace('M',std::uint32_t(measuredWidth),std::uint32_t(measuredHeight));
    const auto add=messageFontAdd,sub=messageFontSub;
    if(horizontal==1)x=add(x,add(sub(width,measuredWidth),1)/2);
    else if(horizontal==2)x=sub(x,add(measuredWidth,1)/2);
    else if(horizontal==3)x=add(x,sub(-1,measuredWidth));
    else if(horizontal==4)x=add(x,sub(sub(width,measuredWidth),1));
    if(vertical==1)y=add(y,add(sub(height,measuredHeight),1)/2);
    else if(vertical==2)y=sub(y,add(measuredHeight,1)/2);
    else if(vertical==3)y=add(y,sub(-1,measuredHeight));
    const auto clipX=box.x,clipY=box.y;
    font->clipping=true;font->clip={clipX,clipY,add(clipX,width),add(clipY,height)};font->color=color;
    if(!surface)throw std::invalid_argument("Aligned text missing surface owner");
    return sub(drawFontOnSurface(font,*surface,text,x,y,count,reveal,context.colors,trace),x);
}
}
