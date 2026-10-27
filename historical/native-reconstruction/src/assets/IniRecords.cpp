// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/IniRecords.hpp"
namespace ra2 {
namespace {
void emit(const IniRecordServices& s,const void* owner,std::int32_t off,std::uint32_t value=0,const void* pointer=nullptr){if(s.store)s.store(owner,off,value,pointer);}
void next(IniEntryLink& w,IniEntryLink* p,const IniRecordServices& s){w.next4=p;emit(s,&w,4,0,p);}
void previous(IniEntryLink& w,IniEntryLink* p,const IniRecordServices& s){w.previous8=p;emit(s,&w,8,0,p);}
void dispatch(IniEntryLink& w,IniNodeDispatch kind,const IniRecordServices& s){w.dispatch0=kind;emit(s,&w,0,std::uint32_t(kind));}
void dispatch(IniRecordList& w,IniListDispatch kind,const IniRecordServices& s){w.dispatch0=kind;emit(s,&w,0,std::uint32_t(kind));}
void detach(IniEntryLink& w,const IniRecordServices& s){
    auto* savedNext=w.next4;
    if(!savedNext)return;
    auto* savedPrevious=w.previous8;
    if(!savedPrevious)return;
    next(*savedPrevious,savedNext,s);
    // The first neighbor store may alias this node. Both fields are read again.
    auto* currentNext=w.next4;auto* currentPrevious=w.previous8;
    if(!currentNext)throw std::invalid_argument("INI detach late null neighbor write refused");
    previous(*currentNext,currentPrevious,s);
    previous(w,nullptr,s);
    next(w,nullptr,s);
}
void freeOwner(const void* owner,const IniRecordServices& s){
    if(!s.release)throw std::invalid_argument("INI record free child unbound");
    s.release(owner);
}
}
IniEntryLink& constructIniRecordNode(IniEntryLink& w,const IniRecordServices& s){
    next(w,nullptr,s);previous(w,nullptr,s);dispatch(w,IniNodeDispatch::base,s);return w;
}
void insertIniRecordAfter(IniEntryLink& anchor,IniEntryLink* node,const IniRecordServices& s){
    if(!node)throw std::invalid_argument("Original INI null insertion write refused");
    detach(*node,s);
    auto* savedNext=anchor.next4;
    previous(*node,&anchor,s);
    next(*node,savedNext,s);
    if(auto* currentNext=anchor.next4)previous(*currentNext,node,s);
    next(anchor,node,s);
}
IniEntryLink& destroyIniRecordNode(IniEntryLink& w,std::uint32_t flags,const IniRecordServices& s){
    dispatch(w,IniNodeDispatch::base,s);detach(w,s);
    if(flags&1)freeOwner(&w,s);
    return w;
}
IniRecordList& constructIniRecordList(IniRecordList& w,bool entryList,const IniRecordServices& s){
    constructIniRecordNode(w.head4,s);
    constructIniRecordNode(w.tail10,s);
    dispatch(w,IniListDispatch::base,s);
    insertIniRecordAfter(w.head4,&w.tail10,s);
    if(entryList)dispatch(w,IniListDispatch::entries,s);
    return w;
}
IniRecordList& destroyIniRecordList(IniRecordList& w,std::uint32_t flags,const IniRecordServices& s){
    dispatch(w,IniListDispatch::base,s);
    std::size_t visited=0;
    while(true){
        auto* member=w.head4.next4;
        if(!member||!member->next4||!member->previous8)break;
        if(visited++>=s.maximumMembers)throw std::invalid_argument("INI cleanup exceeds supplied member domain");
        detach(*member,s);
    }
    destroyIniRecordNode(w.tail10,0,s);
    destroyIniRecordNode(w.head4,0,s);
    if(flags&1)freeOwner(&w,s);
    return w;
}
IniRecordEntry& constructIniRecordEntry(IniRecordEntry& w,const IniRecordArguments& args,const IniRecordServices& s){
    const auto value=args.value;
    next(w.link,nullptr,s);previous(w.link,nullptr,s);
    const auto name=args.name;
    w.value10=value;emit(s,&w.link,0x10,0,value);
    const auto comment=args.comment;
    w.link.nameC=name;emit(s,&w.link,0xc,0,name);
    const auto comments=args.comments;
    w.comment18=comment;emit(s,&w.link,0x18,0,comment);
    const auto metadata20=args.metadata20;
    w.comments14=comments;emit(s,&w.link,0x14,0,comments);
    const auto metadata1C=args.metadata1C;
    w.metadata20=metadata20;emit(s,&w.link,0x20,std::uint32_t(metadata20));
    w.metadata1C=metadata1C;emit(s,&w.link,0x1c,std::uint32_t(metadata1C));
    w.metadata24=args.metadata24;emit(s,&w.link,0x24,std::uint32_t(w.metadata24));
    dispatch(w.link,IniNodeDispatch::entry,s);
    return w;
}
}
