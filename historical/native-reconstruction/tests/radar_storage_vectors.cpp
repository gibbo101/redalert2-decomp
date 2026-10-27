// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/RadarStorage.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Radar storage domain");}
std::uint64_t digest(std::span<const std::uint8_t> bytes,std::size_t padded){
 std::uint64_t value=14695981039346656037ull;need(bytes.size()<=padded);
 for(std::size_t i=0;i<padded;++i){value^=i<bytes.size()?bytes[i]:0xa5;value*=1099511628211ull;}return value;
}
void run(std::istream& in){
 char op;int w,h,x,y,seed,format,forced,repeats;
 need(bool(in>>op>>w>>h>>x>>y>>seed>>format>>forced>>repeats)&&op=='J'&&w>0&&w<=32&&h>0&&h<=32&&seed>=0&&seed<=255&&format>=0&&format<=1&&forced>=0&&forced<=255&&repeats>=1&&repeats<=2);
 std::string tail;need(!(in>>tail));
 RadarStorage storage(format?std::array<std::int32_t,6>{10,3,0,3,5,3}:std::array<std::int32_t,6>{11,3,0,3,5,2},[](char k,auto values){std::cout<<k<<' ';for(auto v:values)std::cout<<v<<' ';});
 for(int iteration=0;iteration<repeats;++iteration){
  RefreshRect rect{17,19,w,h};std::cout<<"I "<<iteration<<' ';
  storage.initialize(rect,x,y,[&](auto& source,auto& region,auto rgb){need(&source==&region&&source==RefreshRect{0,0,w,h});for(std::size_t i=0;i<rgb.size();++i)rgb[i]=std::uint8_t(i*29+seed);},[]{},std::uint8_t(forced));
  std::cout<<"R ";for(auto v:rect)std::cout<<v<<' ';
  std::cout<<storage.second()->width<<' '<<storage.second()->height<<' '<<radarProjectionFloatBits(storage.scale())<<' '<<storage.colorWidth()<<' '<<storage.colorHeight()<<' '<<storage.displayBytes()<<' '<<unsigned(storage.displayVideo())<<' ';
  std::cout<<digest(storage.terrainRGB(),3072)<<' '<<digest(storage.terrainPixels(),32768)<<' '<<digest(storage.bitmap(),4096)<<' '<<digest(storage.displayPixels(),32768)<<' ';
 }
 std::cout<<'\n';
}
void guards(){
 static_assert(!std::is_copy_constructible_v<RadarStorage> && !std::is_move_constructible_v<RadarStorage>);
 RadarStorage storage({11,3,0,3,5,2});int x=0,y=0;RefreshRect r{17,19,0,1};storage.initialize(r,x,y,{},{});need(r==RefreshRect{17,19,0,1}&&!storage.first()&&!storage.second());
 r={0,0,3,2};bool refused=false;try{storage.initialize(r,x,y,{},[]{});}catch(const std::invalid_argument&){refused=true;}need(refused&&!storage.first());
 r={0,0,3,2};storage.initialize(r,x,y,[](auto&,auto&,auto rgb){std::fill(rgb.begin(),rgb.end(),91);},[]{});
 need(storage.first()!=storage.second()&&storage.first()->table!=storage.second()->table&&bool(storage.first()->table->copy8)&&storage.displayBytes()==2&&storage.displayVideo()==0);
 auto before=std::vector<std::uint8_t>(storage.terrainPixels().begin(),storage.terrainPixels().end());
 r={5,6,0,1};storage.initialize(r,x,y,{},{});need(std::equal(before.begin(),before.end(),storage.terrainPixels().begin()));
 std::cout<<"radar storage guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
