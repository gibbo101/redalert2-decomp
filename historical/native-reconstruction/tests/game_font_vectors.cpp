// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/GameFont.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Game font fixture outside domain");}
template<class T>T take(std::istream& s){T v{};require(bool(s>>v));return v;}
void put(Bytes& b,std::size_t p,std::uint32_t v,unsigned n=4){for(unsigned i=0;i<n;++i)b.at(p+i)=std::uint8_t(v>>(i*8));}
Data synthetic(unsigned fill,unsigned columns,unsigned rows,unsigned count,bool x){
    const unsigned stride=columns*rows+1;Bytes b(28+131072+count*stride);
    const std::uint32_t fields[]={0x546e6f66,20,columns,rows,rows+1,count,stride};
    for(unsigned i=0;i<7;++i)put(b,i*4,fields[i]);
    if(count){put(b,28+32*2,1,2);put(b,28+97*2,count,2);put(b,28+65535*2,count,2);if(x)put(b,28+88*2,1,2);}
    for(unsigned i=0;i<count*stride;++i)b[28+131072+i]=std::uint8_t(i*7+fill);
    return Data(std::move(b));
}
void run(std::istream& s,const Data& stock){
    const auto op=take<char>(s);require(op=='G'||op=='S');const auto fill=take<unsigned>(s);require(fill<=255);Data data=stock;
    if(op=='S'){const auto columns=take<unsigned>(s),rows=take<unsigned>(s),count=take<unsigned>(s),x=take<unsigned>(s);require(columns<=4&&rows<=4&&count<=4&&x<=1);data=synthetic(fill,columns,rows,count,x);}
    std::string tail;require(!(s>>tail));GameFont font(data,std::uint8_t(fill));
    std::cout<<"D ";for(auto n:font.fields())std::cout<<n<<' ';std::cout<<font.indexed()<<' ';
    Bytes indices;indices.reserve(131072);for(auto index:font.indices()){indices.push_back(std::uint8_t(index));indices.push_back(std::uint8_t(index>>8));}
    std::cout<<"I "<<assetSha256(Data(std::move(indices)))<<" G "<<assetSha256(font.glyphData())<<" F "<<assetSha256(Data(font.fallback()))<<' ';
    for(const std::u16string_view text:{u"Hello",u"a\tb\r\nx",u"a b",u"\uffffX"}){
        std::int32_t width=0,height=0;require(measureMessageFont(font.metrics(),&text,&width,&height,0));
        std::cout<<"Q "<<width<<' '<<height<<' '<<fitMessageFont(font.metrics(),&text,32,111,1)<<' '<<messageFontWidth(font.metrics(),&text,0)<<' ';
    }
    std::cout<<"R 1\n";
}
void guards(){
    const auto file=synthetic(7,3,4,2,true);GameFont font(file,0xa5);
    require(font.fallback().size()==14&&font.fallback().front()==7&&font.fallback().back()==0xa5&&font.fallback()[1]==std::uint8_t(~14));
    GameFont missing(synthetic(7,3,4,2,false),0x55);for(auto byte:missing.fallback())require(byte==0x55);
    auto bad=*file.storage;bad[0]^=1;bool refused=false;try{GameFont other{Data(bad)};}catch(const std::invalid_argument&){refused=true;}require(refused);
    refused=false;try{GameFont other(file.slice(0,file.size-1));}catch(const std::exception&){refused=true;}require(refused);
    std::cout<<"game font guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==2);const auto stock=readFile(argv[1]);std::string line;while(std::getline(std::cin,line)){std::istringstream s(line);run(s,stock);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
