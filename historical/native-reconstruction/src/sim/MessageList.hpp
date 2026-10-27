// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MessageFontMetrics.hpp"
#include <array>
#include <algorithm>
#include <string>
namespace ra2 {
// Logical stable records; guest addresses/vtables are not mapped by the runtime.
// Untouched allocator bytes are supplied explicitly by the owning allocator.
struct MessageNode {
    MessageNode* next=nullptr;MessageNode* previous=nullptr;
    std::int32_t x=0,y=0,width=0,height=0;
    std::uint8_t dirty=0,sticky=0,field1e=0,padding1f=0;
    std::uint32_t gadgetFlags=0,expires=0,identifier=0,flags=0;
    int slot=-1;std::int32_t color=0,maximumWidth=0;
    std::uint32_t field3c=0;std::uint8_t field40=0,field41=0;
    std::uint16_t padding42=0;std::uint32_t field44=0,field48=0;
    bool destroyed=false;
};
struct MessageList {
    MessageNode* head=nullptr;
    std::int32_t x=0,y=0,maximumLines=0,lineStep=0,width=0;
    std::uint8_t reserved19=0,reserved1a=0;
    std::array<std::array<char16_t,162>,14> text{};
    std::array<std::uint16_t,14> available{};
};
struct MessageListGlobals {
    const MessageFontMetrics* selectedFont=nullptr;
    std::int32_t mode=0;
    std::uint8_t mode3Enabled=0,mode4Enabled=0;
    std::uint32_t clockStart=0xffffffff,clockAccumulated=0;
    std::array<MessageNode*,3> focused{};
    std::int32_t sound=0;
};
struct MessageListServices {
    std::function<MessageNode*()> allocate;
    std::function<void(MessageNode*)> release;
    std::function<std::uint32_t()> milliseconds;
    std::function<void(std::int32_t,std::uint32_t,float,std::uint32_t)> play;
};
struct MessageInsertRequest {
    const std::u16string_view* prefix=nullptr;
    std::uint32_t identifier=0;
    const std::u16string_view* body=nullptr;
    std::int32_t color=0;
    std::uint32_t flags=0;
    std::int32_t lifetime=-1;
    std::uint8_t silent=0;
};
namespace message_list_detail {
inline std::size_t length(std::u16string_view text){
    const auto zero=text.find(char16_t{});return zero==text.npos?text.size():zero;
}
inline MessageNode* first(MessageNode* p){
    for(std::size_t n=0;p&&p->previous;++n){if(n==1048576)throw std::invalid_argument("Message list backward traversal bound");p=p->previous;}return p;
}
inline MessageNode* last(MessageNode* p){
    for(std::size_t n=0;p&&p->next;++n){if(n==1048576)throw std::invalid_argument("Message list forward traversal bound");p=p->next;}return p;
}
inline void clearFocus(MessageNode& node,MessageListGlobals& g){
    if(g.focused[2]==&node){node.gadgetFlags&=0xfffffeffu;g.focused[2]=nullptr;}
}
// Actual4CF170 ->539110 ordinary text-node removal, then6F17F0 destruction.
inline MessageNode* detach(MessageNode& node,MessageListGlobals& g){
    clearFocus(node,g);auto* head=first(&node);auto* tail=last(&node);
    if(node.previous)node.previous->next=node.next;
    if(node.next)node.next->previous=node.previous;
    node.previous=nullptr;node.next=nullptr;
    return head==&node?(tail==&node?nullptr:first(tail)):head;
}
inline void destroy(MessageNode& node,MessageListGlobals& g,const MessageListServices& s){
    if(!s.release)throw std::invalid_argument("Message node release service required");
    clearFocus(node,g);for(unsigned i=0;i<2;++i)if(g.focused[i]==&node)g.focused[i]=nullptr;
    // The base destructor traverses first then last before unlinking, even
    // for detached/new nodes. Its computed replacement head is discarded.
    auto* head=first(&node);auto* tail=last(&node);
    if(node.previous)node.previous->next=node.next;
    if(node.next)node.next->previous=node.previous;
    node.previous=nullptr;node.next=nullptr;
    if(head==&node&&tail!=&node)first(tail);
    node.destroyed=true;s.release(&node);
}
inline void construct(MessageNode& p,MessageList& list,int color,std::uint32_t flags){
    p.y=list.y;p.x=list.x;p.height=1;p.width=1;p.next=nullptr;p.previous=nullptr;
    p.dirty=0;p.field1e=0;p.sticky=0;p.gadgetFlags=0;
    p.slot=-1;p.expires=0;p.identifier=0;p.flags=flags;p.color=color;
    p.maximumWidth=-1;p.field3c=0;p.field40=0;p.field41=0;p.field44=0;p.field48=0;p.destroyed=false;
}
}
// Complete ordinary text insertion5B4DA0. Heap/timeGetTime/audio leaves and
// initial list/font/globals are supplied. Host bounds refuse, never repair,
// overflowing original local buffers and nonterminating recursive/traversal paths.
inline MessageNode* insertMessage(MessageList& list,MessageListGlobals& g,
        const MessageListServices& s,const MessageInsertRequest& request,unsigned depth=0){
    using namespace message_list_detail;
    if(depth>=64)throw std::invalid_argument("Message insertion recursion bound");
    const auto* font=g.selectedFont; // Actual497A50 ignores its color argument.
    if(!request.body||!font)return nullptr;
    std::u16string line;
    if(request.prefix){const auto n=length(*request.prefix);if(n+1>161)throw std::invalid_argument("Message prefix exceeds original local buffer");line.assign(request.prefix->substr(0,n));line.push_back(u':');}
    const auto prefixLength=line.size();std::u16string_view prefix(line);
    const auto prefixWidth=messageFontWidth(*font,&prefix,0);
    const auto bodyLength=length(*request.body);
    if(bodyLength>1048576)throw std::invalid_argument("Message body traversal bound");
    const auto room=messageFontSub(messageFontSub(list.width,prefixWidth),8);
    if(room<=0)return nullptr;
    const auto fitted=fitMessageFont(*font,request.body,room,111,1);
    if(fitted<0)return nullptr;
    if(prefixLength+std::uint32_t(fitted)>161)throw std::invalid_argument("Message line exceeds original local buffer");
    line.append(request.body->substr(0,std::uint32_t(fitted)));
    if(list.maximumLines>0){
        std::int32_t count=0;std::size_t visited=0;
        for(auto* p=list.head;p;p=p->next){if(++visited>1048576)throw std::invalid_argument("Message list count bound");count=messageFontAdd(count,1);}
        if(list.reserved19&&list.reserved1a)count=messageFontAdd(count,1);
        count=messageFontAdd(count,1);
        if(count>list.maximumLines){
            auto* removed=list.head;if(!removed)return nullptr;
            list.head=detach(*removed,g);
            for(unsigned i=0;i<14;++i)if(removed->slot==int(i))list.available[i]=1;
            destroy(*removed,g,s);
        }
    }
    if(!s.allocate)throw std::invalid_argument("Message allocation service required");
    auto* node=s.allocate();
    // The original dereferences a null allocation later. Refuse that entered
    // fault rather than manufacture successful insertion or rollback effects.
    if(!node)throw std::invalid_argument("Original message allocation would fault");
    construct(*node,list,request.color,request.flags|0x8000u);
    node->field41=std::uint8_t(!request.silent&&
        (g.mode==4?bool(g.mode4Enabled):g.mode==3?bool(g.mode3Enabled):true));
    if(request.lifetime==-1)node->expires=0;
    else {
        auto now=g.clockAccumulated;
        if(g.clockStart!=0xffffffffu){
            if(!s.milliseconds)throw std::invalid_argument("Message timeGetTime service required");
            const auto ticks=s.milliseconds()>>4;now+=ticks-g.clockStart;
        }
        node->expires=now+std::uint32_t(request.lifetime);
    }
    node->identifier=request.identifier;node->maximumWidth=list.width;
    unsigned slot=0;while(slot<14&&!list.available[slot])++slot;
    if(slot==14){destroy(*node,g,s);return nullptr;}
    list.available[slot]=0;
    // Original clears0xA2 bytes, although slots have0x144-byte stride.
    std::fill_n(list.text[slot].begin(),81,char16_t{});
    std::copy(line.begin(),line.end(),list.text[slot].begin());list.text[slot][line.size()]=0;
    node->slot=int(slot);
    if(!request.silent){if(!s.play)throw std::invalid_argument("Message sound service required");s.play(g.sound,0x2000,1.f,0);}
    if(list.head){
        auto* tail=last(list.head);tail->next=node;node->previous=tail;node->next=nullptr;
        //5390E0 returns the first node; caller retains its existing head.
        first(node);
    }else list.head=node;
    auto y=list.y;if(list.reserved19&&list.reserved1a)y=messageFontAdd(list.lineStep,list.y);
    std::size_t visited=0;
    for(auto* p=list.head;p;p=p->next){if(++visited>1048576)throw std::invalid_argument("Message layout traversal bound");p->y=y;y=messageFontAdd(y,list.lineStep);}
    if(std::uint32_t(fitted)<bodyLength){
        auto remaining=request.body->substr(std::uint32_t(fitted));
        while(length(remaining)&&remaining[0]<32)remaining.remove_prefix(1);
        if(length(remaining)){auto child=request;child.body=&remaining;child.silent=1;insertMessage(list,g,s,child,depth+1);}
    }
    return node;
}
}
