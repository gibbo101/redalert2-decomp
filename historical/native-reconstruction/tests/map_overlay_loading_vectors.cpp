// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapOverlayLoading.hpp"
#include <openssl/evp.h>
#include <array>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace ra2;
namespace {
using Words=std::vector<std::uint32_t>;
unsigned packed(MapInputPosition p){return std::uint16_t(p.x)|(unsigned(std::uint16_t(p.y))<<16);}
MapInputPosition position(unsigned v){return {std::bit_cast<std::int16_t>(std::uint16_t(v)),std::bit_cast<std::int16_t>(std::uint16_t(v>>16))};}
std::string digest(const Words& words){
    std::vector<unsigned char> bytes;bytes.reserve(words.size()*4);for(auto v:words)for(int i=0;i<4;++i)bytes.push_back(static_cast<unsigned char>(v>>(i*8)));
    unsigned char result[EVP_MAX_MD_SIZE];unsigned size=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),result,&size,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream out;for(unsigned i=0;i<size;++i)out<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(result[i]);return out.str();
}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;Words events;
        const auto event=[&](std::initializer_list<unsigned> v){events.insert(events.end(),v.begin(),v.end());};
        if(op=='B'){
            unsigned p=0;int w=0,h=0;in>>p>>w>>h;
            std::cout<<overlayMapPositionPermitted(position(p),w,h);
        }else if(op=='M'){
            unsigned seed=0,filter=0,typeLimit=0,dataLimit=0,divisor=0,dataMode=0,typeCount=0;
            int version=0,w=0,h=0,typeResult=0,dataResult=0;
            in>>seed>>version>>w>>h>>filter>>typeResult>>dataResult>>typeLimit>>dataLimit>>divisor>>dataMode>>typeCount;
            if(typeCount>255||typeLimit>262144||dataLimit>262144)throw std::invalid_argument("Overlay reader fixture domain");
            std::vector<OverlayTypeInputs> types(typeCount);
            for(auto& type:types){unsigned crate=0,demand=0;in>>type.image>>type.cellAnim>>crate>>demand;type.crate=std::uint8_t(crate);type.demandLoad=std::uint8_t(demand);}
            unsigned count=0;in>>count;if(count>16384)throw std::invalid_argument("Too many overlay fixture Cells");
            std::vector<OverlayLoadCell> cells(count);std::unordered_map<unsigned,unsigned> binding;
            for(unsigned i=0;i<count;++i){unsigned index=0;in>>index;if(index>=262144||!binding.emplace(index,i).second)throw std::invalid_argument("Invalid overlay Cell binding");cells[i].position=position((index%512)|((index/512)<<16));cells[i].overlay=std::bit_cast<std::int32_t>(seed+i*2654435761u);cells[i].data=std::uint8_t(seed+i*37);}
            std::array<std::unordered_map<unsigned,std::uint8_t>,2> bytes;
            for(auto& stream:bytes){in>>count;if(count>262144)throw std::invalid_argument("Too many overlay stream overrides");for(unsigned i=0;i<count;++i){unsigned index=0,value=0;in>>index>>value;if(index>=262144||value>255||!stream.emplace(index,std::uint8_t(value)).second)throw std::invalid_argument("Invalid overlay byte override");}}
            OverlayLoadCell fallback;fallback.position=position(0x12345678);fallback.overlay=std::bit_cast<std::int32_t>(seed^0x87654321u);fallback.data=std::uint8_t(seed^0xa5);
            const auto id=[&](const OverlayLoadCell& c){return &c==&fallback?0xffffffffu:unsigned(&c-cells.data());};
            const auto target=[&](MapInputPosition p)->OverlayLoadCell&{const auto it=binding.find(unsigned(int(p.y)*512+int(p.x)));return it==binding.end()?fallback:cells[it->second];};
            std::array<unsigned,2> cursors{};unsigned attempts=0;
            OverlayMapLoadServices s;
            s.section=[&](auto pack,unsigned capacity){const unsigned pass=unsigned(pack);const int result=pass?dataResult:typeResult;event({0,pass,capacity,unsigned(result)});return result;};
            s.read=[&](auto pack)->std::optional<std::uint8_t>{const unsigned pass=unsigned(pack),index=cursors[pass]++,limit=pass?dataLimit:typeLimit;const bool has=index<limit;unsigned value=pass?(dataMode?0:std::uint8_t(seed+index*37)):255;const auto it=bytes[pass].find(index);if(it!=bytes[pass].end())value=it->second;event({1,pass,index,unsigned(has),has?value:0});if(has)return std::uint8_t(value);return {};};
            s.cell=[&](auto p)->OverlayLoadCell&{event({6,packed(p)});auto& cell=target(p);if(&cell==&fallback){cell.position=p;event({7,packed(p)});}return cell;};
            s.allocate=[&](){const unsigned attempt=attempts++;const bool ok=!divisor||attempt%divisor;event({8,attempt,unsigned(ok)});return ok;};
            s.construct=[&](unsigned index,auto p,int flag){event({9,index,packed(p),unsigned(flag)});auto& cell=target(p);cell.overlay=int(index);event({10,id(cell),0,index});cell.data=std::uint8_t(index*13+seed);event({10,id(cell),1,cell.data});};
            s.store=[&](auto& cell,auto value){event({10,id(cell),1,value});};
            s.cleanup=[&](){event({11});};
            // Observe actual resident getter and permission requests without
            // substituting supplied results for their native computations.
            // The kernel itself emits these through the optional callbacks.
            s.imageQuery=[&](unsigned index){event({2,index});event({5,types[index].image});};
            s.permissionQuery=[&](auto p,bool result){event({3,packed(p)});event({4,unsigned(result)});};
            loadDecodedMapOverlays(version,w,h,filter!=0,types,s);
            Words state{cursors[0],cursors[1],attempts};
            for(const auto& cell:cells)state.insert(state.end(),{packed(cell.position),unsigned(cell.overlay),cell.data});
            state.insert(state.end(),{packed(fallback.position),unsigned(fallback.overlay),fallback.data});
            std::cout<<digest(state)<<' '<<digest(events);
        }else throw std::invalid_argument("Unknown overlay loading command");
        if(!in)throw std::invalid_argument("Incomplete overlay loading command");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing overlay loading command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
