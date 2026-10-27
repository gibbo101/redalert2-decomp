// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingImage.hpp"
#include <array>
#include <cfenv>
#include <bit>
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::runtime_error("Building image vector domain");}
int main(int argc,char**){try{
 if(argc>1){BuildingImageState s;BuildingTypeBoundsState b;const int theater=0;
  need(!ensureBuildingPrimaryImage(s,{})&&!ensureBuildingSecondaryImage(s,b,theater,{}));
  s.demand13e0=1;s.primary13eb="X.SHP";bool refused=false;try{(void)ensureBuildingPrimaryImage(s,{});}catch(const std::invalid_argument&){refused=true;}need(refused);
  const auto previous=std::fegetround();need(std::fesetround(FE_UPWARD)==0);s.demand13e1=0;need(!ensureBuildingSecondaryImage(s,b,theater,{})&&std::fegetround()==FE_UPWARD);need(std::fesetround(previous)==0);
  int image=0;BuildingImageServices io;io.construct=[](int,const std::string&){};io.cache=[](int,int){};
  io.load=[&](int)->const void*{return &image;};io.finish=[](int,int){};
  io.frameCount=[](const void*){return std::int16_t(6);};io.timing1178=[]{return .6;};
  s.demand13e1=1;s.secondaryBf4="CAARMY04";need(std::fesetround(FE_UPWARD)==0);
  need(ensureBuildingSecondaryImage(s,b,theater,io)==&image&&s.countC90==3&&s.durationC94==179&&std::fegetround()==FE_UPWARD);
  need(std::fesetround(previous)==0);
  s.primary13eb=std::string(19,'X');io.load=[](int)->const void*{return nullptr;};refused=false;
  try{(void)ensureBuildingPrimaryImage(s,io);}catch(const std::invalid_argument&){refused=true;}need(refused&&!s.primaryA4);
  s.primary13eb=std::string(25,'X');refused=false;
  try{(void)ensureBuildingPrimaryImage(s,io);}catch(const std::invalid_argument&){refused=true;}need(refused);
  std::cout<<"Building image guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);int op,mode,theater,p,secondary,owned,demandP,demandS,flagB9c,flag1351,count137c,start,count,duration,first,second,frames,repeat;std::uint64_t timingBits;std::string name;
  need(bool(in>>op>>mode>>theater>>p>>secondary>>owned>>demandP>>demandS>>flagB9c>>flag1351>>count137c>>start>>count>>duration>>first>>second>>frames>>repeat>>timingBits>>name));if(name=="-")name.clear();
  std::array<int,4> ids{};auto ptr=[&](int id)->const void*{need(id>=0&&id<4);return id?&ids[id]:nullptr;};auto identify=[&](const void* v){if(!v)return 0;for(int i=1;i<4;++i)if(v==&ids[i])return i;throw std::invalid_argument("Foreign image pointer");};
  BuildingImageState a;a.primaryA4=ptr(p);a.ownedA8=std::uint8_t(owned);a.demand13e0=std::uint8_t(demandP);a.demand13e1=std::uint8_t(demandS);a.flag1351=std::uint8_t(flag1351);a.count137c=count137c;a.startC8c=start;a.countC90=count;a.durationC94=duration;a.primary13eb=name;a.secondaryBf4=name;
  BuildingTypeBoundsState b;b.secondaryB98=ptr(secondary);b.flagB9c=std::uint8_t(flagB9c);double timing=std::bit_cast<double>(timingBits);int loads=0;bool mutated=false;
  const auto mutate=[&](int point){if(mutated||!mode)return;if((mode==1||mode==2||mode==3)&&point!=1)return;if(mode==4&&point!=2)return;if(mode==5&&point!=3)return;
   mutated=true;std::cout<<"M "<<mode<<' ';
   if(mode==1){a.primary13eb="CTRETRY.SHP";a.secondaryBf4="CTRETRY";}
   if(mode==2){a.flag1351=255;a.count137c=2147483647;}
   if(mode==3){a.primaryA4=ptr(3);b.secondaryB98=ptr(3);}
   if(mode==4){a.primaryA4=ptr(3);b.secondaryB98=ptr(3);}
   if(mode==5){a.flag1351=128;a.count137c=-2;}
  };
  BuildingImageServices s{
   [&](int id,const std::string& file){std::cout<<"C "<<id<<' '<<file<<' ';},
   [&](int id,int value){std::cout<<"K "<<id<<' '<<value<<' ';},
   [&](int id){const int result=loads++%2==0?first:second;std::cout<<"L "<<id<<' '<<result<<' ';mutate(1);return ptr(result);},
   [&](int id,int phase){std::cout<<"D "<<id<<' '<<phase<<' ';mutate(2);},
   [&](const void* image){std::cout<<"H "<<identify(image)<<' '<<frames<<' ';mutate(3);return std::int16_t(frames);},
   [&]{std::cout<<"T ";return timing;},
   [&](int off,const void* v){std::cout<<"P "<<off<<' '<<identify(v)<<' ';},
   [&](int off,int bytes,int value){std::cout<<"S "<<off<<' '<<bytes<<' '<<value<<' ';}};
  for(int i=0;i<repeat;++i){loads=0;const auto result=op==0?ensureBuildingPrimaryImage(a,s):ensureBuildingSecondaryImage(a,b,theater,s);std::cout<<"R "<<identify(result)<<' ';}
  std::cout<<"F "<<identify(a.primaryA4)<<' '<<identify(b.secondaryB98)<<' '<<unsigned(a.ownedA8)<<' '<<unsigned(b.flagB9c)<<' '<<unsigned(a.flag1351)<<' '<<a.count137c<<' '<<a.startC8c<<' '<<a.countC90<<' '<<a.durationC94<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
