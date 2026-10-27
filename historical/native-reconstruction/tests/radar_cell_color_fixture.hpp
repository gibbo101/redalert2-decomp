// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/CellRadarColor.hpp"
#include "render/OverlayRadarColor.hpp"
#include "assets/OverlayImage.hpp"
#include "assets/MapOverlay.hpp"
#include "sim/CellResidentSearch.hpp"
#include <iostream>
#include <sstream>
struct CellColorProfile {
 int resident=0,tile=0,overlay=-1,data=0,sub=0,variants=1,raw=0,mode=0,frames=0,nulls=0,force=0,resource=-1,lazy=0;
 std::uint32_t flags=0,scale=0x3f800000;
 void read(std::istream& in){
  if(!(in>>resident>>flags>>tile>>overlay>>data>>sub>>variants>>raw>>mode>>frames>>nulls>>force>>resource>>lazy>>scale)||resident<0||resident>1||(tile!=0&&tile!=1&&tile!=65535)||overlay< -1||overlay>250||data<0||data>255||sub<0||sub>3||variants<1||variants>4||raw<0||raw>9||mode<0||mode>3||frames< -1||frames>4||nulls<0||nulls>15||force<0||force>1||resource< -1||resource>2||lazy<0||lazy>1||(frames<0&&data>3))throw std::invalid_argument("Cell color fixture input");
 }
};
struct CellColorFixture {
 CellColorProfile p;bool recoveredOverlay=false,recoveredDemand=false,recoveredResource=false;ra2::OverlayTypeInputs demandType;std::optional<ra2::Data> demandImage;std::uint8_t demandOwned=0;int seed,clear=1;std::vector<ra2::TileSweepType> types;ra2::Data animation;
 std::vector<ra2::MapResourceType> resources;
 ra2::TileVariantCache cache;ra2::TileVariantTables tables;
 CellColorFixture(CellColorProfile profile,int value):p(profile),seed(value),types(8){
  cache.initialized=1;cache.large.fill(p.raw);tables.small.fill(p.raw);
  ra2::Bytes bytes(104,0);bytes[6]=std::uint8_t(p.frames);bytes[7]=std::uint8_t(p.frames>>8);
  for(int i=0;i<4;++i)for(int k=0;k<3;++k)bytes[20+i*24+k]=std::uint8_t(seed+i*23+k*19);animation=ra2::Data(std::move(bytes));
  demandType.imageName="LOBRDG10";demandType.theater=1;demandType.demandLoad=1;demandType.image=p.lazy?0u:1u;if(!p.lazy)demandImage=animation;
  demandType.tiberium=std::uint8_t(p.mode&1);
  for(int i=0;i<8;++i){types[i].next=i+1;types[i].variants=p.variants;types[i].lazy=std::uint8_t(p.lazy);if(!p.lazy)types[i].image=makeImage(i);}
 }
 void readResources(std::istream& in){
  int count;if(!(in>>count)||count<0||count>8)throw std::invalid_argument("Radar resource registry count");resources.resize(std::size_t(count));
  for(auto& r:resources)if(!(in>>r.index>>r.imageIndex>>r.numImages>>r.numSlopes>>r.numFrames>>r.value))throw std::invalid_argument("Radar resource record");
 }
 ra2::Data makeImage(int id){
  ra2::Bytes bytes(288,0);const auto put=[&](int at,std::uint32_t v){for(int k=0;k<4;++k)bytes[at+k]=std::uint8_t(v>>(k*8));};
  put(0,4);put(4,1);put(8,60);put(12,30);
  for(int i=0;i<4;++i){const int at=32+i*64;put(16+i*4,p.nulls&(1<<i)?0:at);put(at+0x24,p.force?4:0);for(int k=0;k<3;++k)bytes[at+0x2b+k]=std::uint8_t(seed+id*41+i*17+k*53);}
  return ra2::Data(std::move(bytes));
 }
 void initialize(ra2::MapCellAttributes& c){c.input.flags=p.flags;c.input.tile=p.tile;c.input.subTile=std::uint8_t(p.sub);c.overlay=p.overlay;c.overlayData=std::uint8_t(p.data);}
 void colors(ra2::MapCellAttributes& c,ra2::RadarRGB& a,ra2::RadarRGB& b,const std::function<void(ra2::RadarRGB&,unsigned,unsigned,std::uint32_t)>& stores={}){
  ra2::CellRadarColorServices services;
  services.resident471760=[&](auto kind,auto use){std::cout<<"D "<<kind<<' '<<unsigned(use)<<' ';
   const void* primary=p.resident?static_cast<const void*>(&p):nullptr;const void* secondary=nullptr;
   ra2::CellResidentKind6Services resident;resident.kind=[&](const void* owner){if(owner!=&p)throw std::invalid_argument("Resident owner");return 36;};
   return ra2::findCellResident({1},{primary,secondary},kind,use,resident)!=nullptr;};
  services.primary=[](int id){if(id<0||id>1)throw std::invalid_argument("Primary index");return id;};
  services.type=[&](int id)->ra2::TileSweepType&{if(id<0||id>=8)throw std::invalid_argument("Alternate index");return types[id];};
  services.load52B560=[&](int id){std::cout<<"L "<<id<<' ';types[id].image=makeImage(id);};
  services.variant4767A0=[&](const auto& cell,int tile,int variants){
   std::cout<<"J "<<tile<<' '<<variants<<' ';
   auto& t=types[tile];if(cell.subTile&&!t.image&&t.lazy)services.load52B560(tile);
   ra2::TileVariantImage dimensions{4,1};return ra2::selectTileVariant(cache,tables,cell.position.x,cell.position.y,cell.subTile,variants,t.image?&dimensions:nullptr,{});
  };
  services.overlay279=[&](int){return recoveredResource?demandType.tiberium:std::uint8_t(p.mode&1);};
  services.overlayAlternate26C=[&](int)->const ra2::Data*{return p.mode&2?&animation:nullptr;};
  services.overlay5DD000=[&](int id,std::uint32_t data){std::cout<<"O "<<id<<' '<<data<<' ';
   if(recoveredOverlay){
    ra2::OverlayTypeInputs suppliedType;auto& type=recoveredDemand?demandType:suppliedType;type.index=id;type.cellAnim=(p.mode&2)?17u:0u;
    ra2::OverlayRadarColorServices image;image.primaryImage=[&]()->const ra2::Data*{if(recoveredDemand){
     int theater=0;ra2::OverlayImageServices file;file.load=[&](const auto& filename){if(filename!="LOBRDG10.TEM")throw std::invalid_argument("Demand filename");std::cout<<"G 1 G 2 ";return ra2::OverlayImageResult{2,animation};};file.finish=[] {std::cout<<"G 3 G 4 ";};file.store=[](auto off,auto n,auto v){std::cout<<"X "<<off<<' '<<n<<' '<<v<<' ';};
     (void)ra2::ensureOverlayImage(demandType,demandImage,demandOwned,theater,file);return demandImage?&*demandImage:nullptr;
    }return p.lazy?nullptr:&animation;};image.animationImage=[&](auto handle)->const ra2::Data*{if(handle!=17)throw std::invalid_argument("Overlay animation owner");return &animation;};
    ra2::RadarRGB color{};ra2::overlayRadarColor(type,data,color,image);return color;
   }
   return ra2::RadarRGB{std::uint8_t(seed+id*13+data*29),std::uint8_t(seed+id*13+data*29+7),std::uint8_t(seed+id*13+data*29+14)};};
  services.resource5DC0B0=[&](int id){std::cout<<"E "<<id<<' ';
   if(recoveredResource){const auto result=ra2::classifyOverlayResource(id,&demandType,resources,[](int missing){std::cout<<"Z "<<missing<<' ';});std::cout<<"Y "<<std::uint32_t(result)<<' ';return result;}
   return p.resource;};
  services.theaterScale=[&]{return std::bit_cast<float>(p.scale);};
  services.store=stores;ra2::cellRadarColors(c,clear,a,b,services);
 }
};
