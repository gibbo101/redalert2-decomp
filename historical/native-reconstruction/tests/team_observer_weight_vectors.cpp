// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamObserverWeight.hpp"
#include <array>
#include <bit>
#include <cfenv>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Team observer fixture differs");}
void run(std::istream& in){
 int success,rounding,total,count,alias,mutation,repeats;std::array<std::uint64_t,6> bits{};
 require(bool(in>>success>>rounding>>total>>count));for(auto& v:bits)require(bool(in>>v));require(bool(in>>alias>>mutation>>repeats));std::string tail;require(!(in>>tail));
 require((success==0||success==1)&&(rounding==0||rounding==1)&&(alias==0||alias==1)&&mutation>=0&&mutation<=3&&repeats>=1&&repeats<=3);
 double weight=std::bit_cast<double>(bits[0]),minimum=std::bit_cast<double>(bits[1]),maximum=std::bit_cast<double>(bits[2]);
 double rs=std::bit_cast<double>(bits[3]),rf=std::bit_cast<double>(bits[4]),coefficient=std::bit_cast<double>(bits[5]);
 const int previous=std::fegetround(),mode=rounding?FE_TOWARDZERO:FE_TONEAREST;require(std::fesetround(mode)==0);
 struct Restore{int mode;~Restore(){std::fesetround(mode);}} restore{previous};
 std::vector<std::uint64_t> trace;int mutated=0;
 TeamObserverWeightServices services;
 services.rules=[&](){return alias?TeamObserverRules{weight,minimum,maximum}:TeamObserverRules{rs,rf,coefficient};};
 services.store=[&](auto off,auto n,auto value){trace.insert(trace.end(),{off,n,value});
  if(mutated)return;
  if(n==8&&mutation==1){mutated=1;count=INT32_MAX;total=123;}
  if(n==8&&mutation==2){mutated=1;minimum=41.25;maximum=-12.5;}
  if(n==4&&off==0xb8&&mutation==3){mutated=1;minimum=7.125;maximum=-3.75;}
 };
 for(int i=0;i<repeats;++i){updateTeamObserverWeight({weight,minimum,maximum,count,total},success,services);require(std::fegetround()==mode);}
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<std::bit_cast<std::uint64_t>(weight)<<' '<<std::bit_cast<std::uint64_t>(minimum)<<' '<<std::bit_cast<std::uint64_t>(maximum)<<' '<<std::uint32_t(count)<<' '<<std::uint32_t(total)<<' '<<mutated<<'\n';
}
void guards(){
 double w=1,lo=0,hi=10,rs=1,rf=-1,coefficient=1;int count=0,total=1,stores=0;TeamObserverWeightServices s;
 const int previous=std::fegetround();require(std::fesetround(FE_TONEAREST)==0);
 const auto refuses=[&](){bool refused=false;try{updateTeamObserverWeight({w,lo,hi,count,total},true,s);}catch(const std::invalid_argument&){refused=true;}require(refused&&w==1&&count==0&&total==1&&!stores);};
 refuses();s.rules=[&](){return TeamObserverRules{rs,rf,coefficient};};s.store=[&](auto,auto,auto){++stores;};
 for(double v:{std::numeric_limits<double>::infinity(),std::numeric_limits<double>::quiet_NaN(),1e-200,1e200}){rs=v;refuses();}rs=1;
 require(std::fesetround(FE_DOWNWARD)==0);refuses();require(std::fegetround()==FE_DOWNWARD);require(std::fesetround(previous)==0);
 std::cout<<"team observer weight guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
