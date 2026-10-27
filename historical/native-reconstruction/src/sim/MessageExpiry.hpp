// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MessageList.hpp"
namespace ra2 {
// Complete ordinary5B5610. Uses the same borrowed records and destruction
// kernel as insertion. No native frame schedule, heap or time API is implied.
inline bool expireMessages(MessageList& list,MessageListGlobals& globals,
        const MessageListServices& services){
    bool removed=false;std::size_t visited=0;
    auto* node=list.head;
    while(node){
        if(++visited>1048576)throw std::invalid_argument("Message expiry traversal bound");
        if(node->expires){
            auto now=globals.clockAccumulated;
            if(globals.clockStart!=0xffffffffu){
                if(!services.milliseconds)throw std::invalid_argument("Message expiry timeGetTime service required");
                const auto ticks=services.milliseconds()>>4;
                now+=ticks-globals.clockStart;
            }
            // The expiry word is reread after the API; equality retains the
            // message. Original comparison is signed after dword arithmetic.
            if(std::bit_cast<std::int32_t>(now)>std::bit_cast<std::int32_t>(node->expires)){
                auto* next=node->next;
                list.head=message_list_detail::detach(*node,globals);
                for(unsigned i=0;i<14;++i)if(node->slot==int(i))list.available[i]=1;
                message_list_detail::destroy(*node,globals,services);
                removed=true;node=next;continue;
            }
        }
        node=node->next;
    }
    if(removed){
        auto y=list.y;
        if(list.reserved19&&list.reserved1a)y=messageFontAdd(list.lineStep,list.y);
        visited=0;
        for(auto* p=list.head;p;p=p->next){
            if(++visited>1048576)throw std::invalid_argument("Message expiry layout traversal bound");
            p->y=y;y=messageFontAdd(y,list.lineStep);
        }
    }
    return removed;
}
}
