// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TheaterTileInputs.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {
int add(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
int sub(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
}
TheaterTileInputs prepareTheaterTileInputs(const std::array<int,16>& numbers,
    std::span<const TheaterTileSetInput> sets){
    if(sets.empty()||sets.size()>1024)throw std::invalid_argument("Theater set count outside supplied profile");
    TheaterTileInputs result;result.depthBases.fill(-1);int oldCount=0;bool terminated=false;
    for(std::size_t i=0;i<sets.size();++i){
        const auto& set=sets[i];const int base=int(result.types.size());
        result.setStarts.push_back(base);
        for(std::size_t k=0;k<numbers.size();++k)if(numbers[k]==int(i))result.depthBases[k]=base;
        if(set.count==-1){
            if(i+1!=sets.size())throw std::invalid_argument("Theater data after terminator");
            terminated=true;break;
        }
        if(set.count>65536||result.types.size()+std::size_t(set.count>0?set.count:0)>65536)
            throw std::invalid_argument("Theater tile allocation outside supplied profile");
        if(set.lastCount!=-1&&set.lastCount!=set.count){
            oldCount=add(oldCount,set.lastCount);
            result.shifts.push_back({oldCount,sub(set.count,set.lastCount)});
        }else oldCount=add(oldCount,set.count);
        for(int j=0;j<set.count;++j){
            TheaterTileTypeInput type;
            type.index=int(result.types.size());type.setBase=base;
            type.marble=set.marble;type.nonMarble=set.nonMarble;
            type.toSnow=set.toSnow;type.toTemperate=set.toTemperate;
            type.morphable=set.morphable;type.shadowCaster=set.shadowCaster&&set.shadowTiles!=0;
            type.allowPlace=set.allowPlace;type.requiredForRMG=set.requiredForRMG;
            type.allowBurrowing=set.allowBurrowing;type.allowTiberium=set.allowTiberium;
            result.types.push_back(type);
        }
    }
    if(!terminated)throw std::invalid_argument("Theater terminator missing");
    for(auto& type:result.types){
        const auto remap=[&](int value){
            if(value==65535)return value;
            if(value<0||std::size_t(value)>=result.setStarts.size())
                throw std::invalid_argument("Theater alternate set outside supplied table");
            return add(result.setStarts[std::size_t(value)],sub(type.index,type.setBase));
        };
        type.marble=remap(type.marble);type.nonMarble=remap(type.nonMarble);
    }
    return result;
}
}
