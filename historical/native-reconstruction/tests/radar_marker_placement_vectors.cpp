// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/RadarMarkerPlacement.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Radar marker fixture domain");}
void run(std::istream& in){
    char op;unsigned mode,bits,clamp,owns,present,fail,repeats,alias,mutation;
    int x,y,ox,oy,w,h,count,capacity,growth,step;
    need(bool(in>>op>>mode>>bits>>x>>y>>ox>>oy>>w>>h>>clamp>>count>>capacity>>growth>>owns>>present>>fail>>repeats>>step>>alias>>mutation));
    need(op=='M'&&mode<=1&&clamp<=255&&owns<=255&&present<=1&&fail<=1&&repeats>=1&&repeats<=4&&alias<=1&&mutation<=3&&capacity>=0&&capacity<=16);
    std::string tail;need(!(in>>tail));float scale=std::bit_cast<float>(bits);
    RadarShapePoint point{x,y},out{19,23};
    if(mode==0){
        auto& target=alias?point:out;need(&projectRadarMarker(target,point,std::uint8_t(clamp),{scale,ox,oy,w,h})==&target);
        std::cout<<"R "<<target.x<<' '<<target.y<<' '<<point.x<<' '<<point.y<<'\n';return;
    }
    std::vector<std::unique_ptr<RadarShapePoint[]>> pool;
    const auto create=[&]{auto data=std::make_unique<RadarShapePoint[]>(64);const auto slot=pool.size();for(unsigned k=0;k<64;++k)data[k]={int(1000+slot*100+k),int(2000+slot*100+k)};pool.push_back(std::move(data));};create();
    const auto id=[&](auto p){if(!p)return 0u;for(unsigned i=0;i<pool.size();++i)if(p==pool[i].get())return i+1;throw std::invalid_argument("Marker allocation identity");};
    RadarShapeVector v{{present?pool[0].get():nullptr,present?64u:0u},capacity,count,growth,1,std::uint8_t(owns)};
    std::array<std::uint8_t,1024> bytes{};SurfaceMarkBitmap bitmap{bytes,256};auto* bitmapPointer=&bitmap;
    RefreshSurfaceVirtuals table;RefreshSurface surface{&table,w,h},other{&table,7,6};auto* first=&surface;
    unsigned queries=0;
    table.width7C=[&](auto& s){std::cout<<"W "<<(&s==&surface?0:1)<<' '<<s.width<<' ';const auto value=s.width;if(++queries==mutation){first=&other;point.x=2;point.y=1;}return value;};
    table.height80=[&](auto& s){std::cout<<"H "<<(&s==&surface?0:1)<<' '<<s.height<<' ';const auto value=s.height;if(++queries==mutation){first=&other;point.x=2;point.y=1;}return value;};
    RadarDirtyServices s;
    s.vector.fieldStore=[&](auto off,auto n,auto val){std::cout<<"F "<<off<<' '<<n<<' '<<(off==4?id(v.items.data()):val)<<' ';};
    s.vector.pointStore=[&](auto backing,auto off,auto n,auto val){std::cout<<"P "<<id(backing.data())<<' '<<off<<' '<<n<<' '<<val<<' ';};
    s.vector.allocate=[&](auto n)->std::span<RadarShapePoint>{need(n>0&&n<=512&&n%8==0);std::cout<<"A "<<n<<' '<<fail<<' ';if(fail)return {};create();return {pool.back().get(),64};};
    s.vector.release=[&](auto backing){std::cout<<"D "<<id(backing.data())<<' ';};
    s.bitmapStore=[&](auto at,auto value){std::cout<<"B "<<at<<' '<<unsigned(value)<<' ';};
    std::uint8_t dirty=0;s.dirtyStore=[&](auto value){std::cout<<"S "<<unsigned(value)<<' ';};
    for(unsigned i=0;i<repeats;++i){std::cout<<"I "<<i<<' ';queueRadarDirtyPoint(point,{first,bitmapPointer,v,dirty},s);point.x=fillAdd(point.x,step);}
    std::cout<<"R "<<id(v.items.data())<<' '<<v.capacity<<' '<<v.count<<' '<<unsigned(v.valid)<<' '<<unsigned(v.owns)<<' '<<unsigned(dirty)<<' '<<point.x<<' '<<point.y<<' '<<(first==&surface?0:1)<<' ';
    const auto digest=[](auto data){std::uint64_t h=14695981039346656037ull;for(auto b:data){h^=b;h*=1099511628211ull;}return h;};
    std::cout<<digest(bytes)<<' ';
    for(const auto& data:pool){std::array<std::uint8_t,512> raw{};for(unsigned k=0;k<64;++k)for(unsigned axis=0;axis<2;++axis){const auto val=std::uint32_t(axis?data[k].y:data[k].x);for(unsigned b=0;b<4;++b)raw[k*8+axis*4+b]=std::uint8_t(val>>(8*b));}std::cout<<digest(raw)<<' ';}
    std::cout<<'\n';
}
void guards(){
    RadarShapePoint point{-1,0};RefreshSurface* surface=nullptr;SurfaceMarkBitmap* bitmap=nullptr;RadarShapeVector v;std::uint8_t dirty=0;
    queueRadarDirtyPoint(point,{surface,bitmap,v,dirty},{});need(dirty==0);
    point.x=0;bool refused=false;try{queueRadarDirtyPoint(point,{surface,bitmap,v,dirty},{});}catch(const std::invalid_argument&){refused=true;}need(refused);
    RefreshSurfaceVirtuals table;RefreshSurface valid{&table,2,2};surface=&valid;table.width7C=refreshSurfaceWidth;table.height80=refreshSurfaceHeight;
    refused=false;try{queueRadarDirtyPoint(point,{surface,bitmap,v,dirty},{});}catch(const std::invalid_argument&){refused=true;}need(refused&&dirty==0);
    float scale=1;int zero=0;point={0,0};projectRadarMarker(point,point,255,{scale,zero,zero,zero,zero});need(point.x==-1&&point.y==-1);
    std::cout<<"radar marker placement guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
