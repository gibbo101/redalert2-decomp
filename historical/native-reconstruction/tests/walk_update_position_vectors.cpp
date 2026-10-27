// SPDX-License-Identifier: GPL-3.0-or-later
// Reuse the complete child fixture, including every owner and service binding.
#define main standalonePositionMain
#include "infantry_update_position_effects_e1_vectors.cpp"
#undef main
#include "sim/WalkMovement.hpp"
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include "render/Lighting.hpp"
#include "render/VoxelRaster.hpp"
#include <cfenv>
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
 require(argc==4);
 const auto render=readRenderData(readFile(argv[1]),PatchedEngineSha);
 const auto raster=readRasterData(readFile(argv[2]),PatchedEngineSha);
 const auto direction=readDirectionData(readFile(argv[3]),PatchedEngineSha);
 const auto saved=std::fegetround();std::fesetround(FE_TONEAREST);
 const double radians=direction.pi/-32767.;std::fesetround(saved);
 const WalkMovementNumerics numeric{direction,radians,[&](double v){return tableSqrt(render,v);},
  [&](double v){return tableSine(raster,v);},[&](double v){return tableCosine(raster,v);}};
 std::string line;
 while(std::getline(std::cin,line)){
  std::istringstream in(line);const int distance=take<int>(in),lateOn=take<int>(in),late76=take<int>(in),late7a=take<int>(in);
  require(distance==0||distance==1||distance==16);
  require((lateOn==1&&late76==0&&late7a==0)||(lateOn==0&&late76==0&&late7a==0)||
   (lateOn==1&&late76==255&&late7a==0)||(lateOn==1&&late76==0&&late7a==128));
  std::ostringstream suffix;
  run(in,[&](ActorGroundState& ground,std::uint8_t& on,Coord destination,const std::function<void()>& child){
   require(on==1&&ground.position==Coord{15040,22976,208}&&destination==Coord{15232,22912,208});const auto head=ground.position;ground.position.x-=distance;ground.marked74=1;
   Facing body{0,0,37,0,256};int frozen=0;double percent=.375;std::uint8_t a=0,b=0,flag76=0,flag7a=0;
   std::array<std::int32_t,24> route;for(int i=0;i<24;++i)route[std::size_t(i)]=i?100+i:-1;
   TerrainCellPoint cell{0x5678,0x1234};std::int8_t secondary=-1;
   WalkMovementState state{destination,head,1,173,197};
   std::vector<std::string> events;int callbacks=0;
   WalkArrivalContext arrival{{route,cell,on,flag76,flag7a,secondary},{}};
   arrival.services.release=[&](const Coord&){events.emplace_back("release");};
   arrival.services.occupy=[&](const Coord&){events.emplace_back("occupy");};
   arrival.services.notify=[&](int kind){require(kind==2&&ground.position==head&&state.head==Coord{}&&!ground.marked74);
    ++callbacks;events.emplace_back("child");child();events.emplace_back("return");
    on=std::uint8_t(lateOn);flag76=std::uint8_t(late76);flag7a=std::uint8_t(late7a);};
   arrival.services.destination=[&](int,int){events.emplace_back("completion");};
   arrival.services.resetMovement=[&]{events.emplace_back("reset");};
   WalkMovementServices services;services.speed=[] {return 1;};
   services.placement.floor=[&](Coord){return head.z;};
   services.placement.mark=[&](int kind){events.emplace_back("mark"+std::to_string(kind));ground.marked74=std::uint8_t(kind);};
   const auto result=processSelectedWalk(state,{ground,body,frozen,percent,a,b},numeric,services,arrival,37,104,104);
   suffix<<"Z "<<unsigned(result)<<' '<<ground.position.x<<' '<<ground.position.y<<' '<<ground.position.z<<' ';
   for(auto value:route)suffix<<value<<' ';
   for(auto q:{state.head,state.destination})suffix<<q.x<<' '<<q.y<<' '<<q.z<<' ';
   suffix<<unsigned(state.moving34)<<' '<<unsigned(state.inProcessing35)<<' '<<unsigned(state.reallyMoving36)<<' '
    <<unsigned(on)<<' '<<unsigned(flag76)<<' '<<unsigned(flag7a)<<' '<<callbacks<<' ';
   for(const auto& value:events)suffix<<value<<' ';
  });
  std::cout<<suffix.str()<<'\n';
 }
 return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
