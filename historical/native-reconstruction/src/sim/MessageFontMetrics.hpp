// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <bit>
#include <cstdint>
#include <functional>
#include <limits>
#include <optional>
#include <span>
#include <stdexcept>
#include <string_view>
namespace ra2 {
struct MessageFontGlyphs {
    std::span<const std::uint16_t> indices;
    std::uint32_t stride=0,base=0;
    std::function<std::uint8_t(std::uint32_t)> byte;
};
struct MessageFontMetrics {
    const MessageFontGlyphs* primary=nullptr;
    const std::uint8_t* fallback=nullptr;
    std::int32_t lineHeight=0,tab=0,spacing=0;
};
using MessageFontTrace=std::function<void(char,std::uint32_t,std::uint32_t)>;
inline std::int32_t messageFontAdd(std::int32_t a,std::int32_t b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
inline std::int32_t messageFontSub(std::int32_t a,std::int32_t b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
inline std::int32_t messageFontTab(std::int32_t x,std::int32_t tab){
    x=messageFontAdd(x,tab);
    if(!tab||(x==std::numeric_limits<std::int32_t>::min()&&tab==-1))throw std::invalid_argument("Message font original tab division faults");
    return messageFontSub(x,x%tab);
}
inline std::optional<std::uint8_t> messageFontGlyph(char16_t code,const MessageFontGlyphs& p,
        const MessageFontMetrics& font,const MessageFontTrace& trace){
    if(std::size_t(code)>=p.indices.size())throw std::invalid_argument("Message font index outside supplied table");
    const auto index=p.indices[code];if(trace)trace('I',std::uint32_t(code),index);
    const auto address=index?p.base+p.stride*(std::uint32_t(index)-1):0;
    if(address){if(!p.byte)throw std::invalid_argument("Message font glyph backing required");auto b=p.byte(address);if(trace)trace('G',address,b);return b;}
    if(trace)trace('F',bool(font.fallback),font.fallback?*font.fallback:0);
    if(font.fallback)return *font.fallback;
    return {};
}
// Complete4314B0 with UTF-16 code-unit traversal and optional output pointers.
// Font loading/association is supplied. An absent text pointer differs from an
// empty terminated string. A trailing NUL is implicit in the supplied view.
inline bool measureMessageFont(const MessageFontMetrics& font,const std::u16string_view* text,
        std::int32_t* width,std::int32_t* height,std::int32_t limit,const MessageFontTrace& trace={}){
    const auto output=[&](char kind,std::int32_t* p,std::int32_t value){if(p){*p=value;if(trace)trace(kind,std::uint32_t(value),0);}};
    const auto* primary=font.primary;
    if(!primary||!text){output('H',height,0);output('W',width,0);return false;}
    std::int32_t x=0,glyphs=0,maximum=0,totalHeight=font.lineHeight;
    const auto lineHeight=font.lineHeight;
    std::size_t cursor=0,lastSpace=0;bool hasSpace=false;std::int32_t savedMaximum=0;
    char16_t previous=0;
    // Host work bound is an explicit refusal, not an alternate wrapping policy.
    std::size_t visits=0;
    while(cursor<text->size()&&(*text)[cursor]){
        if(++visits>1048576)throw std::invalid_argument("Message font traversal bound");
        const auto code=(*text)[cursor];auto next=cursor+1;
        if(code==10||code==13){if(previous!=13){x=0;glyphs=0;totalHeight=messageFontAdd(totalHeight,lineHeight);}}
        else if(code==9)x=messageFontTab(x,font.tab);
        else {
            if(code==32){lastSpace=next;hasSpace=true;savedMaximum=maximum;}
            if(const auto byte=messageFontGlyph(code,*primary,font,trace)){
                glyphs=messageFontAdd(glyphs,1);const auto advance=messageFontAdd(font.spacing,*byte);x=messageFontAdd(x,advance);
                if(limit&&x>limit){
                    if(hasSpace){if(glyphs>1){next=lastSpace;maximum=savedMaximum;}}
                    else{if(glyphs>1){x=messageFontSub(x,advance);next=cursor;}if(x>maximum)maximum=x;}
                    x=0;glyphs=0;hasSpace=false;totalHeight=messageFontAdd(totalHeight,lineHeight);
                }else if(x>maximum)maximum=x;
            }
        }
        previous=code;cursor=next;
    }
    output('W',width,maximum);output('H',height,totalHeight);return true;
}
// Complete431690: the second argument doubles as limit input and width output.
inline std::int32_t messageFontWidth(const MessageFontMetrics& font,const std::u16string_view* text,
        std::int32_t limit,const MessageFontTrace& trace={}){
    measureMessageFont(font,text,&limit,nullptr,limit,trace);return limit;
}
// Complete431710 prefix fitting; whitespace retreat includes the preceding
// separator, whereas an overwide first character can return zero.
inline std::int32_t fitMessageFont(const MessageFontMetrics& font,const std::u16string_view* text,
        std::int32_t limit,std::uint32_t maxCharacters,std::uint32_t wordWrap,const MessageFontTrace& trace={}){
    const auto* primary=font.primary;if(!primary||!text)return 0;
    std::int32_t x=0,count=0;
    for(std::size_t cursor=0;cursor<text->size()&&(*text)[cursor];++cursor){
        if(cursor>=1048576)throw std::invalid_argument("Message font traversal bound");
        const auto code=(*text)[cursor];
        if(code==9)x=messageFontTab(x,font.tab);
        else if(code!=10&&code!=13)if(const auto byte=messageFontGlyph(code,*primary,font,trace))x=messageFontAdd(x,messageFontAdd(font.spacing,*byte));
        count=messageFontAdd(count,1);
        if(x>limit){
            count=messageFontSub(count,1);
            if(!wordWrap||code<=32||!count)return count;
            auto n=count;auto back=cursor;
            while(n){--back;if((*text)[back]<=32)return n;--n;}
            return count;
        }
        if((maxCharacters&&std::uint32_t(count)==maxCharacters)||(wordWrap&&(code==10||code==13)))return count;
    }
    return count;
}
}
