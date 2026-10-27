// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/BuildingDepthImage.hpp"
#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace ra2;
namespace {
std::string hash(const Bytes& b){unsigned char d[32];SHA256(b.data(),b.size(),d);std::ostringstream o;o<<std::hex<<std::setfill('0');for(auto c:d)o<<std::setw(2)<<int(c);return o.str();}
Bytes unhex(const std::string& s){if(s.size()%2)throw std::invalid_argument("Hex");Bytes b;for(std::size_t i=0;i<s.size();i+=2)b.push_back(std::uint8_t(std::stoul(s.substr(i,2),nullptr,16)));return b;}
void word(Bytes& b,std::uint32_t v){for(int k=0;k<4;++k)b.push_back(std::uint8_t(v>>(k*8)));}
}
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  const auto require=[](bool b){if(!b)throw std::runtime_error("Depth initializer guard failure");};
  const auto rejects=[&](auto f){bool rejected=false;try{f();}catch(const std::invalid_argument&){rejected=true;}require(rejected);};
  auto previous=std::make_shared<Bytes>(32,0x44);BuildingDepthImageState state{previous};
  rejects([&]{initializeBuildingDepthImage(state,{});});require(state.raw==previous);
  Bytes input(32);input[2]=input[4]=input[6]=1;input[28]=32;
  BuildingDepthImageServices s;
  s.release781d3b=[&](const auto& p){require(state.raw==previous&&p==previous);};
  s.construct468f50=[&](auto n){require(n=="BUILDNGZ.SHP"&&!state.raw);};
  s.size2c=[&]{return std::uint32_t(input.size());};s.destroy438410=[]{};s.destroy42f350=[]{};
  s.allocate782017=[](auto n){return std::make_shared<Bytes>(n);};
  s.source5956c0=[&](auto){return std::span<const std::uint8_t>(input);};
  rejects([&]{initializeBuildingDepthImage(state,s);});
  require(state.raw&&*state.raw==input&&*previous==Bytes(32,0x44));
  std::cout<<"Building depth initializer guards PASS\n";return 0;
 }
 if(argc!=1)return 2;
 std::string line;while(std::getline(std::cin,line)){
 std::istringstream in(line);int old,mutation;std::string hex;if(!(in>>old>>mutation>>hex)||old<0||old>1||mutation<0||mutation>2)return 2;
 Bytes source=unhex(hex),stores;BuildingDepthImageState state;auto previous=std::make_shared<Bytes>(32,0x44);if(old)state.raw=previous;
 auto allocated=std::make_shared<Bytes>(source.size(),0xa5),replacement=std::make_shared<Bytes>(source.size(),0x55);
 auto identity=[&](const std::shared_ptr<Bytes>& p){return !p?0:p==previous?1:p==allocated?2:p==replacement?3:throw std::invalid_argument("Owner");};
 auto event=[&](int key,int value){std::cout<<key<<' '<<value<<' ';};
 BuildingDepthImageServices s;
 s.release781d3b=[&](const auto& p){event(1,identity(p));if(state.raw!=previous)throw std::invalid_argument("Release before clear");};
 s.globalStore=[&](const auto& p){event(2,identity(p));};
 s.construct468f50=[&](std::string_view n){if(n!="BUILDNGZ.SHP")throw std::invalid_argument("Name");event(3,identity(state.raw));};
 s.size2c=[&]{event(4,int(source.size()));return std::uint32_t(source.size());};
 s.destroy438410=[&]{event(5,0);};s.destroy42f350=[&]{event(6,0);};
 s.allocate782017=[&](std::uint32_t size){event(7,int(size));return allocated;};
 s.source5956c0=[&](std::string_view n){if(n!="BUILDNGZ.SHP")throw std::invalid_argument("Name");event(8,identity(state.raw));if(mutation==1)state.raw=replacement;if(mutation==2)source.back()^=0x81;return std::span<const std::uint8_t>(source);};
 s.memoryStore=[&](const Bytes& b,std::uint32_t p,std::uint32_t n,std::uint32_t v){word(stores,&b==allocated.get()?2:3);word(stores,p);word(stores,n);word(stores,v);};
 initializeBuildingDepthImage(state,s);
 std::cout<<"F "<<identity(state.raw)<<' '<<hash(*allocated)<<' '<<hash(*replacement)<<' '<<hash(*previous)<<' '<<hash(stores)<<' '<<stores.size()/16<<'\n';
 }}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
