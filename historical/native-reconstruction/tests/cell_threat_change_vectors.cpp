// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/CellThreatChange.hpp"
#include <iostream>
#include <sstream>
#include <vector>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Cell threat fixture differs");}
void run(std::istream& in){
 std::array<std::int32_t,41> f{};for(auto& v:f)require(bool(in>>v));std::string tail;require(!(in>>tail));
 require(f[0]>=0&&f[0]<=3&&f[2]>=-32768&&f[2]<=32767&&f[6]>=-2&&f[6]<=4&&f[7]>=0&&f[7]<16&&f[8]>=0&&f[8]<=1&&f[10]>=0&&f[10]<=2);
 struct H{int index;std::uint8_t a,b;std::uint32_t allies;std::array<int,0x4204> grid;};
 std::array<H,3> hs;std::array<const void*,4> slots{};int enemy=0,count=0;std::span<HouseThreatScore> scores;
 for(int i=0;i<3;++i){require(f[12+4*i]>=0&&f[12+4*i]<=255&&f[13+4*i]>=0&&f[13+4*i]<=255);hs[i].index=f[11+4*i];hs[i].a=std::uint8_t(f[12+4*i]);hs[i].b=std::uint8_t(f[13+4*i]);hs[i].allies=std::uint32_t(f[14+4*i]);hs[i].grid.fill(f[9]);}
 for(int i=0;i<4;++i)slots[i]=(f[7]>>i&1)?nullptr:&hs[f[8]?0:i%3];
 const auto hid=[&](const void* p){for(int i=0;i<3;++i)if(p==&hs[i])return i;throw std::invalid_argument("Foreign threat House");};
 const auto house=[&](const void* p){auto& h=hs[hid(p)];return HouseThreatHouse{p,h.index,h.a,h.a,h.b,h.allies,enemy,count,scores,h.grid};};
 std::array<int,9> offsets,shifts;for(int i=0;i<9;++i){offsets[i]=f[23+i];shifts[i]=f[32+i];}
 std::array<const void*,4> alt{&hs[2],&hs[0],nullptr,&hs[1]};
 std::span<const void*> backing{slots};int result=0,writes=0;
 std::int16_t x=f[0]==0?std::int16_t(f[1]):0,y=std::int16_t(f[2]);
 const CellThreatStore stored=[&](const void* p,int slot,int value){
  std::cout<<hid(p)<<' '<<slot<<' '<<std::uint32_t(value)<<' ';
  if(++writes==1&&f[10]){backing=alt;if(f[10]==1){f[6]=1;x=y=100;}}
 };
 if(f[0]==0){require(f[1]>=-32768&&f[1]<=32767);CellThreatWorld w{f[5],f[6],backing,offsets,shifts,house,stored};changeCellThreat({x,y},f[3],f[4],w);}
 if(f[0]==1)changeHouseCellThreat(house(&hs[0]),f[1],f[4],offsets,shifts,stored);
 if(f[0]==2)result=cellThreatAlliedIndex(house(&hs[0]),f[3]);
 if(f[0]==3)result=cellThreatControlled(house(&hs[0]),f[5]);
 std::cout<<"R "<<result<<' ';
 for(auto& h:hs){std::size_t n=0;for(auto v:h.grid)if(v!=f[9])++n;std::cout<<"G "<<n<<' ';for(int i=0;i<int(h.grid.size());++i)if(h.grid[i]!=f[9])std::cout<<i<<' '<<std::uint32_t(h.grid[i])<<' ';}
 std::cout<<"D "<<std::uint32_t(f[6])<<' '<<(backing.data()==alt.data())<<' '<<std::uint32_t(x)<<' '<<std::uint32_t(y)<<'\n';
}
void guards(){
 int mode=0,count=1,index=2,enemy=0,scoresCount=0,id,other;std::uint8_t a=0,b=0;std::uint32_t allies=0;std::span<HouseThreatScore> scores;std::array<int,1024> grid{};std::array<int,9> offsets{},shifts{};std::array<const void*,2> slots{&id,&other},alt{nullptr,&id};std::span<const void*> backing{slots};
 std::vector<const void*> visited;
 const auto house=[&](const void* p){visited.push_back(p);return HouseThreatHouse{p,index,a,a,b,allies,enemy,scoresCount,scores,grid};};
 CellThreatWorld w{mode,count,backing,offsets,shifts,house,{}};std::int16_t x=0,y=0;
 bool refused=false;w.house={};try{changeCellThreat({x,y},-1,1,w);}catch(const std::invalid_argument&){refused=true;}require(refused);w.house=house;
 count=3;refused=false;try{changeCellThreat({x,y},-1,1,w);}catch(const std::invalid_argument&){refused=true;}require(refused);
 grid.fill(0);count=2;int writes=0;w.stored=[&](auto,int,int){if(++writes==1){count=1;backing=alt;x=100;y=100;}};
 changeCellThreat({x,y},-1,1,w);require(writes==9&&grid[131]==9); // saved Cell, live count
 grid.fill(0);x=y=0;count=2;backing=slots;writes=0;visited.clear();w.stored=[&](auto,int,int){if(++writes==1)backing=alt;};
 changeCellThreat({x,y},-1,1,w);require(writes==18&&grid[131]==18&&visited==std::vector<const void*>({&id,&id})); // live backing, duplicate physical House
 w.stored={};offsets[0]=-9999;refused=false;try{changeHouseCellThreat(house(&id),0,1,offsets,shifts);}catch(const std::invalid_argument&){refused=true;}require(refused);
 std::cout<<"Cell threat guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
