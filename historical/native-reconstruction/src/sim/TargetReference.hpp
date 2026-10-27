// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <functional>
#include <span>
#include <stdexcept>
#include <utility>
namespace ra2 {
struct TargetReference {std::int32_t value=0;std::uint8_t tag=0;std::array<std::uint8_t,3> padding{};};
struct TargetRegistryEntry {std::int32_t key=0;const void* object=nullptr;};
struct TargetReferenceCell {const std::int16_t& x;const std::int16_t& y;};
struct TargetReferenceWorld {
    const std::int32_t& count;
    const std::span<TargetRegistryEntry>& entries;
    std::uint8_t& sorted;
    TargetRegistryEntry*& cached;
    const void* const& fallback;
    // Named virtual2C and secondary-interface+10. The latter receives the
    // original object identity; its adapter supplies object+4 as the receiver.
    std::function<std::int32_t(const void*)> kind;
    std::function<std::int32_t(const void*)> uniqueID;
    std::function<TargetReferenceCell(const void*)> cell24;
    // Read-only sort comparison observer, never an alternative comparison.
    std::function<void(std::size_t,std::size_t,std::int32_t,std::int32_t)> compare;
};
inline int compareTargetRegistryKeys(std::int32_t a,std::int32_t b){return a==b?0:a<b?-1:1;}
// Complete781D46/781E9A/781EE8 algorithm specialized to the actual eight-byte
// guest entries and pure41BA10 signed-key comparator. Host pointers stay native.
inline void sortTargetRegistry(std::span<TargetRegistryEntry> entries,const TargetReferenceWorld& w){
    using Index=std::ptrdiff_t;
    // Keep guest byte distances positive and nonwrapping in the owned domain.
    if(entries.size()>0x0fffffff)throw std::invalid_argument("Target registry exceeds nonwrapping guest extent");
    if(entries.size()<2)return;
    const auto compare=[&](Index a,Index b){
        const auto left=entries[std::size_t(a)].key,right=entries[std::size_t(b)].key;
        if(w.compare)w.compare(std::size_t(a),std::size_t(b),left,right);
        return compareTargetRegistryKeys(left,right);
    };
    const auto swap=[&](Index a,Index b){if(a!=b)std::swap(entries[std::size_t(a)],entries[std::size_t(b)]);};
    std::array<std::pair<Index,Index>,30> pending{};std::size_t depth=0;
    Index low=0,high=Index(entries.size()-1);
    for(;;){
        const auto size=high-low+1;
        if(size<=8){
            for(auto end=high;end>low;--end){
                auto maximum=low;
                for(auto i=low+1;i<=end;++i)if(compare(i,maximum)>0)maximum=i;
                swap(maximum,end);
            }
        }else{
            swap(low+size/2,low);
            auto left=low,right=high+1;
            for(;;){
                do{++left;}while(left<=high&&compare(left,low)<=0);
                do{--right;}while(right>low&&compare(right,low)>=0);
                if(right<left)break;
                swap(left,right);
            }
            swap(right,low);
            const auto push=[&](Index a,Index b){
                if(depth==pending.size())throw std::invalid_argument("Target registry sort exceeds original stack domain");
                pending[depth++]={a,b};
            };
            // Original compares byte distances: (right-low)*8-1 vs (high-left)*8.
            if((right-low)*8-1<(high-left)*8){
                if(left<high)push(left,high);
                if(low+1<right){high=right-1;continue;}
            }else{
                if(low+1<right)push(low,right-1);
                if(left<high){low=left;continue;}
            }
        }
        if(!depth)return;
        const auto range=pending[--depth];low=range.first;high=range.second;
    }
}
inline std::int32_t targetReferenceKind(const void* p,const TargetReferenceWorld& w){
    if(!p||!w.kind)throw std::invalid_argument("Target reference needs owned object kind");
    return w.kind(p);
}
// Complete40DC20. These are the four exact accepted kinds from the pinned table.
inline const void* castTargetTechno(const void* p,const TargetReferenceWorld& w){
    if(!p)return nullptr;
    const auto kind=targetReferenceKind(p,w);
    return kind==1||kind==2||kind==6||kind==15?p:nullptr;
}
// Complete6B54A0. Padding is retained; tag stores precede the virtual ID query.
inline TargetReference* makeTargetReference(TargetReference& out,const void* p,const TargetReferenceWorld& w){
    if(!p){out.tag=0;out.value=0;return &out;}
    if(targetReferenceKind(p,w)==11){
        out.tag=11;
        if(!w.cell24)throw std::invalid_argument("Target reference needs Cell words");
        const auto cell=w.cell24(p);out.value=std::int32_t(cell.x)+1000*std::int32_t(cell.y);
    }else{
        out.tag=52;
        if(!w.uniqueID)throw std::invalid_argument("Target reference needs secondary-interface ID");
        out.value=w.uniqueID(p);
    }
    return &out;
}
inline std::span<TargetRegistryEntry> activeTargetRegistry(const TargetReferenceWorld& w,std::int32_t count){
    if(count<0||std::size_t(count)>w.entries.size())throw std::invalid_argument("Target registry exceeds supplied backing");
    return w.entries.first(std::size_t(count));
}
// Complete6B5910, including cache-before-sort and actual signed binary search.
inline const void* resolveTargetReference(const TargetReference& token,const TargetReferenceWorld& w){
    if(token.tag!=52)return nullptr;
    auto count=w.count;
    if(count!=0){
        if(w.cached&&w.cached->key==token.value)return castTargetTechno(w.cached->object,w);
        if(!w.sorted){
            // Original treats the qsort count as unsigned. Negative lengths are
            // explicitly refused rather than becoming a large host allocation.
            sortTargetRegistry(activeTargetRegistry(w,count),w);
            count=w.count;w.cached=nullptr;w.sorted=1;
        }
        const auto key=token.value;
        auto entries=w.entries;
        if(count>0){
            if(std::size_t(count)>entries.size())throw std::invalid_argument("Target registry search exceeds supplied backing");
            std::size_t base=0;
            while(count>0){
                const auto middle=count/2;auto& entry=entries[base+std::size_t(middle)];
                if(entry.key>key)count=middle;
                else if(entry.key==key){w.cached=&entry;return castTargetTechno(entry.object,w);}
                else{base+=std::size_t(middle)+1;count-=middle+1;}
            }
        }
    }
    return castTargetTechno(w.fallback,w);
}
}
