// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionEvent.hpp"
#include <iostream>
#include <sstream>
#include <vector>

using namespace ra2;
template<class T>T take(std::istream& in){T value{};if(!(in>>value))throw std::invalid_argument("Missing mission-event input");return value;}
void guards() {
    MissionEventServices missing;
    if(missionEventOccurred(33,0,4,0,0,nullptr,missing)||missionEventOccurred(4,0,4,255,0,nullptr,missing))throw std::logic_error("Skipped House query entered");
    if(!missionEventOccurred(47,-1,0,0,-15,nullptr,missing))throw std::logic_error("Signed scenario time");
    MissionEventTimer timer{-1,0};if(!missionEventOccurred(13,99,0,0,0,&timer,missing))throw std::logic_error("Inactive zero timer");
    for(int kind:{33,4,9,13}) {
        bool refused=false;try{(void)missionEventOccurred(kind,0,kind,0,0,nullptr,missing);}catch(const std::invalid_argument&){refused=true;}
        if(!refused)throw std::logic_error("Entered unsupported/missing service accepted");
    }
    int calls=0;MissionEventServices live{[&](auto value){++calls;if(value!=17)throw std::logic_error("Wrong late lookup");throw std::runtime_error("late service fault");}};
    bool propagated=false;try{(void)missionEventOccurred(33,17,33,0,0,nullptr,live);}catch(const std::runtime_error&){propagated=true;}
    if(!propagated||calls!=1)throw std::logic_error("Late mission fault swallowed");
    std::cout<<"9 mission-event guards PASS\n";
}
int main(int argc,char** argv){try {
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)return 2;
    std::string line;
    while(std::getline(std::cin,line)) {
        std::istringstream input(line);if(take<char>(input)!='E')throw std::invalid_argument("Mission event operation");
        const auto kind=take<std::int32_t>(input),value=take<std::int32_t>(input),pulse=take<std::int32_t>(input);
        const auto suppress=take<int>(input),frame=take<std::int32_t>(input);
        MissionEventTimer timer{take<std::int32_t>(input),take<std::int32_t>(input)};
        const auto count=take<int>(input);if(suppress<0||suppress>255||count<0||count>16)throw std::invalid_argument("Mission event profile");
        std::vector<std::int32_t> houses;for(int i=0;i<count;++i)houses.push_back(take<std::int32_t>(input));
        std::string extra;if(input>>extra)throw std::invalid_argument("Extra mission event input");
        MissionEventServices services{[&](auto country){
            // Supplied registry fixture; original4ED760 executes against matching
            // records. This callback is not the production House initializer.
            std::cout<<"H "<<country<<' ';int found=-1;
            for(std::size_t i=0;i<houses.size();++i)if(houses[i]==country){found=int(i);break;}
            std::cout<<"I "<<found<<' ';
        }};
        const auto result=missionEventOccurred(kind,value,pulse,std::uint8_t(suppress),frame,&timer,services);
        std::cout<<"R "<<result<<'\n';
    }
    return 0;
}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}
