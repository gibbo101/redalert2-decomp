// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/IniRecords.hpp"
#include <array>
#include <bit>
#include <iostream>
#include <sstream>
#include <vector>
using namespace ra2;
void require(bool v){if(!v)throw std::invalid_argument("INI record fixture differs");}
void run(std::istream& in){
 std::array<int,8> f;for(auto& v:f)require(bool(in>>v));std::string tail;require(!(in>>tail));
 require(f[0]>=0&&f[0]<7&&f[1]>=0&&f[1]<8&&f[2]>=1&&f[2]<=6&&f[3]>=1&&f[3]<=6&&f[4]>=0&&f[4]<=255&&f[5]>=0&&f[5]<3&&f[6]>=0&&f[6]<7&&f[7]>=1&&f[7]<=3);
 IniRecordList list;std::array<IniRecordEntry,3> entries;IniEntryLink extra;
 std::array<IniEntryLink*,6> nodes{&list.head4,&list.tail10,&entries[0].link,&entries[1].link,&entries[2].link,&extra};
 std::array<const char*,4> strings{"zeta","alpha","middle","value"};
 const auto node=[&](int i){return i?nodes.at(i-1):nullptr;};
 const auto id=[&](const void* p)->unsigned{if(!p)return 0;if(p==&list)return 9;for(unsigned i=0;i<nodes.size();++i)if(p==nodes[i])return i+1;for(unsigned i=0;i<strings.size();++i)if(p==strings[i])return i+20;throw std::invalid_argument("Unknown INI record identity");};
 const std::array<std::array<int,12>,8> graphs{{
  {2,0,0,1,0,0,0,0,0,0,0,0},{3,0,0,4,4,1,2,3,0,0,0,0},
  {4,0,0,3,2,4,3,1,0,0,0,0},{0,0,0,0,4,6,0,3,0,0,0,0},
  {3,0,0,1,3,1,0,0,0,0,0,0},{3,0,0,1,4,6,3,3,0,0,0,0},
  {2,6,1,1,0,0,0,0,0,0,0,0},{3,6,6,6,6,6,6,6,6,6,0,0}}};
 for(unsigned i=0;i<nodes.size();++i){nodes[i]->next4=node(graphs[f[1]][i*2]);nodes[i]->previous8=node(graphs[f[1]][i*2+1]);}
 const auto initial=std::bit_cast<int>(0xa5a5a5a5u);
 for(unsigned i=0;i<3;++i){auto& e=entries[i];e.link.nameC=strings[i];e.value10=strings[3];e.comments14=strings[2];e.comment18=strings[1];e.metadata1C=e.metadata20=e.metadata24=initial;}
 IniRecordArguments args{strings[0],strings[1],strings[2],strings[3],-1,INT32_MIN,INT32_MAX};
 if(f[5]==1)args={nullptr,nullptr,nullptr,nullptr,0,0,0};
 if(f[5]==2)args={strings[3],strings[2],strings[1],strings[0],INT32_MIN,128,-128};
 unsigned stores=0,freed=0,mutated=0;std::vector<std::uint64_t> trace;
 const auto event=[&](std::uint64_t k,std::uint64_t owner=0,std::uint64_t off=0,std::uint64_t value=0,std::uint64_t p=0){trace.insert(trace.end(),{k,owner,off,value,p});};
 const auto mutate=[&](int where){if(mutated||f[6]!=where)return;mutated=1;event(3,0,where);
  if(where==1){node(f[2])->next4=node(6);node(f[2])->previous8=node(5);}
  if(where==2){node(f[2])->next4=node(4);node(f[2])->previous8=node(3);}
  if(where==3)node(f[2])->next4=node(6);
  if(where==4){list.head4.next4=node(5);entries[0].link.nameC=strings[3];}
  if(where==5||where==6)args={strings[3],strings[2],strings[1],strings[0],17,-18,19};
 };
 IniRecordServices s;s.maximumMembers=32;s.release=[&](const void* owner){++freed;event(2,id(owner));mutate(4);};
 s.store=[&](const void* owner,int off,unsigned value,const void* pointer){event(1,id(owner),off,value,id(pointer));++stores;if(stores==1){mutate(1);mutate(5);}if(stores==4){mutate(2);mutate(6);}if(stores==7)mutate(3);};
 for(int i=0;i<f[7];++i){unsigned returned=0;switch(f[0]){
  case 0:returned=id(&constructIniRecordNode(*node(f[2]),s));break;
  case 1:insertIniRecordAfter(*node(f[2]),node(f[3]),s);break;
  case 2:returned=id(&destroyIniRecordNode(*node(f[2]),f[4],s));break;
  case 3:case 4:returned=id(&constructIniRecordList(list,f[0]==4,s));break;
  case 5:returned=id(&destroyIniRecordList(list,f[4],s));break;
  case 6:returned=id(&constructIniRecordEntry(entries[0],args,s).link);break;
 }event(4,returned);}
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<unsigned(list.dispatch0)<<' ';
 for(auto* p:nodes)std::cout<<id(p->next4)<<' '<<id(p->previous8)<<' '<<unsigned(p->dispatch0)<<' ';
 for(auto& e:entries)std::cout<<id(e.link.nameC)<<' '<<id(e.value10)<<' '<<id(e.comments14)<<' '<<id(e.comment18)<<' '<<std::uint32_t(e.metadata1C)<<' '<<std::uint32_t(e.metadata20)<<' '<<std::uint32_t(e.metadata24)<<' ';
 std::cout<<mutated<<' '<<freed<<' '<<id(args.name)<<' '<<id(args.value)<<' '<<id(args.comments)<<' '<<id(args.comment)<<' '<<std::uint32_t(args.metadata24)<<' '<<std::uint32_t(args.metadata1C)<<' '<<std::uint32_t(args.metadata20)<<'\n';
}
void guards(){
 IniRecordServices s;IniRecordList list;constructIniRecordList(list,true,s);require(list.head4.next4==&list.tail10&&list.tail10.previous8==&list.head4);
 IniRecordEntry first,second;constructIniRecordEntry(first,{"zeta","a"},s);constructIniRecordEntry(second,{"alpha","b"},s);
 insertIniRecordAfter(*list.tail10.previous8,&first.link,s);insertIniRecordAfter(*list.tail10.previous8,&second.link,s);
 require(list.head4.next4==&first.link&&first.link.next4==&second.link&&second.link.next4==&list.tail10);
 bool refused=false;try{destroyIniRecordList(list,0,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 s.maximumMembers=2;destroyIniRecordList(list,0,s);require(!first.link.next4&&!first.link.previous8&&!second.link.next4&&!second.link.previous8&&first.link.dispatch0==IniNodeDispatch::entry);
 refused=false;try{insertIniRecordAfter(list.head4,nullptr,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 refused=false;try{destroyIniRecordNode(first.link,1,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 std::cout<<"ini record guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string text;while(std::getline(std::cin,text)){std::istringstream in(text);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
