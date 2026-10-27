// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/VoxelRampShadow.hpp"
#include "assets/Archive.hpp"
#include <bit>
#include <cfenv>
#include <iostream>
#include <limits>
#include <sstream>
using namespace ra2;
int main(int argc,char** argv){try{
    if(argc!=2)return 2;
    const auto data=readRasterData(readFile(argv[1]));
    std::string line;while(std::getline(std::cin,line)) {
        std::istringstream in(line);std::uint64_t a=0,d=0;int mode=0;
        if(!(in>>a>>d>>mode))throw std::invalid_argument("Incomplete ramp shadow fixture");
        in>>std::ws;
        if(!in.eof()||mode<0||mode>3)throw std::invalid_argument("Invalid ramp shadow fixture");
        const int rounding=std::array{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO}[std::size_t(mode)];
        if(std::fesetround(rounding))throw std::runtime_error("Cannot set caller FP mode");
        const auto result=voxelRampShadowMatrices(data,std::bit_cast<double>(a),std::bit_cast<double>(d));
        if(std::fegetround()!=rounding)throw std::runtime_error("Ramp shadow changed caller FP mode");
        for(const auto& m:result)for(float v:m)std::cout<<std::bit_cast<std::uint32_t>(v)<<' ';
        std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
