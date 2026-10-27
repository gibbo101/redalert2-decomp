// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/Facing.hpp"
#include <iostream>
#include <sstream>
#include <string>
int main() {
    std::string line;
    while(std::getline(std::cin,line)) {
        std::istringstream in(line);char op;unsigned desired,start,rate;std::int32_t began,duration,tick;int value=0;
        if(!(in>>op>>desired>>start>>began>>duration>>rate>>tick>>value)) return 2;
        ra2::Facing f{std::uint16_t(desired),std::uint16_t(start),began,duration,std::uint16_t(rate)};int changed=0;
        if(op=='D') changed=f.setDesired(std::uint16_t(value),tick);
        else if(op=='S') changed=f.setCurrent(std::uint16_t(value),tick);
        else if(op=='R') f.setRate(value);
        else if(op!='C') return 3;
        std::cout<<f.current(tick)<<' '<<f.rotating(tick)<<' '<<(f.rotating(tick)&&f.difference()>0)<<' '<<(f.rotating(tick)&&f.difference()<0)<<' '
          <<f.desired<<' '<<f.start<<' '<<f.timerStart<<' '<<f.duration<<' '<<f.rate<<' '<<changed<<'\n';
    }
}
