// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/UnitOccupation.hpp"
#include "assets/MapCoordinateCell.hpp"
#include <openssl/evp.h>
#include <bit>
#include <cfenv>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
int add(int a,int b){return signed32(std::uint32_t(a)+std::uint32_t(b));}
std::string digest(const MapFloorHeightState& s,MapInputPosition p) {
    std::vector<unsigned char> bytes{s.flags};
    const auto word=[&](std::uint64_t n,int size){for(int i=0;i<size;++i)bytes.push_back(std::uint8_t(n>>(i*8)));};
    const auto scalar=[&](double n){word(std::bit_cast<std::uint64_t>(n),8);};
    scalar(s.height);scalar(s.scale);
    for(const auto& v:s.planes)for(double n:{v.x,v.y,v.offset,v.limit,v.add})scalar(n);
    word(std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16),4);
    unsigned char hash[32];unsigned size=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),hash,&size,EVP_sha256(),nullptr)||size!=32)throw std::runtime_error("Occupation height digest failed");
    std::ostringstream out;for(auto n:hash)out<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(n);return out.str();
}
void guards() {
    UnitOccupationCell a{0xaabbcc00,0x12345600,0},b{};Coord p{0,0,104};
    UnitOccupationServices s;int queries=0,stores=0;
    s.cell=[&](const Coord&)->UnitOccupationCell&{if(queries++!=0)throw std::runtime_error("Cell query order");return a;};
    s.floor=[&](const Coord&){if(queries++!=1)throw std::runtime_error("Floor query order");return 0;};
    const auto store=[&](const UnitOccupationCell& c,int offset,std::uint32_t value){
        if(&c!=&a||(offset!=0x124&&offset!=0x128)||(offset==0x124?c.ground:c.elevated)!=value)throw std::runtime_error("Occupation write observer");++stores;};
    markUnitOccupation(p,s,store);queries=0;markUnitOccupation(p,s,store);
    if(a.ground!=0xaabbcc20||a.elevated!=0x12345600||stores!=2)throw std::runtime_error("Full dword/repeated mark");
    queries=0;unmarkUnitOccupation(p,s,store);
    if(a.ground!=0xaabbcc20||a.elevated!=0x12345600)throw std::runtime_error("Mark/unmark bridge asymmetry");
    // A named service can change the input after the saved Cell lookup. This
    // guards the public service boundary without wiring it into live movement.
    queries=0;s.floor=[&](const Coord&){++queries;a.flags=0x100;p.z=1;s.heightThreshold=1;return 0;};
    markUnitOccupation(p,s,store);
    if(a.elevated!=0x12345620||b.ground)throw std::runtime_error("Delayed flags/Z/threshold reads");
    UnitOccupationServices missing;bool refused=false;
    try{markUnitOccupation(p,missing);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Missing services accepted");
    std::cout<<"Unit occupation service order, delayed reads, dword/repeated writes and bridge asymmetry: PASS\n";
}
struct Record {MapCellInput map;UnitOccupationCell occupation;};
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)throw std::invalid_argument("Occupation vectors take commands on stdin");
    std::string line;while(std::getline(std::cin,line)) {
        std::istringstream in(line);char op=0;int mode=0,count=0;Record records[3];MapFloorHeightState state;
        std::uint64_t n=0;in>>op>>mode;
        if(op!='U'||mode<0||mode>3)throw std::invalid_argument("Invalid occupation header");
        for(auto& r:records)for(auto* v:{&r.occupation.ground,&r.occupation.elevated}){in>>n;if(!in||n>0xffffffff)throw std::invalid_argument("Invalid occupation word");*v=std::uint32_t(n);}
        for(auto& plane:state.planes)for(auto* v:{&plane.x,&plane.y,&plane.offset,&plane.limit,&plane.add}){in>>n;*v=std::bit_cast<double>(n);}
        in>>count;if(!in||count<1||count>64)throw std::invalid_argument("Invalid occupation count");
        const int old=std::fegetround();std::fesetround(std::array{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO}[std::size_t(mode)]);
        struct Restore {int old;~Restore(){std::fesetround(old);}} restore{old};const int incoming=std::fegetround();
        records[2].map.position={-7,5};std::vector<MapCellInput*> table(262144);std::vector<std::size_t> previous;
        MapFloorHeightWorld world{table,&records[2].map,[&](MapInputPosition p){std::cout<<"P "<<(std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16))<<' ';}};
        for(int i=0;i<count;++i) {
            int operation=0,resident=0,level=0,ramp=0,ol=0,orr=0,fl=0,fr=0,threshold=0,mutation=0,current=0;Coord p;std::uint64_t flags=0,of=0,ff=0;
            in>>operation>>p.x>>p.y>>p.z>>resident>>level>>ramp>>ol>>orr>>fl>>fr>>flags>>of>>ff>>threshold>>mutation>>current;
            if(!in||operation<0||operation>1||resident<0||resident>3||level<-128||level>127||ol<-128||ol>127||fl<-128||fl>127||ramp<0||ramp>20||orr<0||orr>20||fr<0||fr>20||flags>0xffffffff||of>0xffffffff||ff>0xffffffff||mutation<0||mutation>3)throw std::invalid_argument("Invalid occupation row");
            for(auto slot:previous)table[slot]=nullptr;previous.clear();
            for(int id=0;id<2;++id) {
                const int x=id?add(p.x,256):p.x;const int index=add(signed32(std::uint32_t(p.y/256)<<9),x/256);
                if((resident&(1<<id))&&index>=0&&index<262144){table[std::size_t(index)]=&records[id].map;previous.push_back(std::size_t(index));}
                records[id].map.position={std::bit_cast<std::int16_t>(std::uint16_t(x/256)),std::bit_cast<std::int16_t>(std::uint16_t(p.y/256))};
            }
            for(int id=0;id<3;++id){auto& r=records[id];r.map.level=std::int8_t(id==0?level:id==1?ol:fl);r.map.slope=std::uint8_t(id==0?ramp:id==1?orr:fr);r.occupation.flags=std::uint32_t(id==0?flags:id==1?of:ff);}
            UnitOccupationServices s;s.heightThreshold=threshold;Record* saved=nullptr;
            s.cell=[&](const Coord& point)->UnitOccupationCell& {
                std::cout<<"C "<<point.x<<' '<<point.y<<' '<<point.z<<' ';
                auto& cell=mapCoordinateCell(point,world,262144);
                for(auto& r:records)if(&r.map==&cell){saved=&r;return r.occupation;}
                throw std::runtime_error("Lost occupation Cell identity");
            };
            s.floor=[&](const Coord& point) {
                std::cout<<"F "<<point.x<<' '<<point.y<<' '<<point.z<<' ';
                if(mutation&1){p.x=add(p.x,256);p.z=add(p.z,17);}
                const int value=mapFloorHeight(state,current,point,world);std::cout<<"H "<<value<<' ';
                if(mutation&2){saved->occupation.flags^=0x100;s.heightThreshold=add(s.heightThreshold,0x40000000);p.z=signed32(std::uint32_t(p.z)^0x80000000);}
                return value;
            };
            const auto store=[&](const UnitOccupationCell& c,int offset,std::uint32_t value){for(int id=0;id<3;++id)if(&records[id].occupation==&c){std::cout<<"W "<<id<<' '<<offset<<' '<<value<<' ';return;}throw std::runtime_error("Occupation store lost identity");};
            if(operation)markUnitOccupation(p,s,store);else unmarkUnitOccupation(p,s,store);
            if(std::fegetround()!=incoming)throw std::runtime_error("Occupation changed incoming FP mode");
            std::cout<<"S ";for(const auto& r:records)std::cout<<r.occupation.ground<<' '<<r.occupation.elevated<<' '<<r.occupation.flags<<' ';
            std::cout<<p.x<<' '<<p.y<<' '<<p.z<<' '<<s.heightThreshold<<' '<<digest(state,records[2].map.position)<<' ';
        }
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing occupation fixture");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
