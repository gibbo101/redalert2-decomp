// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapGeometry.hpp"
#include <algorithm>
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {
int add(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
int sub(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
std::uint32_t packed(MapInputPosition p){return std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16);}
}
InitialMapGeometry initialMapGeometry(MapGeometryRect requested){
    const auto total=std::int64_t(requested.width)+requested.height;
    if(requested.width<1||requested.height<1||total>256)
        throw std::invalid_argument("Unsupported initial map dimensions");
    InitialMapGeometry result;
    result.full={0,0,requested.width,requested.height};
    result.maximumX=result.maximumY=int(total)-1;
    result.diamondMinimum=requested.width;
    result.diamondMaximum=requested.width+2*requested.height;
    for(int y=0;y<2*total;++y)for(int x=0;x<total+1;++x){
        if(x+y>requested.width&&x-y<requested.width&&y-x<requested.width&&
           x+y<=result.diamondMaximum)result.positions.push_back({std::int16_t(x),std::int16_t(y)});
    }
    return result;
}
void initializeMapGeometryCells(const InitialMapGeometry& geometry,std::span<MapCellInput> storage,
    std::span<MapCellInput*> table,MapCellInput& fallback,MapInputPosition invalid,
    std::uint8_t level,const MapInputStore& store){
    // Recompute the bounded shape before mutation; callers cannot supply a forged
    // position list that aliases the 512*512 table or overlaps fallback/storage.
    const auto checked=initialMapGeometry(geometry.full);
    if(checked.full!=geometry.full||checked.positions!=geometry.positions||
       storage.size()!=geometry.positions.size()||table.size()!=262144||
       std::any_of(table.begin(),table.end(),[](auto* p){return p!=nullptr;})||
       std::any_of(storage.begin(),storage.end(),[&](const auto& c){return &c==&fallback;}))
        throw std::invalid_argument("Initial map requires matching storage and empty pointer table");
    for(std::size_t i=0;i<storage.size();++i){
        auto& cell=storage[i];resetMapCellInput(cell,invalid,store);
        cell.position=geometry.positions[i];if(store)store(&cell,MapInputField::Position,packed(cell.position));
        table[std::size_t(cell.position.y)*512+std::size_t(cell.position.x)]=&cell;
        cell.level=std::bit_cast<std::int8_t>(level);if(store)store(&cell,MapInputField::Level,level);
    }
    resetMapCellInput(fallback,invalid,store);
}
MapGeometryRect mapVisibleRect(MapGeometryRect full,MapGeometryRect requested){
    // Independent assets-layer expression of original rectangle intersection;
    // assets must not acquire a dependency on render/TerrainVisibility.
    auto r=full;
    bool nonempty=requested.width>0&&requested.height>0&&r.width>0&&r.height>0;
    if(nonempty&&r.x<requested.x){r.width=add(r.width,sub(r.x,requested.x));r.x=requested.x;}
    nonempty=nonempty&&r.width>0;
    if(nonempty&&r.y<requested.y){r.height=add(r.height,sub(r.y,requested.y));r.y=requested.y;}
    nonempty=nonempty&&r.height>0;
    if(nonempty&&add(r.x,r.width)>add(requested.x,requested.width))r.width=add(sub(requested.x,r.x),requested.width);
    nonempty=nonempty&&r.width>0;
    if(nonempty&&add(r.y,r.height)>add(requested.y,requested.height))r.height=sub(add(requested.y,requested.height),r.y);
    nonempty=nonempty&&r.height>0;
    if(!nonempty)r={};
    r.x=std::max(r.x,2);r.y=std::max(r.y,2);
    r.width=std::min(r.width,sub(sub(full.width,r.x),2));
    r.height=std::min(r.height,sub(sub(full.height,r.y),6));
    return r;
}
MapPermissionShape mapPermissionShape(MapGeometryRect full,MapGeometryRect visible){
    return {full.width,visible.x,visible.y,visible.width,visible.height};
}
MapGeometryAllocation mapGeometryAllocation(int width,int height){
    MapGeometryAllocation r;const auto side=std::uint32_t(width)+std::uint32_t(height)+1;
    r.capacity=side*side;r.attributeBytes=r.capacity*4;r.secondaryBytes=r.capacity*10;
    const auto area=std::bit_cast<std::int32_t>(std::uint32_t(width)*std::uint32_t(height)*4);
    r.subzoneCapacities={area/4,area/16,area/64};return r;
}
void initializeMapGeometryBuffer(std::span<std::uint8_t> records){
    if(records.size()%4)throw std::invalid_argument("Map attribute buffer requires four-byte records");
    for(std::size_t i=0;i<records.size();i+=4){records[i]=7;records[i+1]=0;}
}
}
