// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/UnitModelInputs.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace ra2;
namespace {
std::string decode(const std::string& h) {
    if(h=="-")return {};if(h.size()%2)throw std::invalid_argument("Invalid hex input");
    std::string v;for(std::size_t i=0;i<h.size();i+=2)v+=char(std::stoul(h.substr(i,2),nullptr,16));return v;
}
template<class Range> std::string hex(const Range& v) {
    const char* digits="0123456789abcdef";std::string h;
    for(auto byte:v){const auto b=std::uint8_t(byte);h+=digits[b>>4];h+=digits[b&15];}
    return h.empty()?"-":h;
}
ModelImageName image(const std::string& h) {
    const auto v=decode(h);if(v.size()!=25)throw std::invalid_argument("Expected 25 image bytes");
    ModelImageName out;std::copy(v.begin(),v.end(),out.begin());return out;
}
void print(const UnitModelInputs& t){std::cout<<"state "<<hex(t.image)<<' '<<t.turretCount<<' '<<t.turretOffset;}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)) {
        std::istringstream in(line);char op;in>>op;
        if(op=='S') {
            int mode,capacity;std::string valueHex,fallbackHex;in>>mode>>capacity>>valueHex>>fallbackHex;
            if(capacity>64)throw std::invalid_argument("Output exceeds fixture");
            const auto value=decode(valueHex);const auto fallback=fallbackHex=="~"?std::optional<std::string>{}:std::optional<std::string>{decode(fallbackHex)};
            std::array<std::uint8_t,64> out;out.fill(0x93);
            const auto length=readIniStringBuffer(out,capacity,
                mode==5||mode==8?std::optional<std::string_view>{value}:std::nullopt,
                fallback?std::optional<std::string_view>{*fallback}:std::nullopt,mode!=6&&mode!=7&&mode!=8);
            std::cout<<length<<' '<<hex(out);
        } else if(op=='C') {
            std::string h;in>>h;print(initializeUnitModelInputs(image(h)));
        } else if(op=='M') {
            UnitModelInputs t;std::string h,valueHex;int mask,mode;std::array<int,2> values;
            in>>h>>t.turretCount>>t.turretOffset>>mask>>values[0]>>values[1]>>mode>>valueHex;t.image=image(h);
            const auto value=decode(valueHex);UnitModelInputServices s;
            s.image=[&](std::string_view id,const ModelImageName& fallback,ModelImageName& out){
                std::cout<<"image "<<hex(id)<<' '<<hex(modelImageString(fallback))<<' ';
                readIniStringBuffer(out,25,mode==5?std::optional<std::string_view>(value):std::nullopt,modelImageString(fallback));};
            s.rulesInteger=[&](std::string_view id,std::string_view key,int d){
                std::cout<<"rules "<<hex(id)<<' '<<key<<' '<<d<<' ';return mask&1?values[0]:d;};
            s.artInteger=[&](std::string_view id,std::string_view key,int d){
                std::cout<<"art "<<hex(id)<<' '<<key<<' '<<d<<' ';return mask&2?values[1]:d;};
            print(updateUnitModelInputs(t,"HTNK",s));
        } else if(op=='O') {
            std::string rules,art;in>>rules>>art;print(readUnitModelInputs(Ini(readFile(rules).text()),Ini(readFile(art).text()),"HTNK"));
        } else throw std::invalid_argument("Unknown model input command");
        if(!in)throw std::invalid_argument("Missing model input");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing model input");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
