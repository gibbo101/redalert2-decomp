// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SchemeResolver.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void need(bool v){if(!v)throw std::invalid_argument("Scheme resolver fixture domain");}
const std::array<std::string_view,8> names={"LightGrey","lightgrey","Other","",std::string_view("A\0x",3),std::string_view("a\0y",3),std::string_view("\x80Z",2),std::string_view("\x80z",2)};
void run(std::istream& in){
 char op;std::array<std::int32_t,12> f{};need(bool(in>>op)&&op=='S');for(auto& v:f)need(bool(in>>v));std::string tail;need(!(in>>tail));
 need(f[0]>=0&&f[0]<8&&f[2]>=-2&&f[2]<=6&&f[3]>=0&&f[3]<2&&f[4]>=0&&f[4]<=2&&f[5]>=0&&f[5]<6&&f[6]>=0&&f[6]<64&&f[7]>=-2&&f[7]<=6&&f[9]>=0&&f[9]<8&&f[10]>=0&&f[10]<6&&f[11]>=0&&f[11]<=1);
 std::array<SurfaceMarkScheme,6> records{};std::array<int,6> nameIds{0,1,2,3,4,6};std::array<std::int32_t,6> cats{0,1,-1,1,2,INT32_MIN};std::array<const SurfaceMarkScheme*,6> tables[2];
 for(int i=0;i<6;++i){tables[0][i]=&records[i];tables[1][i]=&records[5-i];}
 std::span<const SurfaceMarkScheme*> registry=tables[f[3]];std::int32_t count=f[2];std::uint32_t locale=0;bool changed=false;
 auto id=[&](const SurfaceMarkScheme* p){if(!p)return -1;for(int i=0;i<6;++i)if(p==&records[i])return i;throw std::invalid_argument("Foreign scheme");};
 auto mutate=[&](int stage,std::uint32_t index){if(changed||f[4]!=stage||index!=std::uint32_t(f[5]))return;changed=true;const auto m=f[6];if(m&1)registry=tables[1];if(m&2)count=f[7];if(m&4)cats[1]=f[8];if(m&8)nameIds[1]=f[9];if(m&16)tables[0][index]=&records[f[10]];if(m&32)tables[1][index]=&records[f[10]];};
 SchemeResolverWorld world{registry,count,locale,[&](auto p){return names[nameIds[id(p)]];},[&](auto p){return cats[id(p)];},[&](auto i,auto p,int result){std::cout<<"T "<<i<<' '<<id(p)<<' '<<result<<' ';mutate(1,i);},[&](auto i,auto p,auto category){std::cout<<"U "<<i<<' '<<id(p)<<' '<<category<<' ';mutate(2,i);}};
 for(int i=0;i<1+f[11];++i){auto* result=resolveSurfaceScheme(names[f[0]],f[1],world);std::cout<<"R "<<id(result)<<' ';}
 std::cout<<"F "<<(registry.data()==tables[1].data())<<' '<<count<<' '<<changed<<' ';for(auto x:nameIds)std::cout<<x<<' ';for(auto x:cats)std::cout<<x<<' ';for(auto& t:tables)for(auto x:t)std::cout<<id(x)<<' ';std::cout<<'\n';
}
void guards(){
 SurfaceMarkScheme a{};std::array<const SurfaceMarkScheme*,1> slots{&a};std::span<const SurfaceMarkScheme*> registry=slots;std::int32_t count=0;std::uint32_t locale=1;int queries=0;
 SchemeResolverWorld w{registry,count,locale,[&](auto){++queries;return "";},{},{},{}};need(!resolveSurfaceScheme("",0,w)&&queries==0);count=1;bool refused=false;try{resolveSurfaceScheme("",0,w);}catch(const std::invalid_argument&){refused=true;}need(refused&&queries==0);
 locale=0;w.category310=[](auto){return 1;};need(resolveSurfaceScheme("",1,w)==&a);registry={};refused=false;try{resolveSurfaceScheme("",1,w);}catch(const std::invalid_argument&){refused=true;}need(refused);
 RefreshSurface* surface=nullptr;SurfaceMarkBuckets* buckets=nullptr;SurfaceMarkBitmap* bitmap=nullptr;SurfaceMarkServices marks{surface,buckets,bitmap,registry,{},{},{},{},[&](auto){return &a;},{},{}};std::function<void(const SurfaceMarkScheme*)> returned;const auto before=queries;
 {SchemeResolverBinding bind(marks,w,"",returned);need(queries==before);}need(marks.resolve663D30(1)==&a);
 registry=slots;w.name304=[](auto)->std::string_view{throw std::runtime_error("name fault");};bool propagated=false;try{SchemeResolverBinding bind(marks,w,"",returned);marks.resolve663D30(1);}catch(const std::runtime_error&){propagated=true;}need(propagated&&marks.resolve663D30(1)==&a);
 std::cout<<"scheme resolver guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
