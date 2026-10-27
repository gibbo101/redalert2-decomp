// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TileVariants.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
int selectTileVariant(TileVariantCache& cache,const TileVariantTables& tables,
    std::int16_t x,std::int16_t y,std::uint8_t sub,int variants,
    const TileVariantImage* image,const std::function<std::uint32_t()>& next){
    if(!cache.initialized){
        if(!next)throw std::invalid_argument("Missing original variant RNG");
        for(auto pair:tables.neighbors)if(pair[0]<-1||pair[0]>1||pair[1]<-1||pair[1]>1)
            throw std::invalid_argument("Unsupported variant neighbor displacement");
        cache.initialized=1;cache.large.fill(-1);
        for(int i=0;i<64;++i){
            int candidate=0;
            for(int attempt=0;attempt<64;++attempt){
                candidate=int(next()&7);bool conflict=false;
                for(auto d:tables.neighbors){
                    int neighbor=i+d[1]*8+d[0];if(neighbor<0)neighbor+=64;if(neighbor>=64)neighbor-=64;
                    if(cache.large[std::size_t(neighbor)]==candidate){conflict=true;break;}
                }
                if(!conflict)break;
            }
            cache.large[std::size_t(i)]=candidate;
        }
    }
    if(sub){
        if(!image)return 0;
        if(image->columns<=0||image->columns>255||image->rows<=0||image->rows>255)
            throw std::invalid_argument("Unsupported resident variant image dimensions");
        const auto word=[](int n){return std::bit_cast<std::int16_t>(std::uint16_t(n));};
        x=word(word(int(x)-int(sub)%image->columns)/image->columns);
        y=word(word(int(y)-int(sub)/image->columns)/image->rows);
    }
    const auto ux=std::uint16_t(x),uy=std::uint16_t(y);
    if(variants<=4)return tables.small[(ux&3u)+4u*(uy&3u)];
    return cache.large[(ux&7u)+8u*(uy&7u)];
}
}
