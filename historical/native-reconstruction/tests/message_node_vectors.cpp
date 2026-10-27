// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/MessageNodeDrawing.hpp"
#include "assets/GameFont.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Font text fixture outside domain");}
template<class T>T take(std::istream& s){T v{};require(bool(s>>v));return v;}
void event(Bytes& b,char kind,std::uint32_t a,std::uint32_t v){b.push_back(kind);for(auto n:{a,v})for(unsigned i=0;i<4;++i)b.push_back(std::uint8_t(n>>(8*i)));}
void run(std::istream& s,const GameFont& stock){
 const auto op=take<char>(s);require(op=='N');
 const auto force=take<std::uint32_t>(s);const auto dirty=take<unsigned>(s),hidden=take<unsigned>(s),typewriter=take<unsigned>(s);const auto selector=take<std::int32_t>(s),colorCount=take<std::int32_t>(s);const auto missing=take<unsigned>(s);const auto nodeX=take<std::int32_t>(s),nodeY=take<std::int32_t>(s),maximumWidth=take<std::int32_t>(s);const auto initialScroll=take<std::uint32_t>(s),initialReveal=take<std::uint32_t>(s),initialTime=take<std::uint32_t>(s),milliseconds=take<std::uint32_t>(s),timeStep=take<std::uint32_t>(s);const auto focus=take<unsigned>(s),repeats=take<unsigned>(s),nodeMutation=take<unsigned>(s);unsigned enabled=take<unsigned>(s);const auto lineOverride=take<std::int32_t>(s);std::array<HsvColor,2> hsv;for(auto& c:hsv){c.hue=std::uint8_t(take<unsigned>(s));c.saturation=std::uint8_t(take<unsigned>(s));c.value=std::uint8_t(take<unsigned>(s));}
 require(dirty<=255&&hidden<=255&&typewriter<=255&&missing<=3&&focus<=1&&repeats>=1&&repeats<=3&&nodeMutation<=7&&enabled<=255);
 const auto useStock=take<unsigned>(s),fontPresent=take<unsigned>(s),present=take<unsigned>(s),fallback=take<unsigned>(s),bound=take<unsigned>(s),seed=take<unsigned>(s);
 const auto x=take<std::int32_t>(s),y=take<std::int32_t>(s);const auto color=take<unsigned>(s);const auto spacing=take<std::int32_t>(s),tab=take<std::int32_t>(s),origin=take<std::int32_t>(s);const auto count=take<std::uint32_t>(s);const auto reveal=take<std::int32_t>(s);const auto clipping=take<unsigned>(s);FontRect clip;for(auto& n:clip)n=take<std::int32_t>(s);
 const auto pitch=take<std::uint32_t>(s);const auto width=take<std::int32_t>(s),height=take<std::int32_t>(s);const auto mutation=take<unsigned>(s);FontTextColors colors;for(auto& n:colors.shifts)n=take<std::uint32_t>(s);for(auto& n:colors.target){const auto v=take<unsigned>(s);require(v<=255);n=std::uint8_t(v);}const auto offset=take<unsigned>(s);const auto hex=take<std::string>(s);std::string tail;require(!(s>>tail));
 require(useStock<=1&&fontPresent<=1&&present<=1&&fallback<=1&&bound<=1&&seed<=255&&color<=65535&&clipping<=1&&mutation<=2&&offset<=4096);
 std::u16string text;if(hex!="-"){require(hex.size()%4==0);for(std::size_t i=0;i<hex.size();i+=4)text.push_back(char16_t(std::stoul(hex.substr(i,4),nullptr,16)));}
 std::vector<std::uint16_t> indices(65536);indices[97]=1;indices[98]=2;indices[88]=1;indices[32]=2;
 Bytes glyph(66);for(unsigned i=0;i<glyph.size();++i)glyph[i]=std::uint8_t(i*37+seed);glyph[0]=5;glyph[33]=7;Bytes fb(glyph.begin(),glyph.begin()+10);for(unsigned i=1;i<fb.size();++i)fb[i]^=255;
 MessageFontGlyphs primary{indices,33,1,[&](std::uint32_t a){require(a&&a<=glyph.size());return glyph[a-1];}};
 std::vector<std::uint16_t> pixels(768);for(unsigned i=0;i<pixels.size();++i)pixels[i]=std::uint16_t(i*29+0x1234);
 FontGlyphState f;f.primary=present?&primary:nullptr;f.fallback=fallback?std::span<const std::uint8_t>(fb):std::span<const std::uint8_t>{};f.surface=bound?std::span<std::uint16_t>(pixels):std::span<std::uint16_t>{};f.rows=3;f.rowBytes=3;f.lineHeight=4;f.pitch=32;f.color=std::uint16_t(color);f.spacing=spacing;f.tab=tab;f.origin=origin;f.clipping=clipping;f.clip=clip;
 if(useStock){f.primary=present?stock.metrics().primary:nullptr;f.fallback=fallback?std::span<const std::uint8_t>(stock.fallback()):std::span<const std::uint8_t>{};f.rows=std::bit_cast<std::int32_t>(stock.fields()[2]);f.rowBytes=std::bit_cast<std::int32_t>(stock.fields()[1]);f.lineHeight=stock.metrics().lineHeight;}
 if(lineOverride!=2147483647)f.lineHeight=lineOverride;
 FontGlyphState alternate=f;alternate.spacing=messageFontAdd(f.spacing,2);alternate.lineHeight=messageFontAdd(f.lineHeight,1);alternate.tab=messageFontAdd(f.tab,3);alternate.origin=messageFontAdd(f.origin,17);
 auto* active=&f;MessageList list;require(text.size()<=161);std::copy(text.begin(),text.end(),list.text[0].begin());const std::u16string alternateText=u"baX";std::copy(alternateText.begin(),alternateText.end(),list.text[1].begin());
 MessageNode node;node.x=nodeX;node.y=nodeY;node.maximumWidth=maximumWidth;node.dirty=std::uint8_t(dirty);node.field40=std::uint8_t(hidden);node.field41=std::uint8_t(typewriter);node.color=selector;node.slot=0;node.field3c=initialScroll;node.field44=initialReveal;node.field48=initialTime;
 MessageListGlobals listGlobals;listGlobals.focused[2]=focus?&node:nullptr;
 std::array<const HsvColor*,2> pointers{missing&1?nullptr:&hsv[0],missing&2?nullptr:&hsv[1]};MessageNodeDrawGlobals globals{pointers,colorCount,&f,nullptr,-7};
 Bytes trace;const auto emit=[&](char k,std::uint32_t a,std::uint32_t v){event(trace,k,a,v);};
 unsigned widthCalls=0;const auto observe=[&](char k){emit(k,!active->surface.empty(),std::uint32_t(active->pitch));};
 FontSurfaceServices surface;surface.lock=[&](auto a,auto b){require(!a&&!b);observe('L');return std::span<std::uint16_t>(pixels);};surface.pitchBytes=[&]{observe('P');return pitch;};surface.width=[&]{observe('V');if(!widthCalls++&&(nodeMutation&4)){node.x=7;node.y=9;node.maximumWidth=15;f.lineHeight=7;globals.font=&alternate;for(auto& c:hsv)c.value=173;}return width;};surface.height=[&]{observe('H');if(mutation==1)active->clip={2,2,19,15};return height;};surface.unlock=[&]{observe('U');if(mutation==2){active->pitch=777;active->surface=pixels;}};globals.surface=&surface;
 MessageTextServices message;message.composition=u"ab";message.compositionLength=2;message.compositionCursor=1;message.cursorSuppression=0;message.cursorRgb=0x789abc;
 message.refreshIme=[&]{message.composition.clear();message.compositionLength=message.compositionCursor=0;};
 message.fill=[&](const auto& b,auto value){emit('b',std::uint32_t(b.x),std::uint32_t(b.y));emit('b',std::uint32_t(b.width),std::uint32_t(b.height));emit('b',value,0);};
 message.line=[&](auto x1,auto y1,auto y2,auto color,auto alpha){emit('c',std::uint32_t(x1),std::uint32_t(y1));emit('c',std::uint32_t(y2),color);emit('c',alpha,0);};
 MessageListServices services;unsigned clock=0;services.milliseconds=[&]{const auto now=milliseconds+timeStep*clock++;emit('t',now,0);if(nodeMutation&1){node.field44=3;node.field48=now-48;node.slot=1;listGlobals.focused[2]=listGlobals.focused[2]?nullptr:&node;}return now;};services.play=[&](auto sound,auto flags,auto volume,auto extra){require(flags==8192&&volume==1.f&&!extra);emit('a',std::uint32_t(sound),flags);if(nodeMutation&2){node.field44=2;node.field48=99;node.slot=1;node.field3c=1;listGlobals.focused[2]=listGlobals.focused[2]?nullptr:&node;}};
 FontBlitContext context{std::uint8_t(enabled),&f,&surface,colors};std::vector<unsigned> results;
 for(unsigned i=0;i<repeats;++i){active=globals.font;results.push_back(drawMessageNode(node,list,listGlobals,globals,services,context,message,force,emit));}
 Bytes backing;for(auto v:pixels){backing.push_back(std::uint8_t(v));backing.push_back(std::uint8_t(v>>8));}
 std::cout<<"R "<<results.size();for(auto v:results)std::cout<<' '<<v;std::cout<<" B "<<assetSha256(Data(backing))<<" T "<<assetSha256(Data(trace))<<" S "<<f.color<<' '<<f.pitch<<' '<<f.origin<<' '<<!f.surface.empty();for(auto n:f.clip)std::cout<<' '<<n;std::cout<<" D "<<alternate.color<<' '<<alternate.pitch<<' '<<alternate.origin<<' '<<!alternate.surface.empty();for(auto n:alternate.clip)std::cout<<' '<<n;std::cout<<" E "<<f.clipping<<' '<<alternate.clipping<<" O "<<node.x<<' '<<node.y<<' '<<node.maximumWidth<<' '<<unsigned(node.dirty)<<' '<<node.field3c<<' '<<unsigned(node.field40)<<' '<<unsigned(node.field41)<<' '<<node.field44<<' '<<node.field48<<' '<<node.slot<<" F "<<(listGlobals.focused[2]==&node)<<" G "<<(globals.font==&alternate)<<" H "<<f.lineHeight<<' '<<alternate.lineHeight<<" C";for(const auto& c:hsv)std::cout<<' '<<unsigned(c.hue)<<' '<<unsigned(c.saturation)<<' '<<unsigned(c.value);std::cout<<'\n';
}

void guards(){
 MessageNode n;MessageList l;MessageListGlobals g;MessageNodeDrawGlobals d;MessageListServices s;MessageTextServices t;require(!drawMessageNode(n,l,g,d,s,{},t,0));n.dirty=1;require(!drawMessageNode(n,l,g,d,s,{},t,0)&&!n.dirty);n.field40=1;n.dirty=3;require(!drawMessageNode(n,l,g,d,s,{},t,1)&&n.dirty==3);
 n.field40=0;d.colorCount=1;bool refused=false;try{drawMessageNode(n,l,g,d,s,{},t,1);}catch(const std::invalid_argument&){refused=true;}require(refused);n.slot=14;refused=false;try{messageNodeText(n,l);}catch(const std::invalid_argument&){refused=true;}require(refused);
 std::cout<<"message node guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==2);GameFont stock(readFile(argv[1]));std::string line;while(std::getline(std::cin,line)){std::istringstream s(line);run(s,stock);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
