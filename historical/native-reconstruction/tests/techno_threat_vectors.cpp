// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TechnoThreat.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
int main(int argc,char** argv){try{
 if(argc>1){if(std::string(argv[1])!="--guards")return 2;
  std::int32_t zero=0;TechnoThreatServices s;bool caught=false;
  try{technoThreat(zero,zero,s);}catch(const std::invalid_argument&){caught=true;}if(!caught)return 3;
  s.type80=[]()->const void*{return nullptr;};if(technoThreat(zero,zero,s)!=0)return 4;
  s.type80=[&]()->const void*{return &zero;};caught=false;try{technoThreat(zero,zero,s);}catch(const std::invalid_argument&){caught=true;}if(!caught)return 5;
  s.kind2C=[]{return 6;};std::int32_t one=1;if(technoThreat(one,zero,s)!=0)return 6;
  caught=false;try{technoThreat(zero,zero,s);}catch(const std::invalid_argument&){caught=true;}if(!caught)return 7;
  std::cout<<"guards PASS\n";return 0;}
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);char tag;int root,kind,present;std::int32_t value,field,multiplier;
  if(!(in>>tag>>root>>kind>>present>>value>>field>>multiplier)||tag!='T'||root<0||root>1||(kind!=6&&kind!=15)||(present!=0&&present!=1))return 2;
  std::string extra;if(in>>extra)return 2;
  TechnoThreatServices s;s.type80=[&]()->const void*{std::cout<<"E 128 ";return present?&value:nullptr;};
  s.kind2C=[&]{std::cout<<"E 44 ";return kind;};s.value598=[&](const void* p)->const std::int32_t&{if(p!=&value)throw std::invalid_argument("foreign saved type");return value;};
  auto result=root?buildingThreatValue564(field):technoThreat(field,multiplier,s);
  std::cout<<"R "<<result<<'\n';
 }
 return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
