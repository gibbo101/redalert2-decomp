// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapWallUpdate.hpp"
#include "render/Redraw.hpp"
#include "sim/OriginalRandomRange.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
using Words=std::vector<std::uint32_t>;
std::string digest(const Words& values){
    std::vector<unsigned char> bytes;for(auto n:values)for(unsigned i=0;i<4;++i)bytes.push_back(static_cast<unsigned char>(n>>(8*i)));
    unsigned char hash[EVP_MAX_MD_SIZE];unsigned length=0;if(!EVP_Digest(bytes.data(),bytes.size(),hash,&length,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream out;for(unsigned i=0;i<length;++i)out<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(hash[i]);return out.str();
}
int signedWord(unsigned n){return std::bit_cast<std::int32_t>(n);}
MapInputPosition point(unsigned p){return {std::bit_cast<std::int16_t>(std::uint16_t(p)),std::bit_cast<std::int16_t>(std::uint16_t(p>>16))};}
unsigned packed(MapInputPosition p){return std::uint16_t(p.x)|(unsigned(std::uint16_t(p.y))<<16);}
void append(Words& values,MapWallBounds r){values.insert(values.end(),{unsigned(r.x),unsigned(r.y),unsigned(r.width),unsigned(r.height)});}
void occupants(std::istream& in,std::vector<MapWallOccupant>& out,unsigned n){
    if(n>8)throw std::invalid_argument("Wall occupant count");
    out.resize(n);for(auto& o:out)in>>o.kind>>o.health>>o.type;
}
void damageGuards(){
    unsigned count=0;const auto check=[&](bool ok){if(!ok)throw std::runtime_error("Wall damage guard failed");++count;};
    MapWallCell c;MapWallUpdateServices s;int force=0,levels=4,strength=200,queries=0;std::uint8_t wall=0;
    MapWallDamageServices d{s,force,[&](int)->MapWallDamageType{++queries;return {wall,levels,strength};},{}};
    check(!queries);check(!damageMapWall(c,-1,d)&&!queries);
    c.overlay=203;c.owner=77;check(!damageMapWall(c,-1,d)&&queries==1);
    wall=1;bool refused=false;
    try{damageMapWall(c,1,d);}catch(const std::invalid_argument&){refused=true;}
    check(refused&&c.data==0&&c.owner==77);
    s.bounds=[](const auto&,unsigned){return MapWallBounds{};};
    s.unite=[](auto a,auto b){const auto r=unionDirtyBounds({a.x,a.y,a.width,a.height},{b.x,b.y,b.width,b.height});return MapWallBounds{r.x,r.y,r.width,r.height};};
    s.dirty=[](auto){};
    check(!damageMapWall(c,200,d)&&c.data==16&&c.overlay==203);
    refused=false;try{damageMapWall(c,-1,d);}catch(const std::invalid_argument&){refused=true;}
    check(refused&&c.data==32&&c.overlay==203&&c.owner==77);
    levels=2;s.recalculate=[](auto&,int){throw std::runtime_error("late-recalculation-fault");};
    s.zone=[](unsigned,auto){};s.notify=[](auto){};s.expired=[](auto&){};
    bool fault=false;
    try{damageMapWall(c,-1,d);}catch(const std::runtime_error& e){fault=std::string(e.what())=="late-recalculation-fault";}
    check(fault&&c.overlay==-1&&c.owner==-1&&c.data==0);
    std::cout<<count<<" wall damage live-field/entered-service/late-fault checks PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--damage-guards"){damageGuards();return 0;}
    if(argc!=1)throw std::invalid_argument("Unexpected wall fixture argument");
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;Words events;
        const bool damageMode=op=='D';int damage=0,levels=0,strength=0,forceDamage=0;
        unsigned rngSeed=0,rngDisabled=0;OriginalRandomState random;
        if(damageMode){
            in>>damage>>levels>>strength>>forceDamage>>rngDisabled>>rngSeed>>op;
            if(!in||op!='U'||rngDisabled>255)throw std::invalid_argument("Wall damage prefix");
            random.disabled=std::uint8_t(rngDisabled);random.next1=249;random.next2=103;
            for(unsigned i=0;i<250;++i)random.table[i]=(rngSeed+i*0x9e3779b9u)^(0x12345678u>>(i%13));
        }
        const auto event=[&](std::initializer_list<unsigned> v){events.insert(events.end(),v.begin(),v.end());};
        WallConnectionInputs connections;std::vector<MapWallCell> cells;std::vector<std::vector<MapWallOccupant>> nodes;
        const auto id=[&](const MapWallCell& c){const auto i=&c-cells.data();if(i<0||unsigned(i)>=cells.size())throw std::runtime_error("Wall Cell identity");return unsigned(i);};
        connections.connectionQuery=[&](const auto& c,int target,int facing){event({6,id(c),unsigned(target),unsigned(facing)});};
        connections.occupantQuery=[&](const auto& c,unsigned index){event({7,id(c),index,unsigned(c.occupants[index].kind)});};
        if(op=='C'){
            int target=0,facing=0,overlay=0;unsigned n=0;in>>target>>facing>>overlay;
            for(auto& t:connections.gates)in>>t;in>>n;cells.resize(1);nodes.resize(1);cells[0].overlay=overlay;occupants(in,nodes[0],n);cells[0].occupants=nodes[0];
            if(!in)throw std::invalid_argument("Connection input");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing connection input");
            const auto result=connectsToMapOverlay(cells[0],target,facing,connections);std::cout<<unsigned(result)<<' '<<digest(events)<<'\n';continue;
        }
        if(op!='U')throw std::invalid_argument("Unknown wall command");
        unsigned seed=0,skip=0,p=0,recalc=0,alias=0,allWalls=0,n=0;MapWallUpdateServices s;
        in>>seed>>skip>>p>>s.screenX>>s.screenY>>recalc>>alias>>allWalls;
        for(auto& t:connections.gates)in>>t;s.connections=connections;
        for(auto& visit:s.visits)in>>visit;
        for(auto& direction:s.directions){unsigned q=0;in>>q;direction=point(q);}in>>n;
        if(!in||skip>255||recalc>3||alias>2||allWalls>1||!n||n>16||s.visits!=std::array<int,5>{0,2,4,6,-1})throw std::invalid_argument("Wall update input");
        cells.resize(n);nodes.resize(n);const auto base=point(p);
        for(unsigned i=0;i<n;++i){
            auto& c=cells[i];unsigned data=0,neighbors=0,count=0;
            in>>c.overlay>>data>>neighbors>>c.passability>>c.owner>>count;
            if(c.overlay< -1||c.overlay>=256||data>255||neighbors>255)throw std::invalid_argument("Wall Cell input");
            c.data=std::uint8_t(data);c.neighbors=std::uint8_t(neighbors);occupants(in,nodes[i],count);c.occupants=nodes[i];
            c.position=i?point((unsigned(std::uint16_t(base.x))+i-4)&65535u|(((unsigned(std::uint16_t(base.y))+(i*3)%5-2)&65535u)<<16)):base;
        }
        if(!in)throw std::invalid_argument("Wall Cell input truncated");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing wall input");
        std::array<std::uint8_t,256> flags;for(unsigned i=0;i<flags.size();++i)flags[i]=std::uint8_t(allWalls||(i+seed)%5!=0);s.wallTypes=flags;
        s.cell=[&](MapInputPosition q)->MapWallCell&{
            const unsigned x=std::uint16_t(q.x),y=std::uint16_t(q.y);
            const unsigned index=alias==1?0:(alias==2?(x^y)%std::min(n,2u):(x+3*y+seed)%n);
            event({5,packed(q),index});return cells[index];
        };
        s.bounds=[&](const auto& c,unsigned kind){
            const auto index=id(c);MapWallBounds r;
            switch(seed&3){
                case 0:break;
                case 1:r={int(index)*37-100,int(kind)*41-77,17+int(index),13+int(kind)};break;
                case 2:r={signedWord(seed^(index*0x1234567u)),signedWord(seed+kind*0x7654321u),signedWord(seed^(kind*0x40000000u)),signedWord(seed+index*0x11111111u)};break;
                default:r={signedWord(seed-index*53),signedWord(seed+kind*7),kind==0?-1:23,kind==2?0:17};break;
            }
            event({1,index,kind});append(events,r);return r;
        };
        s.unite=[&](MapWallBounds a,MapWallBounds b){
            event({2});append(events,a);append(events,b);const auto r=unionDirtyBounds({a.x,a.y,a.width,a.height},{b.x,b.y,b.width,b.height});return MapWallBounds{r.x,r.y,r.width,r.height};
        };
        s.dirty=[&](auto r){event({3});append(events,r);};s.notify=[&](auto q){event({4,packed(q)});};
        s.expired=[&](auto& c){event({9,id(c)});};s.zone=[&](unsigned kind,auto q){event({10,kind,packed(q)});};
        s.store=[&](auto& c,unsigned offset,unsigned size,unsigned value){event({12,id(c),offset,size,value});};
        s.recalculate=[&](auto& c,int level){
            event({8,id(c),unsigned(level)});unsigned value=unsigned(c.passability);
            if(recalc==1)value^=(unsigned(c.overlay)+1)&7;else if(recalc==2)value^=1;else if(recalc==3)value=c.overlay!=-1;
            c.passability=signedWord(value);s.store(c,0x4c,4,value);
        };
        bool removed=false;
        if(damageMode){
            const MapWallDamageServices d{s,forceDamage,[&](int index){
                if(index<0||index>=256)throw std::invalid_argument("Wall damage overlay index");
                return MapWallDamageType{flags[std::size_t(index)],levels,strength};
            },[&](int first,int second){
                event({13,unsigned(first),unsigned(second)});
                return rangedOriginalRandom(random,first,second,[&](auto raw,const auto& state){
                    event({14,raw,unsigned(state.next1),unsigned(state.next2)});
                });
            }};
            removed=damageMapWall(cells[0],damage,d);
        }else updateMapWall(cells[0],std::uint8_t(skip),s);
        Words output;for(const auto& c:cells)output.insert(output.end(),{packed(c.position),unsigned(c.overlay),unsigned(c.passability),unsigned(c.owner),c.data,c.neighbors});
        if(damageMode){
            Words state{random.disabled,unsigned(random.next1),unsigned(random.next2)};
            state.insert(state.end(),random.table.begin(),random.table.end());
            std::cout<<unsigned(removed)<<' '<<digest(state)<<' ';
        }
        std::cout<<digest(output)<<' '<<digest(events)<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
