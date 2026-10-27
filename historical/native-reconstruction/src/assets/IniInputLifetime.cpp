// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/IniInputLifetime.hpp"
namespace ra2 {
namespace {
void emit(const IniInputLifetimeServices& s,const void* owner,std::int32_t offset,std::int64_t value=0,const void* pointer=nullptr){
    if(s.store)s.store(owner,offset,value,pointer);
}
void assignSource(IniInputPipeOwner& w,IniInputPipeOwner* p,const IniInputLifetimeServices& s){w.source4=p;emit(s,&w,4,0,p);}
void assignDownstream(IniInputPipeOwner& w,IniInputPipeOwner* p,const IniInputLifetimeServices& s){w.downstream8=p;emit(s,&w,8,0,p);}
void callAttach(IniInputPipeOwner& w,IniInputPipeOwner* p,const IniInputLifetimeServices& s){
    if(!s.attach)throw std::invalid_argument("INI downstream attachment unbound");
    s.attach(w,p);
}
}
IniInputBufferOwner& constructIniInputBuffer(IniInputBufferOwner& w,std::int32_t size,const IniInputLifetimeServices& s){
    w.data0=nullptr;emit(s,&w,0);
    w.size4=size;emit(s,&w,4,size);
    w.owned8=0;emit(s,&w,8);
    if(size>0){
        if(!s.allocate)throw std::invalid_argument("INI buffer allocation unbound");
        auto* data=s.allocate(size);
        w.data0=data;emit(s,&w,0,0,data);
        w.owned8=1;emit(s,&w,8,1);
    }
    return w;
}
void destroyIniInputBuffer(IniInputBufferOwner& w,const IniInputLifetimeServices& s){
    if(w.owned8){
        if(!s.release)throw std::invalid_argument("INI buffer release unbound");
        s.release(w.data0);
    }
    w.data0=nullptr;emit(s,&w,0);
    w.size4=0;emit(s,&w,4);
    w.owned8=0;emit(s,&w,8);
}
void attachIniInputSource(IniInputPipeOwner& w,IniInputPipeOwner* source,const IniInputLifetimeServices& s){
    if(w.source4==source)return;
    if(source){
        if(auto* downstream=source->downstream8){
            callAttach(*downstream,nullptr,s);
            assignDownstream(*source,nullptr,s);
        }
    }
    if(auto* previous=w.source4)assignDownstream(*previous,nullptr,s);
    assignSource(w,source,s);
    if(source)assignDownstream(*source,&w,s);
}
void destroyIniInputPipe(IniInputPipeOwner& w,const IniInputLifetimeServices& s){
    w.baseDispatch=true;emit(s,&w,0,1);
    if(auto* source=w.source4)assignDownstream(*source,w.downstream8,s);
    if(auto* downstream=w.downstream8)callAttach(*downstream,w.source4,s);
    assignDownstream(w,nullptr,s);
    assignSource(w,nullptr,s);
}
}
