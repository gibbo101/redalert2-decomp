// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/UnitDrawingState.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace ra2;
namespace {
void facing(const Facing& f) {
    std::cout<<f.desired<<' '<<f.start<<' '<<f.timerStart<<' '<<f.duration<<' '<<f.rate;
}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)) {
        std::istringstream in(line);char op;in>>op;
        if(op=='F') {
            int frame,rate,hasRate,padding;in>>frame>>rate>>hasRate>>padding;
            facing(initialUnitFacing(frame,hasRate?std::optional<int>(rate):std::nullopt));
        } else if(op=='D') {
            int frame,padding;in>>frame>>padding;const auto s=initialUnitDrawingFields(frame);
            facing(s.barrel);std::cout<<' ';facing(s.body);std::cout<<' ';facing(s.turret);
            std::cout<<' '<<s.statusTimerStart<<' '<<s.statusTimerDuration<<' '<<s.layerFourValue
                     <<' '<<s.animationFrame<<' '<<int(s.flag204)<<' '<<int(s.flag205)<<' '<<int(s.staging);
        } else if(op=='S') {
            int start,duration,frame,first,second;in>>start>>duration>>frame>>first>>second;
            std::cout<<unitDrawingStatusActive(start,duration,frame)<<' '
                     <<int(std::uint8_t(first))<<' '<<int(std::uint8_t(second));
        } else throw std::invalid_argument("Unknown Unit drawing-state command");
        if(!in)throw std::invalid_argument("Missing Unit drawing-state input");
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing Unit drawing-state input");
        std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
