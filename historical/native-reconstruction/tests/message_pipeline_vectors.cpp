// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/MessageListDrawing.hpp"
#include "sim/MessageExpiry.hpp"
#include "assets/GameFont.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
#include <memory>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Message pipeline fixture outside domain");}
template<class T>T take(std::istream& s){T v{};require(bool(s>>v));return v;}
std::u16string decode(const std::string& token){
    if(token=="-")return {};require(token.size()%4==0);std::u16string value;
    for(std::size_t i=0;i<token.size();i+=4)value.push_back(char16_t(std::stoul(token.substr(i,4),nullptr,16)));
    return value;
}
void event(Bytes& bytes,char k,std::uint32_t a,std::uint32_t b){
    bytes.push_back(k);for(auto v:{a,b})for(unsigned i=0;i<4;++i)bytes.push_back(std::uint8_t(v>>(8*i)));
}
std::string hashWords(std::span<const std::uint16_t> values){Bytes b;for(auto v:values){b.push_back(std::uint8_t(v));b.push_back(std::uint8_t(v>>8));}return assetSha256(Data(b));}
void run(std::istream& in,const GameFont& stock){
    require(take<char>(in)=='P');const auto useStock=take<unsigned>(in);require(useStock<=1);
    MessageList list;list.x=take<std::int32_t>(in);list.y=take<std::int32_t>(in);list.width=take<std::int32_t>(in);list.maximumLines=take<std::int32_t>(in);list.lineStep=take<std::int32_t>(in);
    MessageListGlobals g;g.mode=take<std::int32_t>(in);const auto mode3=take<unsigned>(in),mode4=take<unsigned>(in);require(mode3<=255&&mode4<=255);g.mode3Enabled=std::uint8_t(mode3);g.mode4Enabled=std::uint8_t(mode4);g.clockStart=take<std::uint32_t>(in);g.clockAccumulated=take<std::uint32_t>(in);g.sound=-7;
    auto milliseconds=take<std::uint32_t>(in),timeStep=take<std::uint32_t>(in);const auto colorCount=take<std::int32_t>(in);const auto missing=take<unsigned>(in),mutation=take<unsigned>(in),actions=take<unsigned>(in);require(missing<=3&&mutation<=31&&actions<=64);
    for(auto& slot:list.text)slot.fill(char16_t(0xa5a5));list.available.fill(0x101);
    std::vector<std::uint16_t> indices(65536);indices[97]=1;indices[98]=2;indices[88]=1;indices[32]=2;
    Bytes glyph(66);for(unsigned i=0;i<glyph.size();++i)glyph[i]=std::uint8_t(i*37+71);glyph[0]=5;glyph[33]=7;Bytes fb(glyph.begin(),glyph.begin()+10);for(unsigned i=1;i<fb.size();++i)fb[i]^=255;
    MessageFontGlyphs primary{indices,33,1,[&](std::uint32_t a){require(a&&a<=glyph.size());return glyph[a-1];}};
    std::vector<std::uint16_t> pixels(768);for(unsigned i=0;i<pixels.size();++i)pixels[i]=std::uint16_t(i*29+0x1234);
    FontGlyphState font;font.primary=&primary;font.fallback=fb;font.surface=pixels;font.rows=3;font.rowBytes=3;font.lineHeight=4;font.pitch=32;font.color=0xabcd;font.spacing=1;font.tab=8;font.origin=0;font.clip={0,0,31,23};font.clipping=false;
    if(useStock){font.primary=stock.metrics().primary;font.fallback=stock.fallback();font.rows=std::bit_cast<std::int32_t>(stock.fields()[2]);font.rowBytes=std::bit_cast<std::int32_t>(stock.fields()[1]);font.lineHeight=stock.metrics().lineHeight;}
    MessageFontMetrics metrics{font.primary,font.fallback.data(),font.lineHeight,font.tab,font.spacing};g.selectedFont=&metrics;
    std::array<HsvColor,2> hsv{{{0,255,255},{137,211,239}}};std::array<const HsvColor*,2> colors{missing&1?nullptr:&hsv[0],missing&2?nullptr:&hsv[1]};
    std::vector<std::unique_ptr<MessageNode>> nodes;
    const auto id=[&](const MessageNode* p){if(!p)return 0u;for(unsigned i=0;i<nodes.size();++i)if(nodes[i].get()==p)return i+1;throw std::invalid_argument("Unknown pipeline node identity");};
    const auto nodeAt=[&](unsigned n)->MessageNode*{if(!n)return nullptr;require(n<=nodes.size());return nodes[n-1].get();};
    Bytes trace;const auto emit=[&](char k,std::uint32_t a,std::uint32_t b){event(trace,k,a,b);};
    bool drawing=false;MessageNode* active=nullptr;unsigned used=0;std::uint32_t clock=0;
    const auto mutate=[&](unsigned bit){
        if(!drawing||!active||!(mutation&bit)||(used&bit))return;used|=bit;
        if(bit==1||bit==2)active->next=nodes.size()>=3?nodes[2].get():nullptr;
        if(bit==4&&!nodes.empty())list.head=nodes.back().get();
        if(bit==8){g.clockStart=0xffffffffu;g.clockAccumulated=101;active->expires=1;}
        if(bit==16&&!nodes.empty()){g.focused[2]=nodes.back().get();nodes.back()->dirty=1;nodes.back()->field40=0;}
    };
    MessageListServices services;
    services.allocate=[&]{require(nodes.size()<256);auto p=std::make_unique<MessageNode>();p->padding1f=0xa5;p->padding42=0xa5a5;auto* result=p.get();nodes.push_back(std::move(p));emit('A',id(result),0);return result;};
    services.release=[&](MessageNode* p){emit('F',id(p),0);};
    services.milliseconds=[&]{const auto now=milliseconds+timeStep*clock++;emit('t',now,0);mutate(1);return now;};
    services.play=[&](auto sound,auto flags,auto volume,auto extra){require(flags==8192&&volume==1.f&&!extra);emit('a',std::uint32_t(sound),flags);mutate(2);mutate(8);};
    const auto observe=[&](char k){emit(k,!font.surface.empty(),std::uint32_t(font.pitch));};
    FontSurfaceServices surface;surface.lock=[&](auto x,auto y){require(!x&&!y);observe('L');return std::span<std::uint16_t>(pixels);};surface.pitchBytes=[&]{observe('P');return 64u;};surface.width=[&]{observe('V');return 32;};surface.height=[&]{observe('H');return 24;};surface.unlock=[&]{observe('U');};
    MessageNodeDrawGlobals drawGlobals{colors,colorCount,&font,&surface,-9};FontBlitContext blit{1,&font,&surface,{{11,3,0,3,5,2},{255,255,255}}};
    MessageTextServices text;text.composition=u"ab";text.compositionLength=2;text.compositionCursor=1;text.cursorRgb=0x789abc;
    text.refreshIme=[&]{text.composition.clear();text.compositionLength=text.compositionCursor=0;};
    text.fill=[&](const auto& b,auto value){emit('b',std::uint32_t(b.x),std::uint32_t(b.y));emit('b',std::uint32_t(b.width),std::uint32_t(b.height));emit('b',value,0);mutate(4);mutate(16);};
    text.line=[&](auto x,auto y,auto bottom,auto color,auto alpha){emit('c',std::uint32_t(x),std::uint32_t(y));emit('c',std::uint32_t(bottom),color);emit('c',alpha,0);};
    const auto chain=[&](char k,const MessageNode* node,const MessageNode* next){emit(k,id(node),id(next));if(k=='n')active=nodeAt(id(node));};
    const auto snapshot=[&]{
        std::ostringstream out;out<<"H "<<id(list.head)<<" U";for(auto v:list.available)out<<' '<<v;
        Bytes pool;for(const auto& slot:list.text)for(auto c:slot){pool.push_back(std::uint8_t(c));pool.push_back(std::uint8_t(c>>8));}out<<" B "<<assetSha256(Data(pool))<<" G";for(auto* p:g.focused)out<<' '<<id(p);
        out<<" N "<<nodes.size();for(const auto& p:nodes)out<<" O "<<id(p.get())<<' '<<id(p->next)<<' '<<id(p->previous)<<' '<<p->x<<' '<<p->y<<' '<<p->width<<' '<<p->height<<' '<<unsigned(p->dirty)<<' '<<unsigned(p->sticky)<<' '<<unsigned(p->field1e)<<' '<<unsigned(p->padding1f)<<' '<<p->gadgetFlags<<' '<<p->expires<<' '<<p->identifier<<' '<<p->flags<<' '<<p->slot<<' '<<p->color<<' '<<p->maximumWidth<<' '<<p->field3c<<' '<<unsigned(p->field40)<<' '<<unsigned(p->field41)<<' '<<p->padding42<<' '<<p->field44<<' '<<p->field48<<' '<<p->destroyed;
        out<<" L "<<list.x<<' '<<list.y<<' '<<list.width<<' '<<list.lineStep<<' '<<list.maximumLines<<' '<<unsigned(list.reserved19)<<' '<<unsigned(list.reserved1a)<<' '<<g.mode<<' '<<unsigned(g.mode3Enabled)<<' '<<unsigned(g.mode4Enabled)<<' '<<g.clockStart<<' '<<g.clockAccumulated<<' '<<g.sound<<' '<<bool(g.selectedFont);
        out<<" S "<<font.color<<' '<<font.pitch<<' '<<font.origin<<' '<<!font.surface.empty();for(auto v:font.clip)out<<' '<<v;out<<' '<<font.clipping<<" P "<<hashWords(pixels)<<" I "<<text.compositionLength<<' '<<text.compositionCursor<<' '<<text.extra<<' '<<text.cursorSuppression;
        const auto value=out.str();return assetSha256(Data(Bytes(value.begin(),value.end())));
    };
    std::cout<<"R "<<actions;
    for(unsigned i=0;i<actions;++i){
        const auto op=take<char>(in);unsigned result=0;
        if(op=='I'){
            const auto prefixToken=take<std::string>(in),bodyToken=take<std::string>(in);const auto lifetime=take<std::int32_t>(in),color=take<std::int32_t>(in);const auto flags=take<std::uint32_t>(in);const auto silent=take<unsigned>(in);require(silent<=255);
            const auto prefix=decode(prefixToken=="~"?"-":prefixToken),body=decode(bodyToken);const std::u16string_view pv=prefix,bv=body;
            MessageInsertRequest request{prefixToken=="~"?nullptr:&pv,0x81234567,&bv,color,flags,lifetime,std::uint8_t(silent)};result=id(insertMessage(list,g,services,request));
        }else if(op=='E')result=expireMessages(list,g,services);
        else if(op=='D'||op=='G'){
            const auto force=op=='G'?take<std::uint32_t>(in):1;drawing=true;active=nullptr;
            if(op=='D')drawOrdinaryMessageList(list,g,drawGlobals,services,blit,text,emit,chain);
            else drawMessageChain(list.head,list,g,drawGlobals,services,blit,text,force,emit,chain);
            drawing=false;active=nullptr;
        }else if(op=='F'){g.focused[2]=nodeAt(take<unsigned>(in));}
        else if(op=='H'){
            auto* p=nodeAt(take<unsigned>(in));require(p&&!p->destroyed);p->dirty=std::uint8_t(take<unsigned>(in));p->field40=std::uint8_t(take<unsigned>(in));p->field41=std::uint8_t(take<unsigned>(in));p->field44=take<std::uint32_t>(in);p->field48=take<std::uint32_t>(in);p->field3c=take<std::uint32_t>(in);
        }else if(op=='T'){milliseconds=take<std::uint32_t>(in);timeStep=take<std::uint32_t>(in);clock=0;}
        else throw std::invalid_argument("Unknown message pipeline operation");
        std::cout<<' '<<result<<' '<<snapshot();
    }
    std::string tail;require(!(in>>tail));std::cout<<" T "<<assetSha256(Data(trace))<<'\n';
}
void guards(){
    MessageList list;MessageListGlobals g;MessageNodeDrawGlobals draw;MessageListServices services;MessageTextServices text;
    drawOrdinaryMessageList(list,g,draw,services,{},text);drawMessageChain(nullptr,list,g,draw,services,{},text,0xffffffff);
    list.reserved19=1;bool refused=false;try{drawOrdinaryMessageList(list,g,draw,services,{},text);}catch(const std::invalid_argument&){refused=true;}require(refused);
    MessageNode dead;dead.destroyed=true;refused=false;try{drawMessageChain(&dead,list,g,draw,services,{},text,1);}catch(const std::invalid_argument&){refused=true;}require(refused);
    std::cout<<"message pipeline guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==2);const GameFont stock(readFile(argv[1]));std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in,stock);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
