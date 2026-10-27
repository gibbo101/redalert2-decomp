// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SurfaceRadarPixel.hpp"
#ifdef RA2_RADAR_SURFACE_PIXELS
#include "render/RadarSurfacePixels.hpp"
#include "assets/PreparedData.hpp"
#endif
#ifdef RA2_RADAR_DISCOVERY
#include "render/RadarDiscovery.hpp"
#ifdef RA2_RADAR_MAP
#include "render/RadarMap.hpp"
#ifdef RA2_RADAR_ACTORS
#include "render/RadarActors.hpp"
#endif
#include <bit>
#endif
#endif
#ifdef RA2_COVERAGE_RADAR
#include "platform/CoverageRadar.hpp"
#include "sim/RevealArea.hpp"
#endif
#ifdef RA2_RADAR_REFRESH
#include "render/RadarRefresh.hpp"
#endif
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void need(bool v){if(!v)throw std::invalid_argument("Radar pixel fixture domain");}
const std::array<float,7> scales={1,.5f,2,.75f,-1,0x1p-149f,3};
const std::array<std::array<std::int32_t,6>,3> shiftValues={{{11,3,0,3,5,2},{10,3,0,3,5,3},{31,31,33,-1,-32,40}}};
void run(std::istream& in){
 char op;std::array<std::int64_t,33> f{};
#ifdef RA2_RADAR_SURFACE_PIXELS
 #ifdef RA2_RADAR_DISCOVERY
 #ifdef RA2_RADAR_MAP
 #ifdef RA2_RADAR_ACTORS
#ifdef RA2_COVERAGE_RADAR
#ifdef RA2_COVERAGE_RADAR_REFRESH
 need(bool(in>>op)&&op=='F');
#else
 need(bool(in>>op)&&op=='C');
#endif
#else
#ifdef RA2_RADAR_REFRESH
 need(bool(in>>op)&&op=='X');
#else
 need(bool(in>>op)&&op=='A');
#endif
#endif
#else
 need(bool(in>>op)&&op=='M');
#endif
#else
 need(bool(in>>op)&&op=='U');
#endif
#else
 need(bool(in>>op)&&op=='J');
#endif
#else
 need(bool(in>>op)&&op=='R');
#endif
 for(auto& v:f)need(bool(in>>v));
#ifdef RA2_RADAR_SURFACE_PIXELS
 int pixelBpp=0;std::uint32_t pixelOffset=0;std::int32_t pixelDepth=0;need(bool(in>>pixelBpp>>pixelOffset>>pixelDepth));need((pixelBpp==1||pixelBpp==2)&&pixelOffset>=256&&pixelOffset<=259);
#endif
#ifdef RA2_RADAR_DISCOVERY
 std::int32_t discoveryDivisor=0,discoveryCount=0;std::uint32_t discoveryFlags=0;need(bool(in>>discoveryDivisor>>discoveryFlags>>discoveryCount)&&discoveryDivisor!=0&&discoveryDivisor!=-1);
#endif
#ifdef RA2_RADAR_MAP
 std::int32_t levelHeight=0,alternateHeight=0;int floorFlags=0,heightSwapAt=0;std::array<int,8> cellFloorFields{};
 need(bool(in>>levelHeight>>floorFlags)&&floorFlags>=0&&floorFlags<=255);
 for(unsigned i=0;i<8;++i){need(bool(in>>cellFloorFields[i]));need(i%2?(cellFloorFields[i]>=0&&cellFloorFields[i]<=20):(cellFloorFields[i]>=-128&&cellFloorFields[i]<=127));}
 need(bool(in>>heightSwapAt>>alternateHeight)&&heightSwapAt>=0&&heightSwapAt<=8);
#endif
#ifdef RA2_RADAR_ACTORS
 std::array<std::int64_t,9> actorFields{};for(auto& v:actorFields)need(bool(in>>v));
 need(actorFields[0]>=INT32_MIN&&actorFields[0]<=INT32_MAX&&actorFields[1]>=0&&actorFields[1]<8&&actorFields[2]>=0&&actorFields[2]<4&&actorFields[3]>=0&&actorFields[3]<=UINT32_MAX&&actorFields[4]>=0&&actorFields[4]<4&&actorFields[5]>=0&&actorFields[5]<16&&actorFields[6]>=0&&actorFields[6]<2&&actorFields[7]>=0&&actorFields[7]<3&&actorFields[8]>=0&&actorFields[8]<64&&(actorFields[7]==0||!(actorFields[8]&1))&&(actorFields[7]!=0||!(actorFields[8]&8)));
#endif
#ifdef RA2_COVERAGE_RADAR
 std::array<std::int64_t,13> coverageFields{};for(auto& v:coverageFields)need(bool(in>>v));
 need(coverageFields[0]>=0&&coverageFields[0]<2&&coverageFields[1]>=0&&coverageFields[1]<=255&&coverageFields[2]>=-3&&coverageFields[2]<=2&&coverageFields[3]>=-3&&coverageFields[3]<=2&&coverageFields[4]>=0&&coverageFields[4]<=255);
 for(int i=5;i<=7;++i)need(coverageFields[i]>=INT32_MIN&&coverageFields[i]<=INT32_MAX);
 for(int i=8;i<=9;++i)need(coverageFields[i]>=0&&coverageFields[i]<=255);
 for(int i=10;i<12;++i)need(coverageFields[i]>=INT32_MIN&&coverageFields[i]<=INT32_MAX);
 need(coverageFields[12]>=0&&coverageFields[12]<3);
 need(f[0]==1&&f[9]!=0&&f[31]==0&&actorFields[5]==0&&actorFields[8]==0);
#endif
#ifdef RA2_RADAR_REFRESH
 std::array<int,5> refreshFields{};for(auto& v:refreshFields)need(bool(in>>v));
 need(refreshFields[0]>=0&&refreshFields[0]<2&&refreshFields[1]>=1&&refreshFields[1]<=2&&refreshFields[2]>=0&&refreshFields[2]<=2&&refreshFields[3]>=0&&refreshFields[3]<=1&&refreshFields[4]>=0&&refreshFields[4]<=255);
 need(f[0]==1&&f[2]>=1&&f[2]<=5&&f[3]>=1&&f[3]<=3&&f[31]==0&&actorFields[5]==0&&actorFields[8]==0);
#endif
 std::string tail;need(!(in>>tail));
 for(int i=0;i<33;++i)need(f[i]>=INT32_MIN&&f[i]<=((i==23)?std::int64_t(UINT32_MAX):INT32_MAX));
 need(f[0]>=0&&f[0]<=1&&f[1]>=-1&&f[1]<3&&f[2]>=-2&&f[2]<=8&&f[3]>=-2&&f[3]<=8&&f[6]>=0&&f[6]<7&&f[10]>=0&&f[10]<=255&&f[11]>=0&&f[11]<=255&&f[12]>=-1&&f[12]<=3&&f[13]>=0&&f[13]<=3&&f[18]>=-1&&f[18]<3&&f[22]!=0&&f[24]>=0&&f[24]<3&&f[31]>=0&&f[31]<=12&&f[32]>=0&&f[32]<65536&&(!f[0]||f[9]!=0));for(int i=14;i<=17;++i)need(f[i]>=0&&f[i]<8);
 int houses[3]={0,1,2},actors[3]={0,1,2};const void* owners[3]={&houses[0],&houses[1],&houses[2]};const void* current=f[1]<0?nullptr:&houses[f[1]];
 std::int32_t mode=f[9],screenX=f[29],screenY=f[30],frame=f[21];float scale=scales[f[6]];std::int32_t ox=f[7],oy=f[8];std::array<std::int32_t,6> shifts=shiftValues[f[24]];
 RefreshSurfaceVirtuals tables[2];RefreshSurface surfaces[2]={{&tables[0],std::int32_t(f[2]),std::int32_t(f[3])},{&tables[1],5,2}};auto* first=&surfaces[0];auto* second=&surfaces[1];RefreshRect point={std::int32_t(f[4]),std::int32_t(f[5]),123,456},dirty={std::int32_t(f[25]),std::int32_t(f[26]),std::int32_t(f[27]),std::int32_t(f[28])};
 SurfaceMarkEntry entries[3];for(int i=0;i<3;++i)entries[i]={&actors[i],point[0],point[1],0xabc000u+unsigned(i)};
 if(f[13]==1)entries[0].x=fillAdd(entries[0].x,1);if(f[13]==2)for(auto& e:entries)e.x=fillAdd(e.x,10);if(f[13]==3){entries[0].x=0;entries[0].y=0;entries[1].x=1;entries[1].y=0;entries[2].x=2;entries[2].y=1;}
 SurfaceMarkBuckets roots[2];for(auto& b:roots[0])b={entries,std::int32_t(f[12])};for(auto& b:roots[1])b={{entries+1,2},2};auto* buckets=&roots[0];std::array<std::int32_t,3> starts,remaining;starts.fill(f[19]);remaining.fill(f[20]);SurfaceMarkScheme scheme{nullptr,0x1234};bool changed=false;RadarMapPoint* liveMap=nullptr;
 auto aid=[&](const void* p){for(int i=0;i<3;++i)if(p==&actors[i])return i;throw std::invalid_argument("Foreign radar actor");};auto hid=[&](const void* p){if(!p)return -1;for(int i=0;i<3;++i)if(p==&houses[i])return i;throw std::invalid_argument("Foreign radar House");};auto sid=[&](const RefreshSurface& s){need(&s==&surfaces[0]||&s==&surfaces[1]);return &s==&surfaces[1]?1:0;};
 auto mutate=[&](int stage){if(changed||f[31]!=stage)return;changed=true;const auto m=f[32];if(m&1){point[0]=1;point[1]=1;}if(m&2)first=&surfaces[1];if(m&4)second=&surfaces[0];if(m&8)mode=mode?0:1;if(m&16){entries[0].actor=&actors[2];entries[0].x=point[0];entries[0].y=point[1];}if(m&32)current=&houses[2];if(m&64)dirty={100,100,0,0};if(m&128){starts[0]=-1;remaining[0]=3;}if(m&256)shifts=shiftValues[2];if(m&512){screenX=INT32_MAX;screenY=INT32_MIN;}if(m&1024)buckets=&roots[1];if(m&2048)surfaces[0].table=&tables[1];if(m&4096)owners[0]=&houses[2];if(m&8192)for(auto& b:roots[0])b.count=0;if(m&16384)scheme.index330=0xabc;if(m&32768){need(liveMap!=nullptr);*liveMap={111,222,333};}};
 for(int k=0;k<2;++k){tables[k].rect78=[&](auto& s,auto& r){auto* out=refreshSurfaceRect(s,r);std::cout<<"G "<<sid(s)<<' '<<s.width<<' '<<s.height<<' ';mutate(1);return out;};tables[k].width7C=refreshSurfaceWidth;tables[k].height80=refreshSurfaceHeight;}
 RadarPixelVirtuals pixelTables[2];for(int k=0;k<2;++k){pixelTables[k].get28=[&,k](auto& s,auto& p){std::cout<<"V "<<k<<' '<<sid(s)<<' '<<p[0]<<' '<<p[1]<<' '<<f[23]<<' ';mutate(11);return std::uint32_t(f[23]);};pixelTables[k].set24=[&,k](auto& s,auto& p,auto color){std::cout<<"W "<<k<<' '<<sid(s)<<' '<<p[0]<<' '<<p[1]<<' '<<color<<' ';mutate(12);};}
 auto discovery=[&](RadarMapPoint& p,int which){liveMap=&p;const auto value=std::uint8_t(f[which==1?10:11]);std::cout<<(which==1?"H ":"I ")<<p.x<<' '<<p.y<<' '<<p.z<<' '<<unsigned(value)<<' ';mutate(which==1?3:4);return value;};
#ifdef RA2_COVERAGE_RADAR
 bool coverageRadarDrew=false;
#endif
 RadarPixelServices s{current,mode,first,second,scale,ox,oy,screenX,screenY,dirty,buckets,shifts,frame,
 [&](auto* t)->const RadarPixelVirtuals&{need(t==&tables[0]||t==&tables[1]);return pixelTables[t==&tables[1]];},
 [&](auto& p){liveMap=&p;std::cout<<"F "<<p.x<<' '<<p.y<<' '<<p.z<<' ';mutate(2);return -37;},[&](auto& p){return discovery(p,1);},[&](auto& p){return discovery(p,2);},
 [&](const void* p){return owners[aid(p)];},[&](const void* p){const auto h=hid(p);const auto result=std::uint8_t((f[14]>>h)&1);std::cout<<"L "<<h<<' '<<unsigned(result)<<' ';mutate(5);return result;},
 [&](const void* p){const auto a=aid(p);std::cout<<"T "<<a<<' ';mutate(6);return std::uint8_t((f[15]>>a)&1);},
 [&](const void* h,const void* p){const auto a=aid(p);const auto result=std::uint8_t((f[16]>>a)&1);std::cout<<"A "<<hid(h)<<' '<<a<<' '<<unsigned(result)<<' ';mutate(7);return result;},
 [&](const void* p){const auto a=aid(p);const auto result=std::uint8_t((f[17]>>a)&1?255:0);std::cout<<"C "<<a<<' '<<unsigned(result)<<' ';mutate(8);return result;},
 [&](const void* p,std::uint32_t arg)->const void*{need(arg==0);const void* result=f[18]<0?nullptr:&houses[f[18]];std::cout<<"O "<<aid(p)<<' '<<hid(result)<<' ';mutate(9);return result;},
 [&](const void* p){const auto h=hid(p);return std::array<std::uint8_t,3>{std::uint8_t(19+h*77),std::uint8_t(37+h*33),std::uint8_t(251-h*61)};},
 [&](auto category){need(category==1);std::cout<<"S ";mutate(10);return &scheme;},
 [&](const void* p)->RadarPixelTimer{const auto a=aid(p);return {starts[a],remaining[a]};},[&]{std::cout<<"B "<<f[22]<<' ';return std::int32_t(f[22]);},
 [&](auto at,auto value){
#ifdef RA2_COVERAGE_RADAR
 coverageRadarDrew=true;
#endif
 std::cout<<"D "<<at<<' '<<value<<' ';}};
#ifdef RA2_RADAR_SURFACE_PIXELS
 Bytes pixelStorage[2]={Bytes(2048),Bytes(2048)};std::int32_t pixelLocks[2]={pixelDepth,pixelDepth},pixelFormats[2]={pixelBpp,3-pixelBpp};
 for(int k=0;k<2;++k)for(unsigned i=0;i<2048;++i)pixelStorage[k][i]=std::uint8_t(i*29+0x34+k*37);
 std::array<const RefreshSurfaceVirtuals*,2> stockTables{&tables[0],&tables[1]};
 RadarSurfacePixelWorld pixelWorld{stockTables,[&](RefreshSurface& a)->SurfacePixelView{const auto id=sid(a);return {a.width,pixelLocks[id],pixelFormats[id],pixelOffset,pixelStorage[id],{},true};},
 [&](char kind,const auto* table,auto& a,auto& p,auto color){const auto id=table==&tables[1]?1:0;need(table==&tables[id]);std::cout<<kind<<' '<<id<<' '<<sid(a)<<' '<<p[0]<<' '<<p[1]<<' '<<color<<' ';mutate(kind=='V'?11:12);},
 [&](auto value){std::cout<<"E "<<value<<' ';},[&](auto& a,auto p,auto n,auto value){std::cout<<"N "<<sid(a)<<' '<<p<<' '<<n<<' '<<value<<' ';},[&](auto& a,auto depth){std::cout<<"K "<<sid(a)<<' '<<depth<<' ';}};
 RadarSurfacePixelsBinding pixelBinding(s,pixelWorld);
#endif
#ifdef RA2_RADAR_DISCOVERY
#ifdef RA2_RADAR_MAP
 std::array<MapCellInput,4> terrain;std::array<std::uint32_t,4> flags12c{discoveryFlags,0,8,discoveryFlags};std::array<std::int32_t,4> counts{discoveryCount,1,-1,discoveryCount};
 const std::array<MapInputPosition,4> mapPoints{{{3,4},{1,1},{-1,0},{-7,5}}};
 for(unsigned i=0;i<4;++i){terrain[i].position=mapPoints[i];terrain[i].flags=0;terrain[i].level=std::int8_t(cellFloorFields[2*i]);terrain[i].slope=std::uint8_t(cellFloorFields[2*i+1]);}
 std::vector<MapCellInput*> mapSlots(262144,nullptr);mapSlots[0]=&terrain[0];mapSlots[513]=&terrain[1];mapSlots[1026]=&terrain[2];
 MapFloorHeightState floorState;floorState.flags=std::uint8_t(floorFlags);floorState.height=73;floorState.scale=.25;floorState.planes[0].x=1;
 MapFloorHeightWorld floorWorld{mapSlots,&terrain[3],[](auto p){std::cout<<"f "<<p.x<<' '<<p.y<<' ';}};
 MapVisibilityState visibilityState{discoveryDivisor,7,9,1};
 RadarMapWorld radarMap{floorWorld,[&](const auto& cell)->RadarMapDiscoveryFields{const auto id=&cell-terrain.data();need(id>=0&&id<4);return {flags12c[id],counts[id]};},
 [](char k,TerrainCellPoint p){std::cout<<k<<' '<<p.x<<' '<<p.y<<' ';},
 [](const auto& cell,int direction){std::cout<<"n "<<cell.point.x<<' '<<cell.point.y<<' '<<direction<<' ';},
 [](const auto& cell){std::cout<<"c "<<cell.point.x<<' '<<cell.point.y<<' '<<cell.count13c<<' ';}};
 int floorCalls=0;
 RadarMapBinding mapBinding(s,floorState,levelHeight,visibilityState,radarMap,
 [&](auto& p){liveMap=&p;std::cout<<"F "<<p.x<<' '<<p.y<<' '<<p.z<<' ';mutate(2);if(++floorCalls==heightSwapAt){levelHeight=alternateHeight;std::cout<<"g "<<levelHeight<<' ';}},
 [](auto value){std::cout<<"t "<<value<<' ';},
 [&](auto& p,bool count,auto value){liveMap=&p;std::cout<<(count?"I ":"H ")<<p.x<<' '<<p.y<<' '<<p.z<<' '<<unsigned(value)<<' ';mutate(count?4:3);});
#else
 std::array<MapVisibilityCell,4> mapCells{{{{3,4},discoveryFlags,0,discoveryCount},{{1,1},0,2,1},{{-1,0},8,0,-1},{{-7,5},discoveryFlags,0,discoveryCount}}};
 std::vector<MapVisibilityCell*> mapSlots(262144,nullptr);mapSlots[0]=&mapCells[0];mapSlots[513]=&mapCells[1];mapSlots[1026]=&mapCells[2];
 MapVisibilityState visibilityState{discoveryDivisor,7,9,1};MapVisibilityWorld visibilityWorld{mapSlots,&mapCells[3],{1,1}};
 visibilityWorld.query=[](char k,TerrainCellPoint p){std::cout<<k<<' '<<p.x<<' '<<p.y<<' ';};visibilityWorld.fallbackStore=[](auto p){std::cout<<"f "<<p.x<<' '<<p.y<<' ';};
 visibilityWorld.neighbor=[&](const auto& c,int d){std::cout<<"n "<<(&c-mapCells.data())<<' '<<d<<' ';};visibilityWorld.countRead=[&](const auto& c){std::cout<<"c "<<(&c-mapCells.data())<<' '<<c.count13c<<' ';};
 RadarDiscoveryBinding discoveryBinding(s,visibilityState,visibilityWorld,[&](auto& p,bool count,auto value){liveMap=&p;std::cout<<(count?"I ":"H ")<<p.x<<' '<<p.y<<' '<<p.z<<' '<<unsigned(value)<<' ';mutate(count?4:3);});
#endif
#endif
#ifdef RA2_RADAR_ACTORS
#include "radar_actor_pixels_fixture.inc"
#endif
#ifdef RA2_COVERAGE_RADAR
#include "coverage_radar_fixture.inc"
#else
#ifdef RA2_RADAR_REFRESH
#include "radar_refresh_fixture.inc"
#else
 if(f[0]){SurfaceRefreshScratch scratch{};SurfaceRefreshServices refresh{mode,first,second,[]{throw std::logic_error("zero-mode parent unsupported");},[&](auto& p){point=p;refreshRadarPixel(point,s);p=point;}};refreshSurfaces(refresh,scratch);}else refreshRadarPixel(point,s);
#endif
#endif
 std::cout<<"R "<<hid(current)<<' '<<mode<<' '<<sid(*first)<<' '<<sid(*second)<<' '<<(buckets==&roots[1])<<' '<<changed<<' '<<(surfaces[0].table==&tables[1])<<' ';for(unsigned i=0;i<point.size();++i){
#ifdef RA2_RADAR_REFRESH
 continue;
#endif
#ifdef RA2_COVERAGE_RADAR
 if(i>=2)continue;
#endif
 std::cout<<point[i]<<' ';}for(auto v:dirty)std::cout<<v<<' ';std::cout<<screenX<<' '<<screenY<<' '<<scheme.index330<<' ';for(auto v:shifts)std::cout<<v<<' ';for(auto p:owners)std::cout<<hid(p)<<' ';for(int i=0;i<3;++i)std::cout<<starts[i]<<' '<<remaining[i]<<' ';for(auto& e:entries)std::cout<<aid(e.actor)<<' '<<e.x<<' '<<e.y<<' ';std::cout<<roots[0][0].count<<' ';
#ifdef RA2_RADAR_SURFACE_PIXELS
 std::cout<<"Z "<<pixelLocks[0]<<' '<<pixelLocks[1]<<' '<<assetSha256(Data(pixelStorage[0]))<<' '<<assetSha256(Data(pixelStorage[1]))<<' ';
#endif
#ifdef RA2_RADAR_DISCOVERY
#ifdef RA2_RADAR_MAP
 std::cout<<"Y "<<terrain[3].position.x<<' '<<terrain[3].position.y<<' ';
 Bytes lazyBytes{floorState.flags};const auto scalar=[&](double value){auto bits=std::bit_cast<std::uint64_t>(value);for(unsigned j=0;j<8;++j)lazyBytes.push_back(std::uint8_t(bits>>(j*8)));};scalar(floorState.height);scalar(floorState.scale);for(const auto& p:floorState.planes)for(double v:{p.x,p.y,p.offset,p.limit,p.add})scalar(v);
 std::cout<<"O "<<levelHeight<<' '<<assetSha256(Data(lazyBytes))<<' ';
#else
 std::cout<<"Y "<<mapCells[3].point.x<<' '<<mapCells[3].point.y<<' ';
#endif
#endif
#ifdef RA2_RADAR_ACTORS
 std::cout<<"X "<<houseMode<<' '<<radarChanged<<' '<<resolverChanged<<' '<<(schemeRegistry.data()==schemeRegistries[1].data())<<' ';
 for(int i=0;i<3;++i)std::cout<<int(actorKinds[i]==RadarColorActorKind::building)<<' '<<unsigned(actorFlags[i])<<' '<<hid(alternates[i])<<' ';
 for(int i=0;i<3;++i)std::cout<<houseIndexes[i]<<' '<<houseAllies[i]<<' '<<unsigned(humanFlags[i])<<' '<<unsigned(controlFlags[i])<<' ';
 for(int i=0;i<3;++i)std::cout<<(schemeNames[i]=="LightGrey")<<' '<<schemeCategories[i]<<' '<<schemeRecords[i]->index330<<' ';
#endif
#ifdef RA2_COVERAGE_RADAR
 std::cout<<"Q "<<unsigned(activeCoverage)<<' '<<coverageRange<<' ';for(auto b:coverageHouseDirty)std::cout<<unsigned(b)<<' ';
 for(int i=0;i<4;++i)std::cout<<std::bit_cast<std::int32_t>(flags12c[i])<<' '<<coverage130[i]<<' '<<coverage134[i]<<' '<<counts[i]<<' ';
#endif
#ifdef RA2_RADAR_REFRESH
 std::cout<<"U ";for(auto b:refreshBitmapBytes)std::cout<<unsigned(b)<<' ';
#endif
 std::cout<<'\n';
}
void guards(){
 const auto old=std::fegetround();need(std::fesetround(FE_UPWARD)==0);auto p=projectRadarPoint(1,2,1,0,0);need(p.x==640&&p.y==384&&std::fegetround()==FE_UPWARD);bool refused=false;try{projectRadarPoint(0,0,0,0,0);}catch(const std::invalid_argument&){refused=true;}need(refused&&std::fegetround()==FE_UPWARD);std::fesetround(old);
 const void* current=nullptr;std::int32_t mode=0,zero=0;float scale=0;RefreshSurface* surface=nullptr;SurfaceMarkBuckets* buckets=nullptr;RefreshRect dirty{1,2,3,4},point{};std::array<std::int32_t,6> shifts{};RadarPixelServices s{current,mode,surface,surface,scale,zero,zero,zero,zero,dirty,buckets,shifts,zero,{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};refreshRadarPixel(point,s);need(dirty==RefreshRect({1,2,3,4}));
#ifdef RA2_RADAR_DISCOVERY
 MapVisibilityCell fallback{{0,0},0,0,1};std::vector<MapVisibilityCell*> cells(262144,nullptr);MapVisibilityWorld discoveryWorld{cells,&fallback,{1,1}};MapVisibilityState discoveryState{104};int queries=0,restoredDiscovery=0;discoveryWorld.query=[&](auto,auto){++queries;};s.discovery568140=[&](auto&){++restoredDiscovery;return std::uint8_t(7);};s.discovery568280=s.discovery568140;RadarMapPoint mapPoint{};
 {RadarDiscoveryBinding bind(s,discoveryState,discoveryWorld);need(queries==0);need(s.discovery568140(mapPoint)==1&&s.discovery568280(mapPoint)==1);fallback.count13c=0;need(s.discovery568280(mapPoint)==0);}
 need(s.discovery568140(mapPoint)==7&&s.discovery568280(mapPoint)==7&&restoredDiscovery==2);
 bool discoveryFault=false;try{RadarDiscoveryBinding bind(s,discoveryState,discoveryWorld);discoveryState.heightDivisor=0;s.discovery568280(mapPoint);}catch(const std::invalid_argument&){discoveryFault=true;}need(discoveryFault&&s.discovery568280(mapPoint)==7&&restoredDiscovery==3);
#endif
#ifdef RA2_RADAR_MAP
 std::array<MapCellInput,2> terrain;terrain[0].position={4,5};terrain[0].level=2;terrain[1].position={-7,5};terrain[1].level=1;
 std::vector<MapCellInput*> terrainSlots(262144,nullptr);terrainSlots[0]=&terrain[0];int fieldReads=0;std::uint32_t flags12c=0;std::int32_t count=1,currentHeight=104;
 MapFloorHeightWorld floorWorld{terrainSlots,&terrain[1],{}};MapFloorHeightState floorState;floorState.planes[0].x=1;
 RadarMapWorld radarWorld{floorWorld,[&](const auto&)->RadarMapDiscoveryFields{++fieldReads;return {flags12c,count};}};
 discoveryState.heightDivisor=104;int oldFloorCalls=0;s.floor55A280=[&](auto&){++oldFloorCalls;return -37;};
 {RadarMapBinding bind(s,floorState,currentHeight,discoveryState,radarWorld);need(fieldReads==0&&floorState.flags==0);mapPoint={0,0,0};need(s.floor55A280(mapPoint)==208&&floorState.flags==7);terrain[0].flags=UINT32_MAX;need(s.discovery568140(mapPoint)==1);flags12c=8;need(s.discovery568140(mapPoint)==0&&terrain[0].flags==UINT32_MAX);flags12c=0;mapPoint={-1,-257,0};need(s.floor55A280(mapPoint)==104&&terrain[1].position==MapInputPosition({0,-1}));mapPoint.z=104;need(s.discovery568280(mapPoint)==1&&terrain[1].position==MapInputPosition({0,-1}));}
 need(s.floor55A280(mapPoint)==-37&&oldFloorCalls==1&&s.discovery568280(mapPoint)==7);
 bool floorFault=false;terrain[1].slope=21;try{RadarMapBinding bind(s,floorState,currentHeight,discoveryState,radarWorld);s.floor55A280(mapPoint);}catch(const std::invalid_argument&){floorFault=true;}need(floorFault&&s.floor55A280(mapPoint)==-37&&oldFloorCalls==2&&s.discovery568280(mapPoint)==7);
#endif
#ifdef RA2_RADAR_SURFACE_PIXELS
 RefreshSurfaceVirtuals table;table.width7C=refreshSurfaceWidth;RefreshSurface a{&table,2,2};std::array<std::uint8_t,8> bytes{0x34,0x12};std::int32_t depth=0,bpp=2;std::uint32_t offset=0;int views=0,restored=0;
 RadarPixelVirtuals previous{[&](auto&,auto&){++restored;return 7u;},[&](auto&,auto&,auto){++restored;}};s.pixels=[&](auto*)->const RadarPixelVirtuals&{return previous;};
 std::array<const RefreshSurfaceVirtuals*,1> identities{&table};RadarSurfacePixelWorld world{identities,[&](auto& receiver)->SurfacePixelView{++views;return {receiver.width,depth,bpp,offset,bytes,{},true};},{},{},{},{}};RefreshRect origin{},next{1,0,0,0};
 {RadarSurfacePixelsBinding bind(s,world);need(views==0);need(s.pixels(&table).get28(a,origin)==0x1234&&depth==0);s.pixels(&table).set24(a,next,0xabcd);need(bytes[2]==0xcd&&bytes[3]==0xab&&depth==0);}
 need(s.pixels(&table).get28(a,origin)==7&&restored==1);
 table.width7C=[](auto&)->std::int32_t{throw std::runtime_error("width fault");};bool propagated=false;try{RadarSurfacePixelsBinding bind(s,world);s.pixels(&table).get28(a,origin);}catch(const std::runtime_error&){propagated=true;}need(propagated&&depth==1);need(s.pixels(&table).get28(a,origin)==7&&restored==2);
#endif
#ifdef RA2_RADAR_ACTORS
#include "radar_actor_pixels_guards.inc"
#endif
#ifdef RA2_COVERAGE_RADAR
#include "coverage_radar_guards.inc"
#endif
#ifdef RA2_RADAR_REFRESH
#include "radar_refresh_guards.inc"
#endif
#ifdef RA2_COVERAGE_RADAR_REFRESH
#include "coverage_radar_refresh_guards.inc"
#endif
 std::cout<<"surface radar pixel guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
