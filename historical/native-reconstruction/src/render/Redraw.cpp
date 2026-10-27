// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/Redraw.hpp"
#include <bit>
#include <limits>
#include <stdexcept>

namespace ra2 {
namespace {
int add(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
int sub(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
int product(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)*std::uint32_t(b));}
bool same(PixelRect a,PixelRect b){return a.x==b.x&&a.y==b.y&&a.width==b.width&&a.height==b.height;}
void event(const RedrawTrace& trace,char k,int value,int i=-1,int field=-1){if(trace)trace({k,i,field,value});}
void store(DirtyRegionQueue& q,int i,DirtyRegion value,const RedrawTrace& trace){
    q.slots.at(i)=value;
    const int words[]={value.bounds.x,value.bounds.y,value.bounds.width,value.bounds.height,value.flag};
    for(int n=0;n<5;++n)event(trace,'s',words[n],i,n);
}
}
void requestMapRedrawZero(std::uint8_t* tactical,const RedrawTrace& trace){
    if(tactical){*tactical=1;event(trace,'t',1);}
}
void requestMapRedraw(RedrawState& state,int mode,const RedrawTrace& trace){
    requestMapRedrawZero(state.tacticalPresent?&state.tactical:nullptr,trace);
    if(mode){
        if(state.mapMode!=2){state.mapMode=mode;event(trace,'m',mode);}
        state.counter=std::uint8_t(state.counter+1);event(trace,'c',state.counter);
    }
}
void requestObjectRedraw(std::uint8_t& needsRedraw,RedrawState& state,const RedrawTrace& trace){
    if(needsRedraw)return;
    needsRedraw=1;event(trace,'r',1);requestMapRedraw(state,0,trace);
}
PixelRect unionDirtyBounds(PixelRect a,PixelRect b){
    if(a.width<=0||a.height<=0)return b;
    if(b.width<=0||b.height<=0)return a;
    if(a.x>b.x){a.width=add(a.width,sub(a.x,b.x));a.x=b.x;}
    if(a.y>b.y){a.height=add(a.height,sub(a.y,b.y));a.y=b.y;}
    if(add(a.x,a.width)<add(b.x,b.width))a.width=add(add(sub(b.x,a.x),b.width),1);
    if(add(a.y,a.height)<add(b.y,b.height))a.height=add(add(sub(b.y,a.y),b.height),1);
    return a;
}
void registerDirtyRegion(DirtyRegionQueue& q,DirtyRegion incoming,const DirtyRegionGrowth& grow,
                         const RedrawTrace& trace){
    if(q.count<0||std::size_t(q.count)>q.slots.size()||q.slots.size()>std::size_t(std::numeric_limits<int>::max()))
        throw std::invalid_argument("Invalid dirty-region storage/count");
    int best=-1,bestArea=std::numeric_limits<int>::max();
    for(int i=0;i<q.count;++i){
        const auto old=q.slots[i];
        const auto intersection=intersectDrawBounds(old.bounds,incoming.bounds);
        const auto combined=unionDirtyBounds(old.bounds,incoming.bounds);
        if(intersection.width<=0||intersection.height<=0)continue;
        if(same(intersection,incoming.bounds)){
            if(!incoming.flag||old.flag)return;
        }else if(same(intersection,old.bounds)){
            if(!incoming.flag&&old.flag)continue;
            --q.count;event(trace,'n',q.count);
            for(int j=i;j<q.count;++j)store(q,j,q.slots[j+1],trace);
            --i;
        }else{
            const int area=product(combined.width,combined.height);
            const int separate=add(product(old.bounds.width,old.bounds.height),
                                   product(incoming.bounds.width,incoming.bounds.height));
            if(area<separate&&area<bestArea){best=i;bestArea=area;}
        }
    }
    if(best!=-1){
        const auto old=q.slots[best];
        // Final helper receives incoming first, unlike the in-loop area estimate.
        store(q,best,{unionDirtyBounds(incoming.bounds,old.bounds),std::uint8_t(incoming.flag||old.flag)},trace);
        return;
    }
    const int capacity=int(q.slots.size());
    if(q.count>=capacity){
        if((!q.ownsAllocation&&capacity)||q.growth<=0)return;
        const int requested=add(capacity,q.growth);
        if(requested<capacity)throw std::invalid_argument("Dirty-region growth overflows native storage domain");
        if(!grow)throw std::invalid_argument("Dirty-region allocation service required");
        if(!grow(q,requested))return;
        if(q.slots.size()!=std::size_t(requested))throw std::invalid_argument("Dirty-region allocator returned wrong capacity");
    }
    const int index=q.count++;
    event(trace,'n',q.count);store(q,index,incoming,trace);
}
}
