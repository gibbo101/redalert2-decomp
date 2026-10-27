// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/TacticalViewportMatrix.hpp"
#include <array>
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::runtime_error("Joined viewport vector guard");}
auto fields(const TacticalViewportState& s){return std::array{s.originX,s.originY,s.cellX,s.cellY,s.columns,s.rows};}
int main(int argc,char**){try{
 if(argc>1){
  const auto rounding=std::fegetround();need(std::fesetround(FE_UPWARD)==0);
  TacticalViewportState s;s.centerX=100;s.centerY=-100;const int w=10,h=20;
  updateTacticalViewportMatrix(s,w,h,voxelIdentity());
  need(s.originX==95&&s.originY==-110&&std::fegetround()==FE_UPWARD);
  bool refused=false;try{updateTacticalViewportMatrix(s,w,h,voxelIdentity(),[](int,int){throw std::runtime_error("observer");});}
  catch(const std::runtime_error&){refused=true;}need(refused&&std::fegetround()==FE_UPWARD);
  need(std::fesetround(rounding)==0);std::cout<<"Joined viewport guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);std::array<std::int64_t,16> f{};for(auto& v:f)need(bool(in>>v));std::string extra;need(!(in>>extra));
  TacticalViewportState s;s.centerX=int(f[0]);s.centerY=int(f[1]);const int w=int(f[2]),h=int(f[3]);Matrix matrix;
  for(unsigned i=0;i<12;++i)matrix[i]=std::bit_cast<float>(std::uint32_t(f[4+i]));
  auto joined=s;std::vector<std::pair<int,int>> stores;
  updateTacticalViewport(s,w,h,[&](TacticalViewportVector p){
   std::cout<<"I "<<std::bit_cast<std::uint32_t>(p.x)<<' '<<std::bit_cast<std::uint32_t>(p.y)<<' '<<std::bit_cast<std::uint32_t>(p.z)<<' ';
   const auto out=voxelTransform(matrix,{p.x,p.y,p.z});
   std::cout<<"O "<<std::bit_cast<std::uint32_t>(out.x)<<' '<<std::bit_cast<std::uint32_t>(out.y)<<' '<<std::bit_cast<std::uint32_t>(out.z)<<' ';
   return TacticalViewportVector{out.x,out.y,out.z};
  },[&](int offset,int v){stores.emplace_back(offset,v);std::cout<<"S "<<offset<<' '<<v<<' ';});
  std::size_t index=0;updateTacticalViewportMatrix(joined,w,h,matrix,[&](int o,int v){need(index<stores.size()&&stores[index++]==std::pair{o,v});});
  need(index==stores.size()&&fields(joined)==fields(s));
  std::cout<<"Z ";for(auto value:fields(s))std::cout<<value<<' ';std::cout<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
