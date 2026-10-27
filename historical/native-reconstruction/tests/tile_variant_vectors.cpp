// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TileVariants.hpp"
#include <openssl/evp.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
using namespace ra2;
namespace {
std::string digest(const std::vector<std::uint32_t>& values){std::vector<std::uint8_t> bytes;
    for(auto n:values)for(int i=0;i<4;++i)bytes.push_back(std::uint8_t(n>>(i*8)));
    unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;if(!EVP_Digest(bytes.data(),bytes.size(),h,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(h[i]);return s.str();}
std::string randomDigest(const OriginalRandomState& r){std::vector<std::uint32_t> v{r.disabled,unsigned(r.next1),unsigned(r.next2)};v.insert(v.end(),r.table.begin(),r.table.end());return digest(v);}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;in>>op;OriginalRandomState random;unsigned disabled=0,initialized=0,count=0;TileVariantCache cache;
        if(op=='V')in>>initialized;if(op!='V'&&op!='R')throw std::invalid_argument("Unknown variant command");
        in>>disabled>>random.next1>>random.next2;
        if(disabled>255||initialized>255)throw std::invalid_argument("Bad state byte");random.disabled=std::uint8_t(disabled);cache.initialized=std::uint8_t(initialized);
        if(op=='R'){in>>count;if(!count||count>1024)throw std::invalid_argument("Bad RNG sequence count");}
        for(auto& n:random.table)in>>n;
        if(op=='R'){
            if(!in)throw std::invalid_argument("Incomplete RNG command");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing RNG command");
            std::vector<std::uint32_t> values;for(unsigned i=0;i<count;++i)values.push_back(nextOriginalRandom(random));
            std::cout<<count<<' '<<digest(values)<<' '<<randomDigest(random)<<' '<<count<<'\n';
        }else{
            for(auto& n:cache.large)in>>n;TileVariantTables tables;for(auto& n:tables.small)in>>n;for(auto& pair:tables.neighbors)in>>pair[0]>>pair[1];
            int x=0,y=0,sub=0,variants=0,present=0;TileVariantImage image;in>>x>>y>>sub>>variants>>image.columns>>image.rows>>present;
            if(!in||x<-32768||x>32767||y<-32768||y>32767||sub<0||sub>255||(present!=0&&present!=1))throw std::invalid_argument("Bad variant command");
            in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing variant command");
            unsigned calls=0;const auto result=selectTileVariant(cache,tables,std::int16_t(x),std::int16_t(y),std::uint8_t(sub),variants,present?&image:nullptr,[&]{++calls;return nextOriginalRandom(random);});
            std::vector<std::uint32_t> values{cache.initialized};for(auto n:cache.large)values.push_back(std::uint32_t(n));
            std::cout<<std::uint32_t(result)<<' '<<digest(values)<<' '<<randomDigest(random)<<' '<<calls<<'\n';
        }
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
