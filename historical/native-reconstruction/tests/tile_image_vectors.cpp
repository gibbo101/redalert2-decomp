// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TileImagePreparation.hpp"
#include <openssl/evp.h>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void word(std::vector<std::uint8_t>& b,std::uint32_t n){for(int i=0;i<4;++i)b.push_back(std::uint8_t(n>>(i*8)));}
std::string digest(const std::vector<std::uint8_t>& b){unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;
    if(!EVP_Digest(b.data(),b.size(),h,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(h[i]);return s.str();}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;unsigned seed=0,old=0;TileColorPacking p;std::array<int,16> mapping{};std::string hex;
        in>>op>>seed>>old>>p.redLeft>>p.redRight>>p.blueLeft>>p.blueRight>>p.greenLeft>>p.greenRight;
        if((op!='L'&&op!='G')||old>1||(op=='G'&&old))throw std::invalid_argument("Unknown tile image profile");
        for(auto& v:mapping)in>>v;in>>hex;
        if(!in||hex.size()%2)throw std::invalid_argument("Incomplete tile image command");in>>std::ws;
        if(!in.eof())throw std::invalid_argument("Trailing tile image command");
        Bytes bytes;for(std::size_t i=0;i<hex.size();i+=2)bytes.push_back(std::uint8_t(std::stoul(hex.substr(i,2),nullptr,16)));
        const auto r=prepareTileImage(Data{std::move(bytes)},p);std::vector<std::uint8_t> payload,consumer;
        for(auto n:{r.typeColumns,r.typeRows,r.image.columns,r.image.rows,r.image.width,r.image.height})word(payload,std::uint32_t(n));
        for(std::size_t i=0;i<r.subTileOffsets.size();++i){
            word(payload,r.subTileOffsets[i]);if(r.colorRamps[i])for(auto n:*r.colorRamps[i]){payload.push_back(std::uint8_t(n));payload.push_back(std::uint8_t(n>>8));}
            word(consumer,std::uint32_t(mapTileLand(&r.image,int(i),mapping)));word(consumer,std::uint32_t(mapTileRamp(&r.image,int(i))));
            int w=0x12345678,h=std::bit_cast<std::int32_t>(0x87654321u);const bool ok=mapTileDimensions(&r.image,int(i),w,h);
            word(consumer,ok);word(consumer,std::uint32_t(w));word(consumer,std::uint32_t(h));
        }
        std::cout<<r.subTileOffsets.size()<<' '<<digest(payload)<<' '<<digest(consumer)<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
