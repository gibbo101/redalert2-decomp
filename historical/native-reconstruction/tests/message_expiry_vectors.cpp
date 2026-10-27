// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MessageExpiry.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
#include <memory>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Message expiry fixture outside domain");}
template<class T>T take(std::istream& s){T v{};require(bool(s>>v));return v;}
std::u16string decode(const std::string& s){std::u16string r;if(s=="-")return r;require(s.size()%4==0);for(std::size_t i=0;i<s.size();i+=4){auto a=std::stoul(s.substr(i,2),nullptr,16),b=std::stoul(s.substr(i+2,2),nullptr,16);r.push_back(char16_t(a|(b<<8)));}return r;}
struct Fixture {
 MessageList list;MessageListGlobals globals;MessageListServices services;
 std::vector<std::unique_ptr<MessageNode>> nodes;std::vector<std::uint32_t> times;std::size_t clock=0;unsigned mutation=0;bool updating=false;std::vector<std::string> events;
 int id(const MessageNode* p)const{if(!p)return 0;for(std::size_t i=0;i<nodes.size();++i)if(nodes[i].get()==p)return int(i+1);throw std::invalid_argument("Unknown expiry identity");}
 MessageNode* allocate(){auto p=std::make_unique<MessageNode>();p->padding1f=0xa5;p->padding42=0xa5a5;auto* out=p.get();nodes.push_back(std::move(p));return out;}
 Fixture(){
  for(auto& slot:list.text)slot.fill(char16_t(0xa5a5));list.available.fill(0x101);globals.sound=-7;
  services.allocate=[this]{auto* p=allocate();events.push_back("A "+std::to_string(id(p)));return p;};
  services.release=[this](MessageNode* p){events.push_back("F "+std::to_string(id(p)));if(updating&&(mutation&2)){globals.clockStart=0xffffffff;globals.clockAccumulated=101;list.y=-17;list.lineStep=2147483647;list.reserved19=2;list.reserved1a=3;if(nodes.size()>1)nodes[1]->expires=0;}if(updating&&(mutation&4)){MessageNode* last=nullptr;for(const auto& n:nodes)if(!n->destroyed)last=n.get();list.head=last;p->next=last;}};
  services.milliseconds=[this]{const auto value=times.at(clock++%times.size());events.push_back("T "+std::to_string(value));if(updating&&(mutation&1)){globals.clockStart=7;globals.clockAccumulated=777;if(!nodes.empty())nodes[0]->expires=0;if(nodes.size()>1)nodes[1]->expires=101;}return value;};
  services.play=[](int,std::uint32_t,float,std::uint32_t){throw std::invalid_argument("Unexpected expiry audio leaf");};
 }
 void snapshot(int result){
  std::cout<<"R "<<result<<" H "<<id(list.head)<<" U";for(auto v:list.available)std::cout<<' '<<v;
  Bytes b;for(const auto& slot:list.text)for(auto c:slot){b.push_back(std::uint8_t(c));b.push_back(std::uint8_t(c>>8));}std::cout<<" B "<<assetSha256(Data(std::move(b)))<<" G";for(auto* p:globals.focused)std::cout<<' '<<id(p);
  std::cout<<" N "<<nodes.size();for(const auto& p:nodes){std::cout<<" O "<<id(p.get())<<' '<<id(p->next)<<' '<<id(p->previous)<<' '<<p->x<<' '<<p->y<<' '<<p->width<<' '<<p->height<<' '<<unsigned(p->dirty)<<' '<<unsigned(p->sticky)<<' '<<unsigned(p->field1e)<<' '<<unsigned(p->padding1f)<<' '<<p->gadgetFlags<<' '<<p->expires<<' '<<p->identifier<<' '<<p->flags<<' '<<p->slot<<' '<<p->color<<' '<<p->maximumWidth<<' '<<p->field3c<<' '<<unsigned(p->field40)<<' '<<unsigned(p->field41)<<' '<<p->padding42<<' '<<p->field44<<' '<<p->field48<<' '<<p->destroyed;}
  std::cout<<" L "<<list.y<<' '<<list.lineStep<<' '<<unsigned(list.reserved19)<<' '<<unsigned(list.reserved1a)<<' '<<globals.clockStart<<' '<<globals.clockAccumulated<<' '<<clock<<" E";for(const auto& e:events)std::cout<<' '<<e;std::cout<<" END ";
 }
};
void run(std::istream& in){
 Fixture f;const auto n=take<unsigned>(in);require(n<=14);f.globals.clockStart=take<std::uint32_t>(in);f.globals.clockAccumulated=take<std::uint32_t>(in);f.list.y=take<int>(in);f.list.lineStep=take<int>(in);const auto a=take<unsigned>(in),b=take<unsigned>(in),focus=take<unsigned>(in);f.mutation=take<unsigned>(in);require(a<256&&b<256&&focus<=7&&f.mutation<=7);f.list.reserved19=std::uint8_t(a);f.list.reserved1a=std::uint8_t(b);f.list.width=120;f.list.x=-11;f.list.maximumLines=4;
 for(unsigned i=0;i<n;++i){const auto expiry=take<std::uint32_t>(in);const auto slot=take<int>(in);require(slot>=-1&&slot<14);auto* p=f.allocate();message_list_detail::construct(*p,f.list,3,4);p->expires=expiry;p->slot=slot;p->gadgetFlags=0x12345778;p->dirty=2;p->field41=3;p->y=100+int(i);if(slot>=0)f.list.available[unsigned(slot)]=0;if(i){p->previous=f.nodes[i-1].get();f.nodes[i-1]->next=p;}else f.list.head=p;}
 for(unsigned i=0;i<3;++i)f.globals.focused[i]=(n&&(focus&(1u<<i)))?f.nodes[0].get():nullptr;
 const auto nt=take<unsigned>(in);require(nt&&nt<=32);for(unsigned i=0;i<nt;++i)f.times.push_back(take<std::uint32_t>(in));const auto operations=take<unsigned>(in);require(operations&&operations<=32);
 std::array<std::uint16_t,65536> indices;indices.fill(1);MessageFontGlyphs glyph{indices,1,1,[](std::uint32_t p){require(p==1);return std::uint8_t(5);}};std::uint8_t fallback=7;MessageFontMetrics font{&glyph,&fallback,12,64,1};f.globals.selectedFont=&font;
 for(unsigned i=0;i<operations;++i){const auto op=take<char>(in);int result=0;if(op=='U'){f.updating=true;result=expireMessages(f.list,f.globals,f.services);f.updating=false;}else{require(op=='I');const auto duration=take<int>(in);auto raw=decode(take<std::string>(in));std::u16string_view body(raw);MessageInsertRequest request{nullptr,77,&body,-2,0x12345678,duration,1};result=f.id(insertMessage(f.list,f.globals,f.services,request));}f.snapshot(result);}
 std::string tail;require(!(in>>tail));std::cout<<'\n';
}
void guards(){MessageList l;MessageListGlobals g;MessageListServices s;require(!expireMessages(l,g,s));MessageNode n;n.expires=1;l.head=&n;bool refused=false;try{expireMessages(l,g,s);}catch(const std::invalid_argument&){refused=true;}require(!refused);g.clockStart=0;try{expireMessages(l,g,s);}catch(const std::invalid_argument&){refused=true;}require(refused);std::cout<<"message expiry guards PASS\n";}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
