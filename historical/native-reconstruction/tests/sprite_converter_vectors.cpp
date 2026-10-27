// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/Scenery.hpp"
#include <bit>
#include <iostream>
#include <sstream>
using namespace ra2;
int main(){try{
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);int format,nullMask,clipMask,initial,gradient;
  if(!(in>>format>>nullMask>>clipMask>>initial>>gradient))return 2;
  if((format!=1&&format!=3)||nullMask<0||nullMask>15||clipMask<0||clipMask>15||(gradient!=0&&gradient!=2))return 2;
  std::array<std::int32_t,2> state{initial,std::bit_cast<std::int32_t>(std::uint32_t(initial)^0x12345678u)};
  std::vector<Palette16> palettes(53);for(auto& row:palettes)row.fill(0x1234);
  ShpImage image{3,3,{{0,0,1,1,Bytes{42},format},{0,0,1,1,Bytes{42},format}}};
  for(int call=0;call<4;++call){
   const int owner=call%2;const bool absent=nullMask&(1<<call);
   const int flags=absent?std::bit_cast<std::int32_t>(std::uint32_t(initial)^0xfedcba98u):std::array<int,4>{0x6e00,0x6e01,0x4e00,0x4e01}[call];
   std::vector<std::uint16_t> colors(16,0x2222),depth(16,65535),alpha(16,128);
   const auto store=[&]{std::cout<<"W "<<owner<<' '<<state[owner]<<' ';};
   blitConvertedSpriteFrame({state[owner],palettes,store},absent?nullptr:&image,
       {call%2,flags,-3,call%2?0:gradient,1000},{2,2},clipMask&(1<<call)?PixelRect{0,0,0,0}:PixelRect{0,0,4,4},
       4,4,colors,depth,alpha);
   std::cout<<"R "<<state[0]<<' '<<state[1]<<' ';
   for(auto v:colors)std::cout<<v<<' ';for(auto v:depth)std::cout<<v<<' ';
  }
  std::cout<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
