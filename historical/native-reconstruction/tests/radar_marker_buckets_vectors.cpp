// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/RadarMarkerBuckets.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Radar bucket fixture domain");}
struct Actor {int x=91,y=92,kind=15;const void* owner=nullptr;};
std::uint64_t digest(const std::vector<std::uint32_t>& words){std::uint64_t h=14695981039346656037ull;for(auto w:words)for(unsigned b=0;b<4;++b){h^=std::uint8_t(w>>(8*b));h*=1099511628211ull;}return h;}
void run(std::istream& in){
 char op;int mode,x,y,w,h,count,capacity,growth,owns,valid,present,local,failed,dirtyFailed,actor,slot,mutation,repeats,requested;
 need(bool(in>>op>>mode>>x>>y>>w>>h>>count>>capacity>>growth>>owns>>valid>>present>>local>>failed>>dirtyFailed>>actor>>slot>>mutation>>repeats>>requested)&&op=='B');
 need(mode>=0&&mode<=5&&count>=0&&count<=capacity&&capacity<=8&&owns>=0&&owns<=255&&valid>=0&&valid<=255&&present>=0&&present<=1&&local>=0&&local<=7&&failed>=0&&failed<=1&&dirtyFailed>=0&&dirtyFailed<=1&&actor>=0&&actor<3&&slot>=-1&&slot<8&&mutation>=0&&mutation<=3&&repeats>=1&&repeats<=3&&requested>=0&&requested<=16);
 std::string extra;need(!(in>>extra));int houses[2]{};const void* current=&houses[0];std::array<Actor,3> actors{};
 need(present||(capacity==0&&count==0));
 for(unsigned i=0;i<3;++i){actors[i].owner=&houses[(local&(1<<i))?0:1];actors[i].kind=i==2?6:15;}
 const auto norm=[&](std::uintptr_t p){for(unsigned i=0;i<3;++i)if(p==reinterpret_cast<std::uintptr_t>(&actors[i]))return std::uint32_t(101+i);return std::uint32_t(p);};
 std::vector<std::unique_ptr<SurfaceMarkEntry[]>> markers;
 const auto createMarker=[&]{auto data=std::make_unique<SurfaceMarkEntry[]>(128);const auto id=markers.size();for(unsigned k=0;k<128;++k)data[k]={&actors[2],int(1000+id*100+k),int(2000+id*100+k),0xdef000u+id*128+k};markers.push_back(std::move(data));};createMarker();
 for(int i=0;i<count;++i)markers[0][i]={&actors[std::size_t(i%3)],2+i*5,1+i,0xabc000u+unsigned(i)};
 const auto mid=[&](auto p){if(!p)return 0u;for(unsigned i=0;i<markers.size();++i)if(p==markers[i].get())return i+1;throw std::invalid_argument("Marker backing identity");};
 SurfaceMarkBuckets root{};auto* buckets=&root;const auto seeded=radarMarkerBucket(2,1);
 root[seeded]={{present?markers[0].get():nullptr,present?128u:0u},count,capacity,growth,std::uint8_t(valid),std::uint8_t(owns)};
 std::vector<std::unique_ptr<RadarShapePoint[]>> points;
 const auto pid=[&](auto p){if(!p)return 0u;for(unsigned i=0;i<points.size();++i)if(p==points[i].get())return i+1;throw std::invalid_argument("Dirty backing identity");};
 RadarShapeVector dirtyVector;std::array<std::uint8_t,1024> bits{};SurfaceMarkBitmap bitmap{bits,0};auto* bitmapPointer=&bitmap;std::uint8_t dirty=0;
 RefreshSurfaceVirtuals table;RefreshSurface surface{&table,w,h},other{&table,7,6};auto* first=&surface;
 table.rect78=[&](auto& s,auto& out){std::cout<<"G "<<(&s==&surface?0:1)<<' ';auto* result=refreshSurfaceRect(s,out);if(mutation==1)first=&other;if(mutation==3)actors[0].owner=&houses[0];return result;};
 table.width7C=[&](auto& s){std::cout<<"W "<<(&s==&surface?0:1)<<' '<<s.width<<' ';return s.width;};
 table.height80=[&](auto& s){std::cout<<"Y "<<(&s==&surface?0:1)<<' '<<s.height<<' ';return s.height;};
 RadarDirtyServices ds;
 ds.vector.allocate=[&](auto bytes)->std::span<RadarShapePoint>{need(bytes>0&&bytes<=1024&&bytes%8==0);std::cout<<"a "<<bytes<<' '<<dirtyFailed<<' ';if(dirtyFailed)return {};auto p=std::make_unique<RadarShapePoint[]>(128);const auto id=points.size();for(unsigned k=0;k<128;++k)p[k]={int(3000+id*100+k),int(4000+id*100+k)};points.push_back(std::move(p));return {points.back().get(),128};};
 ds.vector.release=[&](auto p){std::cout<<"d "<<pid(p.data())<<' ';};
 ds.vector.fieldStore=[&](auto off,auto n,auto value){std::cout<<"f "<<off<<' '<<n<<' '<<(off==4?pid(dirtyVector.items.data()):value)<<' ';};
 ds.vector.pointStore=[&](auto p,auto off,auto n,auto value){std::cout<<"p "<<pid(p.data())<<' '<<off<<' '<<n<<' '<<value<<' ';};
 ds.bitmapStore=[&](auto at,auto value){std::cout<<"b "<<at<<' '<<unsigned(value)<<' ';};ds.dirtyStore=[&](auto value){std::cout<<"S "<<unsigned(value)<<' ';};
 RadarMarkerBucketServices s;
 s.vector=[&](unsigned index){RadarMarkerVectorServices v;
  v.allocate=[&](auto bytes)->std::span<SurfaceMarkEntry>{need(bytes>0&&bytes<=2048&&bytes%16==0);std::cout<<"A "<<bytes<<' '<<failed<<' ';if(failed)return {};createMarker();return {markers.back().get(),128};};
  v.release=[&](auto p){std::cout<<"D "<<mid(p.data())<<' ';};
  v.fieldStore=[&,index](auto off,auto n,auto value){std::cout<<"F "<<index<<' '<<off<<' '<<n<<' '<<(off==4?mid(root[index].entries.data()):value)<<' ';};
  v.entryStore=[&](auto p,auto off,auto value){std::cout<<"P "<<mid(p.data())<<' '<<off<<' '<<norm(value)<<' ';};return v;};
 s.kind2C=[&](auto p){const auto* a=static_cast<const Actor*>(p);std::cout<<"K "<<(a-actors.data())<<' '<<a->kind<<' ';const auto value=a->kind;if(mutation==2)current=&houses[1];return value;};
 s.owner1B4=[](auto p){return static_cast<const Actor*>(p)->owner;};
 s.position=[](auto p){auto& a=*const_cast<Actor*>(static_cast<const Actor*>(p));return RadarMarkerPosition{a.x,a.y};};
 s.actorStore=[&](auto p,auto off,auto value){std::cout<<"O "<<(static_cast<const Actor*>(p)-actors.data())<<' '<<off<<' '<<std::uint32_t(value)<<' ';};
 s.dirtyStore=ds.dirtyStore;
 s.queue632620=[&](auto point){std::cout<<"Q "<<point.x<<' '<<point.y<<' ';queueRadarDirtyPoint(point,{first,bitmapPointer,dirtyVector,dirty},ds);};
 RadarMarkerBucketFields fields{first,buckets,current,dirty};
 const void* selected=&actors[std::size_t(actor)];int rx=x,ry=y;
 if(slot>=0&&slot<count){const auto& e=root[seeded].entries[std::size_t(slot)];selected=e.actor;rx=e.x;ry=e.y;}
 for(int i=0;i<repeats;++i){std::cout<<"I "<<i<<' ';
  if(mode==0)insertRadarMarker(&actors[std::size_t(actor)],x,y,fields,s);
  else if(mode==1)removeRadarMarker(selected,rx,ry,fields,s);
  else if(mode==2){insertRadarMarker(&actors[0],x,y,fields,s);insertRadarMarker(&actors[1],x,y,fields,s);insertRadarMarker(&actors[0],x,y,fields,s);removeRadarMarker(&actors[0],x,y,fields,s);removeRadarMarker(&actors[0],x,y,fields,s);insertRadarMarker(&actors[2],x,y,fields,s);removeRadarMarker(&actors[1],x,y,fields,s);removeRadarMarker(&actors[2],x,y,fields,s);}
  else if(mode==3){const auto result=resizeRadarMarkerBucket(root[seeded],requested,s.vector(seeded));std::cout<<"T "<<result<<' ';}
  else if(mode==4)clearRadarMarkerBucket(root[seeded],s.vector(seeded));
  else std::cout<<"T "<<findRadarMarker(root[seeded],selected,rx,ry)<<' ';
 }
 for(unsigned i=0;i<256;++i){const auto& b=root[i];if(i==seeded||b.entries.data()||b.count||b.capacity)std::cout<<"V "<<i<<' '<<mid(b.entries.data())<<' '<<b.capacity<<' '<<b.count<<' '<<unsigned(b.valid)<<' '<<unsigned(b.owns)<<' ';}
 std::cout<<"R ";for(const auto& a:actors)std::cout<<a.x<<' '<<a.y<<' '<<(a.owner==&houses[0]?0:1)<<' ';
 std::cout<<unsigned(dirty)<<' '<<(first==&surface?0:1)<<' '<<(current==&houses[0]?0:1)<<' '<<pid(dirtyVector.items.data())<<' '<<dirtyVector.capacity<<' '<<dirtyVector.count<<' '<<unsigned(dirtyVector.valid)<<' '<<unsigned(dirtyVector.owns)<<' ';
 std::uint64_t bitmapHash=14695981039346656037ull;for(auto b:bits){bitmapHash^=b;bitmapHash*=1099511628211ull;}std::cout<<bitmapHash<<' ';
 std::cout<<"H "<<markers.size()<<' ';for(const auto& p:markers){std::vector<std::uint32_t> words;for(unsigned k=0;k<128;++k)for(unsigned j=0;j<4;++j)words.push_back(norm(markerEntryWord({p.get(),128},k*16+j*4)));std::cout<<digest(words)<<' ';}
 std::cout<<points.size()<<' ';for(const auto& p:points){std::vector<std::uint32_t> words;for(unsigned k=0;k<128;++k){words.push_back(std::uint32_t(p[k].x));words.push_back(std::uint32_t(p[k].y));}std::cout<<digest(words)<<' ';}std::cout<<'\n';
}
void guards(){SurfaceMarkBucket b;need(findRadarMarker(b,nullptr,0,0)==-1);b.count=1;bool refused=false;try{(void)findRadarMarker(b,nullptr,0,0);}catch(const std::invalid_argument&){refused=true;}need(refused);std::cout<<"radar marker buckets guards PASS\n";}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
