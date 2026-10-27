// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MessageColor.hpp"
#include "sim/StringLookup.hpp"
#include "sim/MissionTextAction.hpp"
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Message lookup fixture outside domain");}
template<class T>T take(std::istream& s){T v{};require(bool(s>>v));return v;}
std::string decode(const std::string& text){
    if(text=="-")return {};require(text.size()%2==0);std::string out;
    for(std::size_t i=0;i<text.size();i+=2){std::size_t n=0;const auto v=std::stoul(text.substr(i,2),&n,16);require(n==2);out+=char(v);}return out;
}
std::string encode(std::string_view text){if(text.empty())return "-";std::ostringstream s;s<<std::hex<<std::setfill('0');for(unsigned char c:text)s<<std::setw(2)<<unsigned(c);return s.str();}
MessageColorTable colors(std::istream& s){MessageColorTable out;for(auto& c:out){auto n=take<int>(s);require(n>=-128&&n<=127);c=std::int8_t(n);}return out;}
void run(std::istream& s){
    const auto op=take<char>(s);require(op=='P'||op=='J');
    if(op=='P'){const auto selector=take<std::int32_t>(s);const auto table=colors(s);std::string tail;require(!(s>>tail));std::cout<<"R "<<messageColor(selector,table)<<'\n';return;}
    const auto alternate=take<int>(s);require(alternate>=0&&alternate<=255);const auto delay=take<std::uint64_t>(s);
    const auto key=decode(take<std::string>(s));const auto n=take<unsigned>(s);require(n<=16);const auto table=colors(s);
    std::vector<std::string> keys,payloads;std::vector<StringLookupLabel> labels;std::vector<std::uint32_t> words;keys.reserve(n);payloads.reserve(n);
    for(unsigned i=0;i<n;++i){keys.push_back(decode(take<std::string>(s)));auto index=take<unsigned>(s);require(index<n);labels.push_back({keys.back(),index});payloads.push_back(decode(take<std::string>(s)));words.push_back(i);}
    std::string tail;require(!(s>>tail));MissionTextServices services;
    services.color=[&](int selector){auto v=messageColor(selector,table);std::cout<<"C "<<selector<<" V "<<v<<' ';return v;};
    services.localize=[&](std::string_view query)->std::string_view{
        std::cout<<"K "<<encode(query)<<" 0 8350672 1582 ";
        auto slot=lookupString(query,nullptr,{true,labels,n,words,{},0},[](char k,std::uint32_t v){std::cout<<k<<' '<<v<<' ';});
        return payloads.at(slot);
    };
    services.display=[](const MissionTextRequest& r){std::cout<<"M "<<r.leading0<<' '<<r.leading1<<' '<<encode(r.text)<<' '<<r.color<<' '<<r.style<<' '<<r.duration<<' '<<r.trailing<<' ';};
    const auto result=executeMissionTextAction(key,std::uint8_t(alternate),std::bit_cast<double>(delay),services);std::cout<<"R "<<result<<'\n';
}
void guards(){
    MessageColorTable table{};table[0]=-128;table[8]=-1;
    require(messageColor(-2,table)==-1&&messageColor(0,table)==-128&&messageColor(-1,table)==-1&&messageColor(9,table)==9);
    std::istringstream s("J 0 0 - 0 0 0 0 0 0 0 0 0 0");run(s);
    std::cout<<"message text lookup guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream s(line);run(s);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
