// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/IniEnumeration.hpp"
#include "assets/IniRecords.hpp"
#include "assets/TeamObserverDefinitions.hpp"
#include "sim/StringLookup.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("INI observer composition differs");}
int main(){try{
 // Actual recovered list/entry construction and insertion. Text, index/count
 // projection and startup remain supplied in this native composition.
 IniRecordList list;IniRecordEntry first,second;IniRecordServices recordsServices;
 constructIniRecordList(list,true,recordsServices);
 constructIniRecordEntry(first,{"zeta","one"},recordsServices);
 constructIniRecordEntry(second,{"alpha","two"},recordsServices);
 insertIniRecordAfter(*list.tail10.previous8,&first.link,recordsServices);
 insertIniRecordAfter(*list.tail10.previous8,&second.link,recordsServices);
 IniEnumerationSection definitions{list.head4.next4,2};
 std::array<IniSectionIndexEntry,1> entries{{{iniSectionNameCrc("AITriggerTypes"),&definitions}}};
 std::span<IniSectionIndexEntry> indexBacking(entries);int indexCount=1;std::uint8_t sorted=0;IniSectionIndexEntry* hot=nullptr;IniEnumerationSection* fallback=nullptr;
 IniSectionIndex index{indexBacking,indexCount,sorted,hot,fallback};IniEnumerationServices ini;
 ini.maximumLinks=3;unsigned sorts=0;ini.sort=[&](auto saved,int count){require(saved.data()==entries.data()&&count==1);++sorts;};
 std::array<TeamObserverType,2> records;std::array<TeamObserverType*,2> registry{&records[0],&records[1]};
 for(unsigned i=0;i<2;++i){const std::string name=i?"alpha":"zeta";std::copy(name.begin(),name.end(),records[i].identifier24.begin());}
 int count=2,session=0;std::span<TeamObserverType*> backing(registry);
 TeamObserverDefinitionServices services{{},{},compareStringLookupKeys,{},{},{},{},session,{}};
 services.entryCount=[&](auto section){return iniEnumerationCount(index,section,ini);};
 services.entryKey=[&](auto section,int i){const auto* p=iniEnumerationKey(index,section,i,ini);require(p);return std::string_view(p);};
 std::vector<std::string> order;services.load=[&](auto& r){order.emplace_back(reinterpret_cast<const char*>(r.identifier24.data()));++r.valueB0;return false;};
 services.allocate=[](auto)->void*{throw std::invalid_argument("Existing INI records must be reused");};
 loadTeamObserverDefinitions(2,{count,backing},services);
 require(order==std::vector<std::string>{"zeta","alpha"}&&sorts==1&&hot==&entries[0]&&count==2);
 for(auto& r:records)require(r.value9C==2&&r.valueB0==1&&r.byteA4==0);
 // Querying both indices again retains the hot entry and linked order.
 require(std::string(iniEnumerationKey(index,"AITriggerTypes",0,ini))=="zeta");
 require(std::string(iniEnumerationKey(index,"AITriggerTypes",1,ini))=="alpha"&&sorts==1);
 std::cout<<"ini observer composition PASS\n";return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
