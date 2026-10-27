// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TeamObserverDefinitions.hpp"
#include <algorithm>
namespace ra2 {
namespace {
template<class F> const F& child(const F& f){
    if(!f)throw std::invalid_argument("Observer definition child unbound");
    return f;
}
std::string_view identifier(const TeamObserverType& r){
    auto end=std::find(r.identifier24.begin(),r.identifier24.end(),0);
    if(end==r.identifier24.end())throw std::invalid_argument("Observer ID lacks terminator");
    return {reinterpret_cast<const char*>(r.identifier24.data()),std::size_t(end-r.identifier24.begin())};
}
}
void loadTeamObserverDefinitions(std::uint32_t mode,
        const TeamObserverDefinitionRegistry& registry,const TeamObserverDefinitionServices& s){
    constexpr std::string_view definitions="AITriggerTypes",enabled="AITriggerTypesEnable";
    const auto slot=[&](std::int32_t i){
        if(i<0||std::size_t(i)>=registry.slots.size())
            throw std::invalid_argument("Observer definition registry backing unbound");
        return registry.slots[std::size_t(i)];
    };
    const auto find=[&](std::string_view key)->std::optional<TeamObserverType*>{
        if(registry.count<=0)return {};
        for(std::int32_t i=0;;++i){
            const auto record=slot(i);
            if(!record)throw std::invalid_argument("Observer lookup dereferences null record");
            if(!child(s.compare)(identifier(*record),key))return slot(i);
            if(i+1>=registry.count)return {};
        }
    };
    const auto emit=[&](TeamObserverType& r,std::int64_t off,std::uint32_t size,std::uint32_t value){
        if(s.store)s.store(&r,off,size,value,nullptr);
    };
    const auto count=child(s.entryCount)(definitions);
    for(std::int32_t i=0;i<count;++i){
        const auto key=child(s.entryKey)(definitions,i);
        TeamObserverType* record=nullptr;
        if(child(s.compare)("<none>",key)&&child(s.compare)("none",key)){
            const auto match=find(key);
            if(match)record=*match;
            else if(auto* memory=child(s.allocate)(0x110))
                record=child(s.construct)(memory,key);
        }
        if(record){
            child(s.load)(*record); // original deliberately ignores the result
            record->value9C=mode;emit(*record,0x9c,4,mode);
        }
        if(mode==1){
            if(!record)throw std::invalid_argument("Original observer mode1 null store refused");
            record->byteA4=1;emit(*record,0xa4,1,1);
        }
    }
    if(mode)return;
    const auto enableCount=child(s.entryCount)(enabled);
    for(std::int32_t i=0;i<enableCount;++i){
        const auto key=child(s.entryKey)(enabled,i);
        const auto match=find(key);
        if(!match||!*match)continue;
        auto* record=*match;
        const auto raw=child(s.boolean)(enabled,key,false);
        record->byteA4=std::uint8_t(raw)!=0||s.sessionA3D298!=0;
        emit(*record,0xa4,1,record->byteA4);
    }
}
}
