// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionAudioAction.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
namespace {
void require(bool ok){if(!ok)throw std::invalid_argument("Mission audio fixture outside domain");}
template<class T>T take(std::istream& in){T value{};require(bool(in>>value));return value;}
void run(std::istream& in){
    const auto kind=take<int>(in);const auto value=take<std::int32_t>(in);std::string extra;require(!(in>>extra));
    MissionAudioServices services;
    services.playSound=[](std::int32_t index,std::int32_t panning,std::uint32_t volume,const void* controller){
        std::cout<<"S "<<index<<' '<<panning<<' '<<volume<<' '<<(controller?1:0)<<' ';
    };
    services.playSpeech=[](std::int32_t index,std::int32_t mode,std::int32_t parameter){
        std::cout<<"V "<<index<<' '<<mode<<' '<<parameter<<' ';
    };
    const auto result=kind==19?executeMissionSoundAction(value,services):kind==21?executeMissionSpeechAction(value,services):false;
    require(kind==19||kind==21);std::cout<<"R "<<result<<'\n';
}
void guards(){
    MissionAudioServices none;bool sound=false,speech=false;
    try{(void)executeMissionSoundAction(0,none);}catch(const std::invalid_argument&){sound=true;}
    try{(void)executeMissionSpeechAction(0,none);}catch(const std::invalid_argument&){speech=true;}
    require(sound&&speech);
    std::int32_t calls=0;MissionAudioServices services;
    services.playSound=[&](auto index,auto panning,auto volume,const void* controller){require(index==292&&panning==0x2000&&volume==0x3f800000u&&!controller);++calls;};
    services.playSpeech=[&](auto index,auto mode,auto parameter){require(index==247&&mode==2&&parameter==-1);++calls;};
    require(executeMissionSoundAction(292,services)&&executeMissionSpeechAction(247,services)&&calls==2);
    std::cout<<"mission audio action guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
