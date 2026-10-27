// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/IniInputLifetime.hpp"
#include "assets/IniInput.hpp"
#include <array>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace ra2;
void require(bool v){if(!v)throw std::invalid_argument("INI lifetime fixture differs");}
void run(std::istream& in){
 std::array<int,10> f;for(auto& v:f)require(bool(in>>v));std::string tail;require(!(in>>tail));
 require(f[0]>=0&&f[0]<4&&f[2]>=0&&f[2]<=255&&f[3]>=0&&f[3]<3&&f[4]>=0&&f[4]<2&&f[5]>=0&&f[5]<=4&&f[6]>=0&&f[6]<8&&f[7]>=0&&f[7]<6&&f[8]>=1&&f[8]<=3&&f[9]>=0&&f[9]<2);
 std::array<int,2> memory{};std::array<IniInputPipeOwner,4> p{};
 const auto node=[&](int id)->IniInputPipeOwner*{return id?&p.at(id-1):nullptr;};
 const auto id=[&](const void* v)->unsigned{if(!v)return 0;for(unsigned i=0;i<4;++i)if(v==&p[i])return i+1;for(unsigned i=0;i<2;++i)if(v==&memory[i])return i+10;throw std::invalid_argument("Unknown INI lifetime identity");};
 const std::array<std::array<int,8>,8> graphs{{{0,0,0,0,0,0,0,0},{2,0,0,1,0,0,0,0},{2,3,0,1,1,0,0,0},{2,3,0,4,1,0,2,0},{1,1,0,0,0,0,0,0},{0,2,1,3,2,0,0,0},{3,2,4,1,0,0,0,2},{4,4,1,3,2,2,3,1}}};
 for(unsigned i=0;i<4;++i){p[i].source4=node(graphs[f[6]][i*2]);p[i].downstream8=node(graphs[f[6]][i*2+1]);}
 IniInputBufferOwner b{f[3]?&memory[f[3]-1]:nullptr,f[1],std::uint8_t(f[2])};
 unsigned alloc=0,freed=0,attached=0,mutated=0;std::vector<std::uint64_t> trace;
 const auto event=[&](std::uint64_t k,std::uint64_t owner=0,std::uint64_t off=0,std::uint64_t value=0,std::uint64_t pointer=0){trace.insert(trace.end(),{k,owner,off,value,pointer});};
 const auto mutate=[&](int where){if(mutated||f[7]!=where)return;mutated=1;event(5,0,where);
  if(where==1){b.size4=99;b.owned8=128;}if(where==2){b.data0=&memory[1];b.size4=-2;b.owned8=255;}
  if(where==3){p[0].source4=node(4);p[0].downstream8=node(2);if(auto* q=node(f[5]))q->downstream8=node(3);}
  if(where==4){p[0].source4=node(2);p[0].downstream8=node(3);b.data0=&memory[1];b.size4=-7;b.owned8=128;}
  if(where==5){p[0].source4=node(4);if(auto* q=node(f[5]))q->downstream8=node(3);}
 };
 IniInputLifetimeServices s;
 s.allocate=[&](int n)->void*{++alloc;event(2,0,0,std::uint32_t(n),f[4]?0:10);mutate(1);return f[4]?nullptr:&memory[0];};
 s.release=[&](void* v){++freed;event(3,0,0,0,id(v));mutate(2);};
 s.attach=[&](IniInputPipeOwner& w,IniInputPipeOwner* source){++attached;event(4,id(&w),0,0,id(source));mutate(3);if(f[9])attachIniInputSource(w,source,s);};
 s.store=[&](const void* owner,int off,std::int64_t value,const void* ptr){event(1,owner==&b?9:id(owner),off,std::uint32_t(value),id(ptr));mutate(4);if(owner==&p[0]&&off==4)mutate(5);};
 for(int i=0;i<f[8];++i){if(f[0]==0){auto& r=constructIniInputBuffer(b,f[1],s);require(&r==&b);event(6,9);}else if(f[0]==1){destroyIniInputBuffer(b,s);event(6);}else if(f[0]==2){attachIniInputSource(p[0],node(f[5]),s);event(6);}else{destroyIniInputPipe(p[0],s);event(6);}}
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<id(b.data0)<<' '<<std::uint32_t(b.size4)<<' '<<unsigned(b.owned8)<<' ';
 for(auto& w:p)std::cout<<id(w.source4)<<' '<<id(w.downstream8)<<' '<<w.baseDispatch<<' ';
 std::cout<<alloc<<' '<<freed<<' '<<attached<<' '<<mutated<<'\n';
}
void guards(){
 IniInputBufferOwner b;IniInputLifetimeServices s;require(&constructIniInputBuffer(b,0,s)==&b);destroyIniInputBuffer(b,s);
 bool refused=false;try{constructIniInputBuffer(b,1,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
 IniInputPipeOwner pipe,source,downstream;pipe.source4=&source;source.downstream8=&pipe;pipe.downstream8=&downstream;downstream.source4=&pipe;
 s.attach=[&](auto& w,auto* p){attachIniInputSource(w,p,s);};destroyIniInputPipe(pipe,s);require(source.downstream8==&downstream&&downstream.source4==&source&&!pipe.source4&&!pipe.downstream8&&pipe.baseDispatch);
 // One actual buffer/pipe lifecycle feeds the recovered buffered read. Byte I/O
 // and heap remain supplied here; this is native composition, not parser proof.
 std::array<std::uint8_t,8> bytes{};s.allocate=[&](int n)->void*{require(n==8);return bytes.data();};unsigned releases=0;s.release=[&](void* p){require(p==bytes.data());++releases;};
 constructIniInputBuffer(b,8,s);attachIniInputSource(pipe,&source,s);const void* sourceIdentity=pipe.source4;std::span<std::uint8_t> backing(static_cast<std::uint8_t*>(b.data0),8);int cursor=0,available=0;
 IniBufferedInput input{sourceIdentity,backing,b.size4,cursor,available};IniInputServices io;unsigned calls=0;io.sourceRead=[&](const void* p,auto out,int n){require(p==&source&&n==8);if(calls++)return 0;out[0]='x';out[1]='\n';return 2;};io.copy=[](auto out,auto in){std::copy(in.begin(),in.end(),out.begin());};
 IniLineServices line;line.readByte=[&](auto& v){return readBufferedIniInput(input,{&v,1},1,io);};std::array<std::uint8_t,4> out{};std::uint8_t eof=0;
 require(readIniInputLine(out,4,&eof,line)==1&&out[0]=='x'&&out[1]==0&&eof==0);require(readIniInputLine(out,4,&eof,line)==0&&eof==1);
 destroyIniInputBuffer(b,s);destroyIniInputPipe(pipe,s);require(releases==1&&!b.data0&&!b.size4&&!b.owned8&&!source.downstream8);
 std::cout<<"ini input lifetime guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string text;while(std::getline(std::cin,text)){std::istringstream in(text);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
