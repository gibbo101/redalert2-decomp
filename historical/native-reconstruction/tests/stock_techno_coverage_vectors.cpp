// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/TechnoCoverageWorld.hpp"
#include "sim/StockTechnoCoverage.hpp"
#include <vector>
#include <cmath>
#include <cfenv>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
int main(int argc,char** argv){try{
 if(argc>1){
  if(std::string(argv[1])!="--guards")return 2;
  const void* current=nullptr;std::uint8_t active=0;std::int32_t range=0,coordinate=0;
  TechnoCoverageServices services{current};const TechnoCoverageActor actor{active,range,coordinate,coordinate,coordinate};
  changeTechnoCoverage(true,actor,services);current=&range;
  active=255;changeTechnoCoverage(true,actor,services);active=0;changeTechnoCoverage(false,actor,services);
  const auto refused=[&](auto action){bool caught=false;try{action();}catch(const std::invalid_argument&){caught=true;}if(!caught)throw std::runtime_error("coverage guard did not refuse");};
  refused([&]{changeTechnoCoverage(true,actor,services);});
  services.allowed30C=[]{return std::uint8_t(0);};changeTechnoCoverage(true,actor,services);
  services.allowed30C=[]{return std::uint8_t(255);};refused([&]{changeTechnoCoverage(true,actor,services);});
  range=1;refused([&]{changeTechnoCoverage(true,actor,services);});
  if(active!=1)throw std::runtime_error("entered refusal must not claim rollback");
  active=0;range=100;int queries=0;services.projectedHeight=[&](int){++queries;return 0;};
  refused([&]{changeTechnoCoverage(true,actor,services);});if(queries!=2||active!=1)throw std::runtime_error("host bound must preserve prior stores/queries");
  std::int32_t mode=0;const double scale=.125;RevealAreaWorld map;TechnoCoverageWorld world{mode,scale,map};int observed=0,views=0;
  services.localHouse=[](const void*){return std::uint8_t(42);};services.projectedHeight=[](int){return 44;};
  refused([&]{TechnoCoverageWorldBinding bad(services,world);});
  if(services.localHouse(current)!=42)throw std::runtime_error("failed binding changed caller");
  std::uint8_t byte=0;std::uint32_t flags=0;std::int32_t index=0;
  world.house=[&](const void*){++views;return TechnoCoverageHouseView{index,byte,byte,flags};};
  world.cell=[&](RevealAreaCell& cell){return TechnoCoverageCell{cell.flags12c,cell.counter130,cell.maximum134,index};};
  world.query=[&](char,int,int){++observed;};
  try{TechnoCoverageWorldBinding binding(services,world);if(observed||views)throw std::runtime_error("binding queried world");if(services.allied(current,current)!=1||services.allied(current,nullptr)!=0||views)throw std::runtime_error("alliance bypass entered House view");mode=1;int foreign=0;if(services.localHouse(&foreign)!=0||services.localHouse(current)!=1||views)throw std::runtime_error("mode bypass entered House view");mode=0;services.cell(0,0);}catch(const std::invalid_argument&){}
  if(services.localHouse(current)!=42||services.projectedHeight(7)!=44||observed!=5)throw std::runtime_error("unwinding did not restore bindings");
  const int rounding=std::fegetround();if(std::fesetround(FE_UPWARD))throw std::runtime_error("rounding test unavailable");
  (void)projectVisibilityHeight(728,.125);const auto restored=std::fegetround();std::fesetround(rounding);if(restored!=FE_UPWARD)throw std::runtime_error("projection changed caller rounding");
  const void* stockType=&range;std::int8_t signedRange=-2;int stockQueries=0;
  MissionBuildingTargetServices unusedAvailability;StockTechnoCoverageServices stockServices{stockType,{},{},{},unusedAvailability};
  stockServices.rangeADE=[&](const void* p)->const std::int8_t&{++stockQueries;if(p!=&range)throw std::invalid_argument("foreign type guard");return signedRange;};
  stockServices.owner1B4=[&]()->const void*{++stockQueries;return nullptr;};
  services.allowed30C=[]{return std::uint8_t(17);};services.typeRangeADE=[]{return std::int8_t(18);};services.owner3C=[&]{return current;};
  refused([&]{StockTechnoCoverageBinding bad(services,StockCoverageKind(1),stockServices);});
  try{StockTechnoCoverageBinding binding(services,StockCoverageKind::Infantry,stockServices);
   if(stockQueries||services.allowed30C()!=0||stockQueries)throw std::runtime_error("Infantry permission entered borrowed views");
   if(services.typeRangeADE()!=-2||services.owner3C()!=nullptr)throw std::runtime_error("stock views not borrowed");
   stockType=&coordinate;services.typeRangeADE();
  }catch(const std::invalid_argument&){}
  if(stockQueries!=3||services.allowed30C()!=17||services.typeRangeADE()!=18||services.owner3C()!=current)throw std::runtime_error("stock binding restore failed");
  {StockTechnoCoverageBinding binding(services,StockCoverageKind::Building,stockServices);refused([&]{(void)services.allowed30C();});}
  std::cout<<"guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);char tag;std::uint64_t scaleBits;std::array<std::int32_t,23> f{};std::array<std::int64_t,9> fields{};if(!(in>>tag>>scaleBits)||tag!='K')return 2;for(auto& n:f)if(!(in>>n))return 2;for(auto& n:fields)if(!(in>>n))return 2;std::array<std::int64_t,13> stock{};for(auto& n:stock)if(!(in>>n))return 2;std::uint64_t powerBits;if(!(in>>powerBits))return 2;const double scale=std::bit_cast<double>(scaleBits);if(!std::isfinite(scale)||std::abs(scale)>1)return 2;std::string extra;if(in>>extra)return 2;
  // add,active,range,type,allowed,current,local,allied,13d,566a,x,y,z,h0,h1,flags,c130,c134,c13c,cycle,mutation,owner,owner3c
  for(int k:{0,19})if(f[k]<0||f[k]>1)return 2;for(int k:{1,4,6,7,8,9})if(f[k]<0||f[k]>255)return 2;
  if(f[3]<-128||f[3]>127||f[5]<0||f[5]>2||f[20]<0||f[20]>5||f[21]<1||f[21]>2||f[22]<1||f[22]>2||f[2]<-64||f[2]>62)return 2;
  std::uint8_t active=std::uint8_t(f[1]);auto range=f[2],x=f[10],y=f[11],z=f[12];int handles[2]{};const auto hp=[&](int id)->const void*{return id?&handles[id-1]:nullptr;};const auto hid=[&](const void* p){return p==hp(1)?1:p==hp(2)?2:0;};const void* current=hp(f[5]);int owner=f[21];
  std::array<std::uint8_t,2> d{std::uint8_t(f[8]),std::uint8_t(f[8]^1)},b{std::uint8_t(f[9]),std::uint8_t(f[9]^1)},tail{255,254};
  std::array<std::uint32_t,3> flags{};flags.fill(std::uint32_t(f[15]));std::array<std::array<std::int32_t,4>,3> cells{};for(auto& c:cells)c={f[15],f[16],f[17],f[18]};int last=0,queries=0,heights=0;bool changed=false;
  const auto mutate=[&](int leaf){if(changed||f[20]!=leaf)return;changed=true;if(leaf==1){active=255;range=1;x=65535;y=-65535;z=728;}if(leaf==2){range=7;}if(leaf==3){range=2;x=17;y=19;z=999;current=hp(2);}if(leaf==4){owner=2;current=hp(2);}if(leaf==5){current=hp(2);}};
  TechnoCoverageServices s{current};
  s.allowed30C=[&]{std::cout<<"E P "<<f[4]<<' ';mutate(1);return std::uint8_t(f[4]);};
  s.typeRangeADE=[&]{std::cout<<"E T "<<f[3]<<' ';mutate(2);return std::int8_t(f[3]);};
  s.owner3C=[&]()->const void*{std::cout<<"E O "<<f[22]<<' ';mutate(4);return hp(f[22]);};s.owner1B4=[&]{return hp(owner);};
  s.house=[&](const void* p){int id=hid(p);if(!id)throw std::invalid_argument("null House");return TechnoCoverageHouse{d[id-1],b[id-1],tail[id-1]};};
  s.refresh634030=[]{std::cout<<"E F ";};s.redraw4E09A0=[](int v){std::cout<<"E D "<<v<<' ';};
  s.store=[&](char kind,int offset,int value){std::cout<<"W "<<kind<<' '<<(kind=='C'?last:kind=='H'?hid(current):0)<<' '<<offset<<' '<<value<<' ';};
  const auto mode=std::int32_t(fields[0]);
  std::array<std::int32_t,2> indexes{std::int32_t(fields[1]),std::int32_t(fields[5])};
  std::array<std::uint8_t,2> human{std::uint8_t(fields[2]),std::uint8_t(fields[6])},control{std::uint8_t(fields[3]),std::uint8_t(fields[7])};
  std::array<std::uint32_t,2> alliances{std::uint32_t(fields[4]),std::uint32_t(fields[8])};
  std::array<RevealAreaCell,3> mapCells{};std::vector<RevealAreaCell*> table(262144,nullptr);table[0]=&mapCells[0];mapCells[2].point={-30000,29000};
  for(int i=0;i<3;++i){mapCells[i].identity=i;mapCells[i].flags12c=std::uint32_t(f[15]);mapCells[i].counter130=f[16];mapCells[i].maximum134=f[17];}
  RevealAreaWorld map;map.primaryCells=table;map.fallback=&mapCells[2];
  map.fallbackStore=[&](char,TerrainCellPoint p){const auto v=std::uint32_t(std::uint16_t(p.x))|(std::uint32_t(std::uint16_t(p.y))<<16);std::cout<<"W F 0 36 "<<signed32(v)<<' ';};
  TechnoCoverageWorld world{mode,scale,map};
  world.house=[&](const void* p){const int i=hid(p)-1;if(i<0)throw std::invalid_argument("null House view");return TechnoCoverageHouseView{indexes[i],human[i],control[i],alliances[i]};};
  world.cell=[&](RevealAreaCell& c){last=c.identity;auto& words=cells[last];return TechnoCoverageCell{c.flags12c,c.counter130,c.maximum134,words[3]};};
  world.query=[&](char kind,int cx,int cy){if(kind!='C')return;const auto index=signed32(std::uint32_t(cy)*512u+std::uint32_t(cx));if(f[19]&&index>=0&&index<262144)table[std::size_t(index)]=&mapCells[std::size_t(queries%2)];++queries;};
  TechnoCoverageWorldBinding binding(s,world);
  // kind,health,530,54c,3fc,59c,1217,c6c,11fe,1206,powerMutation,alternateADE,padding
  std::int32_t health=std::int32_t(stock[1]),count=std::int32_t(stock[3]),disabled=std::int32_t(stock[4]),typeCount=std::int32_t(stock[7]);
  std::uint8_t enabled=std::uint8_t(stock[2]),operational=std::uint8_t(stock[5]),flag1217=std::uint8_t(stock[6]),flag11fe=std::uint8_t(stock[8]),flag1206=std::uint8_t(stock[9]),zeroByte=0;
  std::int32_t dummy=0;const void* null=nullptr;int types[2]{};const void* type=&types[0];
  const auto typeId=[&](const void* p){if(p==&types[0])return 0;if(p==&types[1])return 1;throw std::invalid_argument("foreign stock type");};
  std::array<std::int8_t,2> ranges{std::int8_t(f[3]),std::int8_t(stock[11])};std::uint8_t alternate1206=1;
  bool powerChanged=false;
  MissionBuildingTargetServices availability;
  availability.type=[&](const void* p){const auto id=typeId(p);return MissionBuildingTargetType{flag1217,typeCount,flag11fe,id?alternate1206:flag1206};};
  availability.housePower4E8330=[&](const void* p){std::cout<<"G "<<hid(p)<<' ';if(stock[10]){powerChanged=true;type=&types[1];count=2;owner=2;}return std::bit_cast<double>(powerBits);};
  StockTechnoCoverageServices stockServices{type,{},{},{},availability};stockServices.rangeADE=[&](const void* p)->const std::int8_t&{return ranges[std::size_t(typeId(p))];};
  stockServices.owner1B4=[&]{return hp(owner);};
  stockServices.building=[&]{return MissionBuildingTarget{&types,health,dummy,dummy,zeroByte,enabled,count,disabled,type,MissionExpirationOwnerView{[&]{return hp(owner);},[](const void*){throw std::logic_error("Unexpected availability Owner write");}},operational,zeroByte,null,null,dummy,null,null};};
  StockTechnoCoverageBinding stockBinding(s,StockCoverageKind(stock[0]),stockServices);
  const auto allowed=s.allowed30C;const auto rangeGetter=s.typeRangeADE;const auto ownerGetter=s.owner3C;
  s.allowed30C=[&]{const auto result=allowed();std::cout<<"E P "<<int(result)<<' ';mutate(1);return result;};
  s.typeRangeADE=[&]{const auto result=rangeGetter();std::cout<<"E T "<<int(result)<<' ';mutate(2);return result;};
  s.owner3C=[&]{const auto result=ownerGetter();std::cout<<"E O "<<hid(result)<<' ';mutate(4);return result;};
  const auto height=s.projectedHeight;const auto local=s.localHouse;const auto allied=s.allied;const auto lookup=s.cell;
  s.projectedHeight=[&](int v){const auto result=height(v);std::cout<<"E Z "<<v<<' '<<result<<' ';mutate(3);return result;};
  s.localHouse=[&](const void* p){const auto result=local(p);std::cout<<"E L "<<hid(p)<<' '<<int(result)<<' ';return result;};
  s.allied=[&](const void* p,const void* q){const auto result=allied(p,q);std::cout<<"E B "<<hid(p)<<' '<<hid(q)<<' '<<int(result)<<' ';return result;};
  s.cell=[&](auto cx,auto cy){const auto result=lookup(cx,cy);std::cout<<"E C "<<cx<<' '<<cy<<' '<<last<<' ';mutate(5);return result;};
  changeTechnoCoverage(bool(f[0]),{active,range,x,y,z},s);
  std::cout<<"R "<<int(active)<<' '<<range<<' '<<x<<' '<<y<<' '<<z<<' '<<hid(current)<<' '<<owner<<' '<<int(tail[0])<<' '<<int(tail[1])<<' '<<int(changed)<<' ';for(std::size_t i=0;i<cells.size();++i){std::cout<<signed32(mapCells[i].flags12c)<<' '<<mapCells[i].counter130<<' '<<mapCells[i].maximum134<<' '<<cells[i][3]<<' ';}std::cout<<"F "<<mapCells[2].point.x<<' '<<mapCells[2].point.y<<' '<<queries<<" V "<<count<<' '<<typeId(type)<<' '<<int(powerChanged)<<'\n';
 }
 return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
