// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/MessageText.hpp"
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
 const auto op=take<char>(s);require(op=='J'||op=='D'||op=='B'||op=='A'||op=='C');
 unsigned enabled=0,fontChoice=0,surfaceChoice=0,diagnostic=0;std::uint32_t rgb=0;std::int32_t horizontal=0,vertical=0;FontTextBox box;
 if(op=='A'){enabled=take<unsigned>(s);fontChoice=take<unsigned>(s);surfaceChoice=take<unsigned>(s);rgb=take<std::uint32_t>(s);horizontal=take<std::int32_t>(s);vertical=take<std::int32_t>(s);box.x=take<std::int32_t>(s);box.y=take<std::int32_t>(s);box.width=take<std::int32_t>(s);box.height=take<std::int32_t>(s);diagnostic=take<unsigned>(s);require(enabled<=255&&fontChoice<=1&&surfaceChoice<=1&&diagnostic<=1);}
 std::int32_t caret=0,scroll=0,compositionCursor=0,extra=0,suppression=0;unsigned ime=0,mask=0,background=0,nullText=0,imeContext=0;std::string compositionHex;std::uint32_t highlight=0,cursorRgb=0;
 if(op=='C'){enabled=take<unsigned>(s);rgb=take<std::uint32_t>(s);box.x=take<std::int32_t>(s);box.y=take<std::int32_t>(s);box.width=take<std::int32_t>(s);box.height=take<std::int32_t>(s);caret=take<std::int32_t>(s);scroll=take<std::int32_t>(s);ime=take<unsigned>(s);mask=take<unsigned>(s);background=take<unsigned>(s);nullText=take<unsigned>(s);imeContext=take<unsigned>(s);compositionCursor=take<std::int32_t>(s);extra=take<std::int32_t>(s);suppression=take<std::int32_t>(s);highlight=take<std::uint32_t>(s);cursorRgb=take<std::uint32_t>(s);compositionHex=take<std::string>(s);require(enabled<=255&&ime<=1&&mask<=1&&background<=1&&nullText<=1&&imeContext<=1);}
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
 FontGlyphState alternate=f;alternate.spacing=messageFontAdd(f.spacing,2);alternate.lineHeight=messageFontAdd(f.lineHeight,1);alternate.tab=messageFontAdd(f.tab,3);alternate.origin=messageFontAdd(f.origin,17);
 auto* active=op=='A'&&fontChoice?&alternate:&f;
 Bytes trace;const auto emit=[&](char k,std::uint32_t a,std::uint32_t v){event(trace,k,a,v);if(op=='A'&&k=='M'&&diagnostic){box.x=messageFontAdd(box.x,5);box.y=messageFontSub(box.y,2);box.width=messageFontAdd(box.width,3);box.height=messageFontAdd(box.height,4);}};
 const auto observe=[&](char k){if(op=='A')emit('C',surfaceChoice?2:1,0);emit(k,!active->surface.empty(),std::uint32_t(active->pitch));};
 FontSurfaceServices surface;surface.lock=[&](auto a,auto b){require(!a&&!b);observe('L');return std::span<std::uint16_t>(pixels);};surface.pitchBytes=[&]{observe('P');return pitch;};surface.width=[&]{observe('V');return width;};surface.height=[&]{observe('H');if(mutation==1)active->clip={2,2,19,15};return height;};surface.unlock=[&]{observe('U');if(mutation==2){active->pitch=777;active->surface=pixels;}};
 MessageTextServices message;
 if(op=='C'){
  message.compositionCursor=compositionCursor;message.extra=extra;message.cursorSuppression=suppression;message.highlightRgb=highlight;message.cursorRgb=cursorRgb;
  if(compositionHex!="-")for(std::size_t i=0;i<compositionHex.size();i+=4)message.composition.push_back(char16_t(std::stoul(compositionHex.substr(i,4),nullptr,16)));
  message.compositionLength=messageTextLength(message.composition);
  message.refreshIme=[&]{if(imeContext)emit('i',std::uint32_t(message.compositionLength),std::uint32_t(message.compositionCursor));else {message.composition.clear();message.compositionLength=message.compositionCursor=0;}};
  message.fill=[&](const auto& b,auto value){emit('b',std::uint32_t(b.x),std::uint32_t(b.y));emit('b',std::uint32_t(b.width),std::uint32_t(b.height));emit('b',value,0);};
  message.line=[&](auto x1,auto y1,auto y2,auto color,auto alpha){emit('c',std::uint32_t(x1),std::uint32_t(y1));emit('c',std::uint32_t(y2),color);emit('c',alpha,0);};
 }
 std::int32_t result=0;
 if(op=='C'){FontBlitContext context{std::uint8_t(enabled),&f,&surface,colors};const std::u16string_view view=text;drawMessageText(context,surface,box,nullText?nullptr:&view,caret,f,rgb,scroll,ime,mask,background,reveal,message,emit);}
 else
 if(op=='A'){FontSurfaceServices explicitSurface=surface;FontBlitContext context{std::uint8_t(enabled),fontPresent?&f:nullptr,&surface,colors};result=drawAlignedFontText(context,rgb,fontChoice?&alternate:nullptr,box,text,count,horizontal,vertical,surfaceChoice?&explicitSurface:nullptr,reveal,emit);}
 else if(op=='B'){bindFontSurface(f,surface);unbindFontSurface(f,surface);}
 else if(op=='J')result=drawFontOnSurface(fontPresent?&f:nullptr,surface,text,x,y,count,reveal,colors,emit);
 else result=drawFontText(f,text,x,y,count,reveal,colors,emit);
 Bytes backing;for(auto v:pixels){backing.push_back(std::uint8_t(v));backing.push_back(std::uint8_t(v>>8));}
 std::cout<<"R "<<result<<" B "<<assetSha256(Data(backing))<<" T "<<assetSha256(Data(trace))<<" S "<<f.color<<' '<<f.pitch<<' '<<f.origin<<' '<<!f.surface.empty();for(auto n:f.clip)std::cout<<' '<<n;if(op=='A'){std::cout<<" D "<<alternate.color<<' '<<alternate.pitch<<' '<<alternate.origin<<' '<<!alternate.surface.empty();for(auto n:alternate.clip)std::cout<<' '<<n;std::cout<<" Q "<<box.x<<' '<<box.y<<' '<<box.width<<' '<<box.height<<" E "<<f.clipping<<' '<<alternate.clipping;}if(op=='C')std::cout<<" Q "<<box.x<<' '<<box.y<<' '<<box.width<<' '<<box.height<<" Z "<<scroll<<' '<<message.cursorSuppression<<' '<<message.compositionLength<<' '<<message.compositionCursor<<' '<<message.extra<<' '<<f.clipping;std::cout<<'\n';
}
void guards(){
 FontGlyphState f;FontSurfaceServices missing;bool refused=false;try{bindFontSurface(f,missing);}catch(const std::invalid_argument&){refused=true;}require(refused);
 bool unlocked=false;FontSurfaceServices service;service.unlock=[&]{unlocked=true;f.pitch=99;};unbindFontSurface(f,service);require(unlocked&&f.pitch==0&&f.surface.empty());
 require(drawFontOnSurface(nullptr,missing,u"a",9,2,0,1,{})==9);
 require(drawAlignedFontText({},0,nullptr,{},u"a",0,0,0,nullptr,0)==0);
 std::array<char16_t,4> scratch;copyMessageText(scratch,u"a",4);require(scratch[0]==u'a'&&!scratch[1]&&!scratch[3]);copyMessageText(scratch,u"abcd",4);require(scratch[3]==u'd');
 refused=false;try{copyMessageText(scratch,u"a",5);}catch(const std::invalid_argument&){refused=true;}require(refused);
 MessageTextServices message;FontTextBox box;std::int32_t scroll=0;refused=false;try{drawMessageText({},missing,box,nullptr,0,f,0,scroll,true,false,false,0,message);}catch(const std::invalid_argument&){refused=true;}require(refused);
 std::cout<<"font text guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==2);GameFont stock(readFile(argv[1]));std::string line;while(std::getline(std::cin,line)){std::istringstream s(line);run(s,stock);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
