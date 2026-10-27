// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <optional>
#include <span>
#include <stdexcept>
#include <string_view>
namespace ra2 {
struct StringLookupLabel {std::string_view key;std::uint32_t index=0;};
using StringLookupTrace=std::function<void(char,std::uint32_t)>;
// CRT781F20's locale-zero branch. Input views supply the original trailing NUL;
// an embedded NUL also terminates comparison. No host locale/case conversion.
inline int compareStringLookupKeys(std::string_view a,std::string_view b){
    for(std::size_t i=0;;++i){
        const auto byte=[i](std::string_view s){return i<s.size()?std::uint8_t(s[i]):std::uint8_t(0);};
        auto x=byte(a),y=byte(b);
        if(x!=y){
            if(x>='A'&&x<='Z')x=std::uint8_t(x+32);
            if(y>='A'&&y<='Z')y=std::uint8_t(y+32);
            if(x!=y)return x<y?-1:1;
        }
        if(!x)return 0;
    }
}
// Complete CRT782025 for valid fixed-size label records, with its lower middle
// for even ranges (including duplicates). Construction/sorting remain supplied.
inline std::optional<std::size_t> searchStringLookupLabel(std::string_view key,
        std::span<const StringLookupLabel> labels,std::uint32_t count,const StringLookupTrace& trace={}){
    if(count>labels.size())throw std::invalid_argument("String lookup count outside supplied labels");
    std::size_t first=0;auto length=count;
    if(trace)trace('B',count);
    while(length){
        const auto half=length/2;const auto middle=first+(length%2?half:(half?half-1:0));
        if(trace)trace('C',std::uint32_t(middle));
        const int comparison=compareStringLookupKeys(key,labels[middle].key);
        if(!comparison)return middle;
        if(comparison<0)length=length%2?half:(half?half-1:0);
        else{first=middle+1;length=half;}
    }
    return {};
}
// Original dword pointer slots are modeled as 32-bit words. Production resolves
// supplied handles to immutable native strings; the algorithm does not read text.
// This also retains output/index/slot aliasing without changing original widths.
struct StringLookupWorld {
    bool labelsPresent=true;
    std::span<const StringLookupLabel> labels;
    std::uint32_t count=0;
    std::span<const std::uint32_t> text,extra;
    std::uint32_t unavailable=0;
};
// Base6F9EC0 through found/no-label returns. Missing-label allocation/formatting/
// logging and nonzero CRT locale are unjoined; missing labels explicitly refuse.
inline std::uint32_t lookupString(std::string_view key,std::uint32_t* extraOutput,
        const StringLookupWorld& world,const StringLookupTrace& trace={}){
    const auto store=[&](std::uint32_t value){*extraOutput=value;if(trace)trace('O',value);};
    if(extraOutput)store(0);
    if(trace)trace('L',world.labelsPresent);
    if(!world.labelsPresent)return world.unavailable;
    const auto found=searchStringLookupLabel(key,world.labels,world.count,trace);
    if(!found)throw std::invalid_argument("Missing string label fallback requires recovery");
    const auto slot=[&](std::span<const std::uint32_t> values,std::uint32_t index){
        if(index>=values.size())throw std::invalid_argument("String lookup index outside supplied slots");return values[index];
    };
    if(extraOutput){const auto index=world.labels[*found].index;if(trace)trace('E',index);store(slot(world.extra,index));}
    // The extra store may alias the found label's index. Read it again.
    const auto index=world.labels[*found].index;if(trace)trace('T',index);return slot(world.text,index);
}
}
