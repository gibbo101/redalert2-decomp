// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/IniEnumeration.hpp"
namespace ra2 {
enum class IniListDispatch : std::uint8_t { supplied=0, base=1, entries=2 };
struct IniRecordList {
    IniListDispatch dispatch0=IniListDispatch::supplied;
    IniEntryLink head4;
    IniEntryLink tail10;
};
struct IniRecordEntry {
    IniEntryLink link;
    const char* value10=nullptr;
    const void* comments14=nullptr;
    const char* comment18=nullptr;
    std::int32_t metadata1C=0,metadata20=0,metadata24=0;
};
struct IniRecordArguments {
    const char* name=nullptr;
    const char* value=nullptr;
    const void* comments=nullptr;
    const char* comment=nullptr;
    std::int32_t metadata24=0,metadata1C=0,metadata20=0;
};
struct IniRecordServices {
    std::function<void(const void*)> release;
    // Post-store observation; native pointer identities and symbolic dispatch
    // replace original addresses. All participating links must be mutable owners.
    std::function<void(const void*,std::int32_t,std::uint32_t,const void*)> store;
    std::size_t maximumMembers=0;
};
// Complete40E160/40E180/40E1D0. Null insertion and unsafe late null writes refuse.
IniEntryLink& constructIniRecordNode(IniEntryLink&,const IniRecordServices&);
void insertIniRecordAfter(IniEntryLink&,IniEntryLink*,const IniRecordServices&);
IniEntryLink& destroyIniRecordNode(IniEntryLink&,std::uint32_t,const IniRecordServices&);
// Complete490E80/510BB0/510C20. Cleanup unlinks members, never deletes them.
IniRecordList& constructIniRecordList(IniRecordList&,bool entryList,const IniRecordServices&);
IniRecordList& destroyIniRecordList(IniRecordList&,std::uint32_t,const IniRecordServices&);
// Complete510B60; arguments are borrowed live caller fields, not snapshotted.
IniRecordEntry& constructIniRecordEntry(IniRecordEntry&,const IniRecordArguments&,const IniRecordServices&);
}
