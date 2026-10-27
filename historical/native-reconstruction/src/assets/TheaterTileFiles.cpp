// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TheaterTileFiles.hpp"
#include <cstdio>
namespace ra2 {
LoadedTheaterTiles prepareLoadedTheaterTiles(const std::array<int,16>& numbers,
    std::span<const TheaterTileSetInput> sets,std::span<const std::string> prefixes,int theater,
    const std::function<std::optional<Data>(const std::string&)>& find){
    if(theater<0||theater>2||prefixes.size()!=sets.size()||!find)
        throw std::invalid_argument("Unsupported loaded theater profile");
    for(const auto& prefix:prefixes){
        if(prefix.empty()||prefix.size()>16)throw std::invalid_argument("Unsupported theater filename prefix");
        for(unsigned char c:prefix)if(!((c>='A'&&c<='Z')||(c>='a'&&c<='z')||(c>='0'&&c<='9')||c=='_'||c=='-'))
            throw std::invalid_argument("Unsupported theater filename prefix");
    }
    LoadedTheaterTiles result;result.inputs=prepareTheaterTileInputs(numbers,sets);
    constexpr std::array<const char*,3> extensions{"TEM","SNO","URB"},marble{"MMT","MMS","MMU"};
    std::size_t primary=0;
    for(std::size_t set=0;set<sets.size()&&sets[set].count!=-1;++set){
        for(int j=0;j<sets[set].count;++j,++primary){
            char number[16];std::snprintf(number,sizeof(number),"%02d",j+1);
            const auto base=prefixes[set]+number;const int first=int(result.allTypes.size());
            result.primary.push_back(first);
            for(unsigned variant=0;;++variant){
                if(variant>26||result.allTypes.size()>=65536)
                    throw std::invalid_argument("Loaded theater variants exceed bounded profile");
                auto stem=base;if(variant)stem+=char(0x60+variant);
                auto source=stem+"."+extensions[std::size_t(theater)];auto data=find(source);
                if(!data&&sets[set].nonMarble!=0){source=stem+"."+marble[std::size_t(theater)];data=find(source);}
                if(variant&&!data)break;
                LoadedTheaterTile tile;tile.type=result.inputs.types.at(primary);
                if(variant){
                    // The original final set-to-tile remap visits primary types only.
                    tile.type.marble=sets[set].marble;tile.type.nonMarble=sets[set].nonMarble;
                    result.allTypes.back().next=int(result.allTypes.size());
                }
                if(data){tile.source=std::move(source);tile.image=prepareTileImage(*data);}
                result.allTypes.push_back(std::move(tile));
                if(!data)break;
            }
            const auto count=int(result.allTypes.size())-first;
            for(int i=0;i<count;++i)result.allTypes[std::size_t(first+i)].variants=count-i;
        }
    }
    return result;
}
}
