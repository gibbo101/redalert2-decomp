// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/IniEnumeration.hpp"
#include <bit>
#include <climits>
#include <zlib.h>
namespace ra2 {
namespace {
void emit(const IniEnumerationServices& s,std::int64_t off,std::uint64_t v=0,const void* p=nullptr){if(s.store)s.store(off,v,p);}
void ensureSorted(IniSectionIndex& w,const IniEnumerationServices& s){
    if(w.sortedC)return;
    if(!s.sort)throw std::invalid_argument("INI index sort child unbound");
    const auto backing=w.backing;const auto count=w.count4;
    if(count<0||std::size_t(count)>backing.size())throw std::invalid_argument("INI sort outside supplied backing");
    s.sort(backing,count);
    w.hot10=nullptr;emit(s,0x10);
    w.sortedC=1;emit(s,0xc,1);
}
IniSectionIndexEntry* search(IniSectionIndex& w,std::uint32_t hash){
    auto count=w.count4;const auto backing=w.backing;
    if(count<=0)return nullptr;
    if(std::size_t(count)>backing.size())throw std::invalid_argument("INI search outside supplied backing");
    const auto key=std::bit_cast<std::int32_t>(hash);std::size_t first=0;
    while(count>0){
        const auto half=count/2;auto* entry=&backing[first+std::size_t(half)];
        const auto candidate=std::bit_cast<std::int32_t>(entry->hash);
        if(candidate>key)count=half;
        else if(candidate==key)return entry;
        else{first+=std::size_t(half)+1;count-=half+1;}
    }
    return nullptr;
}
IniEnumerationSection*& hotValue(IniSectionIndex& w){
    if(!w.hot10)throw std::invalid_argument("INI hot entry disappeared after store");
    return w.hot10->section;
}

void updateHot(IniSectionIndex& w,IniSectionIndexEntry* entry,const IniEnumerationServices& s){w.hot10=entry;emit(s,0x10,0,entry);}
}
std::uint32_t iniSectionNameCrc(std::string_view name){
    name=name.substr(0,name.find('\0'));
    if(name.size()>INT_MAX)throw std::invalid_argument("INI name exceeds original signed length");
    auto crc=crc32(0,reinterpret_cast<const Bytef*>(name.data()),uInt(name.size()));
    const auto tail=name.size()%4;
    if(tail){
        std::uint8_t padding[3]{std::uint8_t(tail),0,0};
        for(std::size_t i=1;i<4-tail;++i)padding[i]=std::uint8_t(name[name.size()-tail]);
        crc=crc32(crc,padding,uInt(4-tail));
    }
    return std::uint32_t(crc);
}
IniSectionIndexEntry* findIniSectionIndex(IniSectionIndex& w,std::uint32_t hash,const IniEnumerationServices& s){
    if(w.count4==0)return nullptr;
    ensureSorted(w,s);return search(w,hash);
}
bool hasIniSectionHot(const IniSectionIndex& w,std::uint32_t hash){return w.hot10&&w.hot10->hash==hash;}
IniEnumerationSection*& iniSectionValue(IniSectionIndex& w,std::uint32_t hash,const IniEnumerationServices& s){
    if(w.count4==0)return w.fallback;
    if(hasIniSectionHot(w,hash))return hotValue(w);
    ensureSorted(w,s);
    if(auto* entry=search(w,hash)){updateHot(w,entry,s);return hotValue(w);}
    return w.fallback;
}
std::int32_t iniEnumerationCount(IniSectionIndex& w,std::optional<std::string_view> name,const IniEnumerationServices& s){
    if(!name)return 0;
    const auto hash=iniSectionNameCrc(*name);
    if(w.count4==0)return 0;
    if(!hasIniSectionHot(w,hash)){
        auto* entry=findIniSectionIndex(w,hash,s);if(!entry)return 0;updateHot(w,entry,s);
    }
    IniEnumerationSection** value=&w.fallback;
    // The parent repeats the lookup, including its live count/hot reads.
    if(w.count4!=0){
        if(hasIniSectionHot(w,hash))value=&hotValue(w);
        else if(auto* entry=findIniSectionIndex(w,hash,s)){updateHot(w,entry,s);value=&hotValue(w);}
    }
    auto* section=*value;return section?section->count30:0;
}
const char* iniEnumerationKey(IniSectionIndex& w,std::optional<std::string_view> name,std::int32_t index,const IniEnumerationServices& s){
    if(!name)return nullptr;
    const auto hash=iniSectionNameCrc(*name);
    if(w.count4==0)return nullptr;
    if(!hasIniSectionHot(w,hash)){
        auto* entry=findIniSectionIndex(w,hash,s);if(!entry)return nullptr;updateHot(w,entry,s);
    }
    auto* section=iniSectionValue(w,hash,s);
    if(!section||index>=section->count30)return nullptr;
    auto* node=section->head18;std::size_t links=0;
    while(node){
        if(links++>=s.maximumLinks)throw std::invalid_argument("INI list exceeds supplied traversal backing");
        auto* next=node->next4;if(!next||!node->previous8)return nullptr;
        if(index==0)return node->nameC;
        node=next;index=std::bit_cast<std::int32_t>(std::uint32_t(index)-1);
    }
    return nullptr;
}
}
