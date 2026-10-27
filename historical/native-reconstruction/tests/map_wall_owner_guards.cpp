// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapWallOwner.hpp"
#include <cfenv>
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace ra2;
int main(){try{
    int owner=17;std::array<WallOwnerBuilding,1> building{{{1,1,1}}};
    for(auto [overlay,wall]:{std::pair{-1,1},std::pair{0,0}}) {
        assignMapWallOwner(overlay,std::uint8_t(wall),owner,building,{});
        if(owner!=17)throw std::runtime_error("Early leaf changed owner");
    }
    bool refused=false;try{assignMapWallOwner(0,1,owner,building,{});}catch(const std::invalid_argument&){refused=true;}
    if(!refused||owner!=17)throw std::runtime_error("Missing callbacks accepted or mutated state");
    refused=false;try{assignMapWallOwner(-2,0,owner,{},{});}catch(const std::invalid_argument&){refused=true;}
    if(!refused||owner!=17)throw std::runtime_error("Invalid overlay binding accepted or mutated state");
    bool observed=false;WallOwnerServices s;s.store=[&](int n){observed=n==-1&&owner==-1;};
    assignMapWallOwner(0,1,owner,{},s);if(!observed)throw std::runtime_error("Owner store observer saw stale state");
    const auto mode=std::fegetround();std::fesetround(FE_UPWARD);
    refused=false;try{wallOwnerCellDistance({},{},[](double)->double{throw std::runtime_error("probe");});}
    catch(const std::runtime_error&){refused=true;}
    if(!refused||std::fegetround()!=FE_UPWARD)throw std::runtime_error("Distance failed to restore FP state on exception");
    if(wallOwnerCellDistance({},{},[](double){return 2147483648.75;})!=std::numeric_limits<int>::min() || std::fegetround()!=FE_UPWARD)
        throw std::runtime_error("Distance qword truncation/wrap or FP restore changed");
    std::fesetround(mode);
    std::cout<<"Wall owner service/store and numeric boundaries: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
