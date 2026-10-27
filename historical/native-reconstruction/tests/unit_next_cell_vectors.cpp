// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/UnitNextCell.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void event(char k,int a=0,int b=0,int c=0){std::cout<<k<<' '<<a<<' '<<b<<' '<<c<<' ';}
int number(std::istream& in,int lo,int hi){long long n=0;in>>n;if(!in||n<lo||n>hi)throw std::invalid_argument("Invalid next-Cell input");return int(n);}
std::uint32_t bits(std::istream& in){unsigned long long n=0;in>>n;if(!in||n>0xffffffff)throw std::invalid_argument("Invalid next-Cell bits");return std::uint32_t(n);}
void guards(){
    UnitAdmissionWorld w;bool refused=false;
    try{ordinaryUnitNextCell(0,{}, {},1,w);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Missing next-Cell ownership accepted");
    std::cout<<"Missing next-Cell ownership refused: PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)throw std::invalid_argument("Unexpected next-Cell argument");
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;if(op!='N')throw std::invalid_argument("Invalid next-Cell command");
        UnitAdmissionWorld w;int slots[2];for(int& n:slots)n=number(in,-1,262143);
        if(slots[0]!=-1&&slots[0]==slots[1])throw std::invalid_argument("Aliased next-Cell slots");
        for(int i=0;i<3;++i){auto& c=w.cells[i];auto& g=w.gates.cells[i];
            g.point.x=std::int16_t(number(in,-32768,32767));g.point.y=std::int16_t(number(in,-32768,32767));
            c.level=std::int8_t(number(in,-128,127));c.flags=bits(in);c.occupation=bits(in);c.elevatedOccupation=bits(in);
            g.head=signed32(bits(in));c.elevatedHead=signed32(bits(in));
        }
        UnitNextCellActor actor;
        actor.location={number(in,INT32_MIN,INT32_MAX),number(in,INT32_MIN,INT32_MAX),number(in,INT32_MIN,INT32_MAX)};
        actor.bridge79=std::uint8_t(number(in,0,255));w.objects[0].crusher=std::uint8_t(number(in,0,255));w.gates.objects[0].kind=1;
        w.gates.fallbackCell=2;std::vector<int> table(262144,-1);
        for(int i=0;i<2;++i)if(slots[i]!=-1)table[std::size_t(slots[i])]=i;
        w.gates.slots=table;w.trace=event;
        const int count=number(in,1,128);
        for(int i=0;i<count;++i){TerrainCellPoint p;
            p.x=std::int16_t(number(in,-32768,32767));p.y=std::int16_t(number(in,-32768,32767));const auto warn=bits(in);
            ordinaryUnitNextCell(0,actor,p,std::uint8_t(warn),w);
            const auto f=w.gates.cells.at(2).point;event('z',f.x,f.y);
        }
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing next-Cell command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
