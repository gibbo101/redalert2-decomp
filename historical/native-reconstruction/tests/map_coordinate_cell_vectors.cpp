// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapCoordinateCell.hpp"
#include <bit>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {unsigned packed(MapInputPosition p){return std::uint16_t(p.x)|(unsigned(std::uint16_t(p.y))<<16);}}
int main(){try{
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);char op=0;int count=0,n=0,queries=0;in>>op>>count>>n;
  if(op!='C'||count<0||count>262144||n<0||n>64)throw std::invalid_argument("Invalid coordinate Cell table");
  std::vector<MapCellInput> cells(static_cast<std::size_t>(n));std::vector<MapCellInput*> table(262144);
  for(int i=0;i<n;++i){int slot=0;in>>slot;if(slot<0||slot>=262144||table[std::size_t(slot)])throw std::invalid_argument("Invalid coordinate Cell slot");
   cells[std::size_t(i)].position={std::int16_t(i*29-32768),std::bit_cast<std::int16_t>(std::uint16_t(i*31+32700))};table[std::size_t(slot)]=&cells[std::size_t(i)];}
  in>>queries;if(queries<1||queries>4096)throw std::invalid_argument("Invalid coordinate query count");
  MapCellInput fallback;fallback.position={-30000,29000};int stores=0;MapFloorHeightWorld world{table,&fallback,[&](auto){++stores;}};
  for(int q=0;q<queries;++q){Coord p;in>>p.x>>p.y>>p.z;if(!in)throw std::invalid_argument("Incomplete coordinate query");
   const int before=stores;auto& result=mapCoordinateCell(p,world,count);const auto id=&result==&fallback?-1:&result-cells.data();
   std::cout<<id<<' '<<packed(result.position)<<' '<<packed(fallback.position)<<' '<<stores-before<<' ';}
  in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing coordinate data");std::cout<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
