// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/AlphaAnimationLifecycle.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){
  AlphaCombinationTable t;t.initialized=1;std::int32_t n=1;std::array<AlphaAnimationRecord*,1> empty{nullptr};std::span<AlphaAnimationRecord*> slots=empty;
  MissionExpirationVector<AlphaAnimationRecord*> v{n,slots,&n};bool refused=false;
  try{cleanupAlphaAnimations(t,v,{});}catch(const std::invalid_argument&){refused=true;}if(!refused)throw std::runtime_error("Null cleanup dereference accepted");
  AlphaAnimationRecord r;r.expired3c=1;empty[0]=&r;refused=false;
  try{cleanupAlphaAnimations(t,v,{});}catch(const std::invalid_argument&){refused=true;}if(!refused)throw std::runtime_error("Unbound deleting child accepted");
  empty[0]=nullptr;n=1048577;refused=false;
  try{cleanupAlphaAnimations(t,v,{});}catch(const std::invalid_argument&){refused=true;}if(!refused)throw std::runtime_error("Unbounded cleanup accepted");
  std::cout<<"Alpha lifecycle guards PASS\n";return 0;
 }
 const auto layout=[](int n){const std::array<std::array<int,4>,4> rows{{{1,2,1,2},{0,1,0,2},{1,0,2,0},{2,1,2,1}}};return rows.at(n);};
 std::string line;while(std::getline(std::cin,line)){
  std::array<std::int64_t,20> f{};std::istringstream in(line);for(auto& n:f)in>>n;if(!in)throw std::invalid_argument("Invalid lifecycle input");
  std::array<int,3> associated{0,1,2};Bytes image(8);auto word=[&](int at,int v){image[at]=std::uint8_t(v);image[at+1]=std::uint8_t(unsigned(v)>>8);};word(2,int(f[14]));word(4,int(f[15]));word(6,1);
  std::array<AlphaAnimationRecord,3> records;std::array<int,3> freed{};
  for(int i=0;i<3;++i){auto& r=records[i];r.associated24=i==0&&f[19]?nullptr:&associated[i];r.bounds28={0x5a5a5a5a,0x5a5a5a5a,0x5a5a5a5a,0x5a5a5a5a};r.image38=image;r.expired3c=(f[18]&(1<<i))?128:0;r.index10=0x5a5a5a5a;r.flags14=std::uint8_t(f[2]);r.value18=r.value1c=0x5a5a5a5a;r.byte20=0x5a;}
  std::array<std::array<std::int32_t,4>,3> publishedBounds;
  for(auto& row:publishedBounds)row.fill(0x5a5a5a5a);
  std::array<AlphaAnimationRecord*,16> pslots,palt;std::array<const void*,16> sslots,salt;
  auto row=layout(int(f[17]));for(int i=0;i<16;++i){pslots[i]=&records[row[i%4]];sslots[i]=&records[row[(15-i)%4]];palt[i]=&records[std::array<int,4>{2,0,1,0}[i%4]];salt[i]=palt[i];}
  std::span<AlphaAnimationRecord*> pspan=pslots;std::span<const void*> sspan=sslots;
  std::int32_t pn=int(f[4]),pc=int(f[5]),pg=int(f[7]),sn=int(f[8]),sc=int(f[9]),sg=int(f[11]);std::uint8_t pa=std::uint8_t(f[6]),sa=std::uint8_t(f[10]);
  AlphaAnimationRegistryView<AlphaAnimationRecord*> primary{{pn,pspan,&pn},pc,pa,pg,{}};
  AlphaAnimationRegistryView<const void*> secondary{{sn,sspan,&sn},sc,sa,sg,{}};
  AlphaCombinationTable table;table.initialized=std::uint8_t(f[1]);for(std::uint32_t i=0;i<65536;++i)table.values[i]=std::uint8_t(i*7+3);
  auto pid=[&](const void* p)->int{if(!p)return 0;for(int i=0;i<3;++i){if(p==&records[i])return i+1;if(p==&associated[i])return i+11;}if(p==image.data())return 21;if(p==&pn)return 31;if(p==&sn)return 32;throw std::invalid_argument("Unknown lifecycle pointer");};
  std::ostringstream trace;auto event=[&](int k,std::int64_t a=0,std::int64_t b=0,std::int64_t c=0,std::int64_t d=0){trace<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};
  bool mutated=false;int resizing=0;
  auto mutate=[&](int where){int m=int(f[13]);if(!m||mutated||where!=m)return;mutated=true;event(9,m);
   if(m==1){sc=0;sg=3;}if(m==2){if(resizing)sn=1;else pn=1;}if(m==3){pspan=palt;pn=2;}if(m==4){pspan=palt;pn=1;}if(m==5)pspan=palt;};
  primary.resize=[&](int cap,std::uint32_t zero){resizing=0;event(2,31,cap,zero,f[12]);if(std::uint8_t(f[12])){std::copy(pspan.begin(),pspan.end(),palt.begin());pspan=palt;pc=cap;pa=1;}mutate(2);return std::uint32_t(f[12]);};
  secondary.resize=[&](int cap,std::uint32_t zero){resizing=1;event(2,32,cap,zero,f[12]);if(std::uint8_t(f[12])){std::copy(sspan.begin(),sspan.end(),salt.begin());sspan=salt;sc=cap;sa=1;}mutate(2);return std::uint32_t(f[12]);};
  AlphaAnimationLifecycleServices s{primary,secondary,{},{},{},{},{}};
  s.typeImage84=[&](const void* p){event(1,pid(p));mutate(1);return std::span<const std::uint8_t>(image);};
  s.projectInterfaces=[&](auto& r,unsigned kind){if(kind==2){event(4,pid(&r),8,8);event(4,pid(&r),12,9);}else for(int i=0;i<4;++i)event(4,pid(&r),4*i,int(kind)*4+i);};
  s.beforeFind=[&](const void* p){event(3,pid(p));mutate(3);};
  s.freeRecord=[&](auto& r){const int id=pid(&r);event(5,id);++freed[id-1];};
  s.store=[&](const void* p,std::int64_t off,std::uint32_t value,const void* pointer){
   if(p==&table){event(6,off,value);return;}
   const int id=pid(p);
   if(id>=1&&id<=3&&off>=0x28&&off<=0x34){
    publishedBounds[id-1][std::size_t((off-0x28)/4)]=std::bit_cast<std::int32_t>(value);
    const auto& b=records[id-1].bounds28;
    if(publishedBounds[id-1]!=std::array<std::int32_t,4>{b.x,b.y,b.width,b.height})
        throw std::runtime_error("Alpha constructor published later fields before their ordered store");
   }
   event(4,id,off,value,pid(pointer));if(p==&pn&&off==16)mutate(5);};
  const auto destroy=[&](auto& r,std::uint32_t deleting){mutate(4);return destroyAlphaAnimation(r,deleting,s);};
  if(f[0]==0||f[0]==5)event(8,pid(constructAlphaAnimation(records[0],table,&associated[0],17,-23,false,s)));
  if(f[0]==1)event(8,pid(constructAlphaAnimation(records[0],table,nullptr,0,0,true,s)));
  if(f[0]==2||f[0]==5)expireAlphaAnimation(records[0],f[3]==1?&associated[0]:f[3]==2?nullptr:&associated[1],std::uint32_t(f[16]),s.store);
  if(f[0]==3)event(8,pid(destroy(records[0],std::uint32_t(f[16]))));
  if(f[0]==4||f[0]==5)cleanupAlphaAnimations(table,primary.entries,[&](auto& r,auto deleting){if(r.derivedInterfaces)mutate(4);deleteAlphaAnimation(r,deleting,s);},s.store);
  std::cout<<trace.str()<<"F "<<mutated<<' ';for(int n:freed)std::cout<<n<<' ';std::cout<<unsigned(table.initialized)<<' ';
  auto registry=[&](auto& v,const auto& alt){std::cout<<std::uint32_t(v.entries.count)<<' '<<std::uint32_t(v.capacity)<<' '<<(v.entries.slots.data()==alt.data())<<' '<<unsigned(v.allocated)<<' '<<std::uint32_t(v.increment)<<' ';for(auto* p:v.entries.slots)std::cout<<pid(p)<<' ';};
  registry(primary,palt);registry(secondary,salt);
  for(auto& r:records)std::cout<<std::uint32_t(r.index10)<<' '<<unsigned(r.flags14)<<' '<<r.value18<<' '<<r.value1c<<' '<<unsigned(r.byte20)<<' '<<pid(r.associated24)<<' '<<std::uint32_t(r.bounds28.x)<<' '<<std::uint32_t(r.bounds28.y)<<' '<<std::uint32_t(r.bounds28.width)<<' '<<std::uint32_t(r.bounds28.height)<<' '<<pid(r.image38.data())<<' '<<unsigned(r.expired3c)<<' ';
  std::cout<<assetSha256(Data(Bytes(table.values.begin(),table.values.end())))<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
