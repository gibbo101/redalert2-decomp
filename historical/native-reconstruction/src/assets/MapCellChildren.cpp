// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapCellChildren.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {
int wrapped(std::uint32_t x){return std::bit_cast<std::int32_t>(x);}
int plus(int a,int b){return wrapped(std::uint32_t(a)+std::uint32_t(b));}
int minus(int a,int b){return wrapped(std::uint32_t(a)-std::uint32_t(b));}
int twice(int n){return wrapped(std::uint32_t(n)*2u);}
MapInputPosition offset(MapInputPosition p,MapInputPosition d){
    return {std::bit_cast<std::int16_t>(std::uint16_t(int(p.x)+d.x)),
            std::bit_cast<std::int16_t>(std::uint16_t(int(p.y)+d.y))};
}
}
MapCellInput& mapAttributeCell(MapInputPosition p,const MapAttributeLookup& world){
    if(world.cells.size()!=262144||!world.fallback)throw std::invalid_argument("Map lookup requires pointer table and fallback");
    if(world.query)world.query(p);
    const int index=int(p.y)*512+int(p.x);
    if(index>=0&&index<262144)if(auto* cell=world.cells[std::size_t(index)])return *cell;
    world.fallback->position=p;if(world.fallbackStore)world.fallbackStore(p);return *world.fallback;
}
bool setupMapLAT(MapCellInput& cell,const MapLATSettings& base,std::span<const MapInputPosition,8> directions,
    const MapAttributeLookup& world,int registryCount,const std::function<void(int)>& store){
    constexpr std::array<int,11> lengths{1,41,15,15,15,15,13,20,13,11,19};
    std::array<int,11> high{};for(unsigned i=0;i<high.size();++i)high[i]=base[i]==-1?-1:plus(base[i],lengths[i]);
    const int initial=cell.tile;
    const auto range=[&](int tile,unsigned i){return tile>=base[i]&&tile<=high[i];};
    const auto write=[&](int tile){cell.tile=tile;if(store)store(tile);};
    const auto neighbors=[&](unsigned group,unsigned singleton,auto compatible){
        if(cell.tile!=base[singleton]&&!range(cell.tile,group))return;
        unsigned mask=0;
        for(unsigned i=0;i<4;++i){const auto& n=mapAttributeCell(offset(cell.position,directions[i*2]),world);if(!compatible(n.tile))mask|=1u<<i;}
        write(mask?plus(base[group],int(mask)):base[singleton]);
    };
    neighbors(2,11,[&](int t){return t==base[11]||range(t,2);});
    if(base[3]!=-1)neighbors(3,12,[&](int t){return t==base[12]||range(t,3);});
    if(base[4]!=-1)neighbors(4,13,[&](int t){return t==base[13]||range(t,4)||range(t,1)||range(t,0);});
    if(base[5]!=-1)neighbors(5,14,[&](int t){return t==base[14]||range(t,5)||range(t,6)||range(t,8)||range(t,7);});
    if(range(cell.tile,10)||range(cell.tile,9)){
        unsigned mask=0;
        constexpr std::array<std::array<unsigned,2>,4> query{{{6,2},{0,4},{2,6},{4,0}}};
        if(cell.slope>=1&&cell.slope<=4){
            for(unsigned i=0;i<2;++i)if(!mapAttributeCell(offset(cell.position,directions[query[cell.slope-1][i]]),world).slope)mask|=1u<<i;
            if(mask)write(plus(base[9],int(mask)+int(cell.slope-1)*3-1));
        }
        if(!mask)write(plus(base[10],int(cell.slope)-1));
    }
    if(cell.tile!=initial&&(cell.tile<0||cell.tile>=registryCount))throw std::invalid_argument("LAT output outside supplied resident registry");
    // Loaded/null images with lazy-load byte zero have no mutations in the
    // original final GetImage/ensure-image check. Loading remains outside scope.
    return cell.tile!=initial;
}
bool mapCellPermitted(MapInputPosition p,bool elevation,const MapPermissionShape& shape,const MapAttributeLookup& world){
    int level=0;const int sum=int(p.x)+int(p.y);
    if(elevation){
        const auto& cell=mapAttributeCell(p,world);level=cell.level;
        if(cell.slope&&sum<plus(plus(plus(shape.dimension0,twice(shape.originY)),4),level))++level;
    }
    if(sum<=plus(plus(shape.dimension0,twice(shape.originY)),level))return false;
    if(sum>plus(plus(plus(shape.dimension0,twice(plus(shape.originY,shape.height))),2),level))return false;
    if(int(p.x)-int(p.y)>=minus(twice(plus(shape.originX,shape.width)),shape.dimension0))return false;
    if(int(p.y)-int(p.x)>=minus(shape.dimension0,twice(shape.originX)))return false;
    return true;
}
int emptyCellPassability(const MapCellInput& cell,bool permitted,std::span<const float> speeds){
    if(!permitted)return 7;
    if(cell.land==2)return 4;
    if(cell.land==6)return 3;
    if(cell.land<0||std::size_t(cell.land)>=speeds.size())throw std::invalid_argument("Cell land outside supplied speed table");
    return double(speeds[std::size_t(cell.land)])>0.01?0:6;
}
}
