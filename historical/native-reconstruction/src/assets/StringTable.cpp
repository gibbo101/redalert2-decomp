// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/StringTable.hpp"

namespace ra2 {
namespace {
void appendUtf8(std::string& text,std::uint32_t cp) {
    if(cp<=0x7f)text+=char(cp);
    else if(cp<=0x7ff){text+=char(0xc0|(cp>>6));text+=char(0x80|(cp&63));}
    else if(cp<=0xffff){text+=char(0xe0|(cp>>12));text+=char(0x80|((cp>>6)&63));text+=char(0x80|(cp&63));}
    else {text+=char(0xf0|(cp>>18));text+=char(0x80|((cp>>12)&63));text+=char(0x80|((cp>>6)&63));text+=char(0x80|(cp&63));}
}
}
StringTable readStringTable(const Data& data) {
    if(data.u32(0)!=0x43534620||data.u32(4)!=3)throw std::invalid_argument("Only CSF v3 is supported");
    const auto count=data.u32(8),strings=data.u32(12);
    if(count>65536||strings>262144)throw std::invalid_argument("CSF count limit");
    data.check(0,24);std::size_t cursor=24;std::uint32_t seen=0;StringTable out;
    auto bytes=[&](std::uint32_t size){const auto* p=data.ptr(cursor,size);std::string s(reinterpret_cast<const char*>(p),size);cursor+=size;return s;};
    for(std::uint32_t i=0;i<count;++i) {
        if(data.u32(cursor)!=0x4c424c20)throw std::invalid_argument("CSF label signature");
        const auto values=data.u32(cursor+4),length=data.u32(cursor+8);cursor+=12;
        if(length==0||length>4096||values>strings-seen)throw std::invalid_argument("Invalid CSF label length/count");
        const auto label=lower(bytes(length));
        if(label.find('\0')!=std::string::npos)throw std::invalid_argument("Invalid CSF label");
        auto& rows=out[label];
        for(std::uint32_t j=0;j<values;++j) {
            const auto marker=data.u32(cursor),units=data.u32(cursor+4);cursor+=8;
            if((marker!=0x53545220&&marker!=0x53545257)||units>1048576)throw std::invalid_argument("CSF string signature/length");
            data.check(cursor,std::size_t(units)*2);LocalizedString row;
            for(std::uint32_t k=0;k<units;++k) {
                std::uint32_t cp=data.u16(cursor+2*k)^65535;
                if(cp>=0xd800&&cp<=0xdbff) {
                    if(++k==units)throw std::invalid_argument("Truncated CSF surrogate");
                    const auto next=data.u16(cursor+2*k)^65535;
                    if(next<0xdc00||next>0xdfff)throw std::invalid_argument("Invalid CSF surrogate");
                    cp=0x10000+((cp-0xd800)<<10)+(next-0xdc00);
                } else if(cp>=0xdc00&&cp<=0xdfff)throw std::invalid_argument("Unpaired CSF surrogate");
                appendUtf8(row.utf8,cp);
            }
            cursor+=std::size_t(units)*2;
            if(marker==0x53545257){const auto size=data.u32(cursor);cursor+=4;row.extra=bytes(size);}
            rows.push_back(std::move(row));++seen;
        }
    }
    if(seen!=strings||cursor!=data.size)throw std::invalid_argument("CSF count/trailing data mismatch");
    return out;
}
const std::string& localizedText(const StringTable& table,const std::string& label) {
    const auto found=table.find(lower(label));
    if(found==table.end()||found->second.size()!=1)throw std::invalid_argument("Missing/ambiguous localized label: "+label);
    return found->second.front().utf8;
}
}
