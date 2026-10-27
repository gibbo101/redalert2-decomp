// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/IniEnumeration.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <iostream>
#include <sstream>
#include <vector>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("INI enumeration fixture differs");}
std::string decode(const std::string& s){if(s=="-")return {};require(s.size()%2==0);std::string r;for(std::size_t i=0;i<s.size();i+=2)r.push_back(char(std::stoul(s.substr(i,2),nullptr,16)));return r;}
void run(std::istream& in){
 std::string raw;std::array<std::int64_t,9> f;require(bool(in>>raw));for(auto& v:f)require(bool(in>>v));std::string tail;require(!(in>>tail));
 require(f[0]>=0&&f[0]<7&&f[1]>=-1&&f[1]<=4&&f[2]>=0&&f[2]<=255&&f[3]>=0&&f[3]<5&&f[4]>=0&&f[4]<6&&f[5]>=INT32_MIN&&f[5]<=INT32_MAX&&f[6]>=0&&f[6]<7&&f[7]>=1&&f[7]<=2&&f[8]>=0&&f[8]<6);
 auto name=raw=="~"?std::optional<std::string>{}:std::optional<std::string>{decode(raw)};const auto hash=iniSectionNameCrc(name?*name:"");
 const auto signedLess=[](const IniSectionIndexEntry& a,const IniSectionIndexEntry& b){return std::bit_cast<std::int32_t>(a.hash)<std::bit_cast<std::int32_t>(b.hash);};
 const std::array<std::array<std::uint32_t,4>,7> hashes{{{hash,0x80000000u,0x7fffffffu,0},{0x80000000u,0,hash,0x7fffffffu},{hash,hash,hash,hash},{1,16,256,4096},{hash,0x80000000u,0x7fffffffu,0},{hash,0x80000000u,0x7fffffffu,0},{0xffffffffu,0xfffffffeu,0x80000000u,0x80000001u}}};
 std::array<IniEnumerationSection,4> sections;std::array<IniSectionIndexEntry,4> entries,alt;
 std::array<std::array<IniEntryLink,4>,4> nodes;const std::array<const char*,4> names{"zeta","alpha","middle","sentinel"};
 for(int i=0;i<4;++i){
  for(int j=0;j<4;++j)nodes[i][j]={j==3?nullptr:&nodes[i][j+1],j==3?nullptr:&nodes[i][j],names[j]};
  if(f[4]==2)nodes[i][0].next4=nullptr;if(f[4]==3)nodes[i][0].previous8=nullptr;if(f[4]==4)nodes[i][1].nameC=nullptr;
  if(f[4]==5){nodes[i][0].next4=&nodes[i][2];nodes[i][2].next4=&nodes[i][1];nodes[i][1].next4=&nodes[i][3];}
  sections[i]={f[4]==1?nullptr:&nodes[i][0],3+2*i};entries[i]={hashes[f[0]][i],&sections[i]};
 }
 if(f[0]==4)std::stable_sort(entries.begin(),entries.end(),signedLess);if(f[0]==5)std::stable_sort(entries.begin(),entries.end(),[&](auto a,auto b){return signedLess(b,a);});
 alt=entries;std::swap(alt[0],alt[1]);IniSectionIndexEntry detached{hash,&sections[1]};
 std::span<IniSectionIndexEntry> backing(entries);int count=int(f[1]);std::uint8_t sorted=std::uint8_t(f[2]);IniSectionIndexEntry* hot=f[3]==1?&entries[0]:f[3]==2?&entries[3]:f[3]==3?&alt[1]:f[3]==4?&detached:nullptr;IniEnumerationSection* fallback=&sections[3];
 const auto pid=[&](const void* p)->unsigned{if(!p)return 0;for(unsigned i=0;i<4;++i){if(p==&entries[i])return 101+i;if(p==&alt[i])return 201+i;if(p==&sections[i])return 1+i;}if(p==&detached)return 301;throw std::invalid_argument("INI fixture pointer unbound");};
 const auto keyId=[&](const char* p){if(!p)return 0u;for(unsigned i=0;i<4;++i)if(p==names[i])return i+1;throw std::invalid_argument("Unknown INI key pointer");};
 std::vector<std::uint64_t> trace;const auto event=[&](std::uint64_t k,std::uint64_t a=0,std::uint64_t b=0,std::uint64_t c=0){trace.insert(trace.end(),{k,a,b,c});};unsigned mutated=0;
 const auto mutate=[&](int where){if(mutated||f[6]!=where)return;mutated=1;event(3,where);
  if(where==1)backing=alt;
  if(where==2)count=1;
  if(where==3)hot=&alt[2];
  if(where==4)count=0;
  if(where==5)sorted=128;
  if(where==6&&hot)hot->section->count30=-1;};
 IniSectionIndex w{backing,count,sorted,hot,fallback};IniEnumerationServices s;
 s.maximumLinks=4;s.sort=[&](auto saved,int n){event(1,pid(saved.data()),std::uint32_t(n));std::stable_sort(saved.begin(),saved.begin()+n,signedLess);mutate(1);mutate(2);mutate(5);};
 s.store=[&](auto off,auto v,const void* p){event(2,off,v,pid(p));if(off==0x10&&p){mutate(3);mutate(4);mutate(6);}};
 for(int i=0;i<f[7];++i){std::uint32_t result=0;
  switch(f[8]){case 0:result=std::uint32_t(iniEnumerationCount(w,name?std::optional<std::string_view>(*name):std::nullopt,s));break;case 1:result=keyId(iniEnumerationKey(w,name?std::optional<std::string_view>(*name):std::nullopt,int(f[5]),s));break;case 2:result=pid(iniSectionValue(w,hash,s));break;case 3:result=pid(findIniSectionIndex(w,hash,s));break;case 4:result=hasIniSectionHot(w,hash);break;case 5:result=hash;break;}
  event(4,result);
 }
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<hash<<' '<<mutated<<' '<<std::uint32_t(count)<<' '<<unsigned(sorted)<<' '<<pid(hot)<<' '<<pid(backing.data())<<' ';
 for(const auto* group:{&entries,&alt})for(auto& e:*group)std::cout<<e.hash<<' '<<pid(e.section)<<' ';for(auto& r:sections)std::cout<<std::uint32_t(r.count30)<<' ';std::cout<<'\n';
}
void guards(){
 std::array<IniSectionIndexEntry,1> entries{};std::span<IniSectionIndexEntry> backing(entries);int count=1;std::uint8_t sorted=0;IniSectionIndexEntry* hot=nullptr;IniEnumerationSection* fallback=nullptr;IniSectionIndex w{backing,count,sorted,hot,fallback};IniEnumerationServices s;
 bool refused=false;try{findIniSectionIndex(w,0,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 count=0;require(!findIniSectionIndex(w,0,s)&&!iniEnumerationKey(w,std::nullopt,0,s));
 IniEntryLink node{&node,&node,"cycle"};IniEnumerationSection section{&node,2};entries[0]={iniSectionNameCrc("a"),&section};count=1;sorted=1;hot=&entries[0];s.maximumLinks=1;
 refused=false;try{iniEnumerationKey(w,"a",-1,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 std::cout<<"ini enumeration guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
