// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MovementGate.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <vector>
using namespace ra2;
namespace {
template<class... T>void event(const T&... v){((std::cout<<v<<' '),...);}
int byte(std::istream& in){int v=0;in>>v;if(!in||v<0||v>255)throw std::invalid_argument("Invalid gate byte");return v;}
bool object(int v){return v>=-1&&v<5;}
bool word(int v){return v>=-32768&&v<=32767;}
void guards(){
    MovementGateWorld w;bool refused=false;
    try{checkMovementGates(-1,{},w);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Missing gate map accepted");
    std::vector<int> slots(262144,-1);w.slots=slots;w.fallbackCell=0;w.cells[0].head=0;
    w.objects[0].next=0;refused=false;
    try{checkMovementGates(0,{},w);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Cyclic gate list accepted");
    refused=false;try{makeMovementGateTraversable(0,w);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Nonbuilding helper accepted");
    std::cout<<"Gate map/list/kind safety boundaries: PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)throw std::invalid_argument("Unexpected gate arguments");
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;
        if(op!='W')throw std::invalid_argument("Invalid gate command");
        MovementGateWorld w;std::array<int,2> indices{};int x=0,y=0;
        in>>w.tick>>w.setPadding>>w.commencePadding>>indices[0]>>indices[1];
        for(int i=0;i<3;++i){in>>w.cells[i].head;if(!in||!object(w.cells[i].head))throw std::invalid_argument("Invalid gate head");}
        in>>x>>y;if(!in||!word(x)||!word(y))throw std::invalid_argument("Invalid fallback words");
        w.cells[2].point={std::int16_t(x),std::int16_t(y)};w.fallbackCell=2;
        std::vector<int> slots(262144,-1);w.slots=slots;
        for(int i=0;i<2;++i){const int slot=indices[i];
            if(slot<-1||slot>=262144||(slot!=-1&&slots[std::size_t(slot)]!=-1))throw std::invalid_argument("Invalid gate slot");
            if(slot!=-1)slots[std::size_t(slot)]=i;
        }
        for(int i=0;i<3;++i){std::uint64_t mask=0;in>>w.houses[i].index>>mask;
            if(!in||mask>0xffffffff)throw std::invalid_argument("Invalid gate House");w.houses[i].allies=std::uint32_t(mask);}
        for(int i=0;i<5;++i){auto& a=w.objects[i];in>>a.kind>>a.next>>a.owner;
            a.gate=std::uint8_t(byte(in));in>>a.mission.mission98>>a.mission.queuedA0;
            a.mission.queuedA4=std::uint8_t(byte(in));a.animation18=std::uint8_t(byte(in));a.animation19=std::uint8_t(byte(in));
            in>>a.statusA8>>a.lastAC>>a.timerStart>>a.timerPadding>>a.timerRemaining;
            if(!in||(a.kind!=1&&a.kind!=6&&a.kind!=36)||!object(a.next)||a.owner<-1||a.owner>2||
               (a.kind==6&&a.gate&&a.owner==-1))throw std::invalid_argument("Invalid gate object");
        }
        // Stable acyclic resident lists are the original comparison domain.
        for(int i=0;i<5;++i){int p=i;std::size_t n=0;while(p!=-1){if(++n>5)throw std::invalid_argument("Cyclic gate fixture");p=w.objects.at(p).next;}}
        w.trace=[](char k,int id){event(k,id);};
        w.kindResult=[](int id,int kind){event('V',id,kind);};
        w.store=[](int id,int off,int n,std::uint32_t v){event('W',id,off,n,v);};
        w.fallbackStore=[](TerrainCellPoint p){event('F',int(p.x),int(p.y));};
        int count=0;in>>count;if(!in||count<1||count>128)throw std::invalid_argument("Invalid gate sequence size");
        for(int i=0;i<count;++i){char action=0;int a=0,b=0,c=0;in>>action>>a>>b>>c;
            if(!in)throw std::invalid_argument("Missing gate action");
            int result=0;
            if(action=='C'){
                if(!object(a)||!word(b)||!word(c))throw std::invalid_argument("Invalid gate check");
                result=checkMovementGates(a,{std::int16_t(b),std::int16_t(c)},w);
            }else if(action=='A'){
                if(a<0||a>2||!object(b)||c)throw std::invalid_argument("Invalid alliance check");
                result=movementGateAllied(a,b,w);
            }else if(action=='G'||action=='I'){
                if(a<0||a>=5||w.objects.at(a).kind!=6||b||c)throw std::invalid_argument("Invalid Building helper");
                result=action=='G'?makeMovementGateTraversable(a,w):movementGateTraversable(a,w);
            }else if(action=='T'){
                if(a<0||a>=5||b<0||b>255||c<0||c>255)throw std::invalid_argument("Invalid supplied animation transition");
                auto& o=w.objects.at(a);o.animation18=std::uint8_t(b);o.animation19=std::uint8_t(c);
                event('U',a,b,c);result=-1;
            }else throw std::invalid_argument("Unknown gate action");
            event('R',result,int(w.cells[2].point.x),int(w.cells[2].point.y));
            for(int j=0;j<5;++j){const auto& o=w.objects.at(j);event(o.mission.mission98,o.mission.queuedA0,
                unsigned(o.mission.queuedA4),o.statusA8,o.lastAC,o.timerStart,o.timerPadding,o.timerRemaining,
                unsigned(o.animation18),unsigned(o.animation19));}
        }
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing gate input");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
