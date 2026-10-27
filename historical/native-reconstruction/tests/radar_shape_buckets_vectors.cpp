// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/RadarShapeBuckets.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Radar shape fixture domain");}
void run(std::istream& in){
 char op;unsigned mode,bits,owned,valid,present,fail,repeats;int count,capacity,growth,requested;
 need(bool(in>>op>>mode>>bits>>count>>capacity>>growth>>owned>>valid>>present>>fail>>repeats>>requested)&&op=='B'&&mode<=2&&capacity>=0&&capacity<=32&&owned<=255&&valid<=255&&present<=1&&fail<=1&&repeats>=1&&repeats<=2);
 RadarShapeDimensions widths,heights;for(auto& v:widths)need(bool(in>>v));for(auto& v:heights)need(bool(in>>v));std::string tail;need(!(in>>tail));
 std::array<RadarShapeVector,22> vectors;
 struct Allocation{std::unique_ptr<RadarShapePoint[]> data;};std::vector<Allocation> pool;unsigned slot=22;
 auto create=[&](unsigned i){auto data=std::make_unique<RadarShapePoint[]>(1024);for(unsigned k=0;k<1024;++k)data[k]={std::bit_cast<std::int32_t>(0x12340000u+i*1024+k),std::bit_cast<std::int32_t>(0x56780000u+i*1024+k)};pool.push_back({std::move(data)});};
 for(unsigned i=0;i<22;++i){create(i);vectors[i]={{present?pool[i].data.get():nullptr,present?1024u:0u},capacity,count,growth,std::uint8_t(valid),std::uint8_t(owned)};}
 auto identity=[&](auto data){for(unsigned i=0;i<pool.size();++i)if(pool[i].data.get()==data)return i+1;need(data==nullptr);return 0u;};
 const auto services=[&](unsigned i){
  RadarShapeServices s;
  s.fieldStore=[&,i](auto off,auto n,auto v){if(off==4&&v)v=identity(vectors[i].items.data());std::cout<<"F "<<i<<' '<<off<<' '<<n<<' '<<v<<' ';};
  s.pointStore=[&](auto backing,auto off,auto n,auto v){std::cout<<"P "<<identity(backing.data())<<' '<<off<<' '<<n<<' '<<v<<' ';};
  s.allocate=[&,i](auto bytes)->std::span<RadarShapePoint>{need(bytes>0&&bytes<=8192&&bytes%8==0);std::cout<<"A "<<i<<' '<<bytes<<' '<<fail<<' ';if(fail)return {};create(slot++);return {pool.back().data.get(),1024};};
  s.release=[&,i](auto backing){std::cout<<"D "<<i<<' '<<identity(backing.data())<<' ';};return s;
 };
 float scale=std::bit_cast<float>(bits);
 for(unsigned iteration=0;iteration<repeats;++iteration){
  std::cout<<"I "<<iteration<<' ';
  if(mode==0)initializeRadarShapeBuckets(vectors,scale,widths,heights,services);
  else if(mode==1){const auto result=resizeRadarShapeVector(vectors[0],requested,services(0));std::cout<<"R "<<result<<' ';}
  else clearRadarShapeVector(vectors[0],services(0));
 }
 std::cout<<"V ";for(const auto& v:vectors)std::cout<<identity(v.items.data())<<' '<<v.capacity<<' '<<v.count<<' '<<unsigned(v.valid)<<' '<<unsigned(v.owns)<<' ';
 std::cout<<"H ";for(const auto& allocation:pool){std::uint64_t h=14695981039346656037ull;for(unsigned i=0;i<1024;++i)for(auto v:{std::uint32_t(allocation.data[i].x),std::uint32_t(allocation.data[i].y)})for(unsigned b=0;b<4;++b){h^=std::uint8_t(v>>(b*8));h*=1099511628211ull;}std::cout<<h<<' ';}std::cout<<'\n';
}
void guards(){
 NativeRadarShapeBuckets owner;float scale=.5f;RadarShapeDimensions width{},height{};width.fill(1);height.fill(1);owner.initialize(scale,width,height);
 for(const auto& v:owner.buckets())need(v.count==1&&v.items[0].x==0&&v.items[0].y==0);
 width.fill(0);height.fill(0);owner.initialize(scale,width,height);
 for(const auto& v:owner.buckets())need(v.count==5&&v.capacity==10);
 bool refused=false;scale=100000.f;try{owner.initialize(scale,width,height);}catch(const std::invalid_argument&){refused=true;} // zero dimensions retain minimum2, so no refusal.
 need(!refused);width.fill(6);height.fill(6);try{owner.initialize(scale,width,height);}catch(const std::invalid_argument&){refused=true;}need(refused);
 std::cout<<"radar shape buckets guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
