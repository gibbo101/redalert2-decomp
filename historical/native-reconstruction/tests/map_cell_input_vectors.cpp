// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapCellInputs.hpp"
#include "assets/Archive.hpp"
#include "assets/Formats.hpp"
#include <openssl/evp.h>
#include <array>
#include <bit>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace ra2;
namespace {
void word(std::vector<std::uint8_t>& b,std::uint32_t n){for(int i=0;i<4;++i)b.push_back(std::uint8_t(n>>(i*8)));}
std::string digest(const std::vector<std::uint8_t>& b){unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;
    if(!EVP_Digest(b.data(),b.size(),h,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(h[i]);return s.str();}
MapInputPosition position(std::uint32_t p){return {std::bit_cast<std::int16_t>(std::uint16_t(p)),std::bit_cast<std::int16_t>(std::uint16_t(p>>16))};}
MapCellInput initial(unsigned seed,unsigned i){MapCellInput c;const auto v=(i+1u)*2654435761u+seed*2246822519u;
    c.position=position(v);c.tile=std::bit_cast<std::int32_t>(v^0x12345678u);c.land=std::bit_cast<std::int32_t>(v);
    c.flags=v;c.tube=std::bit_cast<std::int16_t>(std::uint16_t(v));c.subTile=std::uint8_t(v>>8);
    c.ice=std::uint8_t(v>>16);c.level=std::bit_cast<std::int8_t>(std::uint8_t(v>>24));c.slope=std::uint8_t(v);return c;}
void state(std::vector<std::uint8_t>& b,const MapCellInput& c){for(auto n:std::array<std::uint32_t,9>{
    std::uint16_t(c.position.x)|(std::uint32_t(std::uint16_t(c.position.y))<<16),std::uint32_t(c.tile),
    std::uint16_t(c.tube),std::uint32_t(c.land),c.ice,c.subTile,std::uint8_t(c.level),c.slope,c.flags})word(b,n);}
}
int main(int argc,char** argv){try{
    if(argc==3&&std::string(argv[1])=="--decode"){
        Ini ini(readFile(argv[2]).text());std::map<int,std::string> ordered;
        for(const auto& [k,v]:ini.section("IsoMapPack5"))ordered.emplace(std::stoi(k),v);
        std::string text;for(const auto& [k,v]:ordered)text+=v;const auto bytes=unpackMap(decodeBase64(text));
        std::cout.write(reinterpret_cast<const char*>(bytes.data()),std::streamsize(bytes.size()));return 0;
    }
    if(argc!=1)throw std::invalid_argument("Usage: map-cell-input-vectors [--decode OWNED_MAP]");
    std::string line;while(std::getline(std::cin,line)){
    std::istringstream input(line);char op=0;input>>op;
    if(op=='R'||op=='C'){
        unsigned seed=0,term=0,invalid=0;input>>seed>>term>>invalid;
        std::vector<MapCellInput> cells;MapCellInput fallback=initial(seed,99999);
        std::vector<std::uint8_t> events,states;
        auto stores=[&](const MapCellInput* c,MapInputField f,std::uint32_t v){
            word(events,c==&fallback?0xffffffffu:unsigned(c-cells.data()));word(events,unsigned(f));word(events,v);
        };
        std::size_t consumed=0;
        if(op=='C')resetMapCellInput(fallback,position(invalid),stores);
        else{
            unsigned n=0;input>>n;if(n>128)throw std::invalid_argument("Too many shifts");std::vector<MapTileShift> shifts(n);
            for(auto& s:shifts)input>>s.first>>s.delta;
            input>>n;if(n>16384)throw std::invalid_argument("Too many cells");std::vector<unsigned> indices(n);
            for(auto& i:indices){input>>i;if(i>=262144)throw std::invalid_argument("Invalid pointer index");}
            cells.reserve(n);for(unsigned i=0;i<n;++i)cells.push_back(initial(seed,i));
            std::vector<MapCellInput*> table(262144);for(unsigned i=0;i<n;++i)table[indices[i]]=&cells[i];
            std::string hex;input>>hex;if(hex=="-")hex.clear();if(hex.size()%2)throw std::invalid_argument("Odd stream hex");
            std::vector<std::uint8_t> bytes;for(std::size_t i=0;i<hex.size();i+=2)bytes.push_back(std::uint8_t(std::stoul(hex.substr(i,2),nullptr,16)));
            consumed=loadIsoMapCellInputs(bytes,table,fallback,position(term),position(invalid),shifts,stores);
        }
        for(const auto& c:cells)state(states,c);state(states,fallback);
        std::cout<<consumed<<' '<<digest(states)<<' '<<digest(events);
    }else if(op=='T'){
        MapTileImageInput image;int present=0,sub=0,w=0,h=0;input>>present>>image.columns>>image.rows>>image.width>>image.height>>sub>>w>>h;
        const auto count=std::int64_t(image.columns)*image.rows;if(count<1||count>128)throw std::invalid_argument("Bad fixture tile count");
        for(int i=0;i<count;++i){int has=0,land=0,ramp=0,extra=0;MapSubTileInput s;input>>has>>land>>ramp>>extra>>s.y>>s.extraY;
            s.land=std::uint8_t(land);s.ramp=std::uint8_t(ramp);s.extra=extra!=0;image.subTiles.push_back(has?std::optional{s}:std::nullopt);}
        std::array<int,16> mapping{};for(auto& n:mapping)input>>n;const auto* p=present?&image:nullptr;
        const int land=mapTileLand(p,sub,mapping),ramp=mapTileRamp(p,sub);const bool ok=mapTileDimensions(p,sub,w,h);
        std::cout<<land<<' '<<ramp<<' '<<int(ok)<<' '<<w<<' '<<h;
    }else throw std::invalid_argument("Unknown map input command");
    if(!input)throw std::invalid_argument("Incomplete map input command");input>>std::ws;if(!input.eof())throw std::invalid_argument("Trailing map input command");std::cout<<'\n';
}}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
