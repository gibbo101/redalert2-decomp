// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/RampGeometry.hpp"
#include "render/VoxelRampShadow.hpp"
#include "assets/Archive.hpp"
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include <bit>
#include <cfenv>
#include <iostream>
#include <sstream>
using namespace ra2;
int main(int argc,char** argv){try {
    if(argc!=5)return 2;
    const auto geometry=readRampGeometryData(readFile(argv[1]),PatchedEngineSha);
    const auto render=readRenderData(readFile(argv[2]),PatchedEngineSha);
    const auto raster=readRasterData(readFile(argv[3]),PatchedEngineSha);
    const auto direction=readDirectionData(readFile(argv[4]),PatchedEngineSha);
    std::string line;
    while(std::getline(std::cin,line)) {
        std::istringstream in(line);char kind=0;std::uint64_t value=0;int mode=0;
        if(!(in>>kind)||(kind!='S'&&kind!='T'&&kind!='A'))throw std::invalid_argument("Invalid geometry fixture kind");
        if(kind!='S'&&!(in>>value))throw std::invalid_argument("Incomplete geometry fixture number");
        if(!(in>>mode)||mode<0||mode>3)throw std::invalid_argument("Invalid geometry fixture FP mode");
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing geometry fixture input");
        const int rounding=std::array{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO}[std::size_t(mode)];
        if(std::fesetround(rounding))throw std::runtime_error("Cannot set caller FP mode");
        auto number=[](double v){std::cout<<std::bit_cast<std::uint64_t>(v)<<' ';};
        if(kind=='S') {
            const auto g=stockRampGeometry(render,raster,direction,geometry);
            // Distinct original shadow and Cell chains both produce these values.
            for(int copy=0;copy<2;++copy) {
                for(double v:{g.diagonal,g.diagonalPer60,g.inverseDiagonalPer60,g.angle45,g.angle60,g.angle90})number(v);
                std::cout<<g.levelHeight<<' ';number(g.diagonalTilt);number(g.axisTilt);std::cout<<g.quadrupleHeight<<' ';
            }
            for(const auto& m:voxelRampShadowMatrices(raster,g.axisTilt,g.diagonalTilt))
                for(float v:m)std::cout<<std::bit_cast<std::uint32_t>(v)<<' ';
        } else {
            const auto v=std::bit_cast<double>(value);
            number(kind=='T'?tableTangent(geometry,v):tableArctangent(direction,v));
        }
        if(std::fegetround()!=rounding)throw std::runtime_error("Geometry changed caller FP mode");
        std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
