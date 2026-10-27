// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/MessageNodeDrawing.hpp"
namespace ra2 {
// Observes actual visited/next identities; supplies no traversal or draw answer.
using MessageChainTrace=std::function<void(char,const MessageNode*,const MessageNode*)>;
// Complete4CF260 for live ordinary text-node chains. Low-byte force is retained
// across dispatches; actual Next is read after every draw, even after refusal.
inline void drawMessageChain(MessageNode* first,MessageList& list,MessageListGlobals& listGlobals,
        MessageNodeDrawGlobals& globals,const MessageListServices& services,
        const FontBlitContext& blit,MessageTextServices& textServices,std::uint32_t force,
        const FontGlyphTrace& trace={},const MessageChainTrace& chainTrace={}){
    const auto low=force&255u;std::size_t visits=0;
    for(auto* node=first;node;){
        if(++visits>1048576)throw std::invalid_argument("Message drawing chain traversal bound");
        if(node->destroyed)throw std::invalid_argument("Message drawing entered a destroyed text owner");
        if(chainTrace)chainTrace('n',node,nullptr);
        drawMessageNode(*node,list,listGlobals,globals,services,blit,textServices,low,trace);
        auto* next=node->next;
        if(chainTrace)chainTrace('l',node,next);
        node=next;
    }
}
// Complete5B5B30 ordinary non-editor path through actual head+2C traversal.
// The editor branch has additional window/IME/gadget behavior and is refused.
inline void drawOrdinaryMessageList(MessageList& list,MessageListGlobals& listGlobals,
        MessageNodeDrawGlobals& globals,const MessageListServices& services,
        const FontBlitContext& blit,MessageTextServices& textServices,
        const FontGlyphTrace& trace={},const MessageChainTrace& chainTrace={}){
    if(list.reserved19)throw std::invalid_argument("Message editor drawing is not recovered");
    drawMessageChain(list.head,list,listGlobals,globals,services,blit,textServices,1,trace,chainTrace);
}
}
