// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/UnitMembership.hpp"
#include "sim/UnitOccupation.hpp"
#include "sim/UnitMark.hpp"
#include "sim/MapVisibility.hpp"
#include "sim/UnitDiscovery.hpp"
#include "assets/MapCoordinateCell.hpp"
#include "assets/MapCellAttributes.hpp"
#include "assets/OccupiedCellPassability.hpp"
#include "render/Redraw.hpp"
#include <openssl/evp.h>
#include <bit>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
template<class... T>void event(const T&... v){((std::cout<<v<<' '),...);}
std::string digest(const MapFloorHeightState& s,MapInputPosition p){
    std::vector<unsigned char> bytes{s.flags};
    const auto word=[&](std::uint64_t v,int n){for(int i=0;i<n;++i)bytes.push_back(std::uint8_t(v>>(i*8)));};
    word(std::bit_cast<std::uint64_t>(s.height),8);word(std::bit_cast<std::uint64_t>(s.scale),8);
    for(const auto& q:s.planes)for(double v:{q.x,q.y,q.offset,q.limit,q.add})word(std::bit_cast<std::uint64_t>(v),8);
    word(std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16),4);
    unsigned char hash[32];unsigned n=0;if(!EVP_Digest(bytes.data(),bytes.size(),hash,&n,EVP_sha256(),nullptr)||n!=32)throw std::runtime_error("Membership state digest");
    std::ostringstream out;for(auto v:hash)out<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(v);return out.str();
}
struct Record {MapCellAttributes attributes;MapCellInput& map=attributes.input;UnitOccupationCell occupation;};
void guards(){
    UnitMembershipWorld w;w.actors[0]={};w.cells[0]={};
    // Null entry does not reach floor, visibility or occupation services.
    w.cellInsert(-1,0);w.cellRemove(-1,0);w.mapInsert(-1,{});
    w.actors[0].typeMapFlag=0;w.mapInsert(0,{-32768,-32768});
    w.actors[0].typeMapFlag=1;bool refused=false;
    try{w.mapInsert(0,{-32768,-32768});}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Unsafe speculative map slot accepted");
    w.actors[0].eligible=0;w.actors[0].next=1;w.actors[1].next=1;w.cells[0].head=1;refused=false;
    try{w.cellRemove(0,0);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Cyclic membership accepted");
    std::cout<<"Unit membership null/type gates, bounded slots and cycle safety: PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)throw std::invalid_argument("Unit membership vectors take stdin");
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;int of=0,uf=0,tf=0,gate=0,v1=0,v2=0,param=0,threshold=0,mutation=0,count=0;
        in>>op;const bool occupied=op=='K',joined=op=='J'||occupied;std::array<std::uint32_t,4> visibilityFlags{};
        std::array<std::array<int,8>,4> prepared{};
        if(occupied)for(auto& row:prepared){
            for(auto& v:row)in>>v;
            const auto [tile,land,sub,extra,present,valid,tmpLand,height]=row;
            if(!in||(tile!=65535&&(tile<0||tile>2))||land<0||land>10||sub<0||sub>255||extra<0||extra>255||present<0||present>1||valid<0||valid>1||tmpLand<0||tmpLand>10)throw std::invalid_argument("Invalid occupied membership Cell inputs");
        }
        UnitDiscoveryWorld discovery;UnitDiscoveryActor discovered;MapVisibilityState visibilityState;
        if(joined){
            for(auto& flags:visibilityFlags){std::uint64_t v=0;in>>v;if(!in||v>0xffffffff)throw std::invalid_argument("Invalid joined visibility flags");flags=std::uint32_t(v);}
            for(int i=0;i<2;++i){int human=0,control=0;in>>human>>control;if(!in||human<0||human>255||control<0||control>255)throw std::invalid_argument("Invalid joined House");discovery.houses[i].human134=std::uint8_t(human);discovery.houses[i].control135=std::uint8_t(control);}
            int h13d=0,b372=0,b373=0,b374=0;in>>h13d>>visibilityState.overrideValue>>discovered.owner>>discovered.mission98>>discovered.queuedA0>>b372>>b373>>b374;
            if(!in||h13d<0||h13d>255||b372<0||b372>255||b373<0||b373>255||b374<0||b374>255||discovered.owner<0||discovered.owner>1)throw std::invalid_argument("Invalid joined discovery actor");
            visibilityState.currentHouse13d=std::uint8_t(h13d);visibilityState.heightDivisor=104;
            discovered.field372=std::uint8_t(b372);discovered.current373=std::uint8_t(b373);discovered.other374=std::uint8_t(b374);discovered.queuedA4=255;
            discovery.loading=1;
        }
        in>>of>>uf>>tf>>gate>>v1>>v2>>param>>threshold>>mutation;
        const auto byte=[](int v){return v>=0&&v<=255;};const auto id=[](int v){return v>=-1&&v<=3;};
        if(!in||(op!='U'&&!joined)||!byte(of)||!byte(uf)||!byte(tf)||mutation<0||mutation>7||(joined&&(mutation||param<0||param>1)))throw std::invalid_argument("Invalid Unit membership header");
        discovery.currentHouse=param;discovery.mode=gate;visibilityState.mode=gate;
        UnitMembershipWorld membership;membership.fallbackCell=3;Record records[4];MapFloorHeightState floor;
        membership.foundation.objectFlag=std::uint8_t(of);membership.foundation.unitFlag=std::uint8_t(uf);
        if(!(of&1))membership.foundation.fallback={-23131,-23131};
        if(!(uf&1))membership.foundation.unit={{{-23131,-23131},{-23131,-23131}}};
        membership.services.visibilityGate=gate;membership.services.notificationArgument=param;
        for(int i=0;i<4;++i){
            int level=0,ramp=0,head=0,alt=0;std::uint64_t flags=0,g=0,e=0;
            in>>level>>ramp>>flags>>g>>e>>head>>alt;
            if(!in||level<-128||level>127||ramp<0||ramp>20||flags>0xffffffff||g>0xffffffff||e>0xffffffff||!id(head)||!id(alt))throw std::invalid_argument("Invalid Unit membership Cell");
            auto& r=records[i];r.map.position={std::int16_t(i<3?51+i:-7),std::int16_t(i<3?72:5)};
            r.map.level=std::int8_t(level);r.map.slope=std::uint8_t(ramp);r.occupation={std::uint32_t(g),std::uint32_t(e),std::uint32_t(flags)};
            if(occupied){const auto& a=prepared[i];r.map.tile=a[0];r.map.land=a[1];r.map.subTile=std::uint8_t(a[2]);r.attributes.extraHeight=std::uint8_t(a[3]);r.attributes.passability=17;r.map.flags=std::uint32_t(flags);r.map.tube=0;}
            membership.cells[i]={{r.map.position.x,r.map.position.y},head,alt};
        }
        for(int i=0;i<4;++i){int next=0;in>>next;if(!in||!id(next))throw std::invalid_argument("Invalid Unit membership link");membership.actors[i].next=next;membership.actors[i].typeMapFlag=std::uint8_t(tf);}
        for(auto& p:floor.planes)for(auto* v:{&p.x,&p.y,&p.offset,&p.limit,&p.add}){std::uint64_t bits=0;in>>bits;*v=std::bit_cast<double>(bits);if(!in||!std::isfinite(*v))throw std::invalid_argument("Invalid Unit membership plane");}
        in>>count;if(!in||count<1||count>128)throw std::invalid_argument("Invalid Unit membership count");
        std::array<MapVisibilityCell,4> visibilityCells;
        membership.trace=[](char k,int a,int b){event(k,a,b);};
        membership.store=[&](int subject,int off,std::uint32_t value){
            if(subject==103&&off==0x24){records[3].map.position={std::bit_cast<std::int16_t>(std::uint16_t(value)),std::bit_cast<std::int16_t>(std::uint16_t(value>>16))};visibilityCells[3].point={records[3].map.position.x,records[3].map.position.y};}
            event('W',subject,off,(subject<100||(subject<104&&(off==0xe4||off==0xe8)))?std::int64_t(signed32(value)):std::int64_t(value));
        };
        std::vector<MapCellInput*> table(262144);
        for(int i=0;i<3;++i){table[72*512+51+i]=&records[i].map;membership.slots[72*512+51+i]=i;}
        std::vector<MapVisibilityCell*> visibilityTable(262144);
        for(int i=0;i<4;++i){const auto p=records[i].map.position;visibilityCells[i]={{p.x,p.y},visibilityFlags[i],records[i].occupation.flags};if(i<3)visibilityTable[72*512+51+i]=&visibilityCells[i];}
        MapVisibilityWorld visibilityWorld{visibilityTable,&visibilityCells[3],{1,1}};
        visibilityWorld.query=[](char k,TerrainCellPoint p){event(k,int(p.x),int(p.y));};
        visibilityWorld.neighbor=[&](const auto& c,int d){event('n',int(&c-visibilityCells.data()),d);};
        visibilityWorld.fallbackStore=[&](TerrainCellPoint p){records[3].map.position={p.x,p.y};membership.cells[3].point=p;event('W',103,0x24,std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16));};
        bool observingMapFloor=false;Coord floorPoint;
        MapFloorHeightWorld world{table,&records[3].map,[&](MapInputPosition p){membership.cells[3].point={p.x,p.y};visibilityCells[3].point={p.x,p.y};event('W',103,0x24,std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16));if(observingMapFloor)event('D',3,floorPoint.x,floorPoint.y);}};
        const auto recordId=[&](const MapCellInput& cell){for(int i=0;i<4;++i)if(&records[i].map==&cell)return i;throw std::runtime_error("Membership Cell identity");};
        const auto directFloor=[&](int i,int x,int y){event('D',i,x,y);const auto& r=records[i];return cellFloorHeight(floor,104,r.map.level,r.map.slope,x,y);};
        membership.services.centerFloor=[&](int i){return directFloor(i,128,128);};
        membership.services.visible=[&](const Coord& p){event('V',0,p.x,p.y,p.z);return v1;};
        membership.services.visibleSecondary=[&](const Coord& p){event('V',1,p.x,p.y,p.z);return v2;};
        if(joined){
            membership.services.visible=[&](const Coord& p){event('V',0,p.x,p.y,p.z);return int(mapPrimaryVisibility(p,visibilityState,visibilityWorld));};
            membership.services.visibleSecondary=[&](const Coord& p){event('V',1,p.x,p.y,p.z);return int(mapSecondaryVisibility(p,visibilityState,visibilityWorld));};
        }
        membership.services.notify=[&](int actor,int arg){
            event('N',actor,arg);
            if(mutation){
                event('Z',mutation);
                if(mutation&1){auto& a=membership.actors.at(0);a.position.x=signed32(std::uint32_t(a.position.x)+512);a.position.z=signed32(std::uint32_t(a.position.z)+37);a.eligible=a.eligible?0:255;}
                if(mutation&6){const int slot=72*512+51;table[slot]=(mutation&4)?nullptr:&records[2].map;if(mutation&4)membership.slots.erase(slot);else membership.slots[slot]=2;}
            }
        };
        membership.services.recalculate=[](int cell,int arg){event('R',cell,arg);};
        if(joined){
            discovery.trace=[](char k,int v){event(k,v);};discovery.store=[](int s,int off,std::uint32_t v){event('w',s,off,v);};
            membership.services.notify=[&](int actor,int arg){event('N',actor,arg);if(actor!=0)throw std::invalid_argument("Unsupported joined discovery actor");discoverUnit(discovered,arg,discovery);};
        }
        std::array<MapTileImageInput,3> images;std::array<MapTileAttributes,3> tiles;std::array<int,16> landMap;std::array<float,11> speeds;speeds.fill(1.f);
        std::array<std::array<std::uint8_t,4>,4> buffer4;std::array<std::array<std::uint8_t,10>,4> buffer10;
        for(auto& b:buffer4)b.fill(0xa5);for(auto& b:buffer10)b.fill(0xa5);
        for(int i=0;i<16;++i)landMap[i]=i;
        if(occupied){
            for(int i=0;i<3;++i){auto& image=images[i];image.columns=image.rows=1;image.width=60;image.height=prepared[i][7];image.subTiles={prepared[i][5]?std::optional{MapSubTileInput{std::uint8_t(prepared[i][6]),records[i].map.slope,false,0,0}}:std::nullopt};tiles[i].image=prepared[i][4]?&image:nullptr;}
            membership.services.recalculate=[&](int cell,int arg){
                event('R',cell,arg);MapAttributeServices s;s.tiles=tiles;s.landMap=landMap;s.fallback=cell==3;s.tubeCount=1;
                s.store=[&](MapAttributeField f,std::uint32_t v){
                    if(f==MapAttributeField::Buffer4)event('b',cell,int(v>>8),int(v&255));
                    else if(f==MapAttributeField::Buffer10)event('c',cell,int(v>>8),int(v&255));
                    else{const int off=f==MapAttributeField::Tile?0x38:f==MapAttributeField::SubTile?0x11a:f==MapAttributeField::Land?0xec:f==MapAttributeField::Slope?0x11c:f==MapAttributeField::Level?0x11b:0x11d;event('a',cell,off,v);}
                };
                MapAttributeLookup lookup{table,&records[3].map,{},[&](MapInputPosition p){membership.cells[3].point={p.x,p.y};visibilityCells[3].point={p.x,p.y};event('W',103,0x24,std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16));}};
                s.setupLAT=[&](const MapCellAttributes&){event('l',cell);MapLATSettings lat;lat.fill(-1);constexpr std::array<MapInputPosition,8> dirs{{{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}}};setupMapLAT(records[cell].map,lat,dirs,lookup,3,[&](int tile){event('a',cell,0x38,std::uint32_t(tile));});return records[cell].map.tile;};
                s.updatePassability=[&](const MapCellAttributes& c){
                    event('p',cell);OccupiedCellPassabilityWorld pw;pw.head=membership.cells.at(cell).head;
                    for(int j=0;j<4;++j)pw.actors[j].next=membership.actors.at(j).next;
                    pw.kindQuery=[](int id,int kind){event('k',id,kind);};pw.store=[&](int value){event('a',cell,0x4c,value);};
                    const bool permitted=mapCellPermitted(c.input.position,true,{80,0,0,80,85},lookup);
                    updateOccupiedCellPassability(records[cell].attributes.passability,c.input,permitted,nullptr,speeds,pw);
                    return records[cell].attributes.passability;
                };
                recalculateMapCellAttributes(records[cell].attributes,arg,buffer4[cell],buffer10[cell],s);
            };
        }
        membership.services.occupation=[&](int,const Coord& p,bool mark){
            event('O',int(mark),p.x,p.y,p.z);UnitOccupationServices s;s.heightThreshold=threshold;
            s.cell=[&](const Coord& point)->UnitOccupationCell&{
                event('Q',point.x,point.y,point.z);return records[recordId(mapCoordinateCell(point,world,262144))].occupation;
            };
            s.floor=[&](const Coord& point){
                event('H',point.x,point.y,point.z);
                const int index=signed32((std::uint32_t(point.y/256)<<9)+std::uint32_t(point.x/256));
                const auto* selected=index>=0&&index<262144?table[std::size_t(index)]:nullptr;
                if(selected)event('D',recordId(*selected),point.x,point.y);
                floorPoint=point;observingMapFloor=!selected;
                struct Reset {bool& value;~Reset(){value=false;}} reset{observingMapFloor};
                return mapFloorHeight(floor,104,point,world);
            };
            const auto store=[&](const UnitOccupationCell& c,int off,std::uint32_t value){for(int i=0;i<4;++i)if(&c==&records[i].occupation){event('W',100+i,off,value);return;}throw std::runtime_error("Occupation identity");};
            if(mark)markUnitOccupation(p,s,store);else unmarkUnitOccupation(p,s,store);
        };
        UnitMarkState marked;RedrawState redraw{2,255,0,true};UnitMarkServices ms;
        ms.imageValue=[](){return 17;};ms.owner=[](){return 0;};ms.layer=[](){return 2;};
        ms.coordinates=[&](){return terrainCellPoint(membership.actors.at(0).position);};
        ms.redrawMap=[&](){requestMapRedraw(redraw,0,[&](auto e){if(e.kind!='t')throw std::runtime_error("Unexpected redraw effect");event('W',201,0,e.value);});};
        ms.insert=[&](auto p){membership.mapInsert(0,p);};ms.remove=[&](auto p){membership.mapRemove(0,p);};
        for(int i=0;i<count;++i){
            int root=0,mode=0,actor=0,cell=0,alternate=0,eligible=0;Coord p;
            in>>root>>mode>>actor>>cell>>p.x>>p.y>>p.z>>alternate>>eligible;
            if(!in||root<0||root>4||(actor!=-1&&actor!=0)||cell<0||cell>3||!byte(alternate)||!byte(eligible)||(root==4&&actor!=0))throw std::invalid_argument("Invalid Unit membership row");
            auto& a=membership.actors.at(0);a.position=p;a.alternate=std::uint8_t(alternate);a.eligible=std::uint8_t(eligible);int accepted=-1;
            if(root==0)membership.cellInsert(actor,cell);else if(root==1)membership.cellRemove(actor,cell);
            else if(root==2)membership.mapInsert(actor,terrainCellPoint(p));else if(root==3)membership.mapRemove(actor,terrainCellPoint(p));
            else accepted=markUnitFoot(marked,mode,ms,[&](int off,std::uint8_t value){event('W',0,off,int(value));});
            event('S',accepted,int(marked.onMap),int(marked.needsRedraw),int(redraw.tactical));
            for(int j=0;j<4;++j){const auto& c=membership.cells.at(j);event(c.head,c.alternateHead,records[j].occupation.ground,records[j].occupation.elevated);}
            for(int j=0;j<4;++j)event(membership.actors.at(j).next);event(digest(floor,records[3].map.position));
            if(joined){event('X',unsigned(discovered.current373),unsigned(discovered.other374),discovered.queuedA0,unsigned(discovered.queuedA4));for(int j=0;j<2;++j){const auto& h=discovery.houses.at(j);event(unsigned(h.discovered13c),unsigned(h.field5668),unsigned(h.field5669));}}
            if(occupied)for(int j=0;j<4;++j){const auto& a=records[j].attributes;event('Y',a.input.tile,a.input.land,unsigned(a.input.subTile),int(a.input.level),unsigned(a.input.slope),unsigned(a.extraHeight),a.passability);for(auto v:buffer4[j])event(unsigned(v));for(auto v:buffer10[j])event(unsigned(v));}
        }
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing Unit membership fixture");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
