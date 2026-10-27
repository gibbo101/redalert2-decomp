// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/UnitDrawMetadata.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace ra2;
namespace {
std::string decode(const std::string& hex) {
    if(hex=="-")return {};
    if(hex.size()%2)throw std::invalid_argument("Invalid hex input");
    std::string result;
    for(std::size_t i=0;i<hex.size();i+=2)result+=char(std::stoul(hex.substr(i,2),nullptr,16));
    return result;
}
void print(const UnitDrawMetadata& t) {
    std::cout<<"fields "<<t.zFudgeCliff<<' '<<t.zFudgeColumn<<' '<<t.zFudgeTunnel<<' '
             <<t.zFudgeBridge<<' '<<int(t.tooBigToFitUnderBridge);
}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)) {
        std::istringstream in(line);char op;in>>op;
        if(op=='C')print({});
        else if(op=='M') {
            UnitDrawMetadata t;int bridge,mask,mode,side;std::array<int,4> values;std::string hex;
            in>>t.zFudgeCliff>>t.zFudgeColumn>>t.zFudgeTunnel>>t.zFudgeBridge>>bridge>>mask;
            for(auto& value:values)in>>value;in>>mode>>hex>>side;t.tooBigToFitUnderBridge=std::uint8_t(bridge);
            int index=0;UnitDrawMetadataServices s;
            s.integer=[&](std::string_view key,int fallback){std::cout<<"integer "<<key<<' '<<fallback<<' ';const int i=index++;return mask&(1<<i)?values[i]:fallback;};
            s.boolean=[&](std::string_view key,std::uint8_t fallback){std::cout<<"boolean "<<key<<' '<<int(fallback)<<' ';return iniBooleanValue(mode==5?decode(hex):"",fallback);};
            print(updateUnitDrawMetadata(t,s));
        } else if(op=='O') {
            std::string rules;in>>rules;print(readUnitDrawMetadata(Ini(readFile(rules).text()),"HTNK"));
        } else throw std::invalid_argument("Unknown draw metadata command");
        if(!in)throw std::invalid_argument("Missing draw metadata input");in>>std::ws;
        if(!in.eof())throw std::invalid_argument("Trailing draw metadata input");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
