// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/OwnedMessagePresentation.hpp"
#include "sim/MissionTextAction.hpp"
namespace ra2 {
// Host UTF-8 association used by PreparedStringLookup, not the original CSF
// loader. Preserve code points, including embedded NUL; no normalization.
inline std::u16string missionMessageUtf16(std::string_view text){
    std::u16string out;
    for(std::size_t at=0;at<text.size();){
        const auto first=std::uint8_t(text[at++]);std::uint32_t cp=first;unsigned extra=0;std::uint32_t minimum=0;
        if(first>=0xc2&&first<=0xdf){cp=first&31;extra=1;minimum=0x80;}
        else if(first>=0xe0&&first<=0xef){cp=first&15;extra=2;minimum=0x800;}
        else if(first>=0xf0&&first<=0xf4){cp=first&7;extra=3;minimum=0x10000;}
        else if(first>=0x80)throw std::invalid_argument("Mission message invalid UTF-8");
        if(extra>text.size()-at)throw std::invalid_argument("Mission message truncated UTF-8");
        for(unsigned i=0;i<extra;++i){const auto c=std::uint8_t(text[at++]);if((c&0xc0)!=0x80)throw std::invalid_argument("Mission message UTF-8 continuation");cp=(cp<<6)|(c&63);}
        if(cp<minimum||cp>0x10ffff||(cp>=0xd800&&cp<=0xdfff))throw std::invalid_argument("Mission message invalid Unicode scalar");
        if(cp<=0xffff)out.push_back(char16_t(cp));
        else {cp-=0x10000;out.push_back(char16_t(0xd800+(cp>>10)));out.push_back(char16_t(0xdc00+(cp&1023)));}
    }
    return out;
}
// Actual action11's seven insertion arguments: null prefix, identifier0,
// localized UTF-16, signed color, flags4046, raw duration dword, silent0.
inline const MessageNode* insertMissionMessage(OwnedMessagePresentation& owner,const MissionTextRequest& request){
    if(request.leading0||request.leading1||request.trailing)throw std::invalid_argument("Mission message nonordinary insertion arguments");
    const auto text=missionMessageUtf16(request.text);const std::u16string_view view=text;
    return owner.insert({nullptr,0,&view,request.color,std::uint32_t(request.style),std::bit_cast<std::int32_t>(request.duration),0});
}
}
