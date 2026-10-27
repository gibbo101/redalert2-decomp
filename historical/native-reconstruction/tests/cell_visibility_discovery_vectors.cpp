// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/CellVisibilityDiscovery.hpp"
#include <array>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Cell visibility discovery fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
struct Record {int present=0,level=0,members=0,active=0,ax=0,ay=0,bx=0,by=0;};
void run(std::istream& in){
 require(take<char>(in)=='V');const int sx=take<int>(in),sy=take<int>(in),house=take<int>(in),notify=take<int>(in);require(notify==0||notify==1);
 std::array<Record,8> r{};for(auto& x:r){x={take<int>(in),take<int>(in),take<int>(in),take<int>(in),take<int>(in),take<int>(in),take<int>(in),take<int>(in)};require((x.present==0||x.present==1)&&x.level>=-128&&x.level<=127&&x.members>=0&&x.members<4&&x.active>=0&&x.active<4);}
 std::string extra;require(!(in>>extra)&&sx>=-32768&&sx<=32761&&sy>=-32768&&sy<=32761);
 std::vector<std::string> out;std::array<TerrainCellPoint,9> points{};std::array<std::array<int,2>,8> next{};std::array<std::array<std::uint8_t,2>,8> active{};
 for(int i=0;i<7;++i)points[std::size_t(i)]={std::int16_t(sx+i),std::int16_t(sy+i)};points[8]=points[0];
 const auto object=[](int cell,int member){return cell*2+member;};
 CellVisibilityDiscoveryServices s;
 s.point=[&](int cell){return points.at(std::size_t(cell));};
 s.cellAt=[&](TerrainCellPoint p){const int i=int(p.x)-sx;require(i>=0&&i<7&&int(p.y)-sy==i);const int id=r[std::size_t(i)].present?i:7;if(id==7)points[7]=p;out.push_back("C");out.push_back(std::to_string(p.x));out.push_back(std::to_string(p.y));out.push_back(std::to_string(id));return id;};
 s.level=[&](int cell){out.push_back("L");out.push_back(std::to_string(cell));out.push_back(std::to_string(r.at(std::size_t(cell)).level));return std::int8_t(r.at(std::size_t(cell)).level);};
 s.residents=[&](int cell){const auto& q=r.at(std::size_t(cell));std::vector<int> members;for(int m=0;m<2;++m)if(q.members&(1<<m))members.push_back(m);for(int m=0;m<2;++m){active[std::size_t(cell)][std::size_t(m)]=std::uint8_t((q.active>>m)&1);next[std::size_t(cell)][std::size_t(m)]=-1;}for(std::size_t i=1;i<members.size();++i)next[std::size_t(cell)][std::size_t(members[i-1])]=object(cell,members[i]);
  CellClosestResidentServices n;n.head=[&,cell,members](bool elevated){require(!elevated);return members.empty()?-1:object(cell,members.front());};n.flags=[&,cell](int id){require(id/2==cell);return active[std::size_t(cell)][std::size_t(id%2)];};n.next=[&,cell](int id){require(id/2==cell);return next[std::size_t(cell)][std::size_t(id%2)];};n.coordinates=[&,cell](int id){require(id/2==cell);const auto& z=r.at(std::size_t(cell));out.push_back("P");out.push_back(std::to_string(id));return Coord{id%2?z.bx:z.ax,id%2?z.by:z.ay,0};};n.squareRoot=[](double v){return std::sqrt(v);};n.memberLimit=2;return n;};
 s.notifyCell=[&](TerrainCellPoint p){out.push_back("N");out.push_back(std::to_string(p.x));out.push_back(std::to_string(p.y));};
 s.discoveredBy=[&](int id,int h){out.push_back("D");out.push_back(std::to_string(id));out.push_back(std::to_string(h));};
 discoverVisibleCellResidents(8,house,notify!=0,s);for(std::size_t i=0;i<out.size();++i)std::cout<<(i?" ":"")<<out[i];std::cout<<" R\n";
}
void guards(){CellVisibilityDiscoveryServices s;bool refused=false;try{discoverVisibleCellResidents(0,0,false,s);}catch(const std::invalid_argument&){refused=true;}require(refused);std::cout<<"Cell visibility discovery guards PASS\n";}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
