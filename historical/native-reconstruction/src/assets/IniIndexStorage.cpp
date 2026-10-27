// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/IniIndexStorage.hpp"
#include <bit>
namespace ra2 {
namespace {
std::int32_t add(std::int32_t a,std::int32_t b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
template<class E> void emit(const IniIndexStorageServices<E>& s,int off,std::uint32_t value=0,const void* p=nullptr){if(s.store)s.store(off,value,p);}
template<class E> void emitEntry(const IniIndexStorageServices<E>& s,E& e,int off,std::uint32_t value=0,const void* p=nullptr){if(s.entryStore)s.entryStore(&e,off,value,p);}
template<class E> E& slot(std::span<E> backing,std::int32_t index){
    // Original address arithmetic wraps at32 bits before resolving backing.
    const auto offset=(std::uint32_t(index)*8u)/8u;
    if(offset>=backing.size())throw std::invalid_argument("INI index slot exceeds supplied physical backing");
    return backing[offset];
}
template<class E> void setHot(IniIndexStorage<E> w,E* hot,const IniIndexStorageServices<E>& s){w.hot10=hot;emit(s,0x10,0,hot);}
template<class E> void ensureSorted(IniIndexStorage<E> w,const IniIndexStorageServices<E>& s){
    if(w.sortedC)return;
    if(!s.sort)throw std::invalid_argument("INI index sort child unbound");
    const auto backing=w.backing;const auto count=w.count4;
    if(count<0||std::size_t(count)>backing.size())throw std::invalid_argument("INI index sort outside supplied backing");
    s.sort(backing,count);
    setHot(w,static_cast<E*>(nullptr),s);
    w.sortedC=1;emit(s,0xc,1);
}
template<class E> E* search(IniIndexStorage<E> w,const std::uint32_t& query){
    auto count=w.count4;const auto key=std::bit_cast<std::int32_t>(query);const auto backing=w.backing;
    if(count<=0)return nullptr;
    if(std::size_t(count)>backing.size())throw std::invalid_argument("INI search outside supplied physical backing");
    std::size_t first=0;
    while(count>0){
        const auto half=count/2;auto* candidate=&backing[first+std::size_t(half)];
        const auto hash=std::bit_cast<std::int32_t>(candidate->hash);
        if(hash>key)count=half;
        else if(hash==key)return candidate;
        else{first+=std::size_t(half)+1;count-=half+1;}
    }
    return nullptr;
}
template<class E> bool hotMatches(IniIndexStorage<E> w,const std::uint32_t& query){return w.hot10&&w.hot10->hash==query;}
template<class E> typename IniIndexTraits<E>::Payload*& hotValue(IniIndexStorage<E> w){
    if(!w.hot10)throw std::invalid_argument("INI hot value disappeared after store");
    return IniIndexTraits<E>::value(*w.hot10);
}
}
template<class E> void constructIniIndex(IniIndexStorage<E> w,const IniIndexStorageServices<E>& s){
    w.backing={};emit(s,0);
    w.count4=0;emit(s,4);
    w.capacity8=0;emit(s,8);
    w.sortedC=0;emit(s,0xc);
    setHot(w,static_cast<E*>(nullptr),s);
}
template<class E> bool growIniIndex(IniIndexStorage<E> w,std::int32_t increment,const IniIndexStorageServices<E>& s){
    if(increment<0)return false;
    if(!s.allocate)throw std::invalid_argument("INI index allocation unbound");
    const auto bytes=std::uint32_t(add(w.capacity8,increment))*8u;
    const auto allocated=s.allocate(bytes);
    if(!allocated.data())return false;
    std::int32_t i=0;
    while(i<w.count4){
        // Save this source slot, not the whole entry or the backing for later
        // iterations. The value read follows the destination key store.
        auto& source=slot(w.backing,i);auto& destination=slot(allocated,i);
        const auto hash=source.hash;destination.hash=hash;emitEntry(s,destination,0,hash);
        auto* value=IniIndexTraits<E>::value(source);IniIndexTraits<E>::value(destination)=value;emitEntry(s,destination,4,0,value);
        i=add(i,1);
    }
    if(!s.release)throw std::invalid_argument("INI index release unbound");
    s.release(w.backing);
    const auto capacity=add(w.capacity8,increment);
    w.backing=allocated;emit(s,0,0,allocated.data());
    w.capacity8=capacity;emit(s,8,std::uint32_t(capacity));
    setHot(w,static_cast<E*>(nullptr),s);
    return true;
}
template<class E> bool appendIniIndex(IniIndexStorage<E> w,const std::uint32_t& hash,typename IniIndexTraits<E>::Payload* const& value,const IniIndexStorageServices<E>& s){
    if(add(w.count4,1)>w.capacity8){
        const auto increment=w.capacity8==0?10:w.capacity8;
        if(!growIniIndex(w,increment,s))return false;
    }
    auto& keySlot=slot(w.backing,w.count4);const auto savedHash=hash;
    keySlot.hash=savedHash;emitEntry(s,keySlot,0,savedHash);
    auto& valueSlot=slot(w.backing,w.count4);auto* savedValue=value;
    IniIndexTraits<E>::value(valueSlot)=savedValue;emitEntry(s,valueSlot,4,0,savedValue);
    const auto count=add(w.count4,1);
    w.sortedC=0;emit(s,0xc);
    w.count4=count;emit(s,4,std::uint32_t(count));
    return true;
}
template<class E> E* findIniIndex(IniIndexStorage<E> w,const std::uint32_t& query,const IniIndexStorageServices<E>& s){
    if(w.count4==0)return nullptr;
    ensureSorted(w,s);return search(w,query);
}
template<class E> bool containsIniIndex(IniIndexStorage<E> w,const std::uint32_t& query,const IniIndexStorageServices<E>& s){
    if(w.count4==0)return false;
    if(hotMatches(w,query))return true;
    ensureSorted(w,s);
    if(auto* entry=search(w,query)){setHot(w,entry,s);return true;}
    return false;
}
template<class E> typename IniIndexTraits<E>::Payload*& iniIndexValue(IniIndexStorage<E> w,const std::uint32_t& query,const IniIndexStorageServices<E>& s){
    if(w.count4==0)return w.fallback;
    if(hotMatches(w,query))return hotValue(w);
    ensureSorted(w,s);
    if(auto* entry=search(w,query)){setHot(w,entry,s);return hotValue(w);}
    return w.fallback;
}
#define RA2_INSTANTIATE_INI_INDEX(E) \
 template void constructIniIndex(IniIndexStorage<E>,const IniIndexStorageServices<E>&); \
 template bool growIniIndex(IniIndexStorage<E>,std::int32_t,const IniIndexStorageServices<E>&); \
 template bool appendIniIndex(IniIndexStorage<E>,const std::uint32_t&,IniIndexTraits<E>::Payload* const&,const IniIndexStorageServices<E>&); \
 template bool containsIniIndex(IniIndexStorage<E>,const std::uint32_t&,const IniIndexStorageServices<E>&); \
 template IniIndexTraits<E>::Payload*& iniIndexValue(IniIndexStorage<E>,const std::uint32_t&,const IniIndexStorageServices<E>&); \
 template E* findIniIndex(IniIndexStorage<E>,const std::uint32_t&,const IniIndexStorageServices<E>&);
RA2_INSTANTIATE_INI_INDEX(IniKeyIndexEntry)
RA2_INSTANTIATE_INI_INDEX(IniSectionIndexEntry)
#undef RA2_INSTANTIATE_INI_INDEX
}
