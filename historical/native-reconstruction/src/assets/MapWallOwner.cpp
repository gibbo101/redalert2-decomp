// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapWallOwner.hpp"
#include "sim/OriginalMath.hpp"
#include <bit>
#include <limits>
#include <stdexcept>

namespace ra2 {
namespace {
int signedWord(std::uint32_t value) { return std::bit_cast<std::int32_t>(value); }
}
void assignMapWallOwner(int overlay,std::uint8_t wall,int& owner,
    std::span<const WallOwnerBuilding> buildings,const WallOwnerServices& services) {
    if(overlay< -1)throw std::invalid_argument("Invalid wall owner overlay binding");
    if(overlay==-1 || !wall)return;
    if(!buildings.empty() && (!services.distance || !services.owner))
        throw std::invalid_argument("Wall owner selection requires candidate services");
    int best=std::numeric_limits<int>::max(),selected=-1;
    for(std::size_t i=0;i<buildings.size();++i) {
        const auto& building=buildings[i];
        if(!building.active || !building.onMap || !building.wallOwner)continue;
        const int distance=services.distance(i);
        if(distance<best) {
            best=distance;
            selected=services.owner(i);
        }
    }
    owner=selected;
    if(services.store)services.store(owner);
}
Coord wallOwnerCellCoordinates(MapInputPosition point,int height) {
    return {int(point.x)*256+128,int(point.y)*256+128,height};
}
Coord wallOwnerBuildingCoordinates(Coord point,int width,int height) {
    point.x=signedWord(std::uint32_t(point.x)+(std::uint32_t(width)<<7)-128u);
    point.y=signedWord(std::uint32_t(point.y)+(std::uint32_t(height)<<7)-128u);
    return point;
}
int wallOwnerCellDistance(Coord building,Coord cell,
    const std::function<double(double)>& squareRoot) {
    if(!squareRoot)throw std::invalid_argument("Wall distance requires original table sqrt");
    OriginalRounding rounding;
    const double x=signedWord(std::uint32_t(building.x)-std::uint32_t(cell.x));
    const double y=signedWord(std::uint32_t(building.y)-std::uint32_t(cell.y));
    const double z=signedWord(std::uint32_t(building.z)-std::uint32_t(cell.z));
    // Original x87 has 53-bit precision here. FTOL stores a signed qword and
    // returns its low dword; distances beyond INT_MAX therefore become negative.
    const double result=squareRoot((x*x+y*y)+z*z);
    if(!(result>=0 && result<=4294967295.0))
        throw std::invalid_argument("Wall distance sqrt outside original coordinate domain");
    return signedWord(std::uint32_t(std::int64_t(result)));
}
}
