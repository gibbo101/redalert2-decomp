// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/StringLookup.hpp"
#include <iostream>
#include <array>
#include <sstream>
#include <vector>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("String lookup fixture outside domain");}
template<class T>T take(std::istream& s){T v{};require(bool(s>>v));return v;}
std::string decode(std::string text){
    if(text=="-")return {};require(text.size()%2==0);std::string out;
    for(std::size_t i=0;i<text.size();i+=2){std::size_t used=0;const auto n=std::stoul(text.substr(i,2),&used,16);require(used==2);out+=char(n);}return out;
}
void run(std::istream& s){
    const auto op=take<char>(s);require(op=='L'||op=='B');const auto present=take<int>(s),n=take<int>(s),outKind=take<int>(s),alias=take<int>(s);
    require((present==0||present==1)&&n>=0&&n<=32&&outKind>=0&&outKind<=4&&alias>=0&&(outKind<2||alias<n));
    const auto key=decode(take<std::string>(s));std::vector<std::string> keys;keys.reserve(n);
    std::vector<StringLookupLabel> labels;std::vector<std::uint32_t> texts,extras;
    for(int i=0;i<n;++i){keys.push_back(decode(take<std::string>(s)));labels.push_back({keys.back(),take<std::uint32_t>(s)});texts.push_back(take<std::uint32_t>(s));extras.push_back(take<std::uint32_t>(s));}
    std::string extra;require(!(s>>extra));std::uint32_t output=0xcccccccc;
    auto* out=outKind==0?nullptr:outKind==1?&output:outKind==2?&labels.at(alias).index:outKind==3?&texts.at(alias):&extras.at(alias);
    StringLookupTrace trace=[](char k,std::uint32_t v){std::cout<<k<<' '<<v<<' ';};
    if(op=='L'){const auto result=lookupString(key,out,{bool(present),labels,std::uint32_t(n),texts,extras,0x7f8eb8},trace);std::cout<<"R "<<result<<' ';}
    else{const auto result=searchStringLookupLabel(key,labels,std::uint32_t(n),trace);std::cout<<"R "<<(result?int(*result):-1)<<' ';}
    std::cout<<"F "<<(out?*out:0)<<' ';for(const auto& l:labels)std::cout<<l.index<<' ';for(auto v:texts)std::cout<<v<<' ';for(auto v:extras)std::cout<<v<<' ';std::cout<<'\n';
}
void guards(){
    std::array<StringLookupLabel,1> labels{{{"key",0}}};std::array<std::uint32_t,1> slots{7};std::uint32_t out=99;
    bool refused=false;try{(void)lookupString("missing",&out,{true,labels,1,slots,slots,8});}catch(const std::invalid_argument&){refused=true;}
    require(refused&&out==0);require(lookupString("KEY",nullptr,{true,labels,1,slots,{},8})==7);
    require(lookupString("anything",&out,{false,{},0,{},{},8})==8&&out==0);
    refused=false;try{(void)searchStringLookupLabel("key",labels,2);}catch(const std::invalid_argument&){refused=true;}require(refused);
    labels[0].index=1;refused=false;try{(void)lookupString("key",nullptr,{true,labels,1,slots,{},8});}catch(const std::invalid_argument&){refused=true;}require(refused);
    require(compareStringLookupKeys(std::string("A\0ignored",9),"a")==0&&compareStringLookupKeys("Z","[")>0);
    std::cout<<"string lookup guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream s(line);run(s);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
