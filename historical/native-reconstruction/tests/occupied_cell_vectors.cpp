// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OccupiedCellPassability.hpp"
#include <bit>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
template<class... T>void event(const T&... v){((std::cout<<v<<' '),...);}
int byte(std::istream& in){int v=0;in>>v;if(!in||v<0||v>255)throw std::invalid_argument("Invalid occupied Cell byte");return v;}
void guards(){
    MapCellInput c;std::array<float,11> speeds;speeds.fill(1.f);OccupiedCellPassabilityWorld w;w.head=0;w.actors[0].next=0;int value=17;bool refused=false;
    try{updateOccupiedCellPassability(value,c,true,nullptr,speeds,w);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Cyclic occupant list accepted");
    updateOccupiedCellPassability(value,c,false,nullptr,speeds,w);
    if(value!=7)throw std::runtime_error("Permission did not precede list traversal");
    std::cout<<"Occupied Cell list safety and permission short circuit: PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)throw std::invalid_argument("Occupied Cell vectors take stdin");
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;MapPermissionShape shape;MapCellInput c;MapOverlayType overlay;OccupiedCellPassabilityWorld w;
        int x=0,y=0,level=0,present=0,result=0,count=0;
        in>>op>>shape.dimension0>>shape.originX>>shape.originY>>shape.width>>shape.height>>x>>y>>level;
        c.slope=std::uint8_t(byte(in));in>>c.land>>present>>overlay.land;
        overlay.flag1FD=std::uint8_t(byte(in));overlay.wall=std::uint8_t(byte(in));overlay.rock=std::uint8_t(byte(in));overlay.rubble=std::uint8_t(byte(in));
        if(!in||op!='P'||x<-32768||x>32767||y<-32768||y>32767||level<-128||level>127||c.land<0||c.land>10||present<0||present>1||overlay.land<0||overlay.land>10)throw std::invalid_argument("Invalid occupied Cell header");
        c.position={std::int16_t(x),std::int16_t(y)};c.level=std::int8_t(level);
        const int slot=y*512+x;if(slot<0||slot>=262144)throw std::invalid_argument("Occupied Cell map slot outside fixture domain");
        std::array<float,11> speeds;for(auto& v:speeds){std::uint64_t bits=0;in>>bits;if(!in||bits>0xffffffff)throw std::invalid_argument("Invalid occupied Cell speed bits");v=std::bit_cast<float>(std::uint32_t(bits));}
        in>>w.theater>>result>>w.head>>count;if(!in||count<0||count>8||w.head<-1||w.head>=count)throw std::invalid_argument("Invalid occupied Cell list");
        for(int i=0;i<count;++i){auto& a=w.actors[i];in>>a.kind>>a.next;a.type1359=std::uint8_t(byte(in));a.type135a=std::uint8_t(byte(in));a.house142=std::uint8_t(byte(in));in>>a.mission>>a.terrain278>>a.terrain27c;
            if(!in||(a.kind!=1&&a.kind!=6&&a.kind!=15&&a.kind!=36)||a.next<-1||a.next>=count)throw std::invalid_argument("Invalid occupied Cell actor");}
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing occupied Cell fixture");
        std::vector<MapCellInput*> table(262144);table[std::size_t(slot)]=&c;MapCellInput fallback;
        const MapAttributeLookup lookup{table,&fallback};
        const bool permitted=mapCellPermitted(c.position,true,shape,lookup);
        w.kindQuery=[](int id,int kind){event('k',id,kind);};w.store=[](int v){event('W',v);};
        updateOccupiedCellPassability(result,c,permitted,present?&overlay:nullptr,speeds,w);
        event('R',result);std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
