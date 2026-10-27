// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantrySubcell.hpp"
#include "sim/OriginalMath.hpp"
#include "assets/InfantrySubcellData.hpp"
#include "assets/PreparedData.hpp"
#include "render/Lighting.hpp"
#include <cfenv>
#include <cmath>
#include <iostream>
#include <sstream>
using namespace ra2;
template<class... T> void event(T... args) { ((std::cout<<args<<' '),...); }
struct Cell {
    std::uint32_t ground,elevated,flags;
    int groundHouse,elevatedHouse;
    InfantryOccupationCell view() { return {ground,elevated,flags,groundHouse,elevatedHouse}; }
};
int wrappedAdd(int a,int b) { return signed32(std::uint32_t(a)+std::uint32_t(b)); }
void guards() {
    Coord point{192,192,0};Cell cell{0x12340000,0x56780000,0,9,10};int house=3,threshold=0,height=104;
    InfantrySubcellServices s;bool refused=false;
    try { occupyInfantrySubcell(point,house,threshold,s); } catch(const std::invalid_argument&) { refused=true; }
    if(!refused||cell.ground!=0x12340000)throw std::logic_error("Missing numeric service must refuse");
    s.squareRoot=[](double x){return std::sqrt(x);};s.cell=[&](const Coord&){return cell.view();};
    refused=false;try { occupyInfantrySubcell(point,house,threshold,s); } catch(const std::invalid_argument&) { refused=true; }
    if(!refused||cell.ground!=0x12340000)throw std::logic_error("Missing floor must refuse before writes");
    s.floor=[](const Coord&){return 0;};s.houseQuery=[](){throw std::runtime_error("observer fault");};
    const auto rounding=std::fegetround();std::fesetround(FE_UPWARD);
    refused=false;try { occupyInfantrySubcell(point,house,threshold,s); } catch(const std::runtime_error&) { refused=true; }
    if(!refused||cell.ground!=0x12340010||cell.groundHouse!=9||std::fegetround()!=FE_UPWARD)
        throw std::logic_error("House fault must retain byte store and restore host FP mode");
    std::fesetround(rounding);InfantrySubcellData data;OriginalRandomState rng;
    cell.ground=0x40;refused=false;
    try { (void)chooseInfantrySubcell(cell.view(),point,0,0,data,rng,height,s); } catch(const std::invalid_argument&) { refused=true; }
    if(!refused)throw std::logic_error("Entered building policy must refuse");
    const auto forced=chooseInfantrySubcell(cell.view(),point,255,0,data,rng,height,s);
    cell.ground|=0x20;const Coord empty{-1,2,3};
    if(forced!=Coord{192,192,0}||chooseInfantrySubcell(cell.view(),point,0,0,data,rng,height,s,{},empty)!=empty)
        throw std::logic_error("Force and occupied-bit5 must bypass building policy");
    cell={0xabcdef10,0x98765410,0,9,10};s.houseQuery={};
    occupyInfantrySubcell(point,house,threshold,s);releaseInfantrySubcell(point,threshold,s);
    if(cell.ground!=0xabcdef10||cell.elevated!=0x98765400||cell.groundHouse!=3||cell.elevatedHouse!=-1)
        throw std::logic_error("Occupy/release bridge predicate and upper bytes differ");
    std::cout<<"6 infantry subcell guards PASS\n";
}
int main(int argc,char** argv) { try {
    if(argc==2&&std::string(argv[1])=="--guards") { guards();return 0; }
    if(argc!=3)throw std::invalid_argument("Infantry vectors require render and subcell data");
    const auto render=readRenderData(readFile(argv[1]),PatchedEngineSha);
    const auto data=readInfantrySubcellData(readFile(argv[2]),PatchedEngineSha);
    std::string line;std::size_t sequence=0;
    while(std::getline(std::cin,line)) {
        std::istringstream in(line);char command=0;int disabled,first,second,count;std::uint32_t seed;
        if(!(in>>command>>disabled>>first>>second>>seed)||command!='I'||disabled<0||disabled>255||first<0||first>=250||second<0||second>=250)
            throw std::invalid_argument("Infantry RNG fixture domain");
        std::array<Cell,2> cells{};
        for(auto& c:cells)if(!(in>>c.ground>>c.elevated>>c.flags>>c.groundHouse>>c.elevatedHouse))throw std::invalid_argument("Infantry Cell fixture");
        if(!(in>>count)||count<1||count>1024)throw std::invalid_argument("Infantry step count");
        OriginalRandomState rng{std::uint8_t(disabled),first,second,{}};
        for(auto& word:rng.table) { seed=seed*1664525u+1013904223u;word=seed; }
        event('I');for(const auto& p:initialInfantrySubcellOffsets())event(p.x,p.y,p.z);
        const auto originalRounding=std::fegetround();
        const int modes[]={FE_TONEAREST,FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO};const auto mode=modes[sequence++%4];std::fesetround(mode);
        for(int i=0;i<count;++i) {
            int op,force,elevated,mutation,floor,threshold,house,height,cellId;Coord point;
            if(!(in>>op>>point.x>>point.y>>point.z>>force>>elevated>>mutation>>floor>>threshold>>house>>height>>cellId)||
                op<0||op>3||force<0||force>255||elevated<0||elevated>255||mutation<0||mutation>511||cellId<0||cellId>1)
                throw std::invalid_argument("Infantry step domain");
            int lookupId=cellId;InfantrySubcellServices s;
            s.squareRoot=[&](double value){event('Q',int(value));return tableSqrt(render,value);};
            s.cell=[&](const Coord& p){event('N',lookupId,p.x,p.y,p.z);return cells[std::size_t(lookupId)].view();};
            s.floor=[&](const Coord& p){
                event('F',p.x,p.y,p.z);auto& c=cells[std::size_t(cellId)];
                if(mutation&1)point.z=wrappedAdd(point.z,77);
                if(mutation&2){point.x=wrappedAdd(point.x,257);point.y=wrappedAdd(point.y,-513);}
                if(mutation&4)c.flags^=0x100;
                if(mutation&8)threshold=wrappedAdd(threshold,37);
                if(mutation&16)house=wrappedAdd(house,5);
                if(mutation&32)height=wrappedAdd(height,11);
                if(mutation&64){c.ground^=0x1234561c;c.elevated^=0x9876541c;}
                if(mutation&128){c.groundHouse=-17;c.elevatedHouse=23;}
                if(mutation&256)lookupId=1-cellId;
                return floor;
            };
            s.houseQuery=[&](){event('H',house);};
            auto stores=[&](InfantryOccupationCell c,int offset,int width,std::uint32_t value){
                event('C',&c.ground==&cells[0].ground?0:1,offset,width,value);
            };
            auto draws=[&](std::uint32_t value,const OriginalRandomState& state){event('D',value,state.next1,state.next2);};
            if(op==0) { const auto result=infantrySubcell(point,s.squareRoot);event('R',op,result); }
            else if(op==1) { occupyInfantrySubcell(point,house,threshold,s,stores);event('R',op); }
            else if(op==2) { releaseInfantrySubcell(point,threshold,s,stores);event('R',op); }
            else { const auto p=chooseInfantrySubcell(cells[std::size_t(cellId)].view(),point,std::uint8_t(force),std::uint8_t(elevated),data,rng,height,s,draws);event('R',op,p.x,p.y,p.z); }
            if(std::fegetround()!=mode)throw std::logic_error("Infantry routine changed host FP mode");
            event('P',point.x,point.y,point.z,threshold,house,height);
        }
        std::string extra;if(in>>extra)throw std::invalid_argument("Extra infantry fixture input");
        std::fesetround(originalRounding);event('Z');
        for(const auto& c:cells)event(c.ground,c.elevated,c.flags,c.groundHouse,c.elevatedHouse);
        event("rng",int(rng.disabled),rng.next1,rng.next2);for(auto word:rng.table)event(word);std::cout<<'\n';
    }
    return 0;
} catch(const std::exception& e) { std::cerr<<e.what()<<'\n';return 1; } }
