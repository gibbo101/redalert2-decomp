// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/DriveShadowPose.hpp"
#include "render/RampGeometry.hpp"
#include "render/VoxelRampShadow.hpp"
#include "assets/Archive.hpp"
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include "assets/MapCoordinateCell.hpp"
#include <bit>
#include <cfenv>
#include <cmath>
#include <iostream>
#include <sstream>
using namespace ra2;
int main(int argc,char** argv){try {
    if(argc!=5)return 2;
    const auto geometry=readRampGeometryData(readFile(argv[1]),PatchedEngineSha);
    const auto render=readRenderData(readFile(argv[2]),PatchedEngineSha);
    const auto raster=readRasterData(readFile(argv[3]),PatchedEngineSha);
    const auto direction=readDirectionData(readFile(argv[4]),PatchedEngineSha);
    const auto g=stockRampGeometry(render,raster,direction,geometry);
    const auto ramps=voxelRampShadowMatrices(raster,g.axisTilt,g.diagonalTilt);
    std::string line;MapFloorHeightWorld world;MapCellInput cell,fallback;
    std::vector<MapCellInput*> cells(262144);world.cells=cells;world.fallback=&fallback;int oldIndex=-1;
    while(std::getline(std::cin,line)) {
        std::istringstream input(line);char command=0;std::array<std::int64_t,20> v{};
        if(!(input>>command)||command!='D')throw std::invalid_argument("Invalid Drive shadow command");
        for(auto& n:v)if(!(input>>n))throw std::invalid_argument("Incomplete Drive shadow input");
        input>>std::ws;if(!input.eof())throw std::invalid_argument("Trailing Drive shadow input");
        for(int i=0;i<20;++i) {
            const auto n=v[i];bool valid;
            if(i==0||i==4||i==17)valid=n==0||n==1;
            else if(i==5)valid=n>=0&&n<=20;
            else if(i==6||i==7||i==10)valid=n>=0&&n<=65535;
            else if(i==15||i==16)valid=n>=0&&n<=0xffffffffLL;
            else if(i==19)valid=n>=0&&n<=3;
            else valid=n>=-2147483648LL&&n<=2147483647LL;
            if(!valid)throw std::invalid_argument("Drive shadow fixture domain exceeded");
        }
        DriveShadowInputs in;in.position={int(v[1]),int(v[2]),int(v[3])};in.tick=int(v[11]);
        in.slopeStart=int(v[12]);in.slopeRemaining=int(v[13]);in.slopeDuration=int(v[14]);
        in.rockingX=std::bit_cast<float>(std::uint32_t(v[15]));in.rockingY=std::bit_cast<float>(std::uint32_t(v[16]));
        Facing facing;facing.desired=std::uint16_t(v[6]);facing.start=std::uint16_t(v[7]);
        facing.timerStart=int(v[8]);facing.duration=int(v[9]);facing.rate=std::uint16_t(v[10]);
        std::int32_t key=int(v[18]);fallback.position={-30000,29000};
        fallback.slope=cell.slope=std::uint8_t(v[5]);
        if(oldIndex!=-1)cells[std::size_t(oldIndex)]=nullptr;
        const auto p=in.position;const int index=signed32((std::uint32_t(p.y/256)<<9)+std::uint32_t(p.x/256));
        oldIndex=v[4]&&index>=0&&index<262144?index:-1;
        if(oldIndex!=-1)cells[std::size_t(oldIndex)]=&cell;
        std::ostringstream events;
        DriveShadowServices services;
        services.currentRamp=[&](Coord q){events<<"M "<<q.x<<' '<<q.y<<' '<<q.z<<' ';
            const auto ramp=mapCoordinateCell(q,world,262144).slope;events<<"R "<<int(ramp)<<' ';return ramp;};
        services.bodyFacing=[&](){events<<"F ";return facing.current(in.tick);};
        const int rounding=std::array{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO}[std::size_t(v[19])];
        if(std::fesetround(rounding))throw std::runtime_error("Cannot set caller FP mode");
        const auto pose=driveShadowPose(raster,ramps,in,services,v[17]?&key:nullptr,v[0]!=0,
            [&](std::int32_t n){events<<"K "<<std::uint32_t(n)<<' ';});
        if(std::fegetround()!=rounding)throw std::runtime_error("Drive shadow changed caller FP mode");
        for(float n:pose)std::cout<<std::bit_cast<std::uint32_t>(n)<<' ';
        const auto fallbackBits=std::uint32_t(std::uint16_t(fallback.position.x))|
            (std::uint32_t(std::uint16_t(fallback.position.y))<<16);
        std::cout<<std::uint32_t(key)<<' '<<fallbackBits<<' '<<events.str()<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
