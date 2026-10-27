// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MessageList.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
#include <memory>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Message insertion fixture outside domain");}
template<class T>T take(std::istream& s){T v{};require(bool(s>>v));return v;}
std::u16string decode(const std::string& s){std::u16string r;if(s=="-")return r;require(s.size()%4==0);for(std::size_t i=0;i<s.size();i+=4){const auto a=std::stoul(s.substr(i,2),nullptr,16),b=std::stoul(s.substr(i+2,2),nullptr,16);r.push_back(char16_t(a|(b<<8)));}return r;}
void run(std::istream& in){
 const auto width=take<int>(in),capacity=take<int>(in);const auto res19=take<unsigned>(in),res1a=take<unsigned>(in);const auto mode=take<int>(in);const auto mode3=take<unsigned>(in),mode4=take<unsigned>(in);
 const auto start=take<std::uint32_t>(in),accum=take<std::uint32_t>(in),milliseconds=take<std::uint32_t>(in),glyphWidth=take<unsigned>(in),available=take<unsigned>(in),initial=take<unsigned>(in),focus=take<unsigned>(in),present=take<unsigned>(in),bodyPresent=take<unsigned>(in),silent=take<unsigned>(in);const auto lifetime=take<int>(in);auto prefix=take<std::string>(in),body=take<std::string>(in);const auto repeats=take<unsigned>(in),mutation=take<unsigned>(in);require(mutation<=15);
 require(width>=-100&&width<=2147483647&&capacity>=-1&&capacity<=20&&res19<256&&res1a<256&&mode3<256&&mode4<256&&glyphWidth<=255&&available<=16383&&initial<=14&&focus<=7&&present<=1&&bodyPresent<=1&&silent<=255&&repeats<=20);
 MessageList list;list.width=width;list.maximumLines=capacity;list.x=-11;list.y=23;list.lineStep=-13;list.reserved19=std::uint8_t(res19);list.reserved1a=std::uint8_t(res1a);
 for(auto& slot:list.text)slot.fill(char16_t(0xa5a5));for(unsigned i=0;i<14;++i)list.available[i]=(available&(1u<<i))?0x101:0;
 std::array<std::uint16_t,65536> indices;indices.fill(1);MessageFontGlyphs glyph{indices,1,1,[&](std::uint32_t a){require(a==1);return std::uint8_t(glyphWidth);}};std::uint8_t fallback=7;MessageFontMetrics font{&glyph,&fallback,12,64,1};
 MessageListGlobals g;g.selectedFont=present?&font:nullptr;g.mode=mode;g.mode3Enabled=std::uint8_t(mode3);g.mode4Enabled=std::uint8_t(mode4);g.clockStart=start;g.clockAccumulated=accum;g.sound=-7;
 std::vector<std::unique_ptr<MessageNode>> nodes;
 auto newNode=[&](){auto p=std::make_unique<MessageNode>();p->padding1f=0xa5;p->padding42=0xa5a5;auto* out=p.get();nodes.push_back(std::move(p));return out;};
 auto id=[&](const MessageNode* p){if(!p)return 0;for(std::size_t i=0;i<nodes.size();++i)if(nodes[i].get()==p)return int(i+1);throw std::invalid_argument("Unknown message identity");};
 for(unsigned i=0;i<initial;++i){auto* p=newNode();message_list_detail::construct(*p,list,3,4);p->slot=int(i);p->gadgetFlags=0x12345778;p->dirty=2;p->field41=3;p->y=100+int(i);if(i){p->previous=nodes[i-1].get();nodes[i-1]->next=p;}else list.head=p;}
 for(unsigned i=0;i<3;++i)g.focused[i]=(initial&&(focus&(1u<<i)))?nodes[0].get():nullptr;
 std::vector<std::string> trace;
 auto allocationMutation=[&](){if(mutation&1){list.x=777;list.y=-888;list.width=333;list.maximumLines=17;list.reserved19=1;list.reserved1a=1;list.lineStep=23;g.mode=4;g.mode4Enabled=0;g.sound=12;g.clockStart=999;g.clockAccumulated=0xfffffff0;}if(mutation&8)g.selectedFont=nullptr;};
 MessageListServices services;services.allocate=[&](){auto* p=newNode();trace.push_back("A "+std::to_string(id(p)));allocationMutation();return p;};services.release=[&](MessageNode* p){trace.push_back("F "+std::to_string(id(p)));};services.milliseconds=[&](){trace.push_back("T");if(mutation&2){list.width=444;g.clockStart=7;g.clockAccumulated=777;g.mode=3;g.mode3Enabled=0;g.sound=19;list.y=234;list.lineStep=7;list.reserved19=1;list.reserved1a=1;}return milliseconds;};services.play=[&](int sound,std::uint32_t flags,float volume,std::uint32_t extra){require(sound==g.sound&&flags==8192&&volume==1.f&&!extra);trace.push_back("S");if(mutation&4){list.reserved19=3;list.reserved1a=4;list.y=-999;list.lineStep=45;}};
 auto ptext=decode(prefix=="~"?"-":prefix),btext=decode(body);std::u16string_view pv(ptext),bv(btext);MessageInsertRequest request{prefix=="~"?nullptr:&pv,0x81234567,bodyPresent?&bv:nullptr,-2,0x12345678,lifetime,std::uint8_t(silent)};
 std::vector<int> returns;for(unsigned i=0;i<repeats;++i)returns.push_back(id(insertMessage(list,g,services,request)));
 std::cout<<"R "<<returns.size();for(auto n:returns)std::cout<<' '<<n;std::cout<<" H "<<id(list.head)<<" U";for(auto n:list.available)std::cout<<' '<<n;
 Bytes pool;for(const auto& slot:list.text)for(auto c:slot){pool.push_back(std::uint8_t(c));pool.push_back(std::uint8_t(c>>8));}std::cout<<" B "<<assetSha256(Data(std::move(pool)))<<" G";for(auto* p:g.focused)std::cout<<' '<<id(p);
 std::cout<<" N "<<nodes.size();for(const auto& p:nodes){std::cout<<" O "<<id(p.get())<<' '<<id(p->next)<<' '<<id(p->previous)<<' '<<p->x<<' '<<p->y<<' '<<p->width<<' '<<p->height<<' '<<unsigned(p->dirty)<<' '<<unsigned(p->sticky)<<' '<<unsigned(p->field1e)<<' '<<unsigned(p->padding1f)<<' '<<p->gadgetFlags<<' '<<p->expires<<' '<<p->identifier<<' '<<p->flags<<' '<<p->slot<<' '<<p->color<<' '<<p->maximumWidth<<' '<<p->field3c<<' '<<unsigned(p->field40)<<' '<<unsigned(p->field41)<<' '<<p->padding42<<' '<<p->field44<<' '<<p->field48<<' '<<p->destroyed;}
 std::cout<<" L "<<list.x<<' '<<list.y<<' '<<list.width<<' '<<list.lineStep<<' '<<list.maximumLines<<' '<<unsigned(list.reserved19)<<' '<<unsigned(list.reserved1a)<<' '<<g.mode<<' '<<unsigned(g.mode3Enabled)<<' '<<unsigned(g.mode4Enabled)<<' '<<g.clockStart<<' '<<g.clockAccumulated<<' '<<g.sound<<' '<<bool(g.selectedFont);
 std::cout<<" E";for(const auto& event:trace)std::cout<<' '<<event;std::cout<<'\n';
}
void guards(){
 MessageList l;MessageListGlobals g;MessageListServices s;MessageInsertRequest r;require(!insertMessage(l,g,s,r));
 auto refuses=[&](auto call){bool refused=false;try{call();}catch(const std::invalid_argument&){refused=true;}require(refused);};
 refuses([&]{insertMessage(l,g,s,r,64);});
 std::array<std::uint16_t,65536> indices;indices.fill(1);MessageFontGlyphs glyph{indices,1,1,[](std::uint32_t){return std::uint8_t(5);}};MessageFontMetrics font{&glyph,nullptr,12,64,1};g.selectedFont=&font;
 std::u16string_view body=u"A";r.body=&body;unsigned allocations=0;s.allocate=[&]()->MessageNode*{++allocations;return nullptr;};
 l.width=8;require(!insertMessage(l,g,s,r)&&!allocations);
 l.width=160;refuses([&]{insertMessage(l,g,s,r);});require(allocations==1);
 std::u16string oversized(162,u'A');std::u16string_view prefix=oversized;r.prefix=&prefix;refuses([&]{insertMessage(l,g,s,r);});require(allocations==1);
 std::cout<<"message list guards PASS\n";
}
}
int main(int argc,char**argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
