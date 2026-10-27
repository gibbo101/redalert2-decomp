// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SurfaceStartup.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Surface startup domain");}
void run(std::istream& in){
 char op;std::int32_t w,h;unsigned requested,forced,allocation,created;std::uint32_t bits,caps;
 need(bool(in>>op>>w>>h>>requested>>forced>>allocation>>created>>bits>>caps)&&op=='S'&&requested<=255&&forced<=255&&allocation<=1&&created<=1);std::string tail;need(!(in>>tail));
 DeviceSurfaceStartup s;std::array<std::uint32_t,27> descriptor;descriptor.fill(0xa5a5a5a5);
 const auto out=[](char k,unsigned off,unsigned n,std::uint32_t v){std::cout<<k<<' '<<off<<' '<<n<<' '<<v<<' ';};
 SurfaceStartupServices services;services.objectStore=[&](auto o,auto n,auto v){out('O',o,n,v);};services.descriptorStore=[&](auto o,auto n,auto v){out('D',o,n,v);};
 services.allocate=[&](auto n){std::cout<<"A "<<n<<' ';return allocation?std::span<std::uint32_t>(descriptor):std::span<std::uint32_t>{};};
 services.create=[&](auto d,auto& surface){std::cout<<"C "<<d[0]<<' '<<d[1]<<' '<<d[2]<<' '<<d[3]<<' '<<d[26]<<' ';surface=created;out('O',28,4,created);};
 services.describe=[&](auto surface,auto){std::cout<<"G "<<surface<<' ';descriptor[21]=bits;out('D',84,4,bits);descriptor[26]=caps;out('D',104,4,caps);};
 const std::uint8_t flag=std::uint8_t(forced);initializeDeviceSurface(s,w,h,std::uint8_t(requested),flag,services);
 std::cout<<"R "<<s.width4<<' '<<s.height8<<' '<<s.lockC<<' '<<s.bytes10<<' '<<s.offset14<<' '<<unsigned(s.flag18)<<' '<<unsigned(s.video19)<<' '<<s.surface1C<<' '<<!s.descriptor20.empty();for(auto v:descriptor)std::cout<<' '<<v;std::cout<<'\n';
}
void guards(){
 DeviceSurfaceStartup s;SurfaceStartupServices v;std::array<std::uint32_t,27> d{};int allocations=0,creates=0,describes=0;std::uint8_t forced=0;
 v.allocate=[&](auto n){need(n==108);++allocations;return std::span<std::uint32_t>(d);};
 v.create=[&](auto desc,auto& output){++creates;need(desc[26]==0x800);output=1;};v.describe=[&](auto,auto desc){++describes;need(desc[0]==108&&desc[26]==0);desc[21]=0xffffffff;desc[26]=0x4000;};
 initializeDeviceSurface(s,-1,2,1,forced,v);need(allocations==1&&creates==1&&describes==1&&s.bytes10==0&&s.video19==1);
 v.allocate=[](auto){return std::span<std::uint32_t>{};};initializeDeviceSurface(s,3,4,1,forced,v);need(creates==1&&s.surface1C==0&&s.bytes10==0);
 v.allocate=[&](auto){return std::span<std::uint32_t>(d);};v.create=[](auto,auto&){throw std::runtime_error("device fault");};bool fault=false;
 try{initializeDeviceSurface(s,3,4,1,forced,v);}catch(const std::runtime_error&){fault=true;}need(fault&&s.width4==3&&d[26]==0x800);
 std::cout<<"surface startup guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
