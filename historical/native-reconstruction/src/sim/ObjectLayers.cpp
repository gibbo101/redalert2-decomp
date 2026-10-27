// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/ObjectLayers.hpp"
#include <bit>
#include <limits>
#include <stdexcept>
namespace ra2 {
static void emit(const ObjectLayerTrace& t,char k,std::int64_t a,std::int64_t b=0,std::int64_t c=0){if(t)t({k,a,b,c});}
std::int32_t terrainSortKey(Coord p){return std::bit_cast<std::int32_t>(std::uint32_t(p.x)+std::uint32_t(p.y));}
int ObjectLayers::sortKey(int id,const ObjectLayerTrace& t) const {
    // Original GetYSort invokes the coordinate getter twice, even for one actor.
    emit(t,'c',id);emit(t,'c',id);return terrainSortKey(actors.at(id).position);
}
bool ObjectLayers::ensureCapacity(int index,const ObjectLayerTrace& t) {
    auto& l=layers.at(std::size_t(index));
    if(l.count<0||std::size_t(l.count)>l.slots.size())throw std::invalid_argument("Invalid layer count");
    if(std::size_t(l.count)<l.slots.size())return true;
    if((!l.owned&&!l.slots.empty())||l.growBy<=0)return false;
    const auto size=std::int64_t(l.slots.size())+l.growBy;
    if(size>1000000)throw std::invalid_argument("Layer allocation outside bounded profile");
    l.valid=0;emit(t,'v',index,0);emit(t,'A',index,size*4);
    l.valid=1;emit(t,'v',index,1);
    if(!allocationSucceeds)return false;
    std::vector<int> replacement(std::size_t(size),-3); // Host allocator canary in vectors; unused at runtime.
    for(std::size_t i=0;i<l.slots.size();++i){replacement[i]=l.slots[i];emit(t,'W',index,i,replacement[i]);}
    if(l.storageId!=-1&&l.owned){emit(t,'F',index,l.storageId);l.storageId=-1;emit(t,'P',index,-1);}
    l.storageId=nextStorageId++;emit(t,'P',index,l.storageId);
    l.slots=std::move(replacement);emit(t,'K',index,size);
    l.owned=1;emit(t,'o',index,1);return true;
}
bool ObjectLayers::insert(int index,int id,bool sorted,const ObjectLayerTrace& t) {
    actors.at(id);if(!ensureCapacity(index,t))return false;
    auto& l=layers.at(std::size_t(index));
    if(sorted){
        int at=0;
        while(at<l.count){const auto candidate=sortKey(id,t);const auto existing=sortKey(l.slots.at(std::size_t(at)),t);if(existing>candidate)break;++at;}
        for(int i=l.count;i>at;--i){l.slots[std::size_t(i)]=l.slots[std::size_t(i-1)];emit(t,'W',index,i,l.slots[std::size_t(i)]);}
        l.slots[std::size_t(at)]=id;emit(t,'W',index,at,id);++l.count;emit(t,'N',index,l.count);
    }else{
        const auto at=l.count++;emit(t,'N',index,l.count);l.slots[std::size_t(at)]=id;emit(t,'W',index,at,id);
    }
    return true;
}
bool ObjectLayers::eraseFirst(int index,int id,const ObjectLayerTrace& t) {
    auto& l=layers.at(std::size_t(index));
    int at=0;while(at<l.count&&l.slots.at(std::size_t(at))!=id)++at;
    if(at==l.count)return false;
    --l.count;emit(t,'N',index,l.count);
    for(int i=at;i<l.count;++i){l.slots[std::size_t(i)]=l.slots[std::size_t(i+1)];emit(t,'W',index,i,l.slots[std::size_t(i)]);}
    return true; // Deliberately retain the old final slot beyond the active count.
}
void ObjectLayers::remove(int id,const ObjectLayerTrace& t) {
    if(id==-1)return;
    auto& actor=actors.at(id);if(actor.lastLayer==-1)return;
    if(eraseFirst(actor.lastLayer,id,t)){actor.lastLayer=-1;emit(t,'S',id,-1);return;}
    for(int layer=0;layer<5;++layer)while(eraseFirst(layer,id,t)){}
    actor.lastLayer=-1;emit(t,'S',id,-1);
}
void ObjectLayers::submit(int id,const ObjectLayerTrace& t) {
    if(id==-1)return;
    auto& actor=actors.at(id);if(actor.lastLayer!=-1)remove(id,t);
    emit(t,'I',id,2); // Ground Terrain only; original InWhichLayer executes in oracle.
    if(insert(2,id,true,t)){actor.lastLayer=2;emit(t,'S',id,2);}
}
}
