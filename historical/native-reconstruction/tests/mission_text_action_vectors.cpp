// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionTextAction.hpp"
#include <bit>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
using namespace ra2;
namespace {
void require(bool ok){if(!ok)throw std::invalid_argument("Mission text fixture outside domain");}
template<class T>T take(std::istream& in){T value{};require(bool(in>>value));return value;}
std::string decode(const std::string& value){
    if(value=="-")return {};
    require(value.size()%2==0);std::string out;out.reserve(value.size()/2);
    for(std::size_t i=0;i<value.size();i+=2){unsigned n=0;std::istringstream part(value.substr(i,2));part>>std::hex>>n;require(bool(part)&&n<=255);out.push_back(char(n));}
    return out;
}
std::string encode(std::string_view value){
    if(value.empty())return "-";
    std::ostringstream out;out<<std::hex<<std::setfill('0');for(unsigned char c:value)out<<std::setw(2)<<unsigned(c);return out.str();
}
void run(std::istream& in){
    require(take<char>(in)=='T');const int alternate=take<int>(in);require(alternate>=0&&alternate<=255);
    const auto delayBits=take<std::uint64_t>(in);const auto color1=take<std::int32_t>(in),color2=take<std::int32_t>(in);
    const auto key=decode(take<std::string>(in)),localized=decode(take<std::string>(in));std::string extra;require(!(in>>extra));
    MissionTextServices services;
    services.color=[&](int selector){const auto color=selector==1?color1:color2;std::cout<<"C "<<selector<<' '<<color<<' ';return color;};
    services.localize=[&](std::string_view value){require(value==key);std::cout<<"L "<<encode(value)<<" 0 8350672 1582 ";return std::string_view(localized);};
    services.display=[&](const MissionTextRequest& request){std::cout<<"M "<<request.leading0<<' '<<request.leading1<<' '<<encode(request.text)<<' '
        <<request.color<<' '<<request.style<<' '<<request.duration<<' '<<request.trailing<<' ';};
    const auto result=executeMissionTextAction(key,std::uint8_t(alternate),std::bit_cast<double>(delayBits),services);
    std::cout<<"R "<<result<<'\n';
}
void guards(){
    int colors=0;MissionTextServices services;services.color=[&](int n){++colors;return n;};
    require(executeMissionTextAction({},0,std::numeric_limits<double>::quiet_NaN(),services)&&colors==1);
    bool refused=false;try{(void)executeMissionTextAction("x",0,1.,services);}catch(const std::invalid_argument&){refused=true;}require(refused);
    services.localize=[](auto text){return text;};services.display=[](auto&){};
    require(executeMissionTextAction("x",255,.6,services)&&colors==3&&missionTextDuration(.6)==539);
    refused=false;try{(void)missionTextDuration(std::numeric_limits<double>::infinity());}catch(const std::invalid_argument&){refused=true;}require(refused);
    std::cout<<"mission text action guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
