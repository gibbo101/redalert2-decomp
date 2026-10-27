// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingFrame.hpp"
#include "sim/MissionTypedTagExpiration.hpp"
#include "sim/UnitDiscovery.hpp"
#include <bit>
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::runtime_error("Building frame vector domain");}
void event(int subject,int off,int value){std::cout<<subject<<' '<<off<<' '<<value<<' ';}
int main(int argc,char**){try{
 if(argc>1){int zero=0;BuildingAnimationFrameFields a{zero,zero,zero,zero,zero};bool refused=false;
  try{(void)buildingAnimationFrame(a,{});}catch(const std::invalid_argument&){refused=true;}need(refused);
  BuildingImageState image;BuildingFrameTypeState t;BuildingFrameServices s;s.type=[&]{return BuildingFrameType{image,t};};
  refused=false;try{(void)buildingAnimationFrame(a,s);}catch(const std::invalid_argument&){refused=true;}need(refused);
  t.flag1359=128;need(buildingAnimationFrame(a,s)==0);t.flag1359=0;
  s.mission16c=[&]{zero=-1;return 19;};refused=false;
  try{(void)buildingAnimationFrame(a,s);}catch(const std::invalid_argument&){refused=true;}need(refused);
  zero=0;s.mission16c=[&]{zero=INT32_MIN;return 19;};need(buildingAnimationFrame(a,s)==-1);
  zero=1;refused=false;try{(void)buildingAnimationFrame(a,s);}catch(const std::invalid_argument&){refused=true;}need(refused);
  std::cout<<"Building frame guards PASS\n";return 0;}
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream input(line);std::array<std::int64_t,27> v{};for(auto& n:v){need(bool(input>>n));need(n>=INT32_MIN&&n<=INT32_MAX);}
  std::uint64_t b0,b1;need(bool(input>>b0>>b1));std::string extra;need(!(input>>extra));
  BuildingImageState images[2];BuildingFrameTypeState types[2];int strengths[2]={int(v[13]),100};
  for(int id=0;id<2;++id){auto& im=images[id];auto& t=types[id];
   t.flag1359=v[1];t.flag135a=v[2];im.flag1351=v[3];t.flag121e=v[4];im.count137c=std::bit_cast<std::int32_t>(std::uint32_t(v[14])+std::uint32_t(id));im.startC8c=v[15];im.countC90=v[16];
   for(int i=0;i<5;++i){t.sequences[i].start=v[17+i*2];t.sequences[i].count=v[18+i*2];}
   if(id){im.startC8c=17;im.countC90=23;for(int i=0;i<5;++i)t.sequences[i]={i*11,100+i,0};}
  }
  int stage=v[5],frame=v[6],f4ec=v[7],f4f0=v[8],field564=v[9],health=v[12],type=0;
  UnitDiscoveryActor mission;mission.mission98=v[10];mission.queuedA0=v[11];
  double threshold=std::bit_cast<double>(b0),alternate=std::bit_cast<double>(b1);bool mutated=false;
  const auto mutate=[&](int child){const int mode=v[0];if(mutated||!mode)return;
   if((mode==1||mode==5)&&child!=0)return;if(mode>=2&&mode<=4&&child!=1)return;
   mutated=true;event(4,child,mode);
   if(mode==1||mode==5){type=1;stage=mode==5?INT32_MIN:2;frame=999;}
   else if(mode==2||mode==3){type=1;stage=mode==2?1:2;health=0;}
   else if(mode==4){images[type].count137c=INT32_MAX;threshold=std::bit_cast<double>(std::uint64_t(0x7ff8000000000000));}
  };
  BuildingFrameServices s;s.type=[&]{return BuildingFrameType{images[type],types[type]};};
  s.mission16c=[&]{event(3,0,0);mutate(0);return unitDiscoveryMission(mission);};
  s.healthRatio5d4540=[&]{event(3,1,0);return missionExpirationHealthRatio(health,[&]()->const int&{event(3,2,0);mutate(1);return strengths[type];});};
  s.threshold1368=[&]{return threshold;};s.threshold1370=[&]{return alternate;};s.read=event;
  const int result=buildingAnimationFrame({frame,stage,f4ec,f4f0,field564},s);
  std::cout<<"F "<<result<<' '<<type<<' '<<stage<<' '<<frame<<' '<<health<<' '<<images[type].count137c<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}}
