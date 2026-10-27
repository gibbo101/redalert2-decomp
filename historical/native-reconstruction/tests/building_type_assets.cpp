// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/Archive.hpp"
#include "assets/Shp.hpp"
#include "assets/Formats.hpp"
#include "assets/PreparedData.hpp"
#include "render/BuildingTypeBounds.hpp"
#include <bit>
#include <iostream>
using namespace ra2;
int main(int argc,char** argv){try{
 if(argc!=2)throw std::invalid_argument("Usage: building-type-assets OWNED_INSTALL");
 AssetStore store(argv[1]);
 // Explicit stock Temperate bindings; theater/image lookup and loading are not
 // recovered here. Read-only original headers and the existing decoder agree.
 for(const auto& file:{"ctarmy04.shp","ctarmy01.shp"}){
  auto bytes=store.require(file);auto image=readShp(bytes);const auto count=int(image.frames.size());
  if(count!=6)throw std::invalid_argument("Stock Objective1 image frame count differs");
  auto word=[&](std::size_t off){return std::bit_cast<std::int16_t>(bytes.u16(off));};
  if(word(2)!=image.width||word(4)!=image.height||word(6)!=count)throw std::invalid_argument("Decoded SHP header differs");
  for(int i=0;i<count;++i){const auto& f=image.frames[i];const int off=8+i*24;
   if(word(off)!=f.x||word(off+2)!=f.y||word(off+4)!=f.width||word(off+6)!=f.height)throw std::invalid_argument("Decoded crop differs from original signed header");}
  BuildingTypeBoundsState state;const auto bounds=buildingTypeBounds(state,{}, {[&]{return shpBoundsView(image);},[]{return ShpBoundsView{};},{},{},{}});
  std::cerr<<file<<" native bounds "<<bounds.x<<' '<<bounds.y<<' '<<bounds.width<<' '<<bounds.height<<'\n';
  for(int index=-1;index<count;++index){
   std::cout<<file<<':'<<(index<0?"parent":"frame"+std::to_string(index))<<'\t'<<assetSha256(bytes)<<'\t';
   std::cout<<(index<0?0:1)<<" 0 0 0 0 0 0 0 0 0 -1 -1 0 128 0 -1 "<<(index<0?0:index);
   for(int id=0;id<3;++id){
    std::cout<<' '<<(id?0:word(2))<<' '<<(id?0:word(4))<<' '<<(id?0:word(6));
    for(int frame=0;frame<count;++frame)for(int field=0;field<4;++field)std::cout<<' '<<(id?0:word(8+frame*24+field*2));
   }
   std::cout<<'\n';
  }
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
