// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitTypeVisibility.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace ra2;
int main(){try{
    std::string op;
    while(std::cin>>op){
        if(op=="H"){
            int mode,a,b,current;std::cin>>mode>>a>>b>>current;
            std::cout<<unitOwnerTypeVisible(mode,std::uint8_t(a),std::uint8_t(b),current!=0)<<'\n';
        }else if(op=="A"||op=="S"){
            int arg=0,present,same,owner,current;unsigned mask;
            if(op=="S")std::cin>>arg;
            std::cin>>present>>same>>owner>>current>>mask;
            auto allied=[&]{return unitOwnerAlliedToCurrent(present!=0,same!=0,owner,current,mask);};
            if(op=="A")std::cout<<allied()<<'\n';
            else std::cout<<selectUnitDisplayType(1,2,arg,allied)<<" a "<<arg<<" l\n";
        }else if(op=="C"){
            int frame;std::cin>>frame;const auto a=initialUnitDrawingFields(frame);
            std::cout<<unsigned(a.bridge)<<' '<<unsigned(a.disguise.disguised)<<' '<<a.disguise.creationFrame
                     <<' '<<a.disguise.timerStart<<' '<<a.disguise.timerDuration<<' '<<a.timerStart<<' '<<a.timerDuration
                     <<' '<<unsigned(a.addFourteen)<<' '<<a.alternateType<<' '<<int(a.screenOffset)<<' '<<a.flagHouse<<'\n';
        }else if(op=="V"){
            int frame,disguised,mode,a,b,same,owner,current,sensors;unsigned mask;UnitDisguiseState state;
            std::cin>>frame>>state.timerStart>>state.timerDuration>>disguised>>state.creationFrame
                    >>mode>>a>>b>>same>>owner>>current>>mask>>sensors;
            state.disguised=std::uint8_t(disguised);std::string events=" V";
            const bool result=originalUnitTypeVisible(state,frame,[&]{events+=" o";
                return unitOwnerTypeVisible(mode,std::uint8_t(a),std::uint8_t(b),same!=0);},
                [&]()->std::optional<std::int16_t>{events+=" B A 18304 29312 416 A 18304 29312 416";return std::int16_t(sensors);},
                [&](char k){events+=' ';events+=k;});
            std::cout<<result<<events<<'\n';
        }else throw std::invalid_argument("Unknown Unit type visibility vector");
        if(!std::cin)throw std::invalid_argument("Incomplete Unit type visibility vector");
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
