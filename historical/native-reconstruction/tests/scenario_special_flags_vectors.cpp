// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/ScenarioSpecialFlags.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
namespace {
void need(bool x){if(!x)throw std::invalid_argument("Scenario flag fixture outside domain");}
template<class T>T take(std::istream& in){T x{};need(bool(in>>x));return x;}
void run(std::istream& in){
 const auto op=take<int>(in);need(op>=0&&op<=2);auto flags=take<std::uint32_t>(in);
 const auto open=take<std::int32_t>(in),query=take<std::int32_t>(in);
 const auto type=take<std::uint32_t>(in),data=take<std::uint32_t>(in);auto session=take<std::int32_t>(in);
 const auto rawOverride=take<unsigned>(in);need(rawOverride<256);auto overrideMode=std::uint8_t(rawOverride);
 const auto mutation=take<int>(in);need(mutation>=-1&&mutation<13);const auto mutationFlags=take<std::uint32_t>(in);
 const auto mutationSession=take<std::int32_t>(in);const auto mutationOverride=take<unsigned>(in);need(mutationOverride<256);
 std::array<std::int64_t,13> answers{};for(auto& x:answers){x=take<std::int64_t>(in);need(x>=-1&&x<=4294967295LL);}std::string extra;need(!(in>>extra));
 ScenarioFlagRegistryServices services;
 services.open=[&](std::uint32_t& h){std::cout<<"O "<<flags<<' ';h=0x1234;return open;};
 services.query=[&](auto h,auto& t,auto& d){std::cout<<"Q "<<h<<' ';t=type;d=data;return query;};
 services.close=[](auto h){std::cout<<"C "<<h<<' ';};
 if(op!=1)initializeScenarioSpecialFlags(flags,services);
 if(op!=0){std::size_t index=0;readScenarioSpecialFlags(flags,session,overrideMode,[&](auto key,auto fallback){
  need(key==scenarioSpecialFlagKeys.at(index).key);std::cout<<"B "<<index<<' '<<fallback<<' '<<flags<<' ';
  const auto answer=answers[index]<0?fallback:std::uint32_t(answers[index]);
  if(int(index)==mutation){flags=mutationFlags;session=mutationSession;overrideMode=std::uint8_t(mutationOverride);std::cout<<"M "<<flags<<' '<<session<<' '<<unsigned(overrideMode)<<' ';}
  ++index;return answer;
 });}
 std::cout<<"Z "<<flags<<' '<<session<<' '<<unsigned(overrideMode)<<'\n';
}
void guards(){std::uint32_t flags=0xffffffff;ScenarioFlagRegistryServices r;r.open=[](auto&){return 1;};initializeScenarioSpecialFlags(flags,r);need(flags==0xfff88080u);bool caught=false;try{readScenarioSpecialFlags(flags,0,0,{});}catch(const std::invalid_argument&){caught=true;}need(caught);std::cout<<"Scenario flags guards PASS\n";}
}
int main(int argc,char**argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
