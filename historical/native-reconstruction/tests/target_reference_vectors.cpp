// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TargetReference.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
namespace {
void require(bool b){if(!b)throw std::invalid_argument("Target reference fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
std::uint8_t byte(std::istream& in){auto v=take<unsigned>(in);require(v<=255);return std::uint8_t(v);}
struct Object {std::int32_t kind=0,id=0;std::int16_t x=0,y=0;};
void run(std::istream& in){
 require(take<char>(in)=='J');int root=take<int>(in),token=take<int>(in),object=take<int>(in),count=take<int>(in);auto sorted=byte(in);int backing=take<int>(in),cacheBacking=take<int>(in),cacheIndex=take<int>(in),fallbackID=take<int>(in),mutation=take<int>(in);
 require(root>=0&&root<=3&&token>=0&&token<2&&object>=0&&object<=4&&count>=-2&&count<=32&&backing>=1&&backing<=2&&cacheBacking>=0&&cacheBacking<=3&&cacheIndex>=0&&cacheIndex<32&&(cacheBacking!=3||cacheIndex==0)&&mutation>=0&&mutation<=8);
 std::array<TargetReference,2> tokens;std::array<Object,4> objects;std::array<TargetRegistryEntry,32> primary,alternate;TargetRegistryEntry detached;
 const auto op=[&](int id)->const void*{require(id>=0&&id<=4);return id?&objects[std::size_t(id-1)]:nullptr;};
 const auto oid=[&](const void* p){for(int i=0;i<=4;++i)if(op(i)==p)return i;throw std::invalid_argument("Foreign target object");};
 for(auto& t:tokens){t.value=take<std::int32_t>(in);t.tag=byte(in);for(auto& b:t.padding)b=byte(in);}
 for(auto& o:objects){o.kind=take<std::int32_t>(in);o.id=take<std::int32_t>(in);int x=take<int>(in),y=take<int>(in);require(x>=-32768&&x<=32767&&y>=-32768&&y<=32767);o.x=std::int16_t(x);o.y=std::int16_t(y);}
 const auto readEntry=[&](auto& e){e.key=take<std::int32_t>(in);e.object=op(take<int>(in));};
 for(auto& e:primary)readEntry(e);for(auto& e:alternate)readEntry(e);readEntry(detached);std::string extra;require(!(in>>extra));
 std::span<TargetRegistryEntry> entries=backing==1?std::span(primary):std::span(alternate);
 TargetRegistryEntry* cached=cacheBacking==0?nullptr:cacheBacking==1?&primary[std::size_t(cacheIndex)]:cacheBacking==2?&alternate[std::size_t(cacheIndex)]:&detached;
 const void* fallback=op(fallbackID);TargetReferenceWorld w{count,entries,sorted,cached,fallback};
 const auto cache=[&](){if(!cached)return std::pair{0,0};for(int i=0;i<32;++i){if(cached==&primary[std::size_t(i)])return std::pair{1,i};if(cached==&alternate[std::size_t(i)])return std::pair{2,i};}require(cached==&detached);return std::pair{3,0};};
 bool changed=false;
 const auto mutate=[&](bool id,int i){
  if(changed||((mutation==2||mutation==5||mutation==7)!=id)||!mutation)return;
  changed=true;auto& o=objects[std::size_t(i-1)];auto& t=tokens[std::size_t(token)];
  if(mutation==1){o.kind=11;o.x=-32768;o.y=32767;t.value=-99;t.tag=255;}
  if(mutation==2){t.tag=11;t.value=-7;}
  if(mutation==3){count=0;sorted=255;fallback=op(4);}
  if(mutation==4){entries=alternate;count=32;sorted=0;fallback=op(2);}
  if(mutation==5){entries=alternate;count=8;sorted=0;fallback=op(3);cached=&alternate[0];}
  if(mutation==6){cached=&detached;sorted=0;count=1;t.value=detached.key;t.tag=52;}
  if(mutation==7){o.id=-2147483647;t.padding={255,0,127};primary[0]={-7,op(4)};alternate[0]={-7,op(2)};}
  if(mutation==8){count=-1;sorted=1;fallback=nullptr;cached=nullptr;}
 };
 w.kind=[&](const void* p){int i=oid(p);const auto result=objects.at(std::size_t(i-1)).kind;auto [b,j]=cache();std::cout<<" K "<<i<<' '<<result<<' '<<b<<' '<<j<<' '<<unsigned(sorted)<<' '<<count;mutate(false,i);return result;};
 w.uniqueID=[&](const void* p){int i=oid(p);const auto result=objects.at(std::size_t(i-1)).id;std::cout<<" I "<<i<<' '<<unsigned(tokens[std::size_t(token)].tag)<<' '<<result;mutate(true,i);return result;};
 w.cell24=[&](const void* p){const auto& o=objects.at(std::size_t(oid(p)-1));return TargetReferenceCell{o.x,o.y};};
 w.compare=[&](auto a,auto b,auto x,auto y){std::cout<<" C "<<(entries.data()==primary.data()?1:2)<<' '<<a<<' '<<b<<' '<<x<<' '<<y;};
 const auto make=[&](){require(makeTargetReference(tokens[std::size_t(token)],op(object),w)==&tokens[std::size_t(token)]);std::cout<<" R "<<token+1;};
 const auto resolve=[&](int t){const auto result=resolveTargetReference(tokens[std::size_t(t)],w);std::cout<<" R "<<oid(result);};
 if(root==0)make();if(root==1){resolve(0);resolve(1);resolve(0);}if(root==2){const auto result=castTargetTechno(op(object),w);std::cout<<" R "<<oid(result);}if(root==3){make();resolve(token);resolve(token);}
 auto [b,j]=cache();std::cout<<" F "<<count<<' '<<unsigned(sorted)<<' '<<(entries.data()==primary.data()?1:2)<<' '<<b<<' '<<j<<' '<<oid(fallback)<<' '<<changed;
 for(const auto& t:tokens){std::cout<<' '<<t.value<<' '<<unsigned(t.tag);for(auto p:t.padding)std::cout<<' '<<unsigned(p);}
 for(const auto& o:objects)std::cout<<' '<<o.kind<<' '<<o.id<<' '<<o.x<<' '<<o.y;
 const auto writeEntry=[&](const auto& e){std::cout<<' '<<e.key<<' '<<oid(e.object);};for(const auto& e:primary)writeEntry(e);for(const auto& e:alternate)writeEntry(e);writeEntry(detached);std::cout<<'\n';
}
void guards(){
 int count=0;std::span<TargetRegistryEntry> entries;std::uint8_t sorted=0;TargetRegistryEntry* cached=nullptr;const void* fallback=nullptr;TargetReferenceWorld w{count,entries,sorted,cached,fallback};TargetReference t{7,51,{1,2,3}};
 require(!resolveTargetReference(t,w)&&!castTargetTechno(nullptr,w));makeTargetReference(t,nullptr,w);require(t.value==0&&t.tag==0&&t.padding==std::array<std::uint8_t,3>{1,2,3});t.tag=52;require(!resolveTargetReference(t,w));
 const auto refuses=[&](auto action){bool caught=false;try{action();}catch(const std::invalid_argument&){caught=true;}require(caught);};
 count=-1;refuses([&]{resolveTargetReference(t,w);});count=1;refuses([&]{resolveTargetReference(t,w);});sorted=1;refuses([&]{resolveTargetReference(t,w);});refuses([&]{castTargetTechno(&count,w);});
 w.kind=[](const void*){return 11;};refuses([&]{makeTargetReference(t,&count,w);});w.kind=[](const void*){return 1;};refuses([&]{makeTargetReference(t,&count,w);});
 std::array<TargetRegistryEntry,2> a{{{1,nullptr},{0,nullptr}}};sortTargetRegistry(a,w);require(a[0].key==0&&a[1].key==1);require(compareTargetRegistryKeys(INT32_MIN,INT32_MAX)==-1);std::cout<<"Target reference guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
