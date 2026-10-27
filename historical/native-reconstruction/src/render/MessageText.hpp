// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/FontAlignment.hpp"
#include <algorithm>
#include <string>
#include <type_traits>
namespace ra2 {
// Live IME globals and named platform/surface leaves. Refresh does not supply a
// layout/drawing answer. A zero platform context clears text/length/cursor but
// retains extra; the nonzero Windows conversion path remains a supplied service.
struct MessageTextServices {
    std::u16string composition;
    std::int32_t compositionLength=0,compositionCursor=0,extra=0;
    std::uint32_t highlightRgb=0,cursorRgb=0;
    std::int32_t cursorSuppression=0;
    std::function<void()> refreshIme;
    std::function<void(const FontTextBox&,std::uint32_t)> fill;
    std::function<void(std::int32_t,std::int32_t,std::int32_t,std::uint32_t,std::uint32_t)> line;
};
// Complete783622's forward UTF-16 bounded copy/zero padding for separate source
// and destination owners. No implicit terminator when the count is exhausted.
inline void copyMessageText(std::span<char16_t> destination,std::u16string_view source,std::uint32_t count){
    if(count>destination.size())throw std::invalid_argument("Message copy destination bound");
    bool zero=false;
    for(std::uint32_t i=0;i<count;++i){
        const auto unit=zero||i>=source.size()?char16_t{}:source[i];destination[i]=unit;if(!unit)zero=true;
    }
}
inline std::int32_t messageTextLength(std::u16string_view text){
    const auto n=text.find(char16_t{});const auto length=n==text.npos?text.size():n;
    if(length>1048576)throw std::invalid_argument("Message text length bound");
    return std::int32_t(length);
}
// Complete600830 control/arithmetic over a bounded 2048-unit scratch owner,
// actual prefix fitting and actual aligned text-to-pixels. Original incidental
// EAX bits are unused by the node caller and deliberately not projected.
template<class ScrollWord> requires (std::is_same_v<ScrollWord,std::int32_t>||std::is_same_v<ScrollWord,std::uint32_t>)
inline void drawMessageText(const FontBlitContext& context,const FontSurfaceServices& surface,
        FontTextBox& box,const std::u16string_view* text,std::int32_t caret,FontGlyphState& font,
        std::uint32_t rgb,ScrollWord& scroll,bool ime,bool mask,bool background,
        std::int32_t reveal,MessageTextServices& services,const FontGlyphTrace& trace={}){
    const auto add=messageFontAdd,sub=messageFontSub;
    const auto readScroll=[&]{return std::bit_cast<std::int32_t>(std::uint32_t(scroll));};
    const std::u16string_view source=text?*text:std::u16string_view{};
    if(caret<0||caret>messageTextLength(source))caret=0;
    std::int32_t composition=0,extra=0;
    if(ime){
        if(!services.refreshIme)throw std::invalid_argument("Message IME refresh service required");
        services.refreshIme();composition=services.compositionLength;extra=services.extra;
    }
    std::array<char16_t,2048> scratch{};
    copyMessageText(scratch,source,2048);
    if(composition){
        if(caret>2048||composition<0||composition>2048-caret)throw std::invalid_argument("Message composition scratch bound");
        copyMessageText(std::span(scratch).subspan(std::size_t(caret)),services.composition,std::uint32_t(2048-caret));
        const auto start=std::size_t(composition+caret);
        copyMessageText(std::span(scratch).subspan(start),source.substr(std::size_t(caret)),std::uint32_t(2048-start));
    }
    scratch.back()=0;const auto length=messageTextLength({scratch.data(),scratch.size()});
    if(mask)for(std::int32_t i=0;i<length;++i)scratch[std::size_t(i)]=u'*';
    if(trace)for(std::uint32_t i=0;i<scratch.size();++i)trace('s',i,scratch[i]);
    const auto cursor=extra||composition?add(services.compositionCursor,caret):caret;
    if(cursor<add(readScroll(),5))scroll=cursor>=5?sub(cursor,5):0;
    const auto suffix=[&](std::int32_t offset){
        if(offset<0||offset>=2048)throw std::invalid_argument("Message scratch pointer bound");
        return std::u16string_view(scratch.data()+offset,scratch.size()-std::size_t(offset));
    };
    const MessageFontMetrics metrics={font.primary,font.fallback.empty()?nullptr:font.fallback.data(),font.lineHeight,font.tab,font.spacing};
    while(readScroll()<length){
        const auto current=readScroll();const auto tail=suffix(current);
        const auto fit=fitMessageFont(metrics,&tail,sub(box.width,5),0,0);
        if(trace)trace('f',std::uint32_t(current),std::uint32_t(fit));
        if(fit>=sub(cursor,current))break;
        scroll=add(current,1);
    }
    auto delta=sub(caret,readScroll());const auto prefix=std::max(delta,0);
    auto middle=composition;
    if(delta<0){delta=add(delta,composition);middle=std::max(delta,0);}
    auto last=sub(sub(length,composition),caret);if(delta<0)last=add(last,delta);last=std::max(last,0);
    auto position=readScroll();
    if(background){
        const auto backgroundHeight=add(box.height,2);
        const auto tail=suffix(position);const auto width=messageFontWidth(metrics,&tail,0);
        if(trace)trace('w',std::uint32_t(width),0);
        if(!services.fill)throw std::invalid_argument("Message background fill service required");
        services.fill({sub(box.x,1),sub(box.y,1),add(width,5),backgroundHeight},0);
    }
    const auto segment=[&](std::int32_t count,std::uint32_t color){
        const auto advance=drawAlignedFontText(context,color,&font,box,suffix(position),std::uint32_t(count),0,0,&surface,reveal,trace);
        box.x=add(box.x,advance);box.width=sub(box.width,advance);if(box.width<0)box.width=0;
        position=add(position,count);
    };
    if(prefix)segment(prefix,rgb);
    std::int32_t cursorX=-1;
    if(middle){
        const auto offset=sub(cursor,add(readScroll(),prefix));auto remainder=-1;
        if(offset>=0&&offset<=middle){remainder=sub(middle,offset);middle=sub(middle,remainder);}
        if(middle>0)segment(middle,services.highlightRgb);
        if(remainder>=0){cursorX=box.x;if(remainder)segment(remainder,services.highlightRgb);}
    }else cursorX=box.x;
    if(last)segment(last,rgb);
    if(ime&&cursorX>0&&!services.cursorSuppression){
        if(!services.line)throw std::invalid_argument("Message cursor line service required");
        services.line(cursorX,box.y,sub(add(box.y,box.height),2),services.cursorRgb,255);
        services.line(add(cursorX,1),box.y,sub(add(box.y,box.height),2),services.cursorRgb,255);
    }
    services.cursorSuppression=0;
}
}
