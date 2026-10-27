// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MessageFontMetrics.hpp"
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Message font fixture outside domain");}
template<class T>T take(std::istream& s){T v{};require(bool(s>>v));return v;}
std::u16string decode(std::string text){
    if(text=="-")return {};require(text.size()%4==0);std::u16string out;
    for(std::size_t i=0;i<text.size();i+=4){std::size_t used=0;const auto lo=std::stoul(text.substr(i,2),&used,16);require(used==2);const auto hi=std::stoul(text.substr(i+2,2),&used,16);require(used==2);out+=char16_t(lo|(hi<<8));}return out;
}
void run(std::istream& s){
    const auto op=take<char>(s);require(op=='M'||op=='W'||op=='F');
    const auto present=take<int>(s),hasText=take<int>(s),fallback=take<int>(s);require((present==0||present==1)&&(hasText==0||hasText==1)&&fallback>=-1&&fallback<=255);
    const auto line=take<std::int32_t>(s),tab=take<std::int32_t>(s),spacing=take<std::int32_t>(s);
    const auto stride=take<std::uint32_t>(s),base=take<std::uint32_t>(s);const auto limit=take<std::int32_t>(s);
    const auto max=take<std::uint32_t>(s),wrap=take<std::uint32_t>(s);const auto output=take<int>(s),n=take<int>(s);require(output>=0&&output<=4&&n>=0&&n<=32);
    const auto text=decode(take<std::string>(s));std::vector<std::uint16_t> indices(65536);std::map<std::uint32_t,std::uint8_t> bytes;
    for(int i=0;i<n;++i){const auto code=take<unsigned>(s),index=take<unsigned>(s),width=take<unsigned>(s);require(code<=65535&&index<=65535&&width<=255);indices[code]=std::uint16_t(index);const auto address=index?base+stride*(index-1):0;if(address)bytes[address]=std::uint8_t(width);}
    std::string tail;require(!(s>>tail));MessageFontGlyphs glyphs{indices,stride,base,[&](std::uint32_t p){return bytes.at(p);}};const auto fallbackByte=std::uint8_t(fallback);
    const MessageFontMetrics font{present?&glyphs:nullptr,fallback>=0?&fallbackByte:nullptr,line,tab,spacing};const std::u16string_view view=text;const auto* input=hasText?&view:nullptr;
    MessageFontTrace trace=[](char k,std::uint32_t a,std::uint32_t b){std::cout<<k<<' '<<a<<' '<<b<<' ';};
    std::int32_t width=0x11223344,height=0x55667788,result=0;
    if(op=='M')result=measureMessageFont(font,input,output==1||output==3||output==4?&width:nullptr,output==2||output==3?&height:output==4?&width:nullptr,limit,trace);
    else if(op=='W')result=messageFontWidth(font,input,limit,trace);
    else result=fitMessageFont(font,input,limit,max,wrap,trace);
    std::cout<<"R "<<result<<" FW "<<width<<" FH "<<height<<'\n';
}
void guards(){
    MessageFontMetrics font;std::u16string_view text=u"x";std::int32_t w=1,h=2;
    require(!measureMessageFont(font,&text,&w,&h,0)&&w==0&&h==0&&fitMessageFont(font,&text,0,0,0)==0);
    bool refused=false;try{(void)messageFontTab(1,0);}catch(const std::invalid_argument&){refused=true;}require(refused);
    refused=false;try{(void)messageFontTab(-2147483647,-1);}catch(const std::invalid_argument&){refused=true;}require(refused);
    require(messageFontAdd(2147483647,1)==(-2147483647-1)&&messageFontTab(-7,4)==0);
    std::vector<std::uint16_t> indices(65536);indices['x']=1;
    MessageFontGlyphs glyphs{indices,1,1,[](auto){return std::uint8_t(3);}};font={&glyphs,nullptr,7,4,0};
    require(measureMessageFont(font,&text,&w,&h,0)&&w==3&&h==7);
    std::u16string_view embedded(u"x\0x",3);require(fitMessageFont(font,&embedded,10,0,0)==1);
    require(fitMessageFont(font,&text,2,0,1)==0);
    std::cout<<"message font guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream s(line);run(s);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
