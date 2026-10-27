// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SurfaceRefreshMarks.hpp"
#ifdef RA2_SURFACE_MARK_PIXELS
#include "render/SurfaceMarkPixels.hpp"
#include "assets/PreparedData.hpp"
#endif
#ifdef RA2_SURFACE_COPY_MARK_PIXELS
#include "render/SurfaceRefreshPixels.hpp"
#endif
#ifdef RA2_STOCK_RADAR_COLORS
#include "render/ActorRadarColor.hpp"
#ifdef RA2_SCHEME_RESOLVER
#include "render/SchemeResolver.hpp"
#endif
#endif
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
namespace {
void need(bool v){if(!v)throw std::invalid_argument("Mark fixture domain");}
struct House{int index;
#ifdef RA2_STOCK_RADAR_COLORS
 std::int32_t index30=0;std::uint32_t allies=0;
#endif
};struct Actor{House* owner;
#ifdef RA2_STOCK_RADAR_COLORS
 std::uint8_t byte170=0;const void* alternate=nullptr;RadarColorActorKind kind=RadarColorActorKind::infantry;
#endif
};
void run(std::istream& in){
 char op=0;std::array<std::int32_t,14> f{};
#ifdef RA2_SURFACE_MARK_PIXELS
#ifdef RA2_STOCK_RADAR_COLORS
 #ifdef RA2_SCHEME_RESOLVER
 need(bool(in>>op)&&op=='L');
#else
 need(bool(in>>op)&&op=='V');
#endif
#else
 need(bool(in>>op)&&op=='X');
#endif
#else
 need(bool(in>>op)&&op=='M');
#endif
 for(auto& v:f)need(bool(in>>v));
#ifdef RA2_SURFACE_MARK_PIXELS
 int pixelBpp=0;std::uint32_t pixelOffset=0;std::int32_t pixelLock=0;
 need(bool(in>>pixelBpp>>pixelOffset>>pixelLock));need((pixelBpp==1||pixelBpp==2)&&pixelOffset>=256&&pixelOffset<=259);
#endif
#ifdef RA2_STOCK_RADAR_COLORS
 int radarCurrentId=0,radarAlternateId=0,radarPattern=0,radarMutation=0;std::uint32_t radarMask=0;
 need(bool(in>>radarCurrentId>>radarAlternateId>>radarPattern>>radarMask>>radarMutation));
 need(radarCurrentId>=-1&&radarCurrentId<=2&&radarAlternateId>=-1&&radarAlternateId<=2&&radarPattern>=0&&radarPattern<=3&&radarMutation>=0&&radarMutation<=15);
#endif
#ifdef RA2_SCHEME_RESOLVER
 int resolverPattern=0,resolverAt=0,resolverMask=0;need(bool(in>>resolverPattern>>resolverAt>>resolverMask));need(resolverPattern>=0&&resolverPattern<=1&&resolverAt>=0&&resolverAt<3&&resolverMask>=0&&resolverMask<64);need((resolverAt==0||!(resolverMask&1))&&(resolverAt!=0||!(resolverMask&8)));
#endif
 std::string tail;need(!(in>>tail));
 need(f[0]>=0&&f[0]<=1&&f[3]>=-1&&f[3]<=4&&f[4]>=0&&f[4]<=255&&f[5]>=0&&f[5]<=1&&f[6]>=0&&f[6]<=2&&f[7]>=0&&f[7]<=9&&f[8]>=0&&f[8]<=511&&f[9]>=0&&f[9]<=4&&f[10]>=-1&&f[10]<=4&&f[11]>=0&&f[11]<=255&&f[12]>=0&&f[12]<=7&&f[13]>=0&&f[13]<=2);
 need((f[1]>=-16&&f[1]<=16)||f[1]==2147483647);need(f[2]>=-16&&f[2]<=16);
 House houses[3]={{0},{1},{2}};Actor actors[4];for(auto& a:actors)a.owner=&houses[f[13]];
 auto aid=[&](const void* p){for(int i=0;i<4;++i)if(p==&actors[i])return i;throw std::invalid_argument("Foreign actor");};
 auto hid=[&](const void* p){if(!p)return -1;for(int i=0;i<3;++i)if(p==&houses[i])return i;throw std::invalid_argument("Foreign House");};
#ifdef RA2_STOCK_RADAR_COLORS
 const void* radarCurrent=radarCurrentId<0?nullptr:&houses[radarCurrentId];bool radarChanged=false;
 for(int i=0;i<3;++i){houses[i].index30=i;houses[i].allies=radarMask;}
 for(int i=0;i<4;++i){actors[i].byte170=std::uint8_t(f[4]);actors[i].alternate=radarAlternateId<0?nullptr:&houses[radarAlternateId];actors[i].kind=(radarPattern==1||(radarPattern>=2&&((i+radarPattern)&1)))?RadarColorActorKind::building:RadarColorActorKind::infantry;}
#endif
 SurfaceMarkEntry entries[16];for(int i=0;i<16;++i)entries[i]={&actors[i%4],i%7,0,0xabc000u+unsigned(i)};
 entries[0].x=0;entries[1].x=1;entries[2].x=0;entries[3].x=2;entries[3].y=1;
 if(f[9]==1){entries[0].x=-1;entries[1].x=-8;}if(f[9]==2){entries[0].x=2147483647;entries[0].y=1;}if(f[9]==3)for(int i=0;i<4;++i)entries[i].x=0,entries[i].y=0;
 if(f[9]==4){entries[0].x=-7;entries[0].y=-1;}
 auto eid=[&](const SurfaceMarkEntry& e){for(int i=0;i<16;++i)if(&e==&entries[i])return i;throw std::invalid_argument("Foreign entry");};
 SurfaceMarkBuckets roots[2];for(auto& root:roots)for(auto& b:root)b={{},0};
 roots[0][0]={{entries,4},f[10]};roots[0][1]={{entries+8,2},2};roots[0][255]={{entries+10,1},1};
 roots[1][0]={{entries+4,4},f[10]};roots[1][1]={{entries+11,2},2};roots[1][255]={{entries+13,2},2};
 auto* buckets=&roots[0];std::array<std::uint8_t,64> backing[2];backing[0].fill(std::uint8_t(f[11]));backing[1].fill(std::uint8_t(f[11]^0xa5));
 SurfaceMarkBitmap maps[2]={{backing[0],16},{backing[1],16}};auto* bitmap=&maps[0];
 std::array<std::uint8_t,32> colorData[2];for(int k=0;k<2;++k)for(int i=0;i<32;++i)colorData[k][i]=std::uint8_t(i*17+k*41+3);
 SurfaceMarkPalette palettes[2]={{f[3],colorData[0]},{1,colorData[1]}};SurfaceMarkScheme colors[3]={{&palettes[0],unsigned(f[12])},{&palettes[1],3},{&palettes[0],5}};
 std::array<const SurfaceMarkScheme*,3> registries[2]={{{&colors[0],&colors[1],&colors[2]}},{{&colors[2],&colors[1],&colors[0]}}};std::span<const SurfaceMarkScheme*> registry=registries[0];
 RefreshSurfaceVirtuals table;RefreshSurface surfaces[2]={{&table,f[1],f[2]},{&table,5,2}};auto* first=&surfaces[0];auto* second=&surfaces[1];
 auto sid=[&](RefreshSurface& a){need(&a==&surfaces[0]||&a==&surfaces[1]);return &a==&surfaces[1]?1:0;};
 int widths=0,ccs=0;bool changed=false;
 auto mutate=[&](int stage){if(changed||f[7]!=stage)return;changed=true;auto mask=f[8];
  if(mask&1)first=&surfaces[1];if(mask&2)buckets=&roots[1];if(mask&4)roots[0][0].entries={entries+4,4};
  if(mask&8){entries[0].actor=&actors[3];entries[0].x=7;entries[0].y=1;}
  if(mask&16)bitmap=&maps[1];if(mask&32)registry=registries[1];if(mask&64)actors[0].owner=&houses[2];
  if(mask&128){colors[0].palette30C=&palettes[1];colors[0].index330=2;}if(mask&256)roots[0][0].count=1;
 };
 table.height80=[&](auto& a){auto v=refreshSurfaceHeight(a);std::cout<<"H "<<sid(a)<<' '<<v<<' ';mutate(1);return v;};
 table.width7C=[&](auto& a){auto v=refreshSurfaceWidth(a);std::cout<<"W "<<sid(a)<<' '<<v<<' ';mutate(++widths==1?2:3);return v;};
 table.rect78=[&](auto& a,auto& r){auto* out=refreshSurfaceRect(a,r);std::cout<<"G "<<sid(a)<<' '<<a.width<<' '<<a.height<<' ';return out;};
 table.copy8=[&](auto& a,auto* dst,auto* src,auto* rect,auto z,auto one){std::cout<<"C "<<sid(a)<<' ';for(auto n:*dst)std::cout<<n<<' ';std::cout<<sid(*src)<<' ';for(auto n:*rect)std::cout<<n<<' ';std::cout<<z<<' '<<one<<' ';mutate(9);};
 SurfaceMarkServices marks{first,buckets,bitmap,registry,
  [&](const void* p)->const void*{return actors[aid(p)].owner;},[&](const void* p){return houses[hid(p)].index;},
  [&](const void* p){ccs=0;std::cout<<"A "<<aid(p)<<' '<<f[4]<<' ';mutate(4);return std::uint8_t(f[4]);},
  [&](const void* p,std::uint32_t zero)->const void*{need(zero==0);const void* h=++ccs%2? (f[5]?&houses[1]:nullptr):&houses[f[6]];std::cout<<"O "<<aid(p)<<' '<<zero<<' '<<hid(h)<<' ';mutate(ccs%2?5:6);return h;},
  [&](std::uint32_t one){need(one==1);std::cout<<"D 1 1 ";mutate(7);return &colors[1];},
  [&](auto& a,auto& e,std::uint32_t color){std::cout<<"P "<<sid(a)<<' '<<eid(e)<<' '<<e.x<<' '<<e.y<<' '<<color<<' ';mutate(8);},
  [&](const auto& b,std::size_t p,unsigned n,std::uint32_t v){std::cout<<"B "<<(&b==&maps[1])<<' '<<p<<' '<<n<<' '<<v<<' ';}};
#ifdef RA2_SURFACE_MARK_PIXELS
 Bytes pixels[2]={Bytes(2048),Bytes(2048)};std::int32_t lockDepths[2]={pixelLock,pixelLock},bpps[2]={pixelBpp,3-pixelBpp};
 for(int k=0;k<2;++k)for(unsigned i=0;i<pixels[k].size();++i)pixels[k][i]=std::uint8_t(i*29+0x34+k*37);
 SurfaceMarkPixelServices pixelServices{
  [&](RefreshSurface& a)->SurfacePixelView{const auto id=sid(a);return {a.width,lockDepths[id],bpps[id],pixelOffset,pixels[id],{},true};},
  marks.pixel24,
  [&](auto& a,auto p,auto n,auto value){std::cout<<"S "<<sid(a)<<' '<<p<<' '<<n<<' '<<value<<' ';},
  [&](auto& a,auto depth){std::cout<<"L "<<sid(a)<<' '<<depth<<' ';}};
#ifndef RA2_SURFACE_COPY_MARK_PIXELS
 SurfaceMarkPixelsBinding pixelBinding(marks,pixelServices);
#else
 CopySurface copyOwners[2]={
  {surfaces[0],pixelServices.view(surfaces[0]),{},[&](auto p,auto n,auto v){pixelServices.store(surfaces[0],p,n,v);},[&](auto d){pixelServices.locks(surfaces[0],d);},[&]{return table.width7C(surfaces[0]);}},
  {surfaces[1],pixelServices.view(surfaces[1]),{},[&](auto p,auto n,auto v){pixelServices.store(surfaces[1],p,n,v);},[&](auto d){pixelServices.locks(surfaces[1],d);},[&]{return table.width7C(surfaces[1]);}}
 };
 for(int id=0;id<2;++id)copyOwners[id].observe=[&,id](char kind,auto,auto){if(kind=='R')std::cout<<"G "<<id<<' '<<surfaces[id].width<<' '<<surfaces[id].height<<' ';};
 SurfaceCopyServices copyServices{[&](RefreshSurface& surface)->CopySurface&{return copyOwners[sid(surface)];}};
#ifdef RA2_STOCK_RADAR_COLORS
 RadarColorWorld radar{radarCurrent,[&](const void* p)->RadarColorActor{auto& a=actors[aid(p)];return {a.kind,a.byte170,[&a]{return a.owner;},[&a]{return a.alternate;}};},[&](const void* p)->RadarColorHouse{const auto id=hid(p);need(id>=0);return {houses[id].index30,houses[id].allies};},[&](const void* p,const void* owner,const void* current,bool result){const auto id=aid(p);std::cout<<"J "<<id<<' '<<hid(owner)<<' '<<hid(current)<<' '<<result<<' ';if(radarChanged||!radarMutation)return;radarChanged=true;if(radarMutation&1)actors[id].owner=&houses[2];if(radarMutation&2)radarCurrent=&houses[2];if(radarMutation&4)actors[id].alternate=&houses[2];if(radarMutation&8){houses[2].index30=-1;houses[0].allies^=0xffffffff;}}};
 ActorRadarColorProbes radarProbes{[&](const void* p,std::uint8_t result){ccs=0;std::cout<<"A "<<aid(p)<<' '<<unsigned(result)<<' ';mutate(4);},[&](const void* p,std::uint32_t argument,const void* result){++ccs;std::cout<<"O "<<aid(p)<<' '<<argument<<' '<<hid(result)<<' ';mutate(ccs%2?5:6);}};
 ActorRadarColorBinding radarBinding(marks,radar,radarProbes);
#ifdef RA2_SCHEME_RESOLVER
 std::array<std::string_view,3> schemeNames={"LightGrey",resolverPattern?"Other":"LightGrey","LightGrey"};std::array<std::int32_t,3> schemeCategories={0,1,1};std::int32_t schemeCount=3;std::uint32_t schemeLocale=0;bool resolverChanged=false;
 auto colorId=[&](const SurfaceMarkScheme* p){for(int i=0;i<3;++i)if(p==&colors[i])return i;throw std::invalid_argument("Foreign resolved scheme");};
 auto resolverMutate=[&](int stage,std::uint32_t at){const auto bits=stage==1?(resolverMask&7):((resolverMask>>3)&7);if(resolverChanged||!bits||at!=std::uint32_t(resolverAt))return;resolverChanged=true;if(bits&1)registry=registries[1];if(bits&2)schemeCategories[1]=-1;if(bits&4)schemeNames[1]="Other";};
 SchemeResolverWorld schemeWorld{registry,schemeCount,schemeLocale,[&](auto p){return schemeNames[colorId(p)];},[&](auto p){return schemeCategories[colorId(p)];},[&](auto at,auto p,int cmp){std::cout<<"T "<<at<<' '<<colorId(p)<<' '<<cmp<<' ';resolverMutate(1,at);},[&](auto at,auto p,auto category){std::cout<<"U "<<at<<' '<<colorId(p)<<' '<<category<<' ';resolverMutate(2,at);}};
 std::function<void(const SurfaceMarkScheme*)> resolved=[&](auto p){std::cout<<"K "<<colorId(p)<<' ';mutate(7);};SchemeResolverBinding resolverBinding(marks,schemeWorld,"LightGrey",resolved);
#endif
#endif
#endif
#endif
#ifdef RA2_SURFACE_COPY_MARK_PIXELS
 int mode=0;SurfaceRefreshScratch scratch{};SurfaceRefreshServices refresh{mode,first,second,[]{throw std::logic_error("unjoined finish");},{}};
 const auto probe=table.copy8;SurfaceRefreshPixelsBinding binding(table,refresh,marks,copyServices,marks.pixel24);
 const auto actual=table.copy8;
 table.copy8=[probe,actual](auto& d,auto* dr,auto* source,auto* sr,auto firstFlag,auto secondFlag){probe(d,dr,source,sr,firstFlag,secondFlag);actual(d,dr,source,sr,firstFlag,secondFlag);};
 if(f[0])refreshSurfaces(refresh,scratch);else refreshSurfaceMarks(marks);
#else
 if(f[0]){int mode=0;SurfaceRefreshScratch scratch{};SurfaceRefreshServices refresh{mode,first,second,[]{throw std::logic_error("unjoined finish");},{}};SurfaceRefreshMarksBinding binding(refresh,marks);refreshSurfaces(refresh,scratch);}
 else refreshSurfaceMarks(marks);
#endif
 std::cout<<"R "<<sid(*first)<<' '<<(bitmap==&maps[1])<<' '<<(buckets==&roots[1])<<' '<<(registry.data()==registries[1].data())<<' '<<changed<<' ';
 for(auto& b:backing)for(auto v:b)std::cout<<unsigned(v)<<' ';for(auto& e:entries)std::cout<<aid(e.actor)<<' '<<e.x<<' '<<e.y<<' ';
 for(auto& a:actors)std::cout<<hid(a.owner)<<' ';std::cout<<roots[0][0].count<<' '<<eid(roots[0][0].entries[0])<<' ';
 for(auto& c:colors)std::cout<<(c.palette30C==&palettes[1])<<' '<<c.index330<<' ';
#ifdef RA2_SURFACE_MARK_PIXELS
 std::cout<<"Z "<<lockDepths[0]<<' '<<lockDepths[1]<<' '<<assetSha256(Data(pixels[0]))<<' '<<assetSha256(Data(pixels[1]))<<' ';
#endif
#ifdef RA2_STOCK_RADAR_COLORS
 std::cout<<"Y "<<hid(radarCurrent)<<' '<<radarChanged<<' ';for(auto& a:actors)std::cout<<(a.kind==RadarColorActorKind::building)<<' '<<unsigned(a.byte170)<<' '<<hid(a.alternate)<<' ';for(auto& h:houses)std::cout<<h.index30<<' '<<h.allies<<' ';
#endif
#ifdef RA2_SCHEME_RESOLVER
 std::cout<<"Q "<<schemeCount<<' '<<resolverChanged<<' ';for(auto name:schemeNames)std::cout<<(name=="LightGrey")<<' ';for(auto category:schemeCategories)std::cout<<category<<' ';
#endif
 std::cout<<'\n';
}
void guards(){
 RefreshSurfaceVirtuals table;RefreshSurface surface{&table,1,1};RefreshSurface* first=&surface;SurfaceMarkBuckets buckets{};SurfaceMarkBuckets* root=&buckets;std::array<std::uint8_t,8> bytes{};SurfaceMarkBitmap bitmap{bytes,0};SurfaceMarkBitmap* map=&bitmap;std::span<const SurfaceMarkScheme*> registry;int calls=0;
 SurfaceMarkServices marks{first,root,map,registry,{},{},{},{},{},{},{}};table.height80=refreshSurfaceHeight;table.width7C=refreshSurfaceWidth;
 refreshSurfaceMarks(marks);need(bytes[0]==0);
 SurfaceRefreshServices refresh{calls,first,first,[&]{++calls;},{}};
 {SurfaceRefreshMarksBinding bind(refresh,marks);need(calls==0);refresh.finish6324A0();need(calls==0);}refresh.finish6324A0();need(calls==1);
 surface.width=2147483647;surface.height=1;bool refused=false;try{refreshSurfaceMarks(marks);}catch(const std::invalid_argument&){refused=true;}need(refused);
 surface.width=1;root=nullptr;refused=false;try{refreshSurfaceMarks(marks);}catch(const std::invalid_argument&){refused=true;}need(refused);
 root=&buckets;table.height80=[](auto&)->std::int32_t{throw std::runtime_error("unrelated");};bool propagated=false;try{SurfaceRefreshMarksBinding bind(refresh,marks);refresh.finish6324A0();}catch(const std::runtime_error&){propagated=true;}need(propagated);refresh.finish6324A0();need(calls==2);
#ifdef RA2_SURFACE_MARK_PIXELS
 int queries=0;SurfaceMarkEntry entry{nullptr,0,0,0};marks.pixel24=[&](auto&,auto&,auto){++calls;};
 SurfaceMarkPixelServices pixelServices{[&](auto&)->SurfacePixelView{++queries;throw std::runtime_error("view fault");},{},{},{}};
 propagated=false;try{SurfaceMarkPixelsBinding bind(marks,pixelServices);need(queries==0);marks.pixel24(surface,entry,0);}catch(const std::runtime_error&){propagated=true;}need(propagated&&queries==1);marks.pixel24(surface,entry,0);need(calls==3);
#endif
#ifdef RA2_SURFACE_COPY_MARK_PIXELS
 std::int32_t lock=0,bpp=2;std::uint32_t offset=0;CopySurface record{surface,{surface.width,lock,bpp,offset,bytes,{},true},{},{},{},{}};
 int resolutions=0,restored=0;SurfaceCopyServices owners{[&](auto& receiver)->CopySurface&{need(&receiver==&surface);++resolutions;return record;}};
 table.copy8=[&](auto&,auto*,auto*,auto*,auto,auto){++restored;};marks.pixel24=[&](auto&,auto&,auto){++restored;};refresh.finish6324A0=[&]{++restored;};
 FillRect rect{0,0,1,1};SurfaceMarkEntry point{nullptr,0,0,0};propagated=false;
 try{SurfaceRefreshPixelsBinding bind(table,refresh,marks,owners);need(resolutions==0);table.copy8(surface,&rect,&surface,&rect,0,1);marks.pixel24(surface,point,0x1234);need(bytes[0]==0x34&&bytes[1]==0x12&&lock==0);refresh.finish6324A0();}catch(const std::runtime_error&){propagated=true;}
 need(propagated&&resolutions>0);table.copy8(surface,&rect,&surface,&rect,0,1);marks.pixel24(surface,point,0);refresh.finish6324A0();need(restored==3);
#endif
 std::cout<<"surface refresh marks guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
