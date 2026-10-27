// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/UnitMark.hpp"
#include "render/Redraw.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
template<class... T>void event(const T&... values){((std::cout<<values<<' '),...);}
void guards() {
    UnitMarkState a{0,0,255,255};UnitMarkServices empty;
    if(!markUnitFoot(a,2,empty)||a.onMap||a.needsRedraw||!a.limbo)throw std::runtime_error("Foot mode2 did not bypass parent");
    if(markUnitObject(a,2,empty)||markUnitTechno(a,2,empty))throw std::runtime_error("Object/Techno accepted limbo");
    a={1,1,0,0};if(markUnitObject(a,2,empty))throw std::runtime_error("Dirty Object accepted redraw mode");
    a={0,0,0,0};std::string order;UnitMarkServices s;
    s.imageValue=[&]{order+='i';return 7;};s.owner=[&]{order+='o';return -1;};
    s.coordinates=[&]{order+='c';return TerrainCellPoint{-1,2};};
    s.redrawMap=[&]{if(a.onMap!=1||a.needsRedraw!=1)throw std::runtime_error("Redraw precedes marked/dirty stores");order+='r';};
    s.layer=[&]{order+='l';return 2;};s.insert=[&](auto p){if(p!=TerrainCellPoint{-1,2})throw std::runtime_error("Membership point");order+='a';};
    s.remove=[&](auto){order+='x';};
    if(!markUnitFoot(a,1,s)||order!="iocrlca")throw std::runtime_error("Foot insert query/service order");
    order.clear();if(markUnitFoot(a,1,s)||order!="ioc")throw std::runtime_error("Rejected mode omitted unused getters");
    order.clear();if(!markUnitFoot(a,0,s)||order!="ioclcx")throw std::runtime_error("Foot remove query/service order");
    a={0,0,0,0};bool refused=false;try{markUnitObject(a,1,empty);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Reached missing service accepted");
    std::cout<<"Unit Mark Foot bypass, Object gates, ordered getters/stores/membership and service guards: PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)throw std::invalid_argument("Unit Mark vectors take commands on stdin");
    std::string line;while(std::getline(std::cin,line)) {
        std::istringstream in(line);char op=0;int root=0,present=0,image=0,owner=0,tp=0,mm=0,counter=0,tactical=0,marked=0,redraw=0,count=0;
        in>>op>>root>>present>>image>>owner>>tp>>mm>>counter>>tactical>>marked>>redraw>>count;
        const auto byte=[](int n){return n>=0&&n<=255;};
        if(!in||op!='M'||root<0||root>2||present<0||present>1||tp<0||tp>1||!byte(counter)||!byte(tactical)||!byte(marked)||!byte(redraw)||count<1||count>128)throw std::invalid_argument("Invalid Unit Mark header");
        UnitMarkState a{std::uint8_t(marked),std::uint8_t(redraw),0,0};
        RedrawState map{mm,std::uint8_t(counter),std::uint8_t(tactical),bool(tp)};Coord position;
        UnitMarkServices s;
        s.imageValue=[&]{const int value=present?image:0;event('I',value);return value;};
        s.owner=[&]{event('O',owner);return owner;};
        s.coordinates=[&]{const auto p=terrainCellPoint(position);event('C',p.x,p.y);return p;};
        s.layer=[&]{event('L',2);return 2;};
        s.redrawMap=[&]{event('R',0);requestMapRedraw(map,0,[](auto e){if(e.kind!='t')throw std::runtime_error("Unexpected redraw write");event('T',e.value);});};
        s.specialEvent=[&](int value){event('E',value);};
        s.insert=[](auto p){event('A',p.x,p.y);};s.remove=[](auto p){event('X',p.x,p.y);};
        const UnitMarkStore store=[](int off,std::uint8_t value){event('W',off,unsigned(value));};
        const UnitMarkRedraw entered=[](){event('D');};
        for(int i=0;i<count;++i) {
            int mode=0,limbo=0,special=0,reset=0;in>>mode>>position.x>>position.y>>position.z>>limbo>>special>>reset;
            if(!in||!byte(limbo)||!byte(special)||reset<-1||reset>255)throw std::invalid_argument("Invalid Unit Mark row");
            a.limbo=std::uint8_t(limbo);a.special=std::uint8_t(special);if(reset>=0)a.needsRedraw=std::uint8_t(reset);
            const bool accepted=root==0?markUnitObject(a,mode,s,store,entered):root==1?markUnitTechno(a,mode,s,store,entered):markUnitFoot(a,mode,s,store,entered);
            event('S',int(accepted),unsigned(a.onMap),unsigned(a.needsRedraw),unsigned(a.limbo),unsigned(a.special),unsigned(map.tactical),map.mapMode,unsigned(map.counter));
        }
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing Unit Mark fixture");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
