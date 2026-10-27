// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SurfaceClip.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Surface clip fixture domain");}
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  FillRect a{0,0,4,4},b=a,c=a,d=a;bool refused=false;
  try{clipSurfacePair(a,b,a,d);}catch(const std::invalid_argument&){refused=true;}
  need(refused&&a==b);need(clipSurfacePair(a,b,c,d));
  std::cout<<"surface clip guards PASS\n";return 0;
 }
 need(argc==1);std::string line;
 while(std::getline(std::cin,line)){
  std::istringstream in(line);char tag;need(bool(in>>tag)&&tag=='C');
  std::array<FillRect,4> r;for(auto& rect:r)for(auto& v:rect)need(bool(in>>v));std::string tail;need(!(in>>tail));
  auto trace=[](auto owner,auto field,auto value){std::cout<<"S "<<owner<<' '<<field<<' '<<value<<' ';};
  const auto ok=clipSurfacePair(r[0],r[1],r[2],r[3],trace);
  std::cout<<"R "<<ok;for(const auto& rect:r)for(auto v:rect)std::cout<<' '<<v;std::cout<<'\n';
 }
 return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
