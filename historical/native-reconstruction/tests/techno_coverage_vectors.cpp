// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TechnoCoverage.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
int main(int argc,char** argv){try{
 if(argc>1){
  if(std::string(argv[1])!="--guards")return 2;
  const void* current=nullptr;std::uint8_t active=0;std::int32_t range=0,coordinate=0;
  TechnoCoverageServices services{current};const TechnoCoverageActor actor{active,range,coordinate,coordinate,coordinate};
  changeTechnoCoverage(true,actor,services);current=&range;
  active=255;changeTechnoCoverage(true,actor,services);active=0;changeTechnoCoverage(false,actor,services);
  const auto refused=[&](auto action){bool caught=false;try{action();}catch(const std::invalid_argument&){caught=true;}if(!caught)throw std::runtime_error("coverage guard did not refuse");};
  refused([&]{changeTechnoCoverage(true,actor,services);});
  services.allowed30C=[]{return std::uint8_t(0);};changeTechnoCoverage(true,actor,services);
  services.allowed30C=[]{return std::uint8_t(255);};refused([&]{changeTechnoCoverage(true,actor,services);});
  range=1;refused([&]{changeTechnoCoverage(true,actor,services);});
  if(active!=1)throw std::runtime_error("entered refusal must not claim rollback");
  active=0;range=100;int queries=0;services.projectedHeight=[&](int){++queries;return 0;};
  refused([&]{changeTechnoCoverage(true,actor,services);});if(queries!=2||active!=1)throw std::runtime_error("host bound must preserve prior stores/queries");
  std::cout<<"guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);char tag;std::array<std::int32_t,23> f{};if(!(in>>tag)||tag!='C')return 2;for(auto& n:f)if(!(in>>n))return 2;std::string extra;if(in>>extra)return 2;
  // add,active,range,type,allowed,current,local,allied,13d,566a,x,y,z,h0,h1,flags,c130,c134,c13c,cycle,mutation,owner,owner3c
  for(int k:{0,19})if(f[k]<0||f[k]>1)return 2;for(int k:{1,4,6,7,8,9})if(f[k]<0||f[k]>255)return 2;
  if(f[3]<-128||f[3]>127||f[5]<0||f[5]>2||f[20]<0||f[20]>5||f[21]<1||f[21]>2||f[22]<1||f[22]>2||f[2]<-64||f[2]>62)return 2;
  std::uint8_t active=std::uint8_t(f[1]);auto range=f[2],x=f[10],y=f[11],z=f[12];int handles[2]{};const auto hp=[&](int id)->const void*{return id?&handles[id-1]:nullptr;};const auto hid=[&](const void* p){return p==hp(1)?1:p==hp(2)?2:0;};const void* current=hp(f[5]);int owner=f[21];
  std::array<std::uint8_t,2> d{std::uint8_t(f[8]),std::uint8_t(f[8]^1)},b{std::uint8_t(f[9]),std::uint8_t(f[9]^1)},tail{255,254};
  std::array<std::uint32_t,3> flags{};flags.fill(std::uint32_t(f[15]));std::array<std::array<std::int32_t,4>,3> cells{};for(auto& c:cells)c={f[15],f[16],f[17],f[18]};int last=0,queries=0,heights=0;bool changed=false;
  const auto mutate=[&](int leaf){if(changed||f[20]!=leaf)return;changed=true;if(leaf==1){active=255;range=1;x=65535;y=-65535;z=728;}if(leaf==2){range=7;}if(leaf==3){range=2;x=17;y=19;z=999;current=hp(2);}if(leaf==4){owner=2;current=hp(2);}if(leaf==5){current=hp(2);}};
  TechnoCoverageServices s{current};
  s.allowed30C=[&]{std::cout<<"E P "<<f[4]<<' ';mutate(1);return std::uint8_t(f[4]);};
  s.typeRangeADE=[&]{std::cout<<"E T "<<f[3]<<' ';mutate(2);return std::int8_t(f[3]);};
  s.projectedHeight=[&](int v){auto result=f[13+std::min(heights++,1)];std::cout<<"E Z "<<v<<' '<<result<<' ';mutate(3);return result;};
  s.owner3C=[&]()->const void*{std::cout<<"E O "<<f[22]<<' ';mutate(4);return hp(f[22]);};s.owner1B4=[&]{return hp(owner);};
  s.localHouse=[&](const void* p){auto result=std::uint8_t(f[6]^(hid(p)==2));std::cout<<"E L "<<hid(p)<<' '<<int(result)<<' ';return result;};
  s.allied=[&](const void* p,const void* q){std::cout<<"E B "<<hid(p)<<' '<<hid(q)<<' '<<f[7]<<' ';return std::uint8_t(f[7]);};
  s.house=[&](const void* p){int id=hid(p);if(!id)throw std::invalid_argument("null House");return TechnoCoverageHouse{d[id-1],b[id-1],tail[id-1]};};
  s.cell=[&](auto cx,auto cy){last=f[19]?queries++%3:0;std::cout<<"E C "<<cx<<' '<<cy<<' '<<last<<' ';mutate(5);auto& c=cells[last];return TechnoCoverageCell{flags[last],c[1],c[2],c[3]};};
  s.refresh634030=[]{std::cout<<"E F ";};s.redraw4E09A0=[](int v){std::cout<<"E D "<<v<<' ';};
  s.store=[&](char kind,int offset,int value){std::cout<<"W "<<kind<<' '<<(kind=='C'?last:kind=='H'?hid(current):0)<<' '<<offset<<' '<<value<<' ';};
  changeTechnoCoverage(bool(f[0]),{active,range,x,y,z},s);
  std::cout<<"R "<<int(active)<<' '<<range<<' '<<x<<' '<<y<<' '<<z<<' '<<hid(current)<<' '<<owner<<' '<<int(tail[0])<<' '<<int(tail[1])<<' '<<int(changed)<<' ';for(std::size_t i=0;i<cells.size();++i){std::cout<<signed32(flags[i])<<' ';for(int j=1;j<4;++j)std::cout<<cells[i][j]<<' ';}std::cout<<'\n';
 }
 return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
