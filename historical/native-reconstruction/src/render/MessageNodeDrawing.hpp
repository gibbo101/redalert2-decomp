// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/MessageText.hpp"
#include "render/PlayerColor.hpp"
#include "sim/MessageList.hpp"
namespace ra2 {
struct MessageNodeDrawGlobals {
    std::span<const HsvColor* const> colors;
    std::int32_t colorCount=0;
    FontGlyphState* font=nullptr;
    const FontSurfaceServices* surface=nullptr;
    std::int32_t sound=0;
};
inline std::optional<std::u16string_view> messageNodeText(const MessageNode& node,const MessageList& list){
    if(node.slot==-1)return {};
    if(node.slot<0||node.slot>=14)throw std::invalid_argument("Message node text association outside list");
    const auto& slot=list.text[std::size_t(node.slot)];
    return std::u16string_view(slot.data(),slot.size());
}
// Complete6F1620 with actual4CF240/497A50/4CF630/4FF050 and600830.
// Draw globals borrow selected owners; initial associations and time/audio/
// surface/IME leaves remain supplied. The list slot is resolved again after
// sound, preserving the saved text length versus the late text association.
inline bool drawMessageNode(MessageNode& node,MessageList& list,MessageListGlobals& listGlobals,
        MessageNodeDrawGlobals& globals,const MessageListServices& services,
        const FontBlitContext& blit,MessageTextServices& textServices,
        std::uint32_t force,const FontGlyphTrace& trace={}){
    if(node.field40)return false;
    if(!force&&!node.dirty)return false;
    node.dirty=0;
    const auto count=globals.colorCount;auto index=node.color;
    if(!count)return false;
    if(index<=0||index>=count)index=0;
    if(std::uint32_t(index)>=globals.colors.size())throw std::invalid_argument("Message color table bound");
    const auto* color=globals.colors[std::size_t(index)];if(!color)return false;
    auto* font=globals.font;if(!font)throw std::invalid_argument("Message node font owner required");
    auto x=node.x,y=node.y,width=node.maximumWidth;
    const auto queryWidth=[&]{
        if(!globals.surface||!globals.surface->width)throw std::invalid_argument("Message node surface width required");
        return globals.surface->width();
    };
    if(width<0)width=queryWidth();
    const auto height=font->lineHeight;
    const auto excess=messageFontSub(messageFontAdd(x,width),queryWidth());
    if(excess>0){width=messageFontSub(width,excess);if(width<=0||height<=0)return false;}
    const auto converted=originalHsvToRgb(*color);
    const auto rgb=std::uint32_t(converted.r)|(std::uint32_t(converted.g)<<8)|(std::uint32_t(converted.b)<<16);
    auto text=messageNodeText(node,list);if(!text)throw std::invalid_argument("Original node text length would fault");
    const auto length=messageTextLength(*text);
    if(node.field41){
        if(!services.milliseconds)throw std::invalid_argument("Message node timeGetTime required");
        const auto now=services.milliseconds();const auto old=node.field44;
        node.field44=old?old+((now-node.field48)>>4):1;
        if(old!=node.field44)node.field48=now;
        if(std::bit_cast<std::int32_t>(node.field44)<=length){
            if(!services.play)throw std::invalid_argument("Message node audio service required");
            services.play(globals.sound,0x2000,1.f,0);
        }
    }
    const auto reveal=std::bit_cast<std::int32_t>(node.field44);
    const auto focus=listGlobals.focused[2]==&node;
    text=messageNodeText(node,list);
    if(!globals.surface)throw std::invalid_argument("Message node surface owner required");
    FontTextBox box{x,y,width,height};
    drawMessageText(blit,*globals.surface,box,text?&*text:nullptr,length,*font,rgb,node.field3c,focus,false,true,reveal,textServices,trace);
    return true;
}
}
