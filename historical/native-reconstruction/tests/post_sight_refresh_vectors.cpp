// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/PostSightRefresh.hpp"
#include <bit>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace ra2;
namespace {
void require(bool value){if(!value)throw std::invalid_argument("Post-sight fixture outside domain");}
template<class T>T take(std::istream& in){T value{};require(bool(in>>value));return value;}
void run(std::istream& in){
 require(take<char>(in)=='P');Coord p{take<int>(in),take<int>(in),take<int>(in)};const int inner=take<int>(in),outer=take<int>(in);const auto disabled=take<std::uint32_t>(in);const auto scaleBits=take<std::uint64_t>(in);const int mode=take<int>(in),maskSeed=take<int>(in),primarySeed=take<int>(in);std::string extra;require(!(in>>extra)&&mode>=0&&mode<3);
 auto startup=initializeVisibilityStartup();startup.heightProjectionScale=std::bit_cast<double>(scaleBits);
 std::array<CellVisibilityState,17> cells{};for(int i=0;i<17;++i){cells[std::size_t(i)].identity=i;cells[std::size_t(i)].primary120=std::uint8_t(primarySeed+i*17);cells[std::size_t(i)].redraw138=std::uint8_t((primarySeed+i)&1);}cells[16].point={std::int16_t(0xa5a5),std::int16_t(0xa5a5)};
 std::vector<CellVisibilityState*> table(262144);const int rawx=p.x/256,rawy=p.y/256;if(mode!=2)for(int y=rawy-24;y<=rawy+24;++y)for(int x=rawx-24;x<=rawx+24;++x){const int index=y*512+x;if(index<0||index>=262144||(mode==1&&((x+y)&1)))continue;table[std::size_t(index)]=&cells[std::size_t((x&3)|((y&3)<<2))];}
 PostSightRefreshWorld world{table,&cells[16]};world.fallbackStore=[](TerrainCellPoint q){std::cout<<"F "<<q.x<<' '<<q.y<<' ';};world.query=[](TerrainCellPoint q,int id){std::cout<<"L "<<q.x<<' '<<q.y<<' '<<id<<' ';};
 PostSightRefreshServices services;services.visibilityMask=[&](TerrainCellPoint q){const auto v=std::uint8_t(maskSeed+int(q.x)*3+int(q.y)*5);std::cout<<"M "<<q.x<<' '<<q.y<<' '<<unsigned(v)<<' ';return v;};services.redraw=[](int id){std::cout<<"D "<<id<<' ';};services.trace=[](char k,int a,int b,int){if(k=='H')std::cout<<"H "<<a<<' ';else if(k=='P'||k=='B')std::cout<<k<<' '<<a<<' '<<b<<' ';};
 refreshPostSightVisibility(p,inner,outer,disabled,world,startup,services);std::cout<<'S';for(const auto& c:cells)std::cout<<' '<<unsigned(c.primary120)<<' '<<unsigned(c.redraw138);std::cout<<' '<<cells[16].point.x<<' '<<cells[16].point.y<<'\n';
}
void guards(){std::array<CellVisibilityState*,262144> table{};CellVisibilityState fallback;PostSightRefreshWorld world{table,&fallback};VisibilityStartup startup=initializeVisibilityStartup();PostSightRefreshServices services;services.visibilityMask=[](auto){return std::uint8_t(0);};services.redraw=[](int){};bool refused=false;try{refreshPostSightVisibility({},8,3,0,world,startup,services);}catch(const std::invalid_argument&){refused=true;}require(refused);refreshPostSightVisibility({},8,3,1,world,startup,services);std::cout<<"post-sight refresh guards PASS\n";}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
