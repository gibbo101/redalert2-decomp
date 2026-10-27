// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/IniIndexStorage.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <iostream>
#include <sstream>
#include <vector>
using namespace ra2;
void require(bool v){if(!v)throw std::invalid_argument("INI index fixture differs");}
template<class E> void run(const std::array<int,12>& f){
 using T=typename IniIndexTraits<E>::Payload;
 std::array<T,4> owners{};std::array<std::array<E,32>,4> arrays{};
 const auto payload=[&](int i)->T*{return i?&owners.at(i-1):nullptr;};
 const auto valueId=[&](const void* p)->unsigned{if(!p)return 0;for(unsigned i=0;i<4;++i)if(p==&owners[i])return i+1;throw std::invalid_argument("Unknown INI payload identity");};
 std::uint32_t query=std::uint32_t(f[7]);T* input=payload(1);E detached{query,payload(2)};
 const auto pid=[&](const void* p)->unsigned{if(!p)return 0;if(p==&detached)return 500;for(unsigned a=0;a<4;++a)for(unsigned i=0;i<32;++i)if(p==&arrays[a][i])return 100+a*100+i;throw std::invalid_argument("Unknown INI index slot identity");};
 const auto valueSlotId=[&](T** p)->unsigned{if(p==&input)return 998;for(unsigned a=0;a<4;++a)for(unsigned i=0;i<32;++i)if(p==&IniIndexTraits<E>::value(arrays[a][i]))return 100+a*100+i;if(p==&IniIndexTraits<E>::value(detached))return 500;throw std::invalid_argument("Unknown INI borrowed value slot");};
 const std::array<std::array<unsigned,4>,4> hashes{{{0,0x80000000,0x7fffffff,16},{0x80000000,0,16,0x7fffffff},{42,42,42,42},{0x7fffffff,16,0,0x80000000}}};
 for(auto& a:arrays)for(auto& e:a){e.hash=0xa5a5a5a5;IniIndexTraits<E>::value(e)=nullptr;}
 for(unsigned i=0;i<4;++i){arrays[0][i]={hashes[f[2]][i],payload(i+1)};arrays[1][i]={hashes[f[2]][3-i],payload(4-i)};}
 std::span<E> backing(arrays[0]);int count=f[3],capacity=f[4];std::uint8_t sorted=std::uint8_t(f[5]);E* hot=f[6]==0?nullptr:f[6]==1?&arrays[0][0]:f[6]==2?&arrays[0][3]:f[6]==3?&arrays[1][1]:&detached;T* fallback=payload(4);
 IniIndexStorage<E> w{backing,count,capacity,sorted,hot,fallback};unsigned allocated=0,freed=0,sorts=0,mutated=0;
 std::vector<std::uint64_t> trace;const auto event=[&](std::uint64_t k,std::uint64_t a=0,std::uint64_t b=0,std::uint64_t c=0,std::uint64_t d=0){trace.insert(trace.end(),{k,a,b,c,d});};
 const auto mutate=[&](int where){if(mutated||f[10]!=where)return;mutated=1;event(6,where);
  if(where==1){backing=arrays[1];count=1;capacity=3;}
  if(where==2){backing=arrays[1];count=2;capacity=-1;}
  if(where==3){backing=arrays[1];count=2;query=0x80000000;}
  if(where==4){backing=arrays[1];count=1;}
  if(where==5){query=0x80000000;input=payload(3);IniIndexTraits<E>::value(arrays[0][0])=payload(4);}
  if(where==6)capacity=-3;
  if(where==7)count=3;
  if(where==8){hot=&arrays[1][1];count=1;query=0;}
  if(where==9)count=INT32_MIN;
 };
 IniIndexStorageServices<E> s;
 s.allocate=[&](unsigned bytes)->std::span<E>{++allocated;auto result=f[9]==1?std::span<E>{}:f[9]==2?backing:std::span<E>(arrays[allocated==1?2:3]);event(3,bytes,pid(result.data()));mutate(1);return result;};
 s.release=[&](auto old){++freed;event(4,pid(old.data()));mutate(2);};
 s.sort=[&](auto old,int n){++sorts;event(5,pid(old.data()),std::uint32_t(n));require(n>=0&&unsigned(n)<=old.size());std::stable_sort(old.begin(),old.begin()+n,[](auto& a,auto& b){return std::bit_cast<int>(a.hash)<std::bit_cast<int>(b.hash);});mutate(3);};
 s.store=[&](int off,unsigned v,const void* p){event(1,off,v,pid(p));if(off==0)mutate(6);if(off==0xc&&v==0)mutate(7);if(off==0x10&&!p)mutate(8);};
 s.entryStore=[&](E* e,int off,unsigned v,const void* p){event(2,pid(e),off,v,valueId(p));if(off==0){mutate(4);mutate(5);}else mutate(9);};
 for(int i=0;i<f[11];++i){unsigned result=0,value=0;
  switch(f[1]){case 0:constructIniIndex(w,s);result=1;break;case 1:result=appendIniIndex(w,query,input,s);break;case 2:result=growIniIndex(w,f[8],s);break;case 3:result=containsIniIndex(w,query,s);break;case 4:{auto& slot=iniIndexValue(w,query,s);result=&slot==&fallback?999:valueSlotId(&slot);value=valueId(slot);break;}case 5:result=pid(findIniIndex(w,query,s));break;}
  event(7,result,value);
 }
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<pid(backing.data())<<' '<<std::uint32_t(count)<<' '<<std::uint32_t(capacity)<<' '<<unsigned(sorted)<<' '<<pid(hot)<<' '<<valueId(fallback)<<' '<<query<<' '<<valueId(input)<<' '<<allocated<<' '<<freed<<' '<<sorts<<' '<<mutated<<' ';
 for(auto& a:arrays)for(auto& e:a)std::cout<<e.hash<<' '<<valueId(IniIndexTraits<E>::value(e))<<' ';std::cout<<detached.hash<<' '<<valueId(IniIndexTraits<E>::value(detached))<<'\n';
}
void run(std::istream& in){
 std::array<int,12> f;for(auto& v:f)require(bool(in>>v));std::string tail;require(!(in>>tail));
 require(f[0]>=0&&f[0]<2&&f[1]>=0&&f[1]<6&&f[2]>=0&&f[2]<4&&f[5]>=0&&f[5]<=255&&f[6]>=0&&f[6]<5&&f[9]>=0&&f[9]<3&&f[10]>=0&&f[10]<10&&f[11]>=1&&f[11]<=2);
 if(f[0])run<IniSectionIndexEntry>(f);else run<IniKeyIndexEntry>(f);
}
void guards(){
 std::array<IniKeyIndexEntry,16> entries{};std::span<IniKeyIndexEntry> backing;int count=0,capacity=0;std::uint8_t sorted=0;IniKeyIndexEntry* hot=nullptr;IniRecordEntry* fallback=nullptr;IniIndexStorage<IniKeyIndexEntry> w{backing,count,capacity,sorted,hot,fallback};IniIndexStorageServices<IniKeyIndexEntry> s;
 constructIniIndex(w,s);require(!growIniIndex(w,-1,s));bool refused=false;try{growIniIndex(w,1,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 IniRecordList list;IniRecordEntry first,second;IniRecordServices recordServices;constructIniRecordList(list,true,recordServices);constructIniRecordEntry(first,{"zeta","one"},recordServices);constructIniRecordEntry(second,{"alpha","two"},recordServices);insertIniRecordAfter(*list.tail10.previous8,&first.link,recordServices);insertIniRecordAfter(*list.tail10.previous8,&second.link,recordServices);
 s.allocate=[&](unsigned bytes){require(bytes==80);return std::span<IniKeyIndexEntry>(entries);};s.release=[](auto old){require(!old.data());};s.sort=[](auto old,int n){std::stable_sort(old.begin(),old.begin()+n,[](auto a,auto b){return std::bit_cast<int>(a.hash)<std::bit_cast<int>(b.hash);});};
 require(appendIniIndex(w,iniSectionNameCrc("zeta"),&first,s)&&appendIniIndex(w,iniSectionNameCrc("alpha"),&second,s));require(count==2&&capacity==10&&iniIndexValue(w,iniSectionNameCrc("alpha"),s)==&second&&list.head4.next4==&first.link);
 // Existing Section lookup borrows exactly the same fields after actual reserve.
 std::array<IniSectionIndexEntry,2> old{{{42,nullptr},{0,nullptr}}};std::array<IniSectionIndexEntry,4> grown{};std::span<IniSectionIndexEntry> sections(old);int sectionCount=1,sectionCapacity=2;std::uint8_t sectionSorted=1;auto* sectionHot=&old[0];IniEnumerationSection section{},*sectionFallback=nullptr;old[0].section=&section;
 IniIndexStorage<IniSectionIndexEntry> sw{sections,sectionCount,sectionCapacity,sectionSorted,sectionHot,sectionFallback};IniIndexStorageServices<IniSectionIndexEntry> ss;ss.allocate=[&](unsigned n){require(n==32);return std::span<IniSectionIndexEntry>(grown);};ss.release=[&](auto oldSpan){require(oldSpan.data()==old.data());};require(growIniIndex(sw,2,ss));IniSectionIndex existing{sections,sectionCount,sectionSorted,sectionHot,sectionFallback};require(iniSectionValue(existing,42,{})==&section&&sectionCapacity==4&&sections.data()==grown.data());
 backing={};count=-1;capacity=0;refused=false;try{appendIniIndex(w,0u,&first,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 std::cout<<"ini index guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string text;while(std::getline(std::cin,text)){std::istringstream in(text);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
