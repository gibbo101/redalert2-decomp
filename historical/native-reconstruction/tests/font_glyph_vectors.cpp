// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/FontGlyph.hpp"
#include "assets/GameFont.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Font glyph fixture outside domain");}
template<class T>T take(std::istream& s){T v{};require(bool(s>>v));return v;}
void event(Bytes& b,char kind,std::uint32_t a,std::uint32_t v){b.push_back(kind);for(auto n:{a,v})for(unsigned i=0;i<4;++i)b.push_back(std::uint8_t(n>>(8*i)));}
void run(std::istream& s,const GameFont& stock){
 const auto op=take<char>(s);require(op=='G'||op=='T');
 const auto code=take<std::uint32_t>(s);const auto present=take<unsigned>(s),fallback=take<unsigned>(s),surface=take<unsigned>(s),index=take<unsigned>(s),width=take<unsigned>(s),rows=take<unsigned>(s),stride=take<unsigned>(s),pattern=take<unsigned>(s);
 const auto x=take<std::int32_t>(s),y=take<std::int32_t>(s),overrideColor=take<std::int32_t>(s),spacing=take<std::int32_t>(s),tab=take<std::int32_t>(s),origin=take<std::int32_t>(s);const auto clipping=take<unsigned>(s);FontRect clip;for(auto& n:clip)n=take<std::int32_t>(s);std::string tail;require(!(s>>tail));
 require(present<=1&&fallback<=1&&surface<=1&&index<=1&&width<=24&&rows<=5&&stride<=4&&pattern<=255&&clipping<=1);
 std::vector<std::uint16_t> indices(65536);indices[std::uint16_t(code)]=index;
 Bytes glyph(129);glyph[0]=std::uint8_t(width);for(unsigned i=1;i<glyph.size();++i)glyph[i]=pattern==0?0:pattern==255?255:std::uint8_t(i*37+pattern);
 auto fb=glyph;for(unsigned i=1;i<fb.size();++i)fb[i]^=255;
 MessageFontGlyphs primary{indices,129,1,[&](std::uint32_t a){require(a&&a<=glyph.size());return glyph[a-1];}};
 std::vector<std::uint16_t> pixels(32*24);for(unsigned i=0;i<pixels.size();++i)pixels[i]=std::uint16_t(i*29+0x1234);
 FontGlyphState f;f.primary=present?&primary:nullptr;f.fallback=fallback?std::span<const std::uint8_t>(fb):std::span<const std::uint8_t>{};f.surface=surface?std::span<std::uint16_t>(pixels):std::span<std::uint16_t>{};f.rows=rows;f.rowBytes=stride;f.pitch=32;f.color=0xabcd;f.spacing=spacing;f.tab=tab;f.origin=origin;f.clipping=clipping;f.clip=clip;
 if(op=='T'){f.primary=stock.metrics().primary;f.fallback=fallback?std::span<const std::uint8_t>(stock.fallback()):std::span<const std::uint8_t>{};f.rows=std::bit_cast<std::int32_t>(stock.fields()[2]);f.rowBytes=std::bit_cast<std::int32_t>(stock.fields()[1]);}
 Bytes trace;auto result=drawFontGlyph(f,code,x,y,overrideColor,[&](char k,std::uint32_t a,std::uint32_t v){event(trace,k,a,v);});
 Bytes backing;for(auto v:pixels){backing.push_back(std::uint8_t(v));backing.push_back(std::uint8_t(v>>8));}
 std::cout<<"R "<<result<<" B "<<assetSha256(Data(backing))<<" T "<<assetSha256(Data(trace))<<'\n';
}
void guards(){
 FontGlyphState f;f.tab=0;bool refused=false;try{drawFontGlyph(f,9,0,0);}catch(const std::invalid_argument&){refused=true;}require(refused);
 f.tab=-1;f.origin=0;refused=false;try{drawFontGlyph(f,9,INT32_MIN+1,0);}catch(const std::invalid_argument&){refused=true;}require(refused);
 require(drawFontGlyph(f,65,7,0)==7);
 FontRect a={0,0,10,10},b={2,3,8,9};require(intersectFontRect(b,a,b)&&b==a); // Sequential copy aliases b before clamping.
 std::vector<std::uint16_t> indices(65536);indices[65]=1;MessageFontGlyphs p{indices,2,1,[](auto){return std::uint8_t(255);}};
 std::array<std::uint16_t,1> pixel{};f={};f.primary=&p;f.surface=pixel;f.rows=1;f.pitch=1;f.color=0xbeef;refused=false;try{drawFontGlyph(f,65,0,0);}catch(const std::invalid_argument&){refused=true;}require(refused&&pixel[0]==0xbeef);
 std::cout<<"font glyph guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==2);GameFont stock(readFile(argv[1]));std::string line;while(std::getline(std::cin,line)){std::istringstream s(line);run(s,stock);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
