// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingRedrawRequests.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){
        int x=0,y=0;PixelRect r{};BuildingRedrawRequestServices s;
        auto refuses=[&]{try{requestBuildingRedraw(x,y,r,r,r,0,s);}catch(const std::invalid_argument&){return;}throw std::runtime_error("Missing Building request guard");};
        refuses();s.cellCount=[]{return 801;};refuses();s.cellCount=[]{return 0;};refuses();
        s.dirtyCount=[]{return 129;};refuses();s.dirtyCount=[]{return INT32_MIN;};refuses();
        s.dirtyCount=[]{return 0;};requestBuildingRedraw(x,y,r,r,r,0,s);
        s.cellCount=[]{return 1;};refuses();
        std::cout<<"Building redraw request guards PASS\n";return 0;
    }
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream input(line);std::array<int,39> f;for(auto& v:f)input>>v;if(!input)throw std::invalid_argument("Invalid Building request vector");
        const int mode=f[0];int count=f[1],dirty=f[2],backing=0;PixelPoint origin{f[4],f[5]};
        PixelRect viewport{f[6],f[7],f[8],f[9]},first{f[10],f[11],f[12],f[13]},second{f[14],f[15],f[16],f[17]};
        std::array<int,3> order{f[18],f[19],f[20]};std::array<TerrainCellPoint,3> cells;
        std::array<std::array<PixelRect,3>,2> regions;
        for(int i=0;i<3;++i){cells[i]={std::int16_t(f[21+2*i]),std::int16_t(f[22+2*i])};const int at=27+4*i;regions[0][i]={f[at],f[at+1],f[at+2],f[at+3]};}
        for(int i=0;i<3;++i)regions[1][i]=regions[0][2-i];
        std::ostringstream trace;auto event=[&](int k,int a=0,int b=0,int c=0,int d=0){trace<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};
        bool mutated=false;int phase=1;
        auto mutate=[&](int point){
            if(mutated||!mode||((point==1)!=(mode==1||mode==2||mode==9)))return;
            if((mode==6||mode==8)&&phase!=2)return;
            mutated=true;event(10,mode);
            if(mode==1||mode==3)count=0;
            if(mode==2||mode==4){count=3;order[1]=2;order[2]=1;}
            if(mode==5){origin={17,-23};viewport={9,11,180,140};second={7,8,19,20};}
            if(mode==6){backing=1;dirty=0;}
            if(mode==7)dirty=3;
            if(mode==8)regions[0][0]={51,52,13,14};
            if(mode==9){cells[0]={9,-7};cells[1]={-11,13};}
            if(mode==10)second={21,22,23,24};
        };
        BuildingRedrawRequestServices s;
        s.cellCount=[&]{event(1,count);return count;};
        s.cellAt=[&](int i){const auto id=order.at(i);event(2,i,id);const auto p=cells.at(id);event(3,id,p.x,p.y);return p;};
        s.project6a27a0=[&](Coord p){event(4,p.x,p.y,p.z);mutate(1);return worldPixels(.125,p);};
        s.dirtyCount=[&]{event(5,dirty);phase=2;return dirty;};
        s.dirtyAt=[&](int i){event(6,backing);return regions.at(backing).at(i);};
        s.scan6a9f60=[&](std::uint8_t force,const PixelRect& r,const PixelRect& clip){event(7,&r==&clip,force);event(8,r.x,r.y,r.width,r.height);event(9,clip.x,clip.y,clip.width,clip.height);mutate(2);};
        requestBuildingRedraw(origin.x,origin.y,viewport,first,second,f[3],s);
        std::cout<<trace.str()<<"F "<<count<<' '<<dirty<<' '<<backing<<' '<<origin.x<<' '<<origin.y<<' ';
        for(const auto r:{viewport,first,second})std::cout<<r.x<<' '<<r.y<<' '<<r.width<<' '<<r.height<<' ';
        std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
